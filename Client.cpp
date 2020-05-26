#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <string>

using namespace std;

int main()
{
    char str[20];
    string s;
    char buffer[1024];
    string buffer_str;
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2, 0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(25566);

    connect(server, (SOCKADDR*)&addr, sizeof(addr));
    cout << "Connected to server!" << endl;

    while (true) {

        recv(server, buffer, sizeof(buffer), 0);
        cout << buffer << endl;
        memset(buffer, 0, sizeof(buffer));

        cin >> buffer;
        send(server, buffer, sizeof(buffer), 0);
        cout << "Message sent!" << endl;
        memset(buffer, 0, sizeof(buffer));

        recv(server, buffer, sizeof(buffer), 0);
        cout << "Dlina texta " << buffer << " strok" << endl;
        int ch = atoi(buffer);
        memset(buffer, 0, sizeof(buffer));

        for (int i = 0; i < ch; i++) {
            recv(server, buffer, sizeof(buffer), 0);
            s = string(buffer);
            cout << s << " V stroke " << i + 1 << endl;
            memset(buffer, 0, sizeof(buffer));
        }
        cout << "Konec svyazi " << endl;
        Sleep(1000);
    }
    closesocket(server);
    WSACleanup();
    cout << "Socket closed." << endl << endl;
}