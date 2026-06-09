# Real-Time Multi-Client TCP Chat Application

A real-time chat application built in **C++** using **TCP sockets**, **WinSock2**, and **multithreading**. The server supports multiple clients simultaneously and broadcasts messages between connected users in real time.

## Screenshot

![Chat Application](chat%20app%20.png)

![Chat Application 2](chat%20app%202.png)

## Features

* Real-time messaging
* Multi-client support
* TCP-based communication
* Multithreaded server architecture
* Message broadcasting to connected clients
* Custom chat usernames
* Built using WinSock2 on Windows

## Technologies Used

* C++
* WinSock2 API
* TCP/IP Networking
* Multithreading 
* Visual Studio

## How It Works

1. The server starts listening on a specified port.
2. Clients connect to the server using TCP sockets.
3. A dedicated thread is created for each connected client.
4. Messages received from a client are broadcast to all other connected clients.
5. Clients can send and receive messages simultaneously using separate sender and receiver threads.

## Getting Started

### 1. Clone the Repository

```bash
git clone <repository-url>
```

### 2. Open in Visual Studio

Open the project/solution in Visual Studio.

### 3. Build the Project

Build both the **Server** and **Client** projects.

### 4. Run the Server

Start the server executable first.

### 5. Run Multiple Clients

Launch multiple instances of the client executable and enter a username when prompted.



## Author

**Sandeep Kumar**
B.Tech EE, DTU

Happy Coding!
