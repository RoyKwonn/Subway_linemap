//
//  main.c
//  Navigator
//
//  Created by Seokhwan Kwon on 2020/12/20.
//  20184646 권석환

#include <stdio.h>
#include "heap.h"
#include "Dijkstra.h"
#include "TCP_Server.h"


int main(int argc, char *argv[])
{
    int servSock;                           // Socket descriptor for server
    int clntSock;                           // Socket descriptor for client
    struct sockaddr_in echoServAddr;        // Local address
    struct sockaddr_in echoClntAddr;        // Client address
    unsigned short echoServPort;            // Server port
    unsigned int clntLen;                   // Length of client address data structure

    if(argc != 2)                           // Test for correct number of arguments
    {
        fprintf(stderr, "Usage: %s <Server Port> \n", argv[0]);
    }

    // echoServPort = atoi(argv[1]);           // First arg: local port
    echoServPort = 8000;           // First arg: local port

    // Create socket for incoming connections

    if((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");


    // Construct local address structure

    memset(&echoServAddr, 0, sizeof(echoServAddr));         // Zero out structure
    echoServAddr.sin_family = AF_INET;                      // Internet address family
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);       // Any incoming interface
    echoServAddr.sin_port = htons(echoServPort);            // Local port


    // Bind to the local address

    if(bind(servSock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");


    // Mark the socket so it will listen for incoming connections

    if(listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");

    for(;;)         // Run forever
    {
        // Set the size of the in-out parameter

        clntLen = sizeof(echoClntAddr);


        // Wait for a client to connect

        if((clntSock = accept(servSock, (struct sockaddr *)&echoClntAddr, &clntLen)) < 0)
            DieWithError("accpet() failed");


        // clntSock is connected to a client!
        printf("\n-------------------------------------------------------\n");
        printf("[ Handling client %s ] \n", inet_ntoa(echoClntAddr.sin_addr));
        HandleTCPClient(clntSock);
    }

    // NOT REACHED

    return 0;
}
