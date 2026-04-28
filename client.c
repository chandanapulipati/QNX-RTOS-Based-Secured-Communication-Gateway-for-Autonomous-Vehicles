#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <math.h>
#define PORT 6500
typedef struct {
    char vehicle_id[16];
    int ir;
    float distance;
    char status[16];
    long timestamp;
} vehicle_data_t;
int recv_full(int sock, void *buffer, size_t size) {
    size_t total = 0;
    int n;
    while (total < size) {
        n = recv(sock, (char*)buffer + total, size - total, 0);
        if (n <= 0)
            return -1;
        total += n;
    }
    return total;
}
// -------- COLLISION --------
const char* collision_warning(float d1, float d2) {
   float diff = fabs(d1 - d2);
    if (diff < 10)
        return "🟧COLLISION IMMINENT";
    else if (diff < 30)
        return "🟥HIGH RISK";
    else
        return "🟩SAFE";
}
int connect_to_server(char *ip) {
    int sock;
    struct sockaddr_in server;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, ip, &server.sin_addr);
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("connect failed");
        exit(1);
    }
    printf("Connected to %s\n", ip);
    return sock;
}
// -------- MAIN --------
int main() {
    int sock1 = connect_to_server("10.0.0.1"); // CAR_1 RPI
    int sock2 = connect_to_server("10.0.0.2"); // CAR_2 RPI
    vehicle_data_t car1 = {0}, car2 = {0};
    fd_set readfds;
    struct timeval timeout;
    int maxfd = (sock1 > sock2 ? sock1 : sock2) + 1;
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(sock1, &readfds);
        FD_SET(sock2, &readfds);
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;
        int activity = select(maxfd, &readfds, NULL, NULL, &timeout);
        if (activity <= 0) continue;
        if (FD_ISSET(sock1, &readfds)) {
            if (recv_full(sock1, &car1, sizeof(car1)) < 0) break;
        }
        if (FD_ISSET(sock2, &readfds)) {
            if (recv_full(sock2, &car2, sizeof(car2)) < 0) break;
        }
        printf("\033[2J\033[H");
        printf(" CAR 1 (%s)\n", car1.vehicle_id); 
        printf("IR        : %s\n", car1.ir ? "OBSTACLE" : "CLEAR");
        printf("Distance  : %.2f cm\n", car1.distance);
        printf("Status    : %s\n\n", car1.status);
        printf("CAR 2 (%s)\n", car2.vehicle_id); 
        printf("IR        : %s\n", car2.ir ? "OBSTACLE" : "CLEAR");
        printf("Distance  : %.2f cm\n", car2.distance);
        printf("Status    : %s\n\n", car2.status);
        printf("=====================================\n");
        printf("⚡ COLLISION ANALYSIS\n");
        printf(" %s\n", collision_warning(car1.distance, car2.distance));
        printf("=====================================\n");
        usleep(300000);
    }
    close(sock1);
    close(sock2);
    return 0;
}
