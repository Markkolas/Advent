#include "schem.h"

using namespace std;

Schem::Schem(string s){
    cout << "Autodetecting cols... ";
    cols = s.find("\n")+1;
    cout << "Done: " << cols << endl;

    cout << "Cleaning indents...";
    adbasic::cleanIndents(s, ".");
    cout << " Done!" << endl;

    files = s.size()/cols;
    cout << "Schem is size: " << files << "x" << cols << endl;

    data = s;
}

//TODO: Securize methods
Schem::Point Schem::stp(size_t pos){
    Point point(pos/cols, pos%cols);

    return point;
}

size_t Schem::pts(Point p){
    return p.p[0]*cols+p.p[1];
}

char Schem::getSafely(int y, int x){
    if(x < 0 || x > cols - 1 || y < 0 || y > files - 1) return 0;

    return data[y*cols+x];
}
