//
//  TCP_Server.h
//  Navigator
//
//  Created by Seokhwan Kwon on 2020/12/20.
//  20184646 권석환

#ifndef TCP_Server_h
#define TCP_Server_h

#include <stdio.h>                          // for printf() and fprintf()
#include <sys/socket.h>                     // for socket(), bind(), and connect()
#include <arpa/inet.h>                      // for sockaddr_in and inet_ntoa()
#include <stdlib.h>                         // for atoi() and exit()
#include <string.h>                         // for memset()
#include <unistd.h>                         // for close()

#define MAXPENDING 5                        // Maximum outstanding connection requests

void DieWithError(char *errorMessage);      // Error handling function
void HandleTCPClient(int clntSocket);       // TCP client handling function


#endif /* TCP_Server_h */
