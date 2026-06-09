#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <string>
using namespace std;
   
#pragma comment(lib,"Ws2_32.lib")

//init winsock
// create socket
// connect to server
//send/rec
// close the socket 

bool initialize() {
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void sendMsg(SOCKET s) {
	cout << "enter your chat name";
	string name,message;
	cout << "\n";
	getline(cin, name);
	

	while (1) {
		getline(cin, message);
		string msg = name + " : "  + message;
		int byte_sent = send(s, msg.c_str(), msg.length(), 0);
		if (byte_sent == SOCKET_ERROR) {
			cout << "error sending msg\n";
			break;
		}

		if (message == "leave") {
			cout << " client is leaving\n";
			break;
		}
	}
	closesocket(s);
	WSACleanup();

}

void recMsg(SOCKET s) {
	char buffer[5000];
	int byte_rec; string msg;
	while (1) {
		
		int byte_rec = recv(s, buffer, sizeof(buffer), 0);
		if (byte_rec <= 0) {
			cout << "Disconnected from server";
			break;
		}
		msg = string(buffer, byte_rec);
		cout << msg << endl;
		
	}
	closesocket(s);
	WSACleanup();
}

int main() {
	
	if (!initialize()) {
		cout << "initialization failed\n";
		return 1;
	}

	cout << "client program started\n";

	// create socket

	SOCKET s = socket(AF_INET,SOCK_STREAM,0);
	if (s == INVALID_SOCKET) {
		cout << "invalid socket\n";
		return 1;
	}

	int port = 12345;
	string serverAddress = "127.0.0.1"; // we are connecting to localhost, if we wanted to connect with aws we could have
	 
	sockaddr_in serverAdd; 
	serverAdd.sin_port = htons(port);
	serverAdd.sin_family = AF_INET;
	inet_pton(AF_INET, serverAddress.c_str(), &(serverAdd.sin_addr));

		//connecting to server

	if (connect(s, reinterpret_cast<sockaddr*>(&serverAdd), sizeof(serverAdd)) == SOCKET_ERROR) {
		cout << "not able to connect to server\n";
		closesocket(s);
		WSACleanup();
		return 1;
	}

	cout << "connected to server\n";

	// send / rec 

	thread sender(sendMsg, s);
	thread receiver(recMsg, s);

	sender.join();
	receiver.join();
	

	closesocket(s);
	WSACleanup();
	return 0;
}
