#include "IMT2019006_UsefulFunctions.h" // including Useful functions header file

using namespace std;


int main(int argc, char *argv[])
{
    int i;
    double numInstructions = 0, hits, miss;
    string tag, index, byteOffset, str, address;
    int decIndex;

    // implementing directed map cache 
    // According to question, part a,
    // a) block size = 4 bytes = 2^2 bytes -> 2 bits for bytes offset 
    // b) total cache size = 256 kB = (256 * 1024) bytes 
    // c) address = 32 bits = 4 bytes 
    // d) number of rows = (total cache size) / (address) = 64 * 1024 = 2^16 => 16 bits for index 
    // e) tag bits = address bits - (index bits + byte offset) = 32 - (16 + 2) = 14 bits for tag
    
    // validity array 
    int validity[70000] = {0}; // 2^16 size is needed 

    // tag bits array
    string tagList[70000];  

    // Hits and Miss are initially zero 
    hits = 0;
    miss = 0;

    // argc -> number of command line arguments
    if (argc > 1)
    {
        ifstream file(argv[1]);         // reading file 
        while (getline(file, str))      // line by line
        {
            string subStrs[10];

            Stringsplit(str, subStrs, ' ');

            // subStrs[1] will give us the address
            address = subStrs[1];

            // converting hexa to binary
            address = HexToBin(address);

            // initial 14 bits are for tag 
            tag = address.substr(0, 14);

            // then 15 bits are for index.
            index = address.substr(14, 16);
            decIndex = binToInt(index);      // index in decimal form

            // byte offset is 2
            byteOffset = address.substr(30, 2);

            numInstructions++;

            // If the validity tag is zero that means that index of cache is empty
            if(validity[decIndex] == 0)
            {
                validity[decIndex] = 1;  // update valid bit to 1
                tagList[decIndex] = tag; // tag inserted 
                miss++;                  // miss incremented
            }
            else
            {
                // if given tag is matched with the tag at index "decIndex", its a hit
                if(tagList[decIndex] == tag)
                {
                    hits++;                         //  hits incremented
                }
                else
                {
                    miss++;                         // miss incremented 
                    tagList[decIndex] = tag;        // tag updated   
                }
            }
        }
        cout << "Number of Instructions : " << numInstructions << "\nNumber of hits : " << hits << "\nNumber of miss : " << miss << "\n";
        cout << "Hit rate : " << hits/numInstructions << "\nMiss rate : " << miss/numInstructions << "\n";
    }
    
    return 0;
}