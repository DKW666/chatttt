#ifndef SERVER_H
#define SERVER_H

#include <list>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <iostream>
#include <errno.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"    //"82.157.34.252"
#define SERVER_PORT 9527
#define EPOLL_SIZE 5000
#define BUF_SIZE 0x0FFF
#define BACKLOG SOMAXCONN
#define SERVER_MESSAGE "%s%d : %s"

using namespace std;

#endif
