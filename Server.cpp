#include <iostream>

SOCKET Connections[20];
int Counter = 0;

enum Packet {
    P_ChatMessage,
    P_Test
};

bool ProcessPacket(int index, Packet packettype) {
    switch (packettype) {
    case P_ChatMessage:
    {
        int msg_size;
        recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
        char* msg = new char[msg_size + 1];
        msg[msg_size] = '\0';
        recv(Connections[index], msg, msg_size, NULL);
        for (int i = 0; i < Counter; i++) {
            if (i == index) {
                continue;
            }

            Packet msgtype = P_ChatMessage;
            send(Connections[i], (char*)&msgtype, sizeof(Packet), NULL);
            send(Connections[i], (char*)&msg_size, sizeof(int), NULL);
            send(Connections[i], msg, msg_size, NULL);
        }
        delete[] msg;
        break;
    }
    default:
        std::cout << "Unrecognized packet: " << packettype << std::endl;
        break;
    }

    return true;
}


int main(int argc, char* argv[]) {
    //WSAStartup
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        std::cout << "Error" << std::endl;
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    SOCKET newConnection;
    for (int i = 0; i < 100; i++) {
        newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

        if (newConnection == 0) {
            std::cout << "Error #2\n";
        }
        else {
            std::cout << "������������ ���������!\n";
            std::string msg = "�����������. ��� ��� ������ ��������� ���������� ����!";
            int msg_size = msg.size();
            Packet msgtype = P_ChatMessage;
            send(newConnection, (char*)&msgtype, sizeof(Packet), NULL);
            send(newConnection, (char*)&msg_size, sizeof(int), NULL);
            send(newConnection, msg.c_str(), msg_size, NULL);

            Connections[i] = newConnection;
            Counter++;
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);

            Packet testpacket = P_Test;
            send(newConnection, (char*)&testpacket, sizeof(Packet), NULL);
        }
    }


    system("pause");
    return 0;
}