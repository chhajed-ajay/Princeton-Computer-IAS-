#include "IMT2019006_UsefulFunctions.h"  // including Useful functions header file

using namespace std;

int main(int argc, char *argv[])
{
    int i;
    double numInstructions = 0, hits, miss;
    string tag, index, byteOffset, str, address;
    int decIndex;

    // Implementing set Associative cache

    // According to question, part b,
    // a) block size = 4 bytes = 2^2 bytes -> 2 bytes offset
    // b) total cache size = 256 kB = (256 * 1024) bytes
    // c) address = 32 bits = 4 bytes
    // d) number of sets = (total cache size) / (address * block size) = 16 * 1024 = 2^14 => 14 bits for index
    // e) tag bits = address bits - (index bits + byte offset) = 32 - (14 + 2) = 16 bits for tag

    // activity of any particular set will decide which "way" is used recently and which is used lately.
    int activity[17000][5] = {0};

    // time of any particular set will help us to update the activity  
    int time[17000] = {0}; 

    // separate tag list for separate way (4 ways)
    string tagList1[17000];     // 2^14 size  (index bits)
    string tagList2[17000];
    string tagList3[17000];
    string tagList4[17000];


    // separate validity list for separate way (4 ways)
    int validity1[17000] = {0}; // 2^14 size (index bits)
    int validity2[17000] = {0};
    int validity3[17000] = {0};
    int validity4[17000] = {0};

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

            // initial 16 bits are for tag 
            tag = address.substr(0, 16);

            // then 14 bits are for index.
            index = address.substr(16, 14);
            decIndex = binToInt(index);  // index in decimal form

            // byte offset is 2
            byteOffset = address.substr(30, 2);

            numInstructions++;

            // I am inserting tag in the following order : way1, way2, way3, way4
            // So if validity of way 1 (validity1) is not zero then only I will go to other ways.
            if(validity1[decIndex] == 0)
            {
                validity1[decIndex] = 1;                    // changing validity 
                tagList1[decIndex] = tag;                   // inserting tag
                miss++;                                     // miss incremented
                activity[decIndex][0] = time[decIndex];     // activity updated
            }
            else if(tagList1[decIndex] == tag)
            {
                hits++;                                     //  hits incremented
                activity[decIndex][0] = time[decIndex];     // activity updated
            }
            else if(validity2[decIndex] == 0)
            {
                validity2[decIndex] = 1;
                tagList2[decIndex] = tag;
                miss++;
                activity[decIndex][1] = time[decIndex];
            }
            else if(tagList2[decIndex] == tag)
            {
                hits++;
                activity[decIndex][1] = time[decIndex];
            }
            else if(validity3[decIndex] == 0)
            {
                validity3[decIndex] = 1;
                tagList3[decIndex] = tag;
                miss++;
                activity[decIndex][2] = time[decIndex];
            }
            else if(tagList3[decIndex] == tag)
            {
                hits++;
                activity[decIndex][2] = time[decIndex];
            }
            else if(validity4[decIndex] == 0)
            {
                validity4[decIndex] = 1;
                tagList4[decIndex] = tag;
                miss++;
                activity[decIndex][3] = time[decIndex];
            }
            else if(tagList4[decIndex] == tag) 
            {
                hits++;
                activity[decIndex][3] = time[decIndex];
            }
            // if all the ways are busy, we will go into else, and we will use the "least recently used" replacement policy.
            // In this, we will update that way in which corresponding tag is not used recently as compared to others.
            else                                            
            {
                int minimum = INT32_MAX;

                // minWay will contain the way number which is least recent used 
                int minWay;

                // minWay is getting calculated
                for(i=0;i<4;i++)
                {
                    if(activity[decIndex][i] < minimum)
                    {
                        minimum = activity[decIndex][i];
                        minWay = i; 
                    }
                }   

                // if minWay is 0 --> tag of way1 should be updated, similarly ...
                if(minWay == 0)
                {
                    tagList1[decIndex] = tag;
                }
                else if(minWay == 1)
                {
                    tagList2[decIndex] = tag;
                }
                else if(minWay == 2)
                {
                    tagList3[decIndex] = tag;
                }
                else if(minWay == 3)
                {
                    tagList4[decIndex] = tag;
                }                

                // activity of the minWay will update
                activity[decIndex][minWay] = time[decIndex];

                miss++; 

            }

            time[decIndex]++;       // time of the particluar set is incremented

        }
        cout << "Number of Instructions : " << numInstructions << "\nNumber of hits : " << hits << "\nNumber of miss : " << miss << "\n";
        cout << "Hit rate : " << hits/numInstructions << "\nMiss rate : " << miss/numInstructions << "\n";
    }
    
    return 0;
}