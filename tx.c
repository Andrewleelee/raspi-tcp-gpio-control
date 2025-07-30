#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gpiod.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define CHIPNAME "/dev/gpiochip0"
#define BUTTON_LINE 27   // BCM22 → 按鈕 → GND
#define PORT 7000

// 三個狀態字串
const char *states[] = {"100", "010", "001"};

int main() {
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int state_index = 0;

    // ====== 開啟 GPIO ======
    chip = gpiod_chip_open(CHIPNAME);
    if (!chip) {
        perror("無法開啟 GPIO 晶片");
        return 1;
    }

    line = gpiod_chip_get_line(chip, BUTTON_LINE);
    if (!line) {
        perror("無法取得 GPIO 腳位");
        gpiod_chip_close(chip);
        return 1;
    }

    // 設為輸入 + 上拉電阻
    if (gpiod_line_request_input_flags(line, "button",
        GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP) < 0) {
        perror("無法設定 GPIO 輸入模式");
        gpiod_chip_close(chip);
        return 1;
    }

    // ====== 建立 TCP Server ======
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket 建立失敗");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind 失敗");
        return 1;
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen 失敗");
        return 1;
    }

    printf("[TX] 等待 Client 端連線...\n");
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
    if (client_fd < 0) {
        perror("accept 失敗");
        return 1;
    }
    printf("[TX] 已連線到 Client: %s\n", inet_ntoa(client_addr.sin_addr));

    // ====== 主迴圈 ======
    int last_value = 1; // 因為 PULL-UP 預設是 1
    while (1) {
        int current_value = gpiod_line_get_value(line);
        if (current_value < 0) {
            perror("讀取 GPIO 失敗");
            break;
        }

        // 偵測按鈕「剛剛被按下」(1 -> 0)
        if (last_value == 1 && current_value == 0) {
            const char *msg = states[state_index];
            send(client_fd, msg, strlen(msg), 0);
            printf("[TX] 發送: %s\n", msg);

            // 循環下一個狀態
            state_index = (state_index + 1) % 3;

            // 去抖動 & 等待放開
            usleep(300000); // 300ms
            while (gpiod_line_get_value(line) == 0) {
                usleep(10000); // 等待按鈕放開
            }
        }

        last_value = current_value;
        usleep(5000); // 減少 CPU 占用
    }

    // ====== 清理 ======
    gpiod_line_release(line);
    gpiod_chip_close(chip);
    close(client_fd);
    close(server_fd);
    return 0;
}
