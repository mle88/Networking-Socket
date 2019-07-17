#include <fstream>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class fileParser
{
    public:
    fileParser(std::string file_name);
   ~fileParser();
    vector<string> read();
    string readString();
    string write(string);
    int getFrameCount();
    void setFrameCount(int);


    //data memebers
    int vectorIndex;
    int lineCount;
    int frameCount;
    int charCount;
    fstream file;
    int line_num;
    vector<string> fileLine;
    string textline;
    int index;
    bool eof;
};

fileParser::fileParser(std::string file_name)
{
    file.open("../sample_files/" + file_name);
    if (file.is_open()){
        //cout<<"The file has been found"<<endl;
    }
    charCount= 0;
    lineCount = 0;
    index = 0;
    eof=0;
    vectorIndex = 0;

}

fileParser::~fileParser(){

    file.close();

}


//Function setFramecount(): This function returns the number of frames that will be sent out
//Input: The length of the line divided by 64
//Output: none
void fileParser::setFrameCount(int a){

frameCount=a;
}

//Function getFramecount(): This function returns the number of frames that will be sent out
//Input: none
//Output: the number of frames

int fileParser::getFrameCount(){

return frameCount;
}

//Function read(): This function should be called for each line in the text to break the
//text file into smaller frame sizes.
//Input: none
//Output: A vector which contains frames of a max size of 64 characters for
//one text line
vector<string> fileParser::read(){

    string line;
    getline (file, line);
    if (file.eof())
    {
        //cout<<"End of file."<<endl;
        eof =1;

    }
    double len = line.length();
    double b = len/64.00;

    setFrameCount(ceil(b));

    int j = 0;
    vector<string> temp;

    while(!fileLine.empty()){
        fileLine.pop_back();
    }

    for (int i=0; i<=b; i++){
        string sub = line.substr(j, 64);
        fileLine.push_back(sub);
        j=j+ 64;
        temp=fileLine;
    }
    
    return temp;
}

string fileParser::readString() {  
  /* 
   * Return 64 character chunks of a file from 
   * `fileLine` buffer created by `fp.read()`.
   * 
   * return std::string
   */
    bool existing_buffer = !fileLine.empty();
    
    if (!existing_buffer) {
      read(); // Fill the fileLine buffer
    }
    
    // Psuedo 'Pop' operation, grab the first 
    // chunk and shuffle the rest forward.
    std::string character_chunk = fileLine.front();
    fileLine.erase(fileLine.begin()); 
    
    bool on_last_chunk = fileLine.empty();
    
    if (on_last_chunk) {
      // Indicate to the print queue that we're supposed
      // to flush the buffer now by adding a newline character.
      character_chunk += "\n";
    }
    
    return character_chunk;
}


