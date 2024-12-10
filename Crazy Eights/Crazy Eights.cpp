#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "template/Deck.h"
#include "template/Player.h"
#include "template/Card.h"

using namespace std;

/**
* Simulates a player's turn, including handling input & output to terminal.
*/
void simulateTurn(Player& currPlayer, Deck& mainDeck, Deck& discardDeck);
/**
* Clears the current output screen.
*/
void clearScreen();
/**
* Pause in execution for given seconds.
*/
void delay(int seconds);



int main()
{
    Deck stock = Deck();
    Deck starter = Deck();
    starter.clear();
    stock.shuffle();

    Player player1 = Player();
    Player player2 = Player();

    string name;
    cout << "What is your name p1?: ";
    cin >> name;
    player1.setName(name);

    cout << "What is your name p2?: ";
    cin >> name;
    player2.setName(name);

    //Deal 5 cards to each player
    for (int i = 0; i < 5; i++) {
        player1.addCard(stock.getTopCard());
        player2.addCard(stock.getTopCard());
    }
    
    starter.addCard(stock.getTopCard());    //Turn over top card to start game.

    //Main game loop
    while (player1.getHandSize() > 0 && player2.getHandSize() > 0) {
        clearScreen();
        simulateTurn(player1, stock, starter);
        if (player1.getHandSize() == 0) {
            cout << "Player " << player1.getName() <<" Wins!" << endl;
            break;
        }
        delay(1);


        clearScreen();
        simulateTurn(player2, stock, starter);
        if (player2.getHandSize() == 0) {
            cout << "Player " << player2.getName() << " Wins!" << endl;
            break;
        }
        delay(1);
    }
}





void delay(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}


void clearScreen() {
    cout << "\033[2J\033[1;1H";
}


void simulateTurn(Player& currPlayer, Deck& mainDeck, Deck& starterDeck) {
    int playerChoice; //Declaring variables to be used later (e.g., for user input).

    cout << "--------------- NEW GO -----------------" << endl;
    cout << "The top card is: " << starterDeck.peekTopCard().toString() << endl;
    cout << "----------------------------------------" << endl;
    cout << "Player " << currPlayer.getName() << "'s hand is: " << endl;

    for (int i = 0; i < currPlayer.getHandSize(); i++) {        //Output player's cards one at a time
        cout << "  " << i << ". " << currPlayer.peekCard(i).toString() << endl;
    }
    int drawCardOption = currPlayer.getHandSize();
    cout << "  " << drawCardOption << ". Draw New Card.\n" << endl;

    cout << "Which card would you like to lay? Type the number corresponding to a card or to pick up." << endl;
    cout << ">>>";
    cin >> playerChoice;


    //Handly player input
    if (playerChoice == drawCardOption && mainDeck.isEmpty() == false) {    //If the player chooses to draw a card and deck isn't empty
        Card newCard = mainDeck.getTopCard();
        cout << "Your new card is: " << newCard.toString() << endl;
        currPlayer.addCard(newCard);
    }
    else if (playerChoice == drawCardOption && mainDeck.isEmpty() == true) {    //If the player chooses to draw a card and deck IS empty
        cout << "You cannot pick up, the stock is empty." << endl;
    }
    else {                                                                  //Play a card
        Card chosenCard = currPlayer.getCard(playerChoice);
        starterDeck.addCard(chosenCard);
    }
}