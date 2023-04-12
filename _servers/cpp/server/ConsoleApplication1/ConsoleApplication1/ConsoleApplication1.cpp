#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <winsock2.h>
#include <iomanip>  // for std::setw

#pragma comment(lib, "ws2_32.lib")

const int PORT = 9081;
const int BACKLOG = 5;

void process_request(SOCKET client_socket);

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_size = sizeof(client_addr);

    // Winsock 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Failed to initialize Winsock\n";
        return 1;
    }

    // 소켓 생성
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 소켓에 주소 바인딩
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind to address\n";
        closesocket(server_socket);
        return 1;
    }

    // 클라이언트의 연결 요청 대기
    if (listen(server_socket, BACKLOG) == SOCKET_ERROR) {
        std::cerr << "Failed to listen on socket\n";
        closesocket(server_socket);
        return 1;
    }

    std::cout << "cpp Version : " << __cplusplus << std::endl;
    std::cout << "Server started\n";


    while (true) {
        // 클라이언트 소켓 생성
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "Failed to accept client connection\n";
            continue;
        }

        // 클라이언트 요청 처리
        process_request(client_socket);

        // 클라이언트 소켓 닫기
        closesocket(client_socket);
    }

    // 서버 소켓 닫기
    closesocket(server_socket);

    // Winsock 종료
    WSACleanup();

    return 0;
}

void process_request(SOCKET client_socket) {
    char buffer[1024] = { 0 };
    std::stringstream response;

    // 클라이언트 요청 읽기
    recv(client_socket, buffer, 1024, 0);

    // 요청 메시지 출력
    std::cout<< "Received request:\n" << buffer << std::endl;
    time_t now1 = time(0);
    struct tm time_info;
    localtime_s(&time_info, &now1);

    char buffer2[80];
    strftime(buffer2, 80, "%Y-%m-%d %H:%M:%S", &time_info);
    std::cout << buffer2 << "." << std::setfill('0') << std::setw(3) << (int)GetTickCount64() % 1000 << std::endl;





    // 현재 시간 정보 얻기
    time_t now = time(0);
    struct tm time_info2;
    localtime_s(&time_info2, &now);

    // 응답에 포함할 현재 시간 문자열 생성
    char time_str[80];
    strftime(time_str, 80, "%Y-%m-%d %H:%M:%S", &time_info2);

    // 응답 메시지 작성
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Type: text/plain\r\n";
    response << "\r\n";
    response << time_str << "." << std::setw(2) << std::setfill('0') << (int)GetTickCount64() % 1000 << "\n";


    // 응답 보내기
    send(client_socket, response.str().c_str(), response.str().length(), 0);
}
