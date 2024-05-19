#include<iostream>
//#include<vector> //this time I will use vector
#include<string>
#include<fstream>

enum RESULTS{LOSS=0, DRAW=3, WIN=6};
enum PLAY{ROCK=1, PAPER, SCISSORS};

using namespace std;

unsigned int computeScore(string& line){
    unsigned int enemy_hand, player_hand, score;

    if(line.size() == 0) return 0;//Empty line, just pass

    switch(line[0]){
    case 'A':
        enemy_hand = ROCK;
        break;
    case 'B':
        enemy_hand = PAPER;
        break;
    case 'C':
        enemy_hand = SCISSORS;
        break;
    default:
        cout << "File syntax for elves is incorrect" << endl;
        return 0;
    }

    switch(line[line.size()-1]){
    case 'X':
        player_hand = ROCK;
        break;
    case 'Y':
        player_hand = PAPER;
        break;
    case 'Z':
        player_hand = SCISSORS;
        break;
    default:
        cout << "File syntax for player is incorrect" << endl;
        return 0;
    }

    //Score
    switch(player_hand){
    case ROCK:
        score = ROCK;
        if(player_hand==enemy_hand)
            score += DRAW;
        else if(enemy_hand == PAPER)
            score += LOSS;
        else //SCISSORS
            score += WIN;
        break;

    case PAPER:
        score = PAPER;
        if(player_hand==enemy_hand)
            score += DRAW;
        else if(enemy_hand == ROCK)
            score += WIN;
        else //SCISSORS
            score += LOSS;
        break;

    case SCISSORS:
        score = SCISSORS;
        if(player_hand==enemy_hand)
            score += DRAW;
        else if(enemy_hand == ROCK)
     n       score += LOSS;
        else //PAPER
            score += WIN;
        break;
    }

    return score;
}

int main(int argc, char** argv /*char* argv[] works too*/){
    //vector<int> stack_vec;//header info on stack, elements on heap
    //vector<int>* heap_vec = new vector<int>;//all on heap
    //vector<int*> ptr_vec; //pointers on heap, can point to anywhere(like stack)

    ifstream file("rock_paper_scissors_rounds");
    string line;
    unsigned int score = 0;

    if(file.is_open()){
        while(file){//same as while(file.good())
            getline(file,line);
            //cout << line[0] << " " << line[line.size()-1] << endl;
            score += computeScore(line);
        }

        file.close();
    }
    else{
        cout << "Error opening the file";
    }

    cout << "Total score according to input is:\n" << score << endl;

    return 0;
}
