#include<iostream>
#include<string>
#include<list> //could have used vector too (dynamic array)

#define MAXCALS 100000 //Elves are small

using namespace std;

int whoCarriesMore(const list<list<unsigned int>>& elves){
    unsigned int count = 1, max_holder = 0, elfn;

    for(auto it = elves.begin(); it != elves.end(); it++){
        unsigned int cals_sum = 0;

        for(auto cal = (*it).begin(); cal != (*it).end(); cal++)
            cals_sum += *cal;

        if(cals_sum > max_holder){
            max_holder = cals_sum;
            elfn = count;
        }

        count++;
    }

    return elfn;
}

int main(){

    list<list<unsigned int>> elves;
    list<unsigned int> cals;

    string line;
    int count = 1;
    bool ending = false;

    cout << "Enter list of calories separated by [RETURN].\n" <<
        "Type [RETURN] to specify another Elf.\n" <<
        "Double [RETURN] or Ctrl+D to end list.\n\n" << endl;

    cout << "Contents for Elf " << count << ":\n"<< endl;

    while(getline(cin, line)){ //Read while input buffer is not ended with EOF (Ctrl+D)
        if(line != ""){
            ending = false;
            cals.push_back(stoi(line));
        }
        else{
            if(ending)
                break;

            ending = true;
            elves.push_back(cals);
            cals.clear();

            cout << "Contents for Elf " << ++count << ":\n"<< endl;
        }
    }

    cout << "Inserted contents of " << elves.size() << " elves" << endl;
    cout << "Processing list...\n" << endl;

    cout << "The Elf number " << whoCarriesMore(elves) << " is the one with the most calories" << endl;
}
