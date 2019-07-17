
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

queue <string> receivedLine;


// Takes a string, pushes it into queue, searches for \n,
// writes out line if it finds \n
void stackCheck(string str)
{
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
        //cout<<"removing queue "<<receivedLine.size()<<endl;
    }
}

/*
class Parser
{
public:
    Parser(){ stringFile.open("test_networking_doc.txt"); currentLine = 0;}
    ~Parser(){stringFile.close();}

    fstream& GotoLine(fstream& file, unsigned int num)
    {
        file.seekg(ios::beg);
        for(int i=0; i < num - 1; ++i){
            file.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        return file;
    }

    void breakUpLine()
    {
        GotoLine(stringFile,currentLine);

        string currentString;
        stringFile >> currentString;

        for (int i = 0; i<currentString.size(); i++)
        {

        }
    }

    string loadString()
    {
        string currentString;

        if(loadedString.size()==0){ currentLine++; breakUpLine(); }

        return currentString;
    }

    fstream stringFile;
    unsigned int currentLine;
    vector<string> loadedString;
};
*/