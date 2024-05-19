#include "../adventbasics.h"
#include <string.h>

using namespace std;

constexpr int MAXRED=12, MAXBLUE=14, MAXGREEN=13;

bool checkLine(string& samples){
    char * pch;
    pch = strtok(samples.data(), ",;");

    while(pch != NULL){
        string sample = string(pch);

        //Lets use spaces in our favour
        size_t firstSpaceIndx = sample.find(" ");
        size_t lastSpaceIndx = sample.rfind(" ");

        int number = stoi(sample.substr(firstSpaceIndx+1, lastSpaceIndx-firstSpaceIndx-1));
        if((sample.find("red") != string::npos && number > MAXRED) ||
           (sample.find("blue") != string::npos && number > MAXBLUE) ||
           (sample.find("green") != string::npos && number > MAXGREEN)){
            return false;
        }
        //cout << sample << endl;
        pch = strtok(NULL, ",;");
    }
    return true;
}

int main(){
    fstream file;

    //Open file

    if(!adbasic::readInput(file))
        return 1;

    int result=0, count=0;
    string line;
    while(getline(file, line)){
        //Games ID are put in order of apparition
        count++;
        string samples = line.substr(line.find(':')+1);
        if(checkLine(samples)) result += count;
    }

    cout << result << endl;
}
