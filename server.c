#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#define PORT 6500
#define VEHICLE_ID "CAR_1"   //similarly CAR_2 for second Pi
typedef struct {
    char vehicle_id[16];
    int ir;
    float distance;
    char status[16];
    long timestamp;
} vehicle_data_t;
// -------- SENSOR SIMULATION --------
int read_ir() {
    FILE *fp;
    char buffer[128];
    fp = popen("on -u 0 gpio-bcm2711 get 17", "r");
    if (!fp) return 0;
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        pclose(fp);
        return 0;
    }
      pclose(fp);
    return strstr(buffer, "level=0") ? 1 : 0;
}
float read_ultrasonic() {
    return 10 + rand() % 90;
}
const char* get_status(float d) {
    if (d < 20) return "TOO CLOSE";
    else if (d < 50) return "CAUTION";
    else return "CLEAR";
}
// -------- CLIENT THREAD --------
void* handle_client(void* arg) {
    int client_fd = *(int*)arg;
    free(arg);
    while (1) {
        vehicle_data_t data;
        data.ir = read_ir();
        data.distance = read_ultrasonic();
        strcpy(data.vehicle_id, VEHICLE_ID);
        strcpy(data.status, get_status(data.distance));
        data.timestamp = time(NULL);
        int n = send(client_fd, &data, sizeof(data), 0);

        if (n <= 0) {
            printf("Client disconnected\n");
            break;
        }

        usleep(500000);
    }
    close(client_fd);
    return NULL;
}
// -------- MAIN --------
int main() {
    srand(time(NULL));
    int server_fd;
    struct sockaddr_in addr;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);
    printf("Server %s running...\n", VEHICLE_ID);
    while (1) {
        int *client_fd = malloc(sizeof(int));
        *client_fd = accept(server_fd, NULL, NULL);
        if (*client_fd < 0) continue;
        printf("Client connected\n");
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, client_fd);
        pthread_detach(tid);  // auto cleanup
    }
    return 0;
}
