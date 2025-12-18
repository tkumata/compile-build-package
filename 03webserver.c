#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *http_response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain; charset=UTF-8\r\n"
        "Content-Length: 25\r\n"
        "Connection: close\r\n"
        "\r\n"
        "Hello from C Web Server!\n";

    // 1. ソケットの作成 (Socket creation)
    // AF_INET: IPv4, SOCK_STREAM: TCP
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. ポートの再利用設定 (Optional: Helps avoid "Address already in use" errors)
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 3. アドレスとポートの紐付け (Binding)
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // 全てのネットワークインターフェースで待ち受け
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 4. 接続待ち状態にする (Listening)
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("サーバーが起動しました。 http://localhost:%d で待機中です...\n", PORT);
    printf("停止するには Ctrl+C を押してください。\n");

    while(1) {
        // 5. 接続を受け付ける (Accepting)
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        // 6. ブラウザからのリクエストを読み込む (Reading - 実際には中身を見ずに読み飛ばす)
        read(new_socket, buffer, BUFFER_SIZE);
        // printf("%s\n", buffer); // デバッグ用: リクエスト内容を表示

        // 7. HTTP レスポンスを返す (Sending)
        write(new_socket, http_response, strlen(http_response));
        
        // 8. 接続を閉じる (Closing)
        close(new_socket);
    }

    return 0;
}
