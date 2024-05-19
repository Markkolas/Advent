#include <iostream>
#include <list>

int main(){
    int i[] = {1,2,3,4,5};
    std::list<int> mylist(i, i+5);

    for(std::list<int>::iterator it=mylist.begin(); it != mylist.end();
        ++it){
        std::cout << "\nIteration: " << *it << std::endl;

        std::list<int>::iterator jt(it);
        ++jt;
        while(jt != mylist.end()){
            std::cout << *jt << std::endl;
            ++jt;
        }
    }
}
