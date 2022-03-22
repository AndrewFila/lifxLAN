#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>



#define LIFX_PORT 56700

uint16_t toLittleEndian16(int value){
    uint16_t swapped = (value >> 8) | (value << 8);
    return swapped;
}
uint32_t toLittleEndian32(uint32_t value){
    uint32_t swapped = ((value >> 24) & 0x000000FF) |
                       ((value << 8)  & 0x00FF0000) |
                       ((value >> 8)  & 0x0000FF00) |
                       ((value << 24) & 0xFF000000);
    return swapped;
}
void sendMessage(struct message_setcolor_t * message){

    printf("%lu\n", sizeof(message));
    struct sockaddr_in servaddr = {0};
    //create socket
    int sockfd  = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1){
        perror("failed to create socket");
        exit(EXIT_FAILURE);
    }
    //set broadcast options
    int broadcast = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0){
        perror("failed to create socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(LIFX_PORT);
    servaddr.sin_addr.s_addr = INADDR_BROADCAST;

    int len = sendto(sockfd, message, sizeof(message), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    if (len < 0){
        perror("failed to send");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("%d\n", len);
}
