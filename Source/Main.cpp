#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>

#include "Socket.hpp"


  sockaddr_in make_ip_address(const std::string& ip_address, int port){

    sockaddr_in local_address{};

    local_address.sin_family = AF_INET;

    if(ip_address != "")
      inet_aton(ip_address.c_str(), &local_address.sin_addr);
    else
      local_address.sin_addr.s_addr = htonl(INADDR_ANY);

    local_address.sin_port = htons(port);

    return local_address;
  }

int main(){

int proccess_error;
std::string mensaje;
Message texto_tosend;
Message message;
sockaddr_in remote_addr = make_ip_address("127.0.0.1",56666);
Socket local_socket(make_ip_address("",57777),proccess_error);

  while(getline(std::cin,mensaje)){

    if(mensaje == "quit")
      break;

    mensaje.copy(texto_tosend.text,sizeof(texto_tosend)-1,0);
    local_socket.Sent_to(texto_tosend,remote_addr,proccess_error);
    local_socket.Receive_from(message,remote_addr);

  }
}
