#include "server.h"

/* 
 	Creating socket file descriptor
 	function: socketfd(domain, type, protocol)
 	sockfd: socket descriptor, an integer
 	domain: integer, specifies comunication domain. We use AF_ LOCAL as defined in the POSIX standard for 
 			communication between processes on the same host. For communicating between processes on different hosts connected by IPV4, 
 			we use AF_INET and AF_I NET 6 for processes connected by IPV6.
 	type: communication type, SOCK_STREAM: TCP(reliable, connection oriented), SOCK_DGRAM: UDP(unreliable, connectionless)
 	protocol: Protocol value for Internet Protocol(IP), which is 0. This is the same number which appears on protocol field in the IP header of a packet.
*/
int createSocket(Server *server)
{
    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server->server_fd < 0){
		printk("Dosent create Socket... \n");
		perror("socket failed");
 		exit(EXIT_FAILURE);
		return 0;
	}
	else{
		printk("Created Socket... \n");
		return 1;
	}
}

/* 	Forcefully attaching socket to the port 8080
 	Function: int bind(int sockfd, const struct sockaddr*addr, socklen_t addrlen)

 	After the creation of the socket, the bind function binds the socket to the address and port number specified in addr(custom data structure).
 	In the example code, we bind the server to the localhost, hence we use INADDR_ANY to specify the IP address.
*/

int bindSocket(Server *server){
	if (bind(server->server_fd, (struct sockaddr*)&server->address,sizeof(server->address))< 0) {
		printk("Dosent bind... \n");
 		perror("bind failed");
 		exit(EXIT_FAILURE);
		return 0;
 	}
	else{
		printk("Binding socket successfuly... \n");
		return 1;
	}
}

/* 	Function: int listen(int sockfd, int backlog)

 	It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection. 
 	The backlog, defines the maximum length to which the queue of pending connections for sockfd may grow. 
 	If a connection request arrives when the queue is full, the client may receive an error with an indication of ECONNREFUSED.
*/

void startListening(Server *server){
	if (listen(server->server_fd, 3) < 0) {
		printk("Dosent listen... \n");
 		perror("listen");
 		exit(EXIT_FAILURE);
 	}
	else{
		printk("Server is listening... \n");
	}
}

 	
/* 	Function: int new_socket= accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

 	It extracts the first connection request on the queue of pending connections for the listening socket,
 	sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket. 
 	At this point, the connection is established between client and server, and they are ready to transfer data.
*/ 	

int acceptConnection(Server *server){
	printk("Waiting for client... \n");
	if ((server->new_socket = accept(server->server_fd,(struct sockaddr*)&server->address,(socklen_t*)&server->addrlen))< 0) {	
		printk("Dosent accept... \n");
 		perror("accept");
 		exit(EXIT_FAILURE);
		return 0;
 	}
	else{
		printk("Client connected... \n");
		return 1;
	}
}

 
void handleMessages(Server *server){
	while (1)
 	{ 		
		server->valread = read(server->new_socket, server->buffer, 1024);
 		printf("%s\n", server->buffer);
		char test[] = "Det funkar";
 		send(server->new_socket, test, strlen(test), 0);
 		printf("Hello message sent\n");
 	}
}

/* 	Forcefully attaching socket to the port 8080
 	This helps in manipulating options for the socket referred by the file descriptor sockfd. 
 	This is completely optional, but it helps in reuse of address and port. Prevents error such as: “address already in use”.
*/
void initiateSocket(Server *server){
	if (setsockopt(server->server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEADDR, &server->opt,sizeof(server->opt))) {
		printk("Dosent initiate socket... \n");
 		perror("setsockopt");
 		exit(EXIT_FAILURE);
 	}
	else{
		printk("Initiated Socket Successfully... \n");
		server->address.sin_family = AF_INET;
		server->address.sin_addr.s_addr = INADDR_ANY;
		server->address.sin_port = htons(8080);
	}

}

/*Creating a socket connection*/
int startWebsocket(Server *server)
{	
	if(!createSocket(server))
		return 0;
	
	initiateSocket(server);
	
	if(!bindSocket(server))
		return 0;
	
	startListening(server);

	if(!acceptConnection(server))
		return 0;

	return 1;
}
