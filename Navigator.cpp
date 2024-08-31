//Name: Navigator.cpp
//Project: CMSC 202 Project 3, Spring 2022
//Author:  Jackson Keyser
//Date:   3/28/2022
//Desc: This file contains the header details for the Navigator class


#include "Navigator.h"

#include <vector>
#include <string>


// Declares and initializes an integer constant for the amount of lines in the file being read in
const int FILE_SIZE = 36;
// Declares and initializes a constant for reading in the contents of the file
const char DELIMETER = ',';
// Declares and initializes constants for all of the possible user choices
const int USER_CHOICE_ONE = 1;
const int USER_CHOICE_TWO = 2;
const int USER_CHOICE_THREE = 3;
const int USER_CHOICE_FOUR = 4;
const int USER_CHOICE_FIVE = 5;
// Declares and initializes a constant integer for the number corresponding to the first possible port to be added...
// to the route...
const int FIRST_PORT_OPTION = 1;
// Declares and initializes a constant integer for exiting the port selection process when making a route
const int EXIT_PORT_SELECTION = -1;
// Declares and initializes a constant integer for the number corresponding to the first possible route
const int FIRST_ROUTE_OPTION = 1;

Navigator::Navigator(string fileName){
    // Stores the txt file into a string variable
    m_fileName = fileName;
    // Begins the program
    Start();
}

Navigator::~Navigator(){
    //cout << "Navigator Destructor" << endl;
    // Goes through both vectors, deletes contents and sets them to nullptr
    for(unsigned int i = 0; i < m_ports.size(); i++){
        delete m_ports[i];
        m_ports[i] = nullptr;
    }

    for(unsigned int i = 0; i < m_routes.size(); i++){
        delete m_routes[i];
        m_routes[i] = nullptr;
    }
}

void Navigator::Start(){
    //cout << "***Navigator***" << endl;
    cout << endl;

    ReadFile();

    MainMenu();
}

void Navigator::DisplayPorts(){
    // Creates dynamically allocated port object
    Port *myPort = new Port();

    // Loops through all port objects
    for (unsigned int i = 0; i < m_ports.size(); i++) {
        // Uses overloaded operator for each port
        myPort = m_ports.at(i);
        // Prints out each port
        cout << i+1 << ". " << *myPort << endl;
    }
}

void Navigator::ReadFile(){

    // Declares and initializes string variables for reading in different parts of the file
    string portName = "";
    string portLocation = "";
    string degreesNorth = "";
    string degreesWest = "";
    // Declares and initializes double variables for degrees North and degrees West
    double degreesNorthDouble = 0;
    double degreesWestDouble = 0;

    // Retrieves the file
    ifstream infile(m_fileName);

    // If the file is able to be opened
    if(infile.is_open()){
        // Lets the user know that the file was opened successfully
        cout << "Opened File" << endl;
        // Reads through each line of the file
        for(int i = 0; i < FILE_SIZE; i++){
            // Stores each part of each line into the correct variable
            getline(infile, portName, DELIMETER);
            getline(infile, portLocation, DELIMETER);
            getline(infile, degreesNorth, DELIMETER);
            getline(infile, degreesWest);

            // Casts the strings for degrees North and degrees West to doubles
            // Done this way because getline only works with strings
            degreesNorthDouble = stod(degreesNorth);
            degreesWestDouble = stod(degreesWest);

            // Dynamically allocates a port object using overloaded Port constructor
            Port *myPort = new Port(portName, portLocation, degreesNorthDouble, degreesWestDouble);

            // Adds port to array of ports
            m_ports.push_back(myPort);
        }
        // Lets the user know how many ports have been loaded in
        cout << "Ports loaded: " << FILE_SIZE << endl;
        // Closes the file
        infile.close();
    // If the file is not able to be opened
    }else{
        cout << "This file was unable to be opened" << endl;
    }


}

void Navigator::InsertNewRoute(){
    // Declares and inializes an integer variable for storing the user's choice
    int userChoice = 0;
    // Declares and initalizes a boolean variable for storing whether or not the user wants to...
    // stop adding ports to their roots...
    bool exitPortSelection = false;

    // Declares and initializes variables for storing the contents of the ports to be put into a linked list for the route
    string portName = "";
    string portLocation = "";
    double degreesNorth = 0;
    double degreesWest = 0;

    // Declares and initializes a route object for storing the ports
    Route *myRoute = new Route();

    // Displays all of the ports 
     DisplayPorts();

    
    do{
        // Asks the user which port they would like to add
        cout << "Enter the number of the port to add to your Route: (-1 to end)" << endl;
        // Obtains the user's choice
        cin >> userChoice;

        // If the user enters -1, will exit the route creation process
        if(userChoice == EXIT_PORT_SELECTION){
            // Updates the name of the root
            myRoute->UpdateName();
            // Adds the route to the vector or routes
            m_routes.push_back(myRoute);
            // Exits back to main menu
            exitPortSelection = true;
        }

        // If user choice is not one of the possible options
        while((userChoice < FIRST_PORT_OPTION && userChoice != EXIT_PORT_SELECTION) || userChoice > FILE_SIZE){
            cout << "That is not a possible route. Please enter a number between 1-36 (or -1 to end)" << endl;
            cin >> userChoice;
        }



        // If the user choice is between 1-36
        if(userChoice >= FIRST_PORT_OPTION && userChoice <= FILE_SIZE){
            // Gets all of the port information, stores in variables
            portName = m_ports[userChoice-1]->GetName();
            portLocation = m_ports[userChoice-1]->GetLocation();
            degreesNorth = m_ports[userChoice-1]->GetNorth();
            degreesWest = m_ports[userChoice-1]->GetWest();

            // Inserts port information into a link on the route
            myRoute->InsertEnd(portName, portLocation, degreesNorth, degreesWest);
        }


    }while(exitPortSelection == false);
}

void Navigator::MainMenu(){
    // Declares and initializes an integer variable for the user choice
    int userChoice = 0;
    // Declares and initializes a boolean variable for ending the program
    // If user selects the number 5, this will switch to true, ending the program
    bool programOver = false;

    // Runs the main menu loop
    do{
        // Lists choices and prompts the user to pick one
        cout << "What would you like to do?:" << endl;
        cout << "1. Create New Route" << endl;
        cout << "2. Display Route " << endl;
        cout << "3. Remove Port From Route" << endl;
        cout << "4. Reverse Route" << endl;
        cout << "5. Exit" << endl;
        // Obtains the choice of the user
        cin >> userChoice;

        // If user selection is out of the given range of 1-5
        while(userChoice < USER_CHOICE_ONE || userChoice > USER_CHOICE_FIVE){
            // Lets user know their selection was not an option
            cout << "That is not an option. Please pick a number 1-5" << endl;
            cout << "What would you like to do?:" << endl;
            cout << "1. Create New Route" << endl;
            cout << "2. Display Route " << endl;
            cout << "3. Remove Port From Route" << endl;
            cout << "4. Reverse Route" << endl;
            cout << "5. Exit" << endl;
            // Obtains the choice of the user
            cin >> userChoice;
        }

        if(userChoice == USER_CHOICE_ONE){
            InsertNewRoute();
        }
        if(userChoice == USER_CHOICE_TWO){
            DisplayRoute();
        }
        if(userChoice == USER_CHOICE_THREE){
            RemovePortFromRoute();
        }
        if(userChoice == USER_CHOICE_FOUR){
            ReverseRoute();
        }
        if(userChoice == USER_CHOICE_FIVE){
            cout << "Routes removed from memory" << endl;
            cout << "Deleting Ports" << endl;
            cout << "Deleting Routes" << endl;
            // Sets the boolean to true, ends the program
            programOver = true;
        }
    // While the user has yet to hit option number 5
    }while(programOver == false);
}

int Navigator::ChooseRoute(){
    // Declares and initializes an integer variable for storing user input
    int userInput = 0;

    // If there are no routes
    if(m_routes.size() == 0){
        cout << "There are no routes currently" << endl;
        return -1;
    }else{
        cout << "Which route would you like to use?" << endl;

        for(unsigned int i = 0; i < m_routes.size(); i++){
            cout << i+1 << ". " << m_routes[i]->GetName() << endl;
        }
        cin >> userInput;

        // While the input selected input is not possible
        while(userInput < FIRST_ROUTE_OPTION || userInput > int(m_routes.size())){
            cout << "Not a possible route. Please try again." << endl;
            cin >> userInput;
        }

        // Substracts 1 as the vector begins at 0
        userInput = userInput - 1;
        return userInput;
    }
}

void Navigator::DisplayRoute(){
    // Declares and initializes an integer variable for storing user input
    int userInput = 0;

    // Uses ChooseRoute function to get the index position of the route the user wants to display
    userInput = ChooseRoute();

    // If there is at least 1 route to display
    if(userInput != -1){
        // Displays the route
        m_routes[userInput]->DisplayRoute();

        // Declares and initializes a double variable for storing the distance of the route
        double routeDistance = 0;
        // Uses function to calculate the distance of the route
        routeDistance = RouteDistance(m_routes[userInput]);
        cout << "The total miles of this route is " << routeDistance << " miles" << endl;
    }
}

void Navigator::RemovePortFromRoute(){
    // Declares and initializes an integer variable for storing user input
    int userInput = 0;
    // Declares and initializes an integer variable fo storing the index of the route the user wants to remove
    int routeIndexRemoved = 0;
    // Declares and initializes a string vaiable for the name of the route
    string routeName = "";

    // Uses ChooseRoute function to get the index position of the route the user wants to display
    userInput = ChooseRoute();

    // If there is at least 1 route to display
    if(userInput != -1){
        // Displays the route
        m_routes[userInput]->DisplayRoute();
        // If there are no ports on the route.
        if(m_routes[userInput]->GetSize() == 0){
            cout << "There are no ports. Cannot remove." << endl;
        // If there is at least 1 port on the route
        }else{
        cout << "Which port would you like to remove?" << endl;
        cin >> routeIndexRemoved;
        }

        // If at least 1 port to remove
        if(m_routes[userInput]->GetSize() != 0){
        // Removes the port
        m_routes[userInput]->RemovePort(routeIndexRemoved-1);

        // Displays the new route with the port removed
        m_routes[userInput]->DisplayRoute();

        cout << "The New Route Name is: " << endl;
        routeName = m_routes[userInput]->UpdateName();
        cout << routeName << endl;
        }

    }
}

double Navigator::RouteDistance(Route* theRoute){
    // Creates 2 dynamically allocated port object
    Port *tempPort = new Port();
    Port *tempPort2 = new Port();

    // Declares and intializes a double variable for keeping track of the distance of the route
    double totalDistance = 0;

    // Loops though all of the ports on the route
    for(int i = 0; i < (theRoute->GetSize()-1); i++){
        // Sets the temporary ports to be the ports in the route at the given indexes
        tempPort = theRoute->GetData(i);
        tempPort2 = theRoute->GetData(i+1);

        // Adds the distance between the 2 ports to the total distance
        totalDistance = totalDistance + CalcDistance(tempPort->GetNorth(), tempPort->GetWest(), tempPort2->GetNorth(), tempPort2->GetWest());
        //cout << "DISTANCE " << totalDistance << endl;
    }

    return totalDistance;
}

void Navigator::ReverseRoute(){
    // Declares and initializes an integer variable for storing user input
    int userInput = 0;

    // Uses ChooseRoute function to get the index position of the route the user wants to display
    userInput = ChooseRoute();

    // If there is at least 1 route to display
    if(userInput != -1){
        m_routes[userInput]->ReverseRoute();

        cout << "Done reversing route " << userInput << endl;

        m_routes[userInput]->UpdateName();
    }
}