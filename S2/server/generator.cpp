#include <iostream>

using namespace std;

/*
string decToBin(int n){

    string s;
    while(n!=0) {s=(n%2==0 ?"0":"1")+s; n/=2;}
    return s;
}
*/

//provides a summation of characters ASCII values
int stringSum(string str){

    int sum = 0;

    for (int i=0; i<str.length(); ++i)
    {
        //std::cout << str[i]<<endl;
        //std::cout << str[i]-0<<endl;
        sum = sum + str[i];
    }

    return sum;
}


//generates even parity bit for a given integer
bool generateParity(unsigned int n)
{
    bool parity = 0;
    while (n)
    {
        parity = !parity;

        n      = n & (n - 1);
    }
    return parity;
}

//test function
string getParity(std::string str)
{
   int sum = stringSum(str);
   bool par;
   string parbit;
   par=generateParity(sum);

   if(par)
      parbit="1";
   else
      parbit="0";
   
    return parbit;
}

