15. Low-Level Networking: Raw Sockets
Question:
What are raw sockets, and how would you use them in a C++ program to create a simple packet sniffer or packet generator?

Follow-up:
Write a C++ program that creates a raw socket to capture network packets on a given network interface and prints out basic
 packet details (e.g., source and destination IP).

int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    char buffer[65536];  // Buffer to hold incoming packets
    struct sockaddr_in source_socket_address;
    socklen_t source_socket_address_len = sizeof(source_socket_address);
    while (true) {
        // Receive packet
        ssize_t packet_size = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                       (struct sockaddr*)&source_socket_address, &source_socket_address_len);
        if (packet_size < 0) {
            std::cerr << "Error receiving packet" << std::endl;
            break;
        }


    }
}

Yes, in C++ (and in general), on the server side, you typically need to create a separate socket 
for each client that connects. Here's how it works in a common TCP server setup:

Server Socket: The server creates a listening socket which listens for incoming connections from 
clients. This socket is bound to a specific port and IP address, and it waits for clients to initiate 
a connection.

Accepting Connections: When a client attempts to connect to the server, the server's listening socket
 accepts the connection. This creates a new socket specifically for the communication between the 
 server and that individual client. The listening socket continues to wait for new incoming
  connections.

Multiple Clients: Each client that connects to the server gets its own unique socket. The server
 can manage multiple client connections by maintaining separate sockets for each one, typically 
 using a data structure like an array, map, or list.

Handling Clients Concurrently: If the server needs to handle multiple clients at the same time, 
it can either use:

Multithreading: Each client connection is handled in a separate thread, each with its own socket.
Multiplexing (e.g., using select() or epoll): The server uses a single thread and multiplexes 
communication between multiple clients by checking multiple sockets for data.
Example of Basic Flow:
Server: Creates a listening socket.
Client 1: Connects, server accepts and creates a new socket for communication with Client 1.
Client 2: Connects, server accepts and creates a new socket for communication with Client 2.
Server: Continues to listen for new clients while handling communication with already connected clients.
