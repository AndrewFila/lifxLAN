#include "lifxLAN.h"

#include <iostream>
#include <cstdint>
#include <cstdbool>
#include <cstdlib>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <math.h>
//MACROS
#define LIFX_PORT 56700


int main(){
    uint8_t target[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    //create message
    lifxLight L1;
    struct colmsg_t colMsg;
    struct pwrmsg_t pwrMsg;
    struct wfmsg_t  wfMsg;
    //create light object
    L1.encodeHeader(&pwrMsg.header, 42, 0, 1, 3, target, 0, 1, 1, 117);
    //L1.encodeHeader(&colMsg.header, 42, 0, 1, 3, target, 0, 1, 1, 117);
    L1.encodeHeader(&colMsg.header, 49, 0, 1, 3, target, 0, 1, 1, 102);
    L1.setPower(&pwrMsg.payload, 1, 0);
    //L1.setWaveform(&wfMsg.payload);
    //TODO

    struct sockaddr_in servaddr = {0};
    std::cout << "creating socket" << std::endl;
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        perror("socket creation failure");
        exit(EXIT_FAILURE);
    } else {
        std::cout << "socket created" << std::endl;
    }
    int broadcast = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0){
        perror("error in setting broadcast option");
        close(sockfd);
        exit(EXIT_FAILURE);
    } else {
        std::cout << "broadcast options set" << std::endl;
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_port  = htons(LIFX_PORT);
    servaddr.sin_addr.s_addr = INADDR_BROADCAST;
    for (int i = 0; i < sizeof(colMsg); i++){
        if((i % 8) == 0 && i != 0){
            std::cout << "\n";
        } else {
            printf("%02x ", ((char*)&colMsg)[i]);
        }
    }
    int len = sendto(sockfd, &pwrMsg, sizeof(pwrMsg), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    std::cout << "\n";
    float y = 0;
    float x = 0;
    while(1){
        //y = 120 * (sin(1./15. * x) +(.5 * sin(10 * x))) + 180;
        y = 90 * (pow(sin(x),101)) + 180;
        //y = (int)x % 360;
        L1.setColor(&colMsg.payload, (int) y, 1, 1, 0, 0);
        len = sendto(sockfd, &colMsg, sizeof(colMsg), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        if (len == -1){
            perror("failed to send");
        }else {
            //std::cout << "message sent to lights size: " << len << std::endl;
        }
        x = x + .0001;
        //std::cout << "f(" << i;
        //std::cout << ") = " << y << std::endl;
        usleep(1000000/40);
    }
    return 1;
}
