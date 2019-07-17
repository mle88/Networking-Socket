#include "ServerSocket.h"
#include "./../SocketException.h"
#include <stdlib.h> 
#include <string>
#include <iostream>
#include "generator.cpp"
#include "fileParser.cpp"
#include <queue>
#include <thread>
#include <vector>


bool transferData(ServerSocket new_sock, ServerSocket new_sock2, std::string file_name)
{
  fileParser FileParser(file_name);
  std::cout<< "New connection with client started."<< std::endl;
  
  // For multiple threading, you need to create
  // a new thread here and pass new_sock to it.
  // The thread will use new_sock to communicate
  // with the client.
  
  try
  {
    int frame_counter = 0;
    int failed_frame = rand() % 5;
    int sequence_counter = 0;
    
    std::string previous_client_response;
    std::string client_response;
    std::string parity_bit;
    
    // Read 64 characters from the file parser
    std::string data  = FileParser.readString();
    bool continueTrasfer = true;
    
    bool eof=false;
    
    while (continueTrasfer){ //continuely sends out data while not eof
      
      if (previous_client_response == ACK){
        data = FileParser.readString(); //Gets next string to send
        if (FileParser.eof){
          data = END_TRANSMISSION;
          eof = true;
        }
      } 

      // Wait for 0.15s between transmissions
      // so we can display multithreading.
      usleep(15000); 
      
      // Every five frames, one should have a
      // reversed parity bit that should illicit 
      // a NAK from the client to resend the data.
      parity_bit = getParity(data);
      if (frame_counter > 4) {
        // Five frames have passed, so we
        // need to recalculate the frame number
        // that will have a flipped parity bit.
        frame_counter = 0;
        failed_frame = rand() % 5;
      }
      
      if (failed_frame == frame_counter) {
        // The current frame is the frame to
        // fail, so flip to parity bit.
        parity_bit = (parity_bit == "1") ? "0" : "1";
      }
      
      // std::cout << "Failed frame: " << failed_frame << " Frame counter: " << frame_counter << std::endl;
      
      // Send the data    
      std::cout<<"SENDING: "<< data.substr (0,data.length()-1) <<std::endl; // a quick hack to ignore the \n when couting the outgoing data
      new_sock << parity_bit + data;
      
      // Receive ACK/NAK response 
      new_sock2 >> client_response;
      std::cout<<"RECEIVED: "<< client_response <<std::endl;
      
      std::cout<<std::endl; //a space to seperate messages.
      
      if (client_response == ACK) {
        previous_client_response = ACK;
	
        if (FileParser.eof) 
        {
          continueTrasfer = false; 
          std::cout<<"TRANSMISSION END. SERVER DISCONNECT."<<std::endl;
        }
      }
      else{
        previous_client_response = NAK;
      }
      frame_counter++;
    }
  }
  catch(SocketException& e)
  {
     std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    return false;
  } 
  
  return true;
}


int main(int argc, char **argv)
{

    if (argc != 2) {
      // The script name is always passed as argv[0] 
      std::cout << "Please enter 1 argument!\n"
        "1) port #\n"
        "\n";
      return 0;
    }

    // Convert char array to strings
    std::vector<std::string> all_args(argv, argv + argc);

    int port = std::stoi(all_args[1]); // string -> int
    int ack_port = port + 1;

    std::cout << "runningData....\n"<<endl;
    try{
      // Create the socket
      ServerSocket server_socket(port);
      ServerSocket ack_socket(ack_port);

      ServerSocket client_socket;
      ServerSocket client_ack_socket;
      
      while (true){
        // Wait for a client to connect (Block)
        server_socket.accept(client_socket);

        // Get the requested file name
        std::string file_name;
        client_socket >> file_name;
        
        // Wait for an ack channel connection 
        ack_socket.accept(client_ack_socket);
        
        // Create a new thread to serve the client with
        std::thread transfer_thread(
          transferData,
          // Pass sockets by reference or else they 
          // get copied which destroys the link.
          std::ref(client_socket), 
          std::ref(client_ack_socket),
          file_name
        );
        // Detatch the new thread from the main 
        // thread, so the server can go back to
        // listening. 
        transfer_thread.detach();
      }
    }
    catch (SocketException& e){
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
    return 0;
  }
  
