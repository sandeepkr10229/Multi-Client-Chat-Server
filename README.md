**#Multi-Client Chat Application using TCP Sockets in C++**

A real-time chat application built using C++, WinSock2, TCP sockets, and multithreading. The server can handle multiple clients simultaneously, and messages sent by one client are broadcast to all connected clients.

**Features:**

TCP-based communication
Multi-client support
Multithreaded server architecture
Real-time message broadcasting
Custom chat usernames
Built using WinSock2 on Windows

**Technologies Used:**

C++
WinSock2 API
TCP/IP Networking
Multithreading 
Visual Studio


├── Server.cpp
├── Client.cpp
└── README.md

**How It Works**

The server starts listening on a specified port.
Clients connect to the server using TCP.
A separate thread is created for each connected client.
Messages received from one client are broadcast to all other connected clients.
Clients can send and receive messages simultaneously using separate sender and receiver threads.

**How to Run:**

1. Clone the Repository

git clone

2. Open in Visual Studio

Open the solution/project in Visual Studio.

3. Build the Project

Build both the Server and Client projects.

4. Start the Server

Run the server executable first.

5. Start Multiple Clients

Run multiple instances of the client executable.



Enjoyy!!


Author

Sandeep Kumar
B.Tech EE, DTU
