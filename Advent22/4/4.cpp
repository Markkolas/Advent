//Space needed in elven camp. Cleanup is needed.
//Camp is divided into sections with unique ID.
//Each Elf is assigned with a range of sections to clean.
//The assignment of sections overlap.

#include<iostream>
#include<fstream>
#include<string>
#include<array>//struct that contains a simple array. Useful for returning and for its methods.
#include<vector>

using namespace std;

//Stop the bullshit and use C++ capabilities. Use vector. Not very efficient
//with large number of sectors tho. Could use list cause no need for indexation.

/*
Returns a pointer to array of 2 elements: start and end sector.
*/
std::array<int,2> find_sectors(const string& IDs){
    unsigned int pos = IDs.find('-');
    int ID1 = std::stoi(IDs.substr(0, pos));
    int ID2 = std::stoi(IDs.substr(pos+1));

    return std::array<int,2>{ID1, ID2};
}

std::vector<int> compute_sectors(const int first, const int last){
    std::vector<int> vec;

    for(int i=first; i<=last; i++)
        vec.push_back(i);

    return vec;
}

/*
 Returns 3 possible int values:
 0 if no overlap
 1 if overlap but neither contains the another
 2 if one contains the another
*/
unsigned int check_sectors(std::vector<int>& sectors1, std::vector<int>& sectors2){
    if((sectors1.back() < sectors2.front()) || (sectors2.back() < sectors1.front()))
        return 0; //no overlap

    if((((sectors1.front() <= sectors2.front()) && (sectors1.back() >= sectors2.back())) ||
        ((sectors2.front() <= sectors1.front()) && (sectors2.back() >= sectors1.back()))))
        return 2;//one contains another

    //Finally, by discard, here the sectors overlap but are not contained in one another
    return 1;
}

int main(){
    ifstream file("assignment_pairs");

    if(file.is_open()){
        string line;
        unsigned int n_contain{0};

        while(file){
            getline(file,line);

            if(line != ""){
                unsigned int pos = line.find(',');
                string IDs1 = line.substr(0, pos);
                string IDs2 = line.substr(pos+1);

                cout << "---PAIR---" << endl;
                cout << "ID range of Elf 1: " << IDs1 << "ID range of Elf 2:" << IDs2 << endl;

                std::array<int,2> sectors_pair1 = find_sectors(IDs1);
                std::array<int,2> sectors_pair2 = find_sectors(IDs2);

                std::vector<int> sectors1(compute_sectors(sectors_pair1[0], sectors_pair1[1]));
                std::vector<int> sectors2(compute_sectors(sectors_pair2[0], sectors_pair2[1]));

                cout << "---TEST---" << endl;
                cout << "Sectors of Elf 1: ";
                for(vector<int>::iterator it = sectors1.begin(); it != sectors1.end(); ++it)
                    cout << *it << " ";
                cout << "\n";
                cout << "Sectors of Elf 2: ";
                for(vector<int>::iterator it = sectors2.begin(); it != sectors2.end(); ++it)
                    cout << *it << " ";
                cout << "\n";

                switch(check_sectors(sectors1, sectors2)){
                case 0:
                    cout << "There is no overlap\n" << endl;
                    break;
                case 2:
                    cout << "One sector assignment contains the other";
                    break;
                case 1:
                    cout << "Overlap in assignment with no containment";
                    n_contain += 1;
                    break;
                }

                cout << "\n\n";
            }
        }

        cout << "FINAL SCORE: " << n_contain << endl;

        file.close();
    }
    else
        cout << "Error opening the file";

    return 0;
}
