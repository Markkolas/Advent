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
    list<StarPart> spart_list;
    cout << "Detecting numbers with stars..." << endl;
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
            for(int x = left.p[1]-1; x <= right.p[1]+1; x++){
                const char c = schem.getSafely(y, x);
                if(c==42){
                    //cout << (*it).num << " has a star!" << endl;
                    Schem::Point spoint(y,x);
                    spart_list.push_back(StarPart(*it, spoint));
                }
            }
        }
    }

    //Check from first to last. If exactly two numbers with same star
    //are found, multiply them.
    //End iteration by deleting the items with same star.
    cout << "Detecting gears..." << endl;
    list<GearPair> gpairs;
    list<Schem::Point> points_checked;

    for(list<StarPart>::iterator it=spart_list.begin();
        it != spart_list.end(); ++it){

        StarPart originp(*it);
        bool alredy_checked = false;

        for(list<Schem::Point>::iterator jt = points_checked.begin();
            jt != points_checked.end(); ++jt){
            if(originp.star_p==*jt){
                alredy_checked = true;
                break;
            }
        }

        list<StarPart> parts_to_check = {originp};

        list<StarPart>::iterator jt(it);
        jt++;
        while(jt != spart_list.end() && !(alredy_checked)){
            StarPart compp(*jt);

            if((originp.star_p == compp.star_p)){
                parts_to_check.push_back(compp);
            }

            jt++;
        }

        if(parts_to_check.size()==2){
            GearPair pair{parts_to_check.front(), parts_to_check.back()};
            gpairs.push_back(pair);
        }
    }

    for(list<GearPair>::iterator it = gpairs.begin();
        it != gpairs.end(); ++it){
        cout << "Pair: (" << (*it).pair[0].num << ","
             << (*it).pair[1].num << ") has a gear!" << endl;

        result += (*it).pair[0].num * (*it).pair[1].num;
    }

    cout << result << endl;
    return 0;
}
