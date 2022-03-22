#include "message.h"
#include "setters.h"
#include "util.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <math.h>

#include <time.h>

#define LIFX_PORT 56700



void main(){
    //create message and set target and color
    //uint8_t target1[] = {0xD0, 0x73, 0xD5, 0x3E, 0x4D, 0x47, 0x00, 0x00};
    uint8_t target1[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    struct message_setcolor_t message1;
    encodeHeader(&message1.header, 49, 0, 1, 2, target1, 0, 1, 1, 102);
    //sendMessage(&message1);
    // socket stuff
    struct sockaddr_in servaddr = {0};

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1){
        perror("failded to create socket");
        exit(EXIT_FAILURE);
    }
    int broadcast = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        perror("error in setting broadcast option");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(LIFX_PORT);
    servaddr.sin_addr.s_addr = INADDR_BROADCAST;
    float x = 0;
    float y = (sin(5 * x) * .5 )+ .5;
    while (true){
        printf("%f\n", y);
        setColor(&message1, y * 360, 1,(int) (y * 65535), 0, 0);
        int len1 = sendto(sockfd, &message1, sizeof(message1), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        if (len1 == -1){
            perror("failed to send");
        }
        x = x + .01;
        y = (sin(5 * x) * .5)+ .5;
        usleep(1000000/18);
    }
    close(sockfd);
}
