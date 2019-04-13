#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include <thread>

#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>

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

  void send_to(const sockaddr_in& remote_address,Socket& local_socket, int& perror){

    std::string mensaje;
    Message message{};

    while(getline(std::cin,mensaje)){

      mensaje.copy(message.text,sizeof(message)-1,0);
      local_socket.Sent_to(message,remote_address,perror);

      if(mensaje == "quit")
        break;

    }


  }

  void receive_from(sockaddr_in& remote_address,Socket& local_socket, int& perror){

    Message message{};

      while(1){

        local_socket.Receive_from(message,remote_address,perror);

        if(message.text == "quit")
          break;
          std::cout << message.remote_ip << " Envió: " << message.text << "\n";


      }

  }

int main(){

int proccess_error;

try{

  sockaddr_in remote_addr = make_ip_address("192.168.1.72",57777);
  Socket local_socket(make_ip_address("",56666),proccess_error);

    std::thread send_thread(&send_to,std::ref(remote_addr),std::ref(local_socket),std::ref(proccess_error));
    std::thread receive_thread(&receive_from,std::ref(remote_addr),std::ref(local_socket),std::ref(proccess_error));

    send_thread.join();
    receive_thread.join();

}
catch(std::system_error& e){

    std::cerr << "MultiUser-Chat: " << e.what() << "\n";
    return proccess_error;

}
}
