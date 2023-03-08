#!/bin/bash

gcc -o server ../includes/server.c

./server

mv server ../bin
