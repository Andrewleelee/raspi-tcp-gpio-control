#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // for open(), O_WRONLY, etc.

const char *host = "192.168.0.197"; // Raspberry Pi 4 (TCP Server) IP
int port = 7000;                    // TCP Server port

int main()
{
    int sock_fd;
    struct sockaddr_in serv_name;
    int status;
    char indata[1024] = {0};

    // Create socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1)
    {
        perror("Socket creation error");
        exit(1);
    }

    // Set server address
    serv_name.sin_family = AF_INET;
    inet_aton(host, &serv_name.sin_addr); // A's IP address
    serv_name.sin_port = htons(port);

    // Connect to the server (A)
    status = connect(sock_fd, (struct sockaddr *)&serv_name, sizeof(serv_name));
    if (status == -1)
    {
        perror("Connection error");
        exit(1);
    }

    // Convert socket to file stream for fgets
    FILE *sock_stream = fdopen(sock_fd, "r");
    if (sock_stream == NULL)
    {
        perror("fdopen error");
        close(sock_fd);
        exit(1);
    }
    // 打開設備文件 /dev/gpio_device
    int fd = open("/dev/GPIO_device", O_WRONLY); // 以寫模式打開設備
    if (fd == -1)
    {
        perror("Failed to open device file");
        return 1;
    }

    while (1)
    {
        ssize_t recv_size = recv(sock_fd, indata, sizeof(indata) - 1, 0);
        if (recv_size <= 0)
        { // recv() 返回 0 代表 Server 關閉，-1 代表錯誤
            printf("Server closed connection or error receiving data.\n");
            break;
        }
        indata[recv_size] = '\0'; // 確保字串結尾
        printf("recv: %s\n", indata);

        write(fd, indata, 3);

        
    }
    close(fd);
    fclose(sock_stream);
    close(sock_fd);
    return 0;
}
