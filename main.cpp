#include "lifxLAN.h"
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




int main(){
    //create message and set target and color
    //uint8_t target1[] = {0xD0, 0x73, 0xD5, 0x3E, 0x4D, 0x47, 0x00, 0x00};
    uint8_t target1[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    msg_setcol_t message1;
    encodeHeader(&message1.header, 49, 0, 1, 2, target1, 0, 1, 1, 102);

    msg_setpwr_t power;
    encodeHeader(&power.header, 38, 0, 1, 3, target1, 0, 1, 1, 21);
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
    srand(time(NULL));
    setPower(&power, 1);
    int i = 0;
    while (true){
        setColor(&message1, i, .8, .5, 0, 0);
        int len2 = sendto(sockfd, &message1, sizeof(message1), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        if (len2 == -1){
            perror("failed to send");
        }
        usleep(1000000/20);
        i = (i + 1) % 360;
    }
    close(sockfd);
    return 1;
}
