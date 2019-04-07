//
//  main.c
//  testServ
//
//  Created by MacBook on 07/04/2019.
//  Copyright © 2019 MacBook. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "additionalFuncs.h"

#define PORT 7890

int main(int argc, const char * argv[]) {
    int sockfd, new_sockfd;
    struct sockaddr_in host_addr, client_addr;
    socklen_t sin_size;
    int recv_lenght=1, yes=1;
    char buffer[1024];
    
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        printf("%s","socket errrr");
    
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        printf("%s","with SO_REUSEADDR param errrr");
    
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = 0;
    memset(&(host_addr.sin_zero), '\0', 8);
    
    if (bind(sockfd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1)
        printf("%s","connection with socket errrr");
    
    if (listen(sockfd, 5) == -1)
        printf("%s","listen from socket errrr");
    
    while (1) {
        sin_size = sizeof(struct sockaddr_in);
        new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
        if (new_sockfd == -1)
            printf("%s","accept a connection errrr");
        printf("server: received a connection %s port %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        send(new_sockfd, "TY PIDOR!!!\n", 13, 0);
        recv_lenght = recv(new_sockfd, &buffer, 1024, 0);
        while(recv_lenght > 0) {
            printf("RECV: %d bytes\n", recv_lenght);
            dump(buffer, recv_lenght);
            recv_lenght = recv(new_sockfd, &buffer, 1024, 0);
        }
        close(new_sockfd);
    }
    
    return 0;
}
