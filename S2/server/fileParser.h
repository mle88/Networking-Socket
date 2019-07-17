#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class fileParser
{
    public:
    fileParser();
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
#endif
