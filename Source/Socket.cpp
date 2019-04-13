#include "Socket.hpp"

Socket::Socket(const sockaddr_in& address, int& serror){

   fd = socket(AF_INET, SOCK_DGRAM,0);

  if(fd < 0)
      serror = SOCKET_CREATION_ERROR;
  else{

    int result = bind(fd,reinterpret_cast<const sockaddr*>(&address),sizeof(address));

    if (result < 0)
      serror = SOCKET_BINDING_ERROR;
  }
}

Socket::~Socket(){

  close(fd);

}

void Socket::Sent_to(const Message& message, const sockaddr_in& remote_address, int& serror){

  int result = sendto(fd, &message, sizeof(message), 0, reinterpret_cast<const sockaddr*>(&remote_address),sizeof(remote_address));
  if(result < 0)
    serror = ERROR_SENDING_MESSAGE;
}

void Socket::Receive_from(Message& message, sockaddr_in& remote_address){

  socklen_t src_len = sizeof(remote_address);

  int result = recvfrom(fd, &message, message.size,0,reinterpret_cast<sockaddr*>(&remote_address),&src_len);

  char* remote_ip = inet_ntoa(remote_address.sin_addr);
  int remote_port = ntohs(remote_address.sin_port);

  message.text[254] = '\0';
  std::cout << "El sistema " << remote_ip << ":" << remote_port << "envia el mensaje: " << message.text << "\n";
}
