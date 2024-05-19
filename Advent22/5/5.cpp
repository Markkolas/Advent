#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<stdlib.h>

using namespace std;

//TODO: A function to print the stack on console

//Returns a double pointer to strings.
//Each string represents a stack
string** proc_stacks(ifstream& file, int& n_stacks){
    string line;
    list<string> stacks_rows;

    while(file){
        getline(file, line);
        if (line == "") break;

        stacks_rows.push_back(line);

        if(!n_stacks)
            n_stacks = line.length();
        else if(n_stacks != line.length()){
            cout << "Bad file syntax!" << endl;
            exit(1);
        }
    }

    string** stacks;
    stacks = (string**) malloc(n_stacks * sizeof(string*));

    for(int i=0; i<n_stacks; i++){
        string holder="";
        string crate;

        for(list<string>::reverse_iterator rit=stacks_rows.rbegin(); rit!=stacks_rows.rend(); ++rit){
            crate = (*rit)[i];
            if(crate != " ")//trim whitespaces
                holder += crate;
        }
        //Whats the point of using 'new' keyword and not using C++ utilities like list?
        //That way we could return the stacks as a list of strings, each element
        //representing a stack.
        //Shut up I wanted to use double pointers and it works
        *(stacks+i) = new string(holder);
    }

    return stacks;
}

string reverse_string(string& s){
    string aux = "";
    for(string::reverse_iterator rit=s.rbegin(); rit!=s.rend(); ++rit)
        aux += *rit;

    return aux;
}

int main(){
    ifstream file("stack_drawing");
    string line;

    if(file.is_open()){
        int n_stacks{0};//TODO: Fix the n_stacks issue
        string** stacks = proc_stacks(file, n_stacks);//I want to use double ptr because fcking yes

        while(file){
            getline(file, line);

            if(line == "") break;

            int move = stoi(line.substr(0, line.find(" ")));
            line = line.substr(line.find(" ")+1);

            int from = stoi(line.substr(0, line.find(" ")));
            line = line.substr(line.find(" ")+1);

            int to = stoi(line.substr(0, line.find(" ")));

            if((move <= 0) || (from <= 0) || (to <= 0)){
                cout << "Bad instruction syntax";
                exit(1);
            }

            cout << "move: " << move << " from: " << from << " to: " << to << endl;
            cout << "Processing..." << endl;

            string stack_from = **(stacks+from-1);
            string stack_to = **(stacks+to-1);
            string crates = stack_from.substr(stack_from.length()-move); //move should not be 0

            cout << "stack from: " << stack_from << endl;
            cout << "stack to: " << stack_to <<endl;

            stack_to += reverse_string(crates);
            stack_from.erase(stack_from.length()-move);

            cout << "stack from: " << stack_from << endl;
            cout << "stack to: " << stack_to << endl;

            **(stacks+from-1) = stack_from;
            **(stacks+to-1) = stack_to;
        }

        file.close();

        cout << "Top crates after instructions are:\n";
        for(int i=0; i<n_stacks; i++)
            cout << (**(stacks+i)).back();
        cout << endl;
    }
    else
        cout << "Error opening the file" << endl;
}
