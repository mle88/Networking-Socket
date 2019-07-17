#include "ClientSocket.h"
#include "../SocketException.h"
#include <iostream>
#include <string>
#include <queue>
#include <vector> 
#include <array>
#include "./../server/generator.cpp"


queue <string> receivedLine;

std::array<std::string, 5> VALID_FILES = {{
    "sample_aeronautics.txt",
    "sample_brothers.txt",
    "sample_empire.txt",
    "sample_la_casa.txt",
    "sample_salidarismus.txt"
}};


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

bool is_valid_filename(std::string file_name) {
    /*
     * Assert file name is within list of valid file names
     */
    for (int i=0; i < VALID_FILES.size(); i++) {
        if (file_name == VALID_FILES[i]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        // The script name is always passed as argv[0] 
        std::cout << "Please pass 3 arguments!\n"
            "  1) port #\n"
            "  2) host \n"
            "  3) file name\n"
            "\n";
        return 0;
    }

    // Convert char array args to strings
    std::vector<std::string> all_args(argv, argv + argc);

    int port = std::stoi(all_args[1]); // string -> int 
    int ack_port = port + 1; 
    std::string host = all_args[2]; 
    std::string file_name = all_args[3];

    if (!is_valid_filename(file_name)) {
        std::cout << "Enter a valid file name: \n"
            "- sample_aeronautics.txt\n"
            "- sample_brothers.txt\n"
            "- sample_empire.txt\n"
            "- sample_la_casa.txt\n"
            "- sample_salidarismus.txt\n"
            "\n";
        return 0;
    }

    try{
        // Replace "localhost" with the hostname
        // that you're running your server.
        ClientSocket client_socket(host, port);
        ClientSocket client_socket2(host, ack_port);

        // Immediately send the file name when the server accepts.
        client_socket << file_name;
        
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
