#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

int checkMinMult(string& samples){
    char * pch;
    pch = strtok(samples.data(), ",;");

    int MAXRED=0, MAXBLUE=0, MAXGREEN=0;

    while(pch != NULL){
        string sample = string(pch);

        //Lets use spaces in our favour
        size_t firstSpaceIndx = sample.find(" ");
        size_t lastSpaceIndx = sample.rfind(" ");

        int number = stoi(sample.substr(firstSpaceIndx+1, lastSpaceIndx-firstSpaceIndx-1));
        if(sample.find("red") != string::npos && number > MAXRED){
            MAXRED = number;
        }
        else if(sample.find("blue") != string::npos && number > MAXBLUE){
            MAXBLUE = number;
        }
        else if(sample.find("green") != string::npos && number > MAXGREEN){
            MAXGREEN = number;
        }
        //cout << sample << endl;
        pch = strtok(NULL, ",;");
    }

    return MAXRED*MAXBLUE*MAXGREEN;
}

int main(){
    fstream file;

    //Open file
    file.open("input.txt", ios::in);
    if(!file.is_open()){
        cout << "Error opening file";
        return 1;
    }

    int result=0;
    string line;
    while(getline(file, line)){
        //Games ID are put in order of apparition
        string samples = line.substr(line.find(':')+1);
        result += checkMinMult(samples);
    }

    cout << result << endl;
}
