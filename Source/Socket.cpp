#include "Socket.hpp"

Socket::Socket(const sockaddr_in& address,int& serror){

   fd = socket(AF_INET, SOCK_DGRAM,0);

  if(fd < 0){
      serror = SOCKET_CREATION_ERROR;
      throw std::system_error(errno, std::system_category(),"no se pudo crear el Socket: ");
  }else{

    int result = bind(fd,reinterpret_cast<const sockaddr*>(&address),sizeof(address));

    if (result < 0){
      serror = SOCKET_BINDING_ERROR;
      throw std::system_error(errno, std::system_category(), "No se pudo enlazar el socket: ");
    }
  }
}

Socket::~Socket(){

  close(fd);

}

void Socket::Sent_to(const Message& message, const sockaddr_in& remote_address, int& serror){

  int result = sendto(fd, &message, sizeof(message), 0, reinterpret_cast<const sockaddr*>(&remote_address),sizeof(remote_address));
  if(result < 0){
    serror = ERROR_SENDING_MESSAGE;
    throw std::system_error(errno, std::system_category(), "No se pudo enviar el mensaje: ");
  }
}

void Socket::Receive_from(Message& message, sockaddr_in& remote_address, int& serror){

  socklen_t src_len = sizeof(remote_address);

  int result = recvfrom(fd, &message, message.size,0,reinterpret_cast<sockaddr*>(&remote_address),&src_len);
    if(result < 0){
      serror = ERROR_RECEIVING_MESSAGE;
      throw std::system_error(errno, std::system_category(), "No se pudo recibir el mensaje: ");
    }

  message.remote_ip = inet_ntoa(remote_address.sin_addr);
  message.remote_port = ntohs(remote_address.sin_port);

}
