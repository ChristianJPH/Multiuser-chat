#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <iostream>

const int ERROR_SENDING_MESSAGE = -2;
const int SOCKET_CREATION_ERROR = -3;
const int SOCKET_BINDING_ERROR = -5;

const int MESSAGE_SIZE = 1024;

struct Message{

  char text[MESSAGE_SIZE];
  int size = MESSAGE_SIZE;
};

class Socket {

private:

  int fd;

public:

  Socket(const sockaddr_in& address,int& serror);
  ~Socket();
  void Sent_to(const Message& message, const sockaddr_in& remote_address,int& serror);
  void Receive_from(Message& message, sockaddr_in& remote_address);

};
