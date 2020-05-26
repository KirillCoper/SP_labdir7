#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <fstream>
#include <iostream>
#include <winsock2.h>
#include <string>
#include <windows.h>


using namespace std;

int main()
{
    WSADATA WSAData;

    SOCKET server, client;

    SOCKADDR_IN serverAddr, clientAddr;

    WSAStartup(MAKEWORD(2, 0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(25566);

    bind(server, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    listen(server, 0);

    cout << "Listening for incoming connections..." << endl;
    char buffer[1024];
    int clientAddrSize = sizeof(clientAddr);
        if ((client = accept(server, (SOCKADDR*)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
        {
            cout << "Client connected!" << endl;
            while (true) {
                strcpy(buffer, "Vvedite slovo ili fragment");
                send(client, buffer, strlen(buffer) + 1, 0);
                recv(client, buffer, sizeof(buffer), 0);
                cout << "Client says: " << buffer << endl;

                string s;
                int ch = 0;
                string str = string(buffer);
                memset(buffer, 0, sizeof(buffer));

                ifstream file("D:\\kirill_coper\\SP\\Lab7\\TEXT.txt");
                while (getline(file, s))
                {
                    ch++;
                }
                file.close();

                cout << "Dlina texta " << ch << " strok" << endl;
                sprintf(buffer, "%d", ch);
                send(client, buffer, sizeof(buffer), 0);
                Sleep(1000);

                ifstream file1("D:\\kirill_coper\\SP\\Lab7\\TEXT.txt");
                while (getline(file1, s))
                {
                    cout << s << endl;
                    if (s.find(str) < 1000)
                    {
                        strcpy(buffer, "Naideno");
                        send(client, buffer, strlen(buffer) + 1, 0);
                        cout << "Naideno v pozicii " << s.find(str) << endl;
                        Sleep(1000);
                    }
                    else
                    {
                        strcpy(buffer, "Ne naideno");
                        send(client, buffer, strlen(buffer) + 1, 0);
                        cout << "Ne naideno" << endl;
                        Sleep(1000);
                    }

                }
                file1.close();
                cout << "Konec svyazi " << endl;
                Sleep(1000);
            }
            
        }
    
    closesocket(client);
    cout << "Client disconnected." << endl;
}