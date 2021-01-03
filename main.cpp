/*
    Filename main.cpp
    description: contains the main game logic and the game loop
*/
#include<iostream>
#include<random>
#include"Characters/character.h"
#include<SFML/Graphics.hpp>
#include<windows.h>

Character* P1 = nullptr;
Character* P2 = nullptr;
bool TWO_PLAYER = false; 

int random_int(){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> range(0,4);
    return range(mt);
}
/*
allows player to select a class
@param None
@return Pointer to a Character Object
*/
Character* select_character(){
    using namespace std;
    cout << "Please select a character: 'Wizard', 'Dragon', 'Knight', 'Mage', 'Goblin' :: ";
    string input;
    getline(cin >> ws,input);
    cout << input << " class has been Chosen!\n";
    for(int i = 0; i < input.size();i++){
        input[i] = tolower(input[i]);
    }
    if(input == "wizard"){
        return new Wizard;
    // }else if(input == "dragon"){
    //     return new Dragon;
    // }else if(input == "knight"){
    //     return new Knight;
    }else if(input == "mage"){
        return new Mage;
    // }else if(input == "goblin"){
    //     return new Goblin;
    }else{
        std::cout << "Error " << input << " Is not a class!\n";
    }
    return nullptr;
}

/*
Randomly selects a class for the computer
@param none
@return Pointer to Character Object 
*/
Character* get_computer_character(){
    int rand_int = random_int();
    // switch (rand_int)
    // {
    // case 0:
    //     return new Wizard;        
    //     break;
    // case 1:
    //     return new Dragon;
    //     break;
    // case 2:
    //     return new Mage;
    //     break;
    // case 3:
    //     return new Knight;
    //     break;
    // case 4:
    //     return new Goblin;
    //     break;
    // }
    return new Wizard;
}

void enable_two_player(){
    using namespace std;
    cout << "Would you like to enable two player?(Y/n) ";
    char input = tolower(getchar());
    if(input=='y'){
        TWO_PLAYER = true;
    }

}

void setup_game(){

    // enable_two_player();
    if(TWO_PLAYER){
        while(P1 == nullptr){
            P1 = select_character();
        }
        while(P2 == nullptr){
            P2 = select_character();
        }
        P1->select_moves();
        P2->select_moves();
    }else{
        while(P1 == nullptr){
            P1 = select_character();
        }
        P2 = get_computer_character();

        P1->select_moves();
        P2->choose_computer_attacks();
    }

}

void playerAttack(Character* player, Character* Other){
    player->attack(Other);
}
void computer_attack(Character* computer, Character* other){
    int move = random_int();
    computer->choose_computer_attacks();
}

int main(){
    enable_two_player();
    setup_game();
    system("clear");

    //main game loop
    bool P1turn = true;
    while(true){
        if(TWO_PLAYER){
            if(P1turn){
                //do something that allows player 1 to attack
                std::cout << "Player 1, it is your turn!\n";
                P1->attack(P2);
                P1turn = !P1turn;
            }else{
                //do something that allows player 2 to attack
                std::cout << "Player 2, it is your turn\n";
                P2->attack(P1);
                P1turn = !P1turn;

                P1->update_pp_on_turn();    
                P2->update_pp_on_turn();
            }
        }else{
            P1->attack(P2);
            P2->choose_computer_attacks();
        } 
    }

    return 0; 
}