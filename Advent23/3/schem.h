#include "../adventbasics.h"

struct Schem{
    std::string data;
    int files, cols;

    const char invalid = 0;

    struct Point{
        int p[2];
        Point(int y, int x): p{y,x}{}

        inline bool operator==(const Point& other){
            return (p[0] == other.p[0]) && (p[1] == other.p[1]);
        }

        inline bool operator!=(const Point& other){return !(*this==other);}
    };

    Schem(std::string s);

    char& operator[](Point p){return data[pts(p)];}
    char& operator[](size_t pos){return data[pos];}

    Point stp(size_t pos); //serial to pararel
    size_t pts(Point p); //pararel to serial

    char getSafely(int y, int x);

};

struct Part{
    int num;
    size_t i_indx, e_indx;

    Part(){}
    Part(int initnum): num{initnum}{}
    Part(int initnum, size_t i, size_t e): Part(initnum){
        i_indx = i;
        e_indx = e;
    }

};

struct StarPart:Part{
    Schem::Point star_p;

    StarPart(Part part, Schem::Point p): Part{part}, star_p{p}{};
};

struct GearPair{
    StarPart pair[2];

    GearPair(StarPart part1, StarPart part2): pair{part1, part2}{}
};
