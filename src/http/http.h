namespace HTTP {
class Server {
private:
  int server_socket;
  int backlog;

  void handle_request(int client_socket);

public:
  Server(int port, int backlog);
  void serve();
};
} // namespace HTTP