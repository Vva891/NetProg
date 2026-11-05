#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // 1. Создаем UDP-сокет
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    // 2. Настройка адреса (Локальный адрес для проверки дома)
    sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(13); // Тестовый порт
    server_addr.sin_addr.s_addr = inet_addr("172.16.40.1"); // Локальный IP 

    // 3. Отправляем пустой пакет-запрос
    if (sendto(sock, "", 0, 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Ошибка отправки запроса" << std::endl;
        close(sock);
        return 1;
    }

    // 4. Создаем массив (буфер) для приема текстового ответа
    char buffer[512];

    // 5. Ждем и принимаем ответ от сервера
    socklen_t addr_len = sizeof(server_addr);
    ssize_t bytes_received = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, 
                                      (struct sockaddr*)&server_addr, &addr_len);
    if (bytes_received < 0) {
        std::cerr << "Ошибка получения данных" << std::endl;
        close(sock);
        return 1;
    }

    // 6. Корректно закрываем строку нулевым символом и выводим на экран
    buffer[bytes_received] = '\0';
    std::cout << "Время от сервера:\n" << buffer << std::endl;

    // 7. Закрываем сокет
    close(sock);
    return 0;
}
