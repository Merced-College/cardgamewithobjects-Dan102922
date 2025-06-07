// Daniel Mota
//06.06.2025
//This program is basically a simplified blackjack program, where the player starts with a certain set of cards and has to
//stand with more than the dealer, if the player goes over 21, they bust and the dealer wins, and vice versa

#include <iostream>
using namespace std;

class Card { // Keeps a card object
public:

Card(string argSuit = "", string argRank = "", int argValue = 0) {
        suit = argSuit;
        rank = argRank;
        value = argValue;
}

  int get_value() { return value; }
void print_card() { // prints the rank and suit of card when told to
        cout << rank << " of " << suit << endl;
    }
private:

string suit, rank;
int value;
};

//the rest of the code:
const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3",  "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
const int VALUES[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

Card deck[52];
int currentCardIndex = 0;
/*
defines the arrays and variables related to a deck of playing cards through the
suits, ranks, the current card index, and the deck itself.
*/

void initializeDeck() {
  int deckIndex = 0;
  for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
    for (int rankIndex = 0; rankIndex < 13; rankIndex++) {
      // Card(string suit, string rank, int value);
      deck[deckIndex++] =
          Card(SUITS[suitIndex], RANKS[rankIndex], VALUES[rankIndex]);
    }
  }
}

void printDeck() {
  for (int i = 0; i < 52; i++)
    deck[i].print_card();
}

void shuffleDeck() {
  srand((time(0)));
  for (int i = 0; i < 52; i++) {
    int index = rand() % 52;
    Card temp = deck[i]; // these next three lines are a swap function
    deck[i] = deck[index];
    deck[index] = temp;
  }
}

Card dealCard() { 
  return deck[currentCardIndex++]; 
}

int dealInitialPlayerCards() {
  Card card1 = dealCard();
  Card card2 = dealCard();
  cout << "Your cards: ";
  card1.print_card();
  card2.print_card();

  return card1.get_value() + card2.get_value();
}

int dealInitialDealerCards() { //This was added to give the dealer's starting card, as the dealer didn't do anything before and only won when the player busted
  Card card1 = dealCard();
  int dealerTotal = card1.get_value();
  cout << "Dealer's card: ";
  card1.print_card();
  return dealerTotal;
}

int playerTurn(int playerTotal) { //Handles the player's turn, lets them hit or stand, and ensures that they don't enter any other input
  while (true) {
    cout << "Your total is " << playerTotal << ". Do you want to hit or stand?"
         << endl;
    string action;
    getline(cin, action);
    if (action == "hit") {
      Card newCard = dealCard();
      playerTotal += newCard.get_value();
      cout << "You drew a ";
      newCard.print_card();
      if (playerTotal > 21) {
        break;
      }
    } else if (action == "stand") {
      break;
    } else {
      cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
    }
  }
  return playerTotal;
}


int dealerTurn(int dealerTotal) { //This was added to allow the dealer to act, and to stick when the total is above 18
    while (dealerTotal < 18) {
        Card newCard = dealCard();
        cout << "Dealer draws: ";
        newCard.print_card();
        dealerTotal += newCard.get_value();
    }
    return dealerTotal;
  }

int main() {
  initializeDeck();
  shuffleDeck();

  int playerTotal = dealInitialPlayerCards();
  int dealerTotal = dealInitialDealerCards(); // Added so dealer has an initial card
  
  cout << "The playerTotal is " << playerTotal << endl;

  playerTotal = playerTurn(playerTotal); //Added some win/lose conditions so the player can, well, win/lose
  if (playerTotal > 21) {
    cout << "You busted! Dealer wins." << endl;
  } else {
      dealerTotal = dealerTurn(dealerTotal);
      cout << "Dealer's total: " << dealerTotal << endl;
      
      if (dealerTotal > 21) {
          cout << "Dealer busted, you win!" << endl;
      } else if (dealerTotal > playerTotal) {
          cout << "Dealer wins." << endl;
       } else if (dealerTotal < playerTotal) {
          cout << "You win!" << endl;
      } else {
          cout << "It's a draw." << endl;
      }
  }
  return 0;
}
