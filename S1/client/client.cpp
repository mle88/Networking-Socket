#include "ClientSocket.h"
#include "../SocketException.h"
#include <iostream>
#include <string>
#include <queue>
#include <vector> 
#include <array>
#include "./../server/generator.cpp"


queue <string> receivedLine;

void stackCheck(string str)
{
    /*
     * Takes a string, pushes it into queue, searches for 
     * newline (\n). Writes out line if it finds newline.
     */
    receivedLine.push(str);

    string currentStr = receivedLine.back();

    size_t found = currentStr.find("\n"); // returns position at found character

    if (found!=string::npos)
    {
        //cout << "\\n found at: " << found << '\n';
        int sz = receivedLine.size();

        for(int i = 0; i<sz; i++)
        {
            cout<<receivedLine.front();
            receivedLine.pop();
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        // The script name is always passed as argv[0] 
        std::cout << "Please pass 3 arguments!\n"
            "  1) port #\n"
            "  2) host \n"
            "\n";
        return 0;
    }

    // Convert char array args to strings
    std::vector<std::string> all_args(argv, argv + argc);

    int port = std::stoi(all_args[1]); // string -> int 
    int ack_port = port + 1; 
    std::string host = all_args[2]; 

    try{
        // Replace "localhost" with the hostname
        // that you're running your server.
        ClientSocket client_socket(host, port);
        ClientSocket client_socket2(host, ack_port);

        // Immediately send the file name when the server accepts.
        client_socket << "sample_aeronautics.txt";
        
        bool continueTrasfer = true;
      
        while(continueTrasfer){ 
            std::string frame, received_parbit, expected_parbit;
            std::string response;
	 
            // Usually in real applications, the following
            // will be put into a loop. 
            try {
                // Receive the frame from server
                client_socket >> frame;

                // Split the parity bit from the rest of the frame
                received_parbit=frame[0];
                frame=frame.substr(1);
                
                expected_parbit=getParity(frame);

                // Select the response and send it to the server
                response = (expected_parbit == received_parbit) ? ACK : NAK;

                if (response != NAK) {
                    stackCheck(frame);
                }
                
                if (frame == END_TRANSMISSION) {
                    std::cout << "Reached the end of the file, exiting." << std::endl;
                    continueTrasfer = false; 
                }
            
                client_socket2 << response;
            }
            catch(SocketException&){
                // do nothing
            }
            //std::cout << "We received this frame from the server:\n\"" << frame << "\"\n";
        //std::cout<<"Client is sending a "<<response<<std::endl<<std::endl;
      }
    }
    catch(SocketException& e){
        std::cout << "Exception was caught:" << e.description() << "\n";
    }

    return 0;
}
