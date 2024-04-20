#include "http/http.h"
#include <iostream>

#define PORT 8080
#define BACKLOG 10

int main() {
  HTTP::Server server(PORT, BACKLOG);
  server.serve();
  
  return 0;
}
