#include "../adventbasics.h"
#include "schem.h"
#include <list>

using namespace std;

int main(int argc, char *argv[]){
    string in;
    list<Part> numlist;

    if(argc == 1){
        cout << "Specify argument.\n"
             << "0: From console\n"
             << "1: From 'test.txt' file\n"
             << "2: From 'input.txt' file" << endl;

        return 0;
    }

    if(*argv[1] == '0')
        adbasic::getFromConsole(in);
    else if(*argv[1] == '1')
        in = adbasic::readTest();
    else if(*argv[1] == '2')
        in = adbasic::readInput();
    else{
        cout << "Wrong argument, exiting..." << endl;
        return 0;
    }

    Schem schem(in);

    cout << "Detecting numbers..." << endl;
    for(size_t i=0; i<schem.data.size(); i++){
        if(schem[i] >= 48 && schem[i] <= 57){
            size_t e_num_indx;
            string aux = schem.data.substr(i);
            int num = stoi(aux, &e_num_indx);
            Part part(num, i, i+e_num_indx-1);

            numlist.push_back(part);

            i += e_num_indx;
        }
    }

    int result = 0;
    for(list<Part>::iterator it=numlist.begin();
        it != numlist.end(); ++it){
        // cout << "Num: " << (*it).num
        //      << "; Init indx: " << (*it).i_indx
        //      << "; End indx: " << (*it).e_indx << endl;

        Schem::Point left = schem.stp((*it).i_indx);
        Schem::Point right = schem.stp((*it).e_indx);

        // cout << "Checking: " << (*it).num << endl;
        if(left.p[0] != right.p[0]){
            cout << "Something is very odd!" << endl;
            exit(0);
        }

        for(int y = left.p[0]-1; y <= left.p[0]+1; y++){
            bool issymb = false;
            for(int x = left.p[1]-1; x <= right.p[1]+1; x++){
                const char c = schem.getSafely(y, x);
                if(!((c >= 48 && c <= 57) || c == 46) && c != 0){
                    //cout << "Has symbol!: " << c << endl;
                    issymb = true;
                    break;
                }
            }

            if(issymb){
                result += (*it).num;
                break;
            }
        }
    }

    cout << result << endl;
    return 0;
}
