#include<iostream>
#include<vector>
#include "hangman_function.h"
using namespace std;

//define functions
void greet(){
  cout << "=======================" << endl;
  cout << "Welcome to Hangman Game" << endl;
  cout << "=======================" << endl;
  cout << "Instructions: Save your friend from being hanged by guessing the letters in the codeword" << endl;
  cout << "Enter 'hint' for a hint. Each hint costs 10 points." << endl;
  cout << "You have 50 points to start." << endl;
  cout << "Press 'q' to quit at any time." << endl;
}

void display_misses(int misses){
  if (misses==0){
    cout << "  +---+ \n";
    cout << "  |   | \n";
    cout << "      | \n";
  }
  else if (misses==1){
    cout << "  +---+ \n";
    cout << "  |   | \n";
    cout << "  O   | \n";
    cout << "      | \n";
  }
  else if (misses==2){
    cout << "  +---+ \n";
    cout << "  |   | \n";
    cout << "  O   | \n";
    cout << "  |   | \n";
    cout << "      | \n";
  }
  else if (misses==3){
    cout << "  +---+ \n";
    cout << "  |   | \n";
    cout << "  O   | \n";
    cout << " /|   | \n";
    cout << "      | \n";
  }
  else if (misses==4){
    cout << "  +---+ \n";
    cout << "  |   | \n";
    cout << "  O   | \n";
    cout << " /|\\  | \n";
    cout << "      | \n";
  }
  else if (misses==5){
    cout << "  +---+ \n";
    cout << "  |   | \n";
    cout << "  O   | \n";
    cout << " /|\\  | \n";
    cout << " /     | \n";
    cout << "      | \n";
  }
  else if (misses==6){
    cout << "  +---+ \n";
    cout << "  |   | \n";
    cout << "  O   | \n";
    cout << " /|\\  | \n";
    cout << " / \\  | \n";
    cout << "      | \n";
  }
}

void display_status(vector<char> incorrect, string answer){
  cout << "Incorrect guesses: ";
  for (char c : incorrect){
    cout << c << " ";
  }
  cout << endl;
  cout << "Current answer: " << answer << endl;
}

void end_game(string answer, string codeword){
  if(answer==codeword){
    cout << "Congratulations! You've won!" << endl;
  }
  else{
    cout << "Game over! The codeword was: " << codeword << endl;
  }
}