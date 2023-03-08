#!/bin/bash

gcc -o client ../includes/client.c

./client

mv client ../bin
