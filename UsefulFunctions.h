// Header file which will contain important useful functions.
// a) split string function 
// b) binary to decimal conversion
// c) hexadecimal to binary string conversion

// all important libraries 
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>


// split string method to separate sub-strings separated by particular character 
void Stringsplit(std::string s, std::string subStrings[], char ch)
{
    // sentence intitally empty
    std::string Sentence = "";
    int i = 0;

    for (auto c : s)
    {
        if (c != ch)
        {
            Sentence = Sentence + c;
        }
        else
        {
            subStrings[i++] = Sentence;
            Sentence = "";
        }
    }

    // making substrings
    subStrings[i] = Sentence;
}


// binary string to decimal conversion
int binToInt(std::string str)
{
    int value = 0;
    int i;
    for (i = 0; i < str.size(); i++)
    {
        if (str[i] == '1')
        {
            value = value + pow(2, str.size() - 1 - i);
        }
    }
    return value;
}


// Hexadecimal to binary string conversion 
std::string HexToBin(std::string hexaString)
{
    int i = 0;
    
    // removing "0x" part from string hexdec
    hexaString = hexaString.substr(2, 8);

    // Now hexdec will contain only 8 digits (excluding "0x") of the hexadecimal string 
    std::string t;

    while (hexaString[i])
    {

        switch (hexaString[i])
        {
        case '0':
            t = t + "0000";
            break;
        case '1':
            t = t + "0001";
            break;
        case '2':
            t = t + "0010";
            break;
        case '3':
            t = t + "0011";
            break;
        case '4':
            t = t + "0100";
            break;
        case '5':
            t = t + "0101";
            break;
        case '6':
            t = t + "0110";
            break;
        case '7':
            t = t + "0111";
            break;
        case '8':
            t = t + "1000";
            break;
        case '9':
            t = t + "1001";
            break;
        case 'a':
            t = t + "1010";
            break;
        case 'b':
            t = t + "1011";
            break;
        case 'c':
            t = t + "1100";
            break;
        case 'd':
            t = t + "1101";
            break;
        case 'e':
            t = t + "1110";
            break;
        case 'f':
            t = t + "1111";
            break;
        default:
            break;
        }
        i++;
    }
    return t;
}

