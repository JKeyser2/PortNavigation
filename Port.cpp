//Name: Port.cpp
//Project: CMSC 202 Project 3, Spring 2022
//Author:  Jackson Keyser
//Date:   3/28/2022
//Desc: This file contains the header details for the Port class


#include "Port.h"

Port::Port(){
    // Default constructor with default values
    m_name = "New Port";
    m_location = "New Location";
    m_north = 0;
    m_west = 0;
    m_next = nullptr;
}

Port::Port(string portName, string portLocation, double degreesNorth, double degreesWest){
    // Overloaded constructor with values given from the file being read in
    m_name = portName;
    m_location = portLocation;
    m_north = degreesNorth;
    m_west = degreesWest;
}

Port::~Port(){
    //cout << "Ports Destructor" << endl;
    // Clears all values, sets m_next pointer to be nullptr
    m_name = "";
    m_location = "";
    m_north = 0;
    m_west = 0;
    m_next = nullptr;
}

string Port::GetName(){
    // Getter for name of the port
    return m_name;
}

Port* Port::GetNext(){
    // Getter for returning the pointer to the next port
    return m_next;
}

double Port::GetNorth(){
    // Getter for degrees North the port is 
    return m_north;
}

double Port::GetWest(){
    // Getter for degrees West the port is
    return m_west;
}

string Port::GetLocation(){
    // Getter for location of the port
    return m_location;
}

void Port::SetNext(Port* nextPort){
    // Sets the pointer to the next port
    m_next = nextPort;
}

