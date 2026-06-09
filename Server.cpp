#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <thread>
#include <vector>
using namespace std;

#pragma comment(lib,"Ws2_32.lib")

//writing code for server -> steps 

//initialize winsock library
// create new project
// get ip and port
// bind the ip/port with the socket 
// listen on socket
// accept         blocking call , code will wait until connection from client comes 
// receive and send
//close the socket
//cleanup the winsock





bool initialize() {
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void interact(SOCKET clientSocket, vector<SOCKET>& clients) {
	cout << "client connected\n";
	
	char buffer[5000];

	while (1) {
		// now we have connected to client , now we can sened and receive data we wil use send and receive api
		int byteReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

		if (byteReceived <= 0) {
			cout << "client disconnected";
			break;
		}

		string message(buffer, byteReceived);
		cout << "Msg received from client : " << message << endl;

		for (auto client : clients) {
			if (client != clientSocket) {
				send(client, message.c_str(), message.length(), 0);
			}
		}
		

	}

	auto it = find(clients.begin(), clients.end(), clientSocket);
	if (it != clients.end()) {
		clients.erase(it);
	}
	

	closesocket(clientSocket);
}



int main() {

	// first we initialized the winsock lib and added header files and then we checked if it is initialized or not 
	
	if (!initialize()) {
		 cout << "winsock initialization failed \n";
		 return 1;
	}

	cout << "server program\n";


	//crerating socket using    socket   api ,,   we using AF_INET for ipv4 addressing, if we want ipv6 use AF_INET6
	//protocol stream - > SOCK_STREAM for using TCP ,  SOCK_DGRAM for UDP prototcol 

	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (listenSocket == INVALID_SOCKET) {
		cout << "Socket creation failed \n"; 
		return 1;
	}

	//create address structur -> get ip and port
	
	int port = 12345;
	sockaddr_in serverAddr;  /// we created serverAddr structure for addr
	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_port = htons(port); // host to network short api using we can't directly put integer  

	//convert the ip add (0.0.0.0) , put it inside sin_family in binary struct, using api for that

	if (InetPtonW(AF_INET, _T("0.0.0.0"), &serverAddr.sin_addr) != 1) {
		cout << "Setting addr structure failed\n";
		closesocket(listenSocket); // as we already created socket we should cleanup before going
		WSACleanup();
		return 1;
	}

	// binding listensocket and server add struc

	if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
		cout<<"Bind failed";
		closesocket(listenSocket); 
		WSACleanup();
		return 1;
	}

	// listen

	if (listen(listenSocket, 0x7fffffff) == SOCKET_ERROR) { // 2nd parameter is max devices we can put in queue 
		cout << "listen failed\n";
		closesocket(listenSocket);
		WSACleanup();
		return 1; 
			
	}

	cout << "server has started listening on port " << port << endl;

	//accept

	// here we want that when ever we take msg from one client 
	// it should again go to accept stage , so that we can take msg from another client
	vector <SOCKET> clients;
	while (1) {
		SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);

		if (clientSocket == INVALID_SOCKET) {
			cout << "INVALID client socket \n";
		}
		clients.push_back(clientSocket);

		thread t1(interact, clientSocket, std::ref(clients));

		t1.detach();

		// this will work forever 
	}

	

	
	closesocket(listenSocket);

	WSACleanup();
	return 0;
}