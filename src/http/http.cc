#include "http.h"
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

HTTP::Server::Server(int port, int backlog) : backlog(backlog) {
  // Create a socket
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket == -1) {
    throw std::runtime_error("Error: Unable to create socket.");
  }

  sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(port);

  // lose the pesky "Address already in use" error message.
  int yes = 1;
  if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) ==
      -1) {
    throw std::runtime_error("Error: setsockopt");
  }

  // Bind the socket to the port.
  if (bind(server_socket, (struct sockaddr *)&server_address,
           sizeof(server_address)) < 0) {
    close(server_socket);
    throw std::runtime_error("Error: Unable to bind to port 8080.");
  }
}

void HTTP::Server::serve() {
  // Listen for incoming connections
  if (listen(server_socket, backlog) < 0) {
    close(server_socket);
    throw std::runtime_error("Error: Unable to listen on socket.");
  }

  // TODO: Switch to glog.
  std::cout << "Server is listening on port 8080..." << std::endl;

  while (true) {
    // Accept incoming connection
    sockaddr_in client_address;
    socklen_t client_address_length = sizeof(client_address);
    int client_socket =
        accept(server_socket, (struct sockaddr *)&client_address,
               &client_address_length);
    if (client_socket < 0) {
      close(server_socket);
      throw std::runtime_error("Error: Unable to accept incoming connection.");
    }

    // Handle the request
    handle_request(client_socket);
  }
}

// Function to handle incoming HTTP requests
void HTTP::Server::handle_request(int client_socket) {
  // Read the HTTP request
  char buffer[1024];
  int bytes_read = read(client_socket, buffer, sizeof(buffer));
  if (bytes_read > 0) {
    // Print the received HTTP request
    std::cout << "Received HTTP request:\n" << buffer << std::endl;

    // Send the HTTP response
    std::string response =
        "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!\r\n";
    write(client_socket, response.c_str(), response.length());
  }
  // Close the client socket
  close(client_socket);
}