//
//  HandleTCPClient.c
//  Navigator
//
//  Created by Seokhwan Kwon on 2020/12/20.
//  20184646 권석환

#include "TCP_Server.h"
#include "heap.h"
#include "Dijkstra.h"

#include <stdio.h>                          // for printf() and fprintf()
#include <sys/socket.h>                     // for recv() and send()
#include <unistd.h>                         // for close()
#include <string.h>                         // for str___()
#include <stdlib.h>                         // for itoa()

#define RCVBUFSIZE 32                       // Size of receive buffer
#define CHAR_MAX 128

void DieWithError(char *errorMessage);      // Error handling function

typedef char  Station_Type;


void HandleTCPClient(int clntSocket)
{
    int start, end;
    GraphType g = { 7,
            {   //  0    1    2    3    4    5    6
                {   0,   7, INF, INF,   3,  10, INF },  // 0
                {   7,   0,   4,  10,   2,   6, INF },  // 1
                { INF,   4,   0,   2, INF, INF, INF },  // 2
                { INF,  10,   2,   0,  11,   9,   4 },  // 3
                {   3,   2, INF,  11,   0, INF,   5 },  // 4
                {  10,   6, INF,   9, INF,   0, INF },  // 5
                { INF, INF, INF,   4,   5, INF,   0 }   // 6
            }
        };
    
    HeapElem u;
    char stringTemp[RCVBUFSIZE];            // 반환값
    char echoBuffer[RCVBUFSIZE];            // Buffer for echo string
    int recvMsgSize;                        // Size of received message
    
    
    Station_Type station[7][40];
    
    strcpy(station[0], "서울");
    strcpy(station[1], "용산");
    strcpy(station[2], "청량리");
    strcpy(station[3], "부산");
    strcpy(station[4], "대구");
    strcpy(station[5], "대전");
    strcpy(station[6], "전주");
    // Receive message from client
    
    if((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");
    
    
    char *s1 = malloc(sizeof(echoBuffer));
    strcpy(s1, echoBuffer);
    char *ptr = strtok(s1, "/");
    
    for(int i = 0; i < 7; i++)
    {
        if(strcmp(ptr, station[i]) == 0)
            start = i;
    }
    // start = atoi(ptr);
    
    while(ptr != NULL)
    {
        for(int i = 0; i < 7; i++)
        {
            if(strcmp(ptr, station[i]) == 0)
                end = i;
        }
        //end = atoi(ptr);
        ptr = strtok(NULL, "/");
    }
    
    
    free(s1);
    
    printf("요청 : %d <- %d \n", end, start);
    u = PQueue_Dijkstra(&g, start, end);
    
    // 서버 로그 기록용
    printf("최소경로 : ");
    for(int i = 0; i < u.route.count; i++)
        printf("%d <- ", u.route.edge[i]);
    printf("%d\n", start);
    printf("거리 : %2d\n", u.weight);
    
    // 전달용
    strcpy(echoBuffer, "");
    for(int i = 0; i < u.route.count; i++)
    {
        //sprintf(stringTemp, "%d", u.route.edge[i]);
        //strcat(echoBuffer, stringTemp);
        strcat(echoBuffer, station[u.route.edge[i]]);
        strcat(echoBuffer, "<-");
    }
    //sprintf(stringTemp, "%d", start);
    //strcat(echoBuffer, stringTemp);
    strcat(echoBuffer, station[start]);
    strcat(echoBuffer, "/");
    sprintf(stringTemp, "%d", u.weight);
    strcat(echoBuffer, stringTemp);
    
    
    // Send received string and receive again util end of transmission
    
    while(recvMsgSize > 0)                  // Zero indicates end of transmission
    {
        // Echo message back to client
        
        //if(send(clntSocket, echoBuffer, strlen(echoBuffer), 0) != recvMsgSize)
        //    DieWithError("send() failed");
        send(clntSocket, echoBuffer, strlen(echoBuffer), 0);
        
        // See if there is more data to receive
        
        if((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed");
    }
    
    close(clntSocket);                      // Close client socket
}

