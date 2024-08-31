//Name: proj3.cpp
//Project: CMSC 202 Project 3, Spring 2022
//Author:  Jackson Keyser
//Date:   3/28/2022
//Desc: This file contains the header details for the proj3 class


//#include "Navigator.h"
#include "Navigator.cpp"
#include "Route.cpp"
#include "Port.cpp"
#include <iostream>
using namespace std;


/*
int main (int argc, char* argv[]) {
  if (argc < 2)
    {
      cout << "You are missing a data file." << endl;
      cout << "Expected usage ./proj3 proj3_data.txt" << endl;
      cout << "File 1 should be a file with ports" << endl;
    }
  else
    {
      cout << endl << "***Navigator***" << endl << endl;
      Navigator S = Navigator(argv[1]);
      S.Start();
    }
  return 0;
}
*/



int main () {
    //Sequencer sequence("proj3_case4.txt");

    Navigator myNavigator("proj3_data.txt");
      
    return 0;
}
