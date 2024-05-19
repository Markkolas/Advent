#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string digarr[9][2] = {{"1", "one"},
                       {"2", "two"},
                       {"3", "three"},
                       {"4", "four"},
                       {"5", "five"},
                       {"6", "six"},
                       {"7", "seven"},
                       {"8", "eight"},
                       {"9", "nine"}};

int convert(string& s){
    for(int i=0; i<9; i++){
        if(s.compare(digarr[i][0]) == 0 || s.compare(digarr[i][1]) == 0)
            return i+1;
    }
    cout << "OOPA" << endl;
    return -1;
}

int getFirst(string& s){
    size_t firstIndx = string::npos;
    string firstVal;

    for(int i=0; i<9; i++){
        size_t numIndx = s.find(digarr[i][0]);
        size_t wrtIndx = s.find(digarr[i][1]);

        if(numIndx < firstIndx && numIndx != string::npos){
            firstIndx = numIndx;
            firstVal = digarr[i][0];
        }
        if(wrtIndx < firstIndx && wrtIndx != string::npos){
            firstIndx = wrtIndx;
            firstVal = digarr[i][1];
        }
    }
    return convert(firstVal);
}

int getLast(string& s){
    size_t lastIndx = 0;
    string lastVal;

    for(int i=0; i<9; i++){
        size_t numIndx = s.rfind(digarr[i][0]);
        size_t wrtIndx = s.rfind(digarr[i][1]);

        if(numIndx >= lastIndx && numIndx != string::npos){
            lastIndx = numIndx;
            lastVal = digarr[i][0];
        }
        if(wrtIndx >= lastIndx && wrtIndx != string::npos){
            lastIndx = wrtIndx;
            lastVal = digarr[i][1];
        }
    }

    return convert(lastVal);
}

int main(){
    fstream file;

    //Open file
    file.open("input.txt", ios::in);
    if(!file.is_open()){
        cout << "Error opening file";
        return 1;
    }

    string line;
    int result = 0;
    while(getline(file, line)){
        //cout << getFirst(line) << getLast(line) << endl;
        if(line.length() > 0)
            result += 10*getFirst(line)+getLast(line);
    }

    cout << result;
    // string test = "2799ph";
    // cout << getFirst(test)*10+getLast(test) << endl;
}
