//Name: Route.cpp
//Project: CMSC 202 Project 3, Spring 2022
//Author:  Jackson Keyser
//Date:   3/28/2022
//Desc: This file contains the header details for the Route class

#include "Route.h"

Route::Route(){
    // Default constructor for the route with default values
    m_name = "Test";
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

void Route::SetName(string name){
    // Sets the root name equal to the name the user has given
    m_name = name;
}

Route::~Route(){
    //cout << "Routes Destructor" << endl;
    // Creates dynamically allocated port. Sets it equal to the head
    Port *curr = m_head;
    // While we have yet to reach the end of the linked list
    while(curr != nullptr){
        // Sets the head to be curr
        m_head = curr;
        // Sets curr to be the next node
        curr = curr->GetNext();
        // Deletes the head node
        delete m_head;
    }
    // Sets the head and tail to be nullptr
    m_head = nullptr;
    m_tail = nullptr;
    // Sets the size to be 0
    m_size = 0;
}

void Route::InsertEnd(string portName, string portLocation, double degreesNorth, double degreesWest){
    // Creates a dynamically allocated port object for inserting at the end of the route
    Port *myPort = new Port(portName, portLocation, degreesNorth, degreesWest);
    // Sets the pointer to the next port on the route to be nullptr
    myPort->SetNext(nullptr);


    // If the linked list for the route is empty
    if(m_head == nullptr){
        // Sets the port to be the head of the route
        m_head = myPort;
    }
    // If the linked list for the route already has at least 1 port
    else{
        // Creates a temporary port for looping through all of the ports until the end is reached
        Port *tempPort = new Port();
        // Sets the temporary port to be the head of the route
        tempPort = m_head;

        // While we have yet to reach the end of the linked list
        while(tempPort->GetNext() != nullptr){
            // Sets the temporary port equal to the next port
            tempPort = tempPort->GetNext();
        }
        // When the end of the route is reached, sets the port to be last on the route
        tempPort->SetNext(myPort);
        // Sets the port to also be the tail of the route
        m_tail = myPort;
    }
    // Increments the size of the route by 1
    m_size++;
}

void Route::RemovePort(int port){
    // If the index is not possible
    if(port < 0 || port > (m_size-1)){
      cout << "That is not a possible port" << endl;
    // If the index is possible
    }else{
        // Creates 2 dynamically allocated port objects
        Port *curr = new Port();
        Port *prev = new Port();
        // Sets them both equal to the head
        curr = m_head;
        prev = m_head;
        // Creates and initializes an integer counter to keep track of our position in linked lsit
        int counter = 0;
        // So we do not go off the end
        while(curr != nullptr){
            // Where we remove the node. Only if it is not the fist node in the linked list
            if(counter == port && port != 0){
                // Sets the next node for prev to be the next node for curr, skipping the node that is curr
                prev->SetNext(curr->GetNext());
                // Removes the node
                delete curr;
                // If the port is last in the linked list
                if((port + 1) == m_size){
                    // Changes the value of the tail to be prev
                    m_tail = prev;
                }
                // Decements size by 1
                m_size--;
            }
            // If the first node in the linked list
            if(port == 0){
                // Sets the head to the next node
                m_head = m_head->GetNext();
                // Decrements size by 1
                m_size--;
                return;
            }
            // For looping through all of the nodes in the linked list
            prev = curr;
            curr = curr->GetNext();
            // Increments counter by 1
            counter++;
        }
    }
}

string Route::GetName(){
    // Returns the name of the route back to the user
    return m_name;
}

string Route::UpdateName(){
    // If there are no ports
    if(m_size == 0){
        m_name = "No Ports";
        return m_name;
    }
    // If there is 1 port
    if(m_size == 1){
        m_name = m_head->GetName();
        return m_name;
    }
    // Declares and initializes a string variable for the name of the route
    string routeName = "";
    // Gets the names of the first and last ports on the route
    routeName = m_head->GetName() + " to " + m_tail->GetName();
    
    m_name = routeName;

    return routeName;
}

int Route::GetSize(){
    return m_size;
}

void Route::ReverseRoute(){
    // Creates 3 dynamically allocated ports
    Port *curr = new Port();
    Port *prev = new Port();
    Port *next = new Port();

    // Sets curr to be the head, prev/next to be nullptr
    curr = m_head;
    prev = nullptr;
    next = nullptr;

    // While we have yet ro reach the tail of the linked list
    while (curr != nullptr) {
        // Stores next node
        next = curr->GetNext();
        // Reverses the current node's pointer
        curr->SetNext(prev);
        // Moves nodes one position ahead
        prev = curr;
        curr = next;
    }
    m_head = prev;


    // This is for changing the tail
    // Creates dynamically allocated port
    Port *temp = new Port();
    // Sets it to be the head
    temp = m_head;

    // While we have yet to reach the last value in the linked list
    while(temp->GetNext() != nullptr){
        // Sets temp to be the next value
        temp = temp->GetNext();
    }
    // Sets the tail to be temp
    m_tail = temp;


}

Port* Route::GetData(int index){
    // Declares and initializes a counter variable for keeping track where you are in the linked list
    int counter = 0;

    // Creates a dynamically allocated port object
    Port *tempPort = new Port();
    tempPort = m_head;

    // While we have not reached the end of the linked list
    while(tempPort != nullptr){
        // If you have reached the wanted index
        if(counter == index){
            // Returns that port object
            return tempPort;
        }

        tempPort = tempPort->GetNext();
        counter++;
    }
}

void Route::DisplayRoute(){
    // Declares and initializes a string variable for storing the name of the route
    string routeName = "";
    // Gets the name of the route
    routeName = GetName();
    // Prints out the name of the route
    cout << routeName << endl;
    // Declares and initializes a integer for keeping track of which port we are on when displaying them
    int counter = 1;

    // If the linked list is empty
    if(m_size == 0){
        cout << "This route is empty!" << endl;
    // If the linked list is not empty
    }else{
        // Creates a dynamically allocated port object 
        Port *tempPort = new Port();
        // Sets the temporary port to be the head
        tempPort = m_head;
        // While we have yet to reach the end of the linked list
        while(tempPort != nullptr){
            // Prints out all of the information about the port
            cout << counter << ". " << tempPort->GetName() << ", " << tempPort->GetLocation() << "(N" << tempPort->GetNorth() << " W" << tempPort->GetWest() << ")" << endl;
            // Goes to the next port
            tempPort = tempPort->GetNext();
            // Increments the counter by 1
            counter++;
        }
    }
}