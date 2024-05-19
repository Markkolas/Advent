#include<iostream>
#include<fstream>
#include<string>

#define NUM_ALPHA_CHARS 52 //26*2 alphabet letters, objects representation
#define MINUS_OFFSET_SCORE 96
#define UPPER_OFFSET_SCORE 38

using namespace std;

namespace bagChecker{
    bool compareArray(const unsigned char object, const char* begin, const int length);
    unsigned int checkBag(const string& line);
}

bool bagChecker::compareArray(const unsigned char object, const char* array, const int length){
    for(const char* o = array; o!=array+length; o++){
        //cout << (void*) o << endl;
        //cout << *o << endl;
        if(*o == object) return true;
    }

    return false;
}

unsigned int bagChecker::checkBag(const string& line){
    char lettersBuff[NUM_ALPHA_CHARS];//lets do it hard, fuck the string
    unsigned int max_index=0, score=0;

    if(line.size() % 2){
        cout << "This bag has not an even number of elements, ignoring" << endl;
        return 0;
    }
    string comp1 = line.substr(0, (line.size()/2)-1);
    string comp2 = line.substr(line.size()/2, line.size()-1);

    //Quiero tener en cuenta los caracteres ya buscados, creo que voy a usar otra
    //string o un array de chars

    cout << "Comparing '" << comp1 << "' with '"  << comp2 << "'" << endl;

    //TODO: Random accesses pos search
    for(string::iterator it=comp1.begin(); it!=comp1.end(); it++){
        if(!compareArray(*it, lettersBuff, max_index+1) && //order matters in func evaluation
           compareArray(*it, comp2.c_str(), comp2.size()))
        {
            lettersBuff[max_index] = *it;
            max_index++;
            cout << "Object of type: " << *it << " badly stored"<< endl;

            if(97<=*it && *it<=122) //minus letter
                score += *it - MINUS_OFFSET_SCORE;
            else if(65<=*it && *it<=90) //upper letter
                score += *it - UPPER_OFFSET_SCORE;
        }
    }

    return score;
}

int main(int argc, char** argv){
    ifstream file("bag_contents");
    string line;
    unsigned int score = 0, count=0;

    if(file.is_open()){
        while(file){
            getline(file,line);
            if(!line.empty()){
                cout << "Processing bag with id: " << ++count <<", contents" << endl;
                score += bagChecker::checkBag(line);
                cout << "\n";
            }
        }
        file.close();
    }
    else
        cout << "Error opening file";

    cout << "Final score: " << score << endl;

    return 0;
}
