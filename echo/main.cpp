#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h> // Сокеты
#include <netinet/in.h> // Интернет-адреса
#include <arpa/inet.h>   // Преобразование IP
#include <unistd.h>     // Функция close()

int main() {
    //  Создаем TCP-сокет (SOCK_STREAM)
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    //  Настраиваем адрес сервера кафедры (Порт 7 — служба Echo)
    sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7); // Порт 7 закреплен за Echo
    server_addr.sin_addr.s_addr = inet_addr("172.16.40.1"); // IP кафедры

    // Устанавливаем постоянное TCP-соединение с сервером
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Ошибка подключения к серверу кафедры" << std::endl;
        close(sock);
        return 1;
    }
    std::cout << "Успешно подключено к серверу Echo!" << std::endl;

    //  Вводим строку с клавиатуры
    std::string message;
    std::cout << "Введите текст для отправки: ";
    std::getline(std::cin, message);

    //  Отправляем строку в созданный TCP-канал
    if (send(sock, message.c_str(), message.length(), 0) < 0) {
        std::cerr << "Ошибка отправки данных" << std::endl;
        close(sock);
        return 1;
    }

    // Выделяем массив под ответ и принимаем эхо от сервера
    char buffer[512];
    ssize_t bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0) {
        std::cerr << "Ошибка получения ответа" << std::endl;
        close(sock);
        return 1;
    }

    //  Ограничиваем строку нулевым символом и выводим на экран
    buffer[bytes_received] = '\0';
    std::cout << "Ответ от сервера: " << buffer << std::endl;

    // Закрытие TCP-сессии
    close(sock);
    return 0;
}
