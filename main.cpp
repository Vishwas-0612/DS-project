#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <limits>
#include <algorithm>
using namespace std;

// Structure to store transport details
struct Transport
{
    int number;
    string name;
    string source;
    string destination;
    string departure_time;
    string arrival_time;
    double price;
    int seats_left;
    Transport *next; // For linked list
};

// Binary Search Tree node for transport data
struct BSTNode
{
    Transport *transport;
    BSTNode *left;
    BSTNode *right;

    BSTNode(Transport *transport) : transport(transport), left(nullptr), right(nullptr) {}
};

// Linked List for storing transports
class TransportList
{
public:
    Transport *head;

    TransportList()
    {
        head = nullptr;
    }

    // Add transport data to the list
    void addTransport(int number, string name, string source, string destination, string departure_time, string arrival_time, double price, int seats_left)
    {
        Transport *newTransport = new Transport{number, name, source, destination, departure_time, arrival_time, price, seats_left, nullptr};
        if (!head)
        {
            head = newTransport;
        }
        else
        {
            Transport *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newTransport;
        }
    }

    // Display all transport data
    void displayAllTransports()
    {
        Transport *temp = head;
        while (temp)
        {
            cout << "Transport Number: " << temp->number << endl;
            cout << "Name: " << temp->name << ", Source: " << temp->source << ", Destination: " << temp->destination << endl;
            cout << "Departure: " << temp->departure_time << ", Arrival: " << temp->arrival_time << endl;
            cout << "Price: " << temp->price << ", Seats Left: " << temp->seats_left << endl;
            cout << "---------------------------------" << endl;
            temp = temp->next;
        }
    }

    // Update the seats left after booking
    void updateSeats(int transportNumber, int bookedSeats)
    {
        Transport *temp = head;
        while (temp)
        {
            if (temp->number == transportNumber)
            {
                temp->seats_left -= bookedSeats;
                break;
            }
            temp = temp->next;
        }
    }

    // // Function to search for transport by source and destination (using binary search)
    // Transport *searchBySourceDestination(string source, string destination)
    // {
    //     BSTNode *bstRoot = nullptr;
    //     // First build a BST from the linked list
    //     buildBSTFromLinkedList(bstRoot, head);

    //     // Now search for the transport by source and destination in the BST
    //     return searchBST(bstRoot, source, destination);
    // }

    // Function to search transport by source and destination, using the BST
    // Transport *searchBySourceDestination(string source, string destination)
    // {
    //     BSTNode *bstRoot = nullptr;
    //     // First, build the BST from the linked list
    //     buildBSTFromLinkedList(bstRoot, head);

    //     // Then, search for the transport in the BST
    //     return searchBST(bstRoot, source, destination);
    // }

    void searchBySourceDestination(string source, string destination)
    {
        if (!source.empty())
        {
            // Make the first character uppercase
            source[0] = toupper(source[0]);
        }
        if (!destination.empty())
        {
            // Make the first character uppercase
            destination[0] = toupper(destination[0]);
        }
        Transport *temp = head;
        bool found = false;

        // Iterate through the linked list and print all matching transports
        while (temp)
        {
            if (temp->source == source && temp->destination == destination)
            {
                found = true;
                // Display transport details
                cout << "Transport Number: " << temp->number << endl;
                cout << "Transport Name: " << temp->name << endl;
                cout << "Source: " << temp->source << ", Destination: " << temp->destination << endl;
                cout << "Departure Time: " << temp->departure_time << ", Arrival Time: " << temp->arrival_time << endl;
                cout << "Price: " << temp->price << ", Seats Left: " << temp->seats_left << endl;
                cout << "---------------------------------------------" << endl;
            }
            temp = temp->next;
        }

        if (!found)
        {
            cout << "No transport found for the specified route!" << endl;
        }
    }
    // Transport *searchBySourceDestination(string source, string destination)
    // {
    //     Transport *temp = head;
    //     while (temp)
    //     {
    //         if (temp->source == source && temp->destination == destination)
    //         {
    //             return temp;
    //         }
    //         temp = temp->next;
    //     }
    //     return nullptr; // No match found
    // }
    // Function to build a BST from the linked list
    void buildBSTFromLinkedList(BSTNode *&root, Transport *head)
    {
        Transport *temp = head;
        while (temp)
        {
            BSTNode *newNode = new BSTNode(temp);
            insertBST(root, newNode);
            temp = temp->next;
        }
    }

    // // Function to insert a node into the BST
    // void insertBST(BSTNode *&root, BSTNode *newNode)
    // {
    //     if (!root)
    //     {
    //         root = newNode;
    //     }
    //     else if (newNode->transport->source < root->transport->source)
    //     {
    //         insertBST(root->left, newNode);
    //     }
    //     else
    //     {
    //         insertBST(root->right, newNode);
    //     }
    // }

    // Function to build the BST with comparison based on both source and destination
    void insertBST(BSTNode *&root, BSTNode *newNode)
    {
        if (!root)
        {
            root = newNode;
        }
        else
        {
            // Compare both source and destination for sorting order in the tree
            string source_dest_current = root->transport->source + root->transport->destination;
            string source_dest_new = newNode->transport->source + newNode->transport->destination;

            if (source_dest_new < source_dest_current)
            {
                insertBST(root->left, newNode);
            }
            else
            {
                insertBST(root->right, newNode);
            }
        }
    }

    // // Function to search the BST by source and destination
    // Transport *searchBST(BSTNode *root, string source, string destination)
    // {
    //     if (!root)
    //     {
    //         return nullptr;
    //     }
    //     if (root->transport->source == source && root->transport->destination == destination)
    //     {
    //         return root->transport;
    //     }
    //     if (source < root->transport->source)
    //     {
    //         return searchBST(root->left, source, destination);
    //     }
    //     return searchBST(root->right, source, destination);
    // }

    // Function to search the BST by source and destination
    Transport *searchBST(BSTNode *root, string source, string destination)
    {
        if (!root)
        {
            return nullptr;
        }

        // Compare the source and destination fields
        if (root->transport->source == source && root->transport->destination == destination)
        {
            return root->transport;
        }

        string source_dest_current = root->transport->source + root->transport->destination;
        string source_dest_query = source + destination;

        // Search the left or right subtree based on the combined source and destination string
        if (source_dest_query < source_dest_current)
        {
            return searchBST(root->left, source, destination);
        }
        else
        {
            return searchBST(root->right, source, destination);
        }
    }
    void displayTicket(string username, Transport *transport, int seats_booked)
    {
        // Get the current date and time
        time_t t = time(0);
        struct tm *now = localtime(&t);

        cout << "=================== TICKET =====================" << endl;
        cout << "Username: " << username << endl;
        cout << "Transport Number: " << transport->number << endl;
        cout << "Transport Name: " << transport->name << endl;
        cout << "Source: " << transport->source << ", Destination: " << transport->destination << endl;
        cout << "Departure Time: " << transport->departure_time << ", Arrival Time: " << transport->arrival_time << endl;
        cout << "Seats Booked: " << seats_booked << ", Total Price: " << seats_booked * transport->price << endl;
        cout << "Booking Date: " << asctime(now);
        cout << "=============================================" << endl;
    }
};

// Function to display current date and time for the ticket
string currentDateTime()
{
    time_t now = time(0);
    char *dt = ctime(&now);
    return string(dt);
}

// Function to handle user login or account creation
bool userLogin(string username)
{
    string password;
    cout << "Enter Password: ";
    cin >> password;

    // Check if user exists in the file
    ifstream userFile("user.txt");
    string line;
    while (getline(userFile, line))
    {
        stringstream ss(line);
        string fileUsername, filePassword;
        ss >> fileUsername >> filePassword;
        if (fileUsername == username && filePassword == password)
        {
            cout << "Login Successful!" << endl;
            return true;
        }
    }
    cout << "Invalid credentials. Do you want to create a new account? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y')
    {
        ofstream userFileOut("user.txt", ios::app);
        userFileOut << username << " " << password << endl;
        cout << "Account created successfully!" << endl;
        return true;
    }
    return false;
}

// Function to display a ticket
void printTicket(string username, int transportNumber, int bookedSeats, Transport *transport)
{
    cout << "\n=================== TICKET =====================" << endl;
    cout << "Username: " << username << endl;
    cout << "Transport Number: " << transport->number << endl;
    cout << "Transport Name: " << transport->name << endl;
    cout << "Source: " << transport->source << ", Destination: " << transport->destination << endl;
    cout << "Departure Time: " << transport->departure_time << ", Arrival Time: " << transport->arrival_time << endl;
    cout << "Seats Booked: " << bookedSeats << ", Total Price: " << transport->price * bookedSeats << endl;
    cout << "Booking Date: " << currentDateTime() << endl;
    cout << "=================================================" << endl;
}

// Main ticket booking system
int main()
{
    // Login process
    string username;
    cout << "Enter Username: ";
    cin >> username;
    if (!userLogin(username))
    {
        cout << "Login Failed! Exiting the system." << endl;
        return 0;
    }

    // Load transport data from file (train.txt, plane.txt, bus.txt)
    TransportList transportList;
label1:
    int choice;
    cout << "Choose the mode of transport" << endl;
    cout << "1) To book train ticket" << endl;
    cout << "2) To book bus ticket" << endl;
    cout << "3) To book plane ticket" << endl;
    cout << "4) To exit" << endl;
    cout << "Enter your choice:-";
    cin >> choice;

    // Declare common variables here
    int number;
    string name, source, destination, departure_time, arrival_time;
    double price;
    int seats_left;

    switch (choice)
    {
    case 1:
    {
        ifstream trainFile("train.txt");
        if (!trainFile)
        {
            cout << "Error opening train.txt file." << endl;
            break;
        }
        while (trainFile >> number >> ws && getline(trainFile, name) && getline(trainFile, source) &&
               getline(trainFile, destination) && getline(trainFile, departure_time) &&
               getline(trainFile, arrival_time) && trainFile >> price >> seats_left)
        {
            transportList.addTransport(number, name, source, destination, departure_time, arrival_time, price, seats_left);
        }
        trainFile.close();
        break;
    }

    case 2:
    {
        ifstream busFile("bus.txt");
        if (!busFile)
        {
            cout << "Error opening bus.txt file." << endl;
            break;
        }
        while (busFile >> number >> ws && getline(busFile, name) && getline(busFile, source) &&
               getline(busFile, destination) && getline(busFile, departure_time) &&
               getline(busFile, arrival_time) && busFile >> price >> seats_left)
        {
            transportList.addTransport(number, name, source, destination, departure_time, arrival_time, price, seats_left);
        }
        busFile.close();
        break;
    }

    case 3:
    {
        ifstream planeFile("plane.txt");
        if (!planeFile)
        {
            cout << "Error opening plane.txt file." << endl;
            break;
        }
        while (planeFile >> number >> ws && getline(planeFile, name) && getline(planeFile, source) &&
               getline(planeFile, destination) && getline(planeFile, departure_time) &&
               getline(planeFile, arrival_time) && planeFile >> price >> seats_left)
        {
            transportList.addTransport(number, name, source, destination, departure_time, arrival_time, price, seats_left);
        }
        planeFile.close();
        break;
    }

    case 4:
        cout << "Thanks for Visiting." << endl;
        exit(0); // Exit the program
        break;

    default:
        cout << "Incorrect choice" << endl;
        break;
    }

    // Display available transports
    transportList.displayAllTransports();

    // Book a ticket
    cout << "Enter Source (e.g., Delhi): ";
    string sourceQuery;
    cin >> sourceQuery;
    cout << "Enter Destination (e.g., Mumbai): ";
    string destinationQuery;
    cin >> destinationQuery;

    // Search the transport via BST for the source and destination
    // Transport *selectedTransport = transportList.searchBySourceDestination(sourceQuery, destinationQuery);
    // if (selectedTransport)
    // {
    //     cout << "Transport Found!" << endl;
    //     cout << "Transport Number: " << selectedTransport->number << endl;
    //     cout << "Name: " << selectedTransport->name << ", Source: " << selectedTransport->source << ", Destination: " << selectedTransport->destination << endl;
    //     cout << "Departure: " << selectedTransport->departure_time << ", Arrival: " << selectedTransport->arrival_time << endl;
    //     cout << "Price: " << selectedTransport->price << ", Seats Left: " << selectedTransport->seats_left << endl;

    //     cout << "Enter number of seats to book: ";
    //     int bookedSeats;
    //     cin >> bookedSeats;
    //     // Book seats and update transport data
    //     if (bookedSeats <= selectedTransport->seats_left)
    //     {
    //         // Update the seats left
    //         transportList.updateSeats(selectedTransport->number, bookedSeats);
    //         cout << "Booking Successful!" << endl;

    //         // Print the ticket
    //         string username = "User"; // Assume the username is obtained from the login process
    //         printTicket(username, selectedTransport->number, bookedSeats, selectedTransport);
    //     }
    //     else
    //     {
    //         cout << "Sorry, not enough seats available!" << endl;
    //     }
    // }
    // else
    // {
    //     cout << "No transport found for the specified route!" << endl;
    // }

    // // Save updated transport data back to file (train.txt, plane.txt, bus.txt)
    // ofstream trainFileOut("train.txt");
    // Transport *temp = transportList.head;
    // while (temp)
    // {
    //     trainFileOut << temp->number << endl;
    //     trainFileOut << temp->name << endl;
    //     trainFileOut << temp->source << endl;
    //     trainFileOut << temp->destination << endl;
    //     trainFileOut << temp->departure_time << endl;
    //     trainFileOut << temp->arrival_time << endl;
    //     trainFileOut << temp->price << endl;
    //     trainFileOut << temp->seats_left << endl;
    //     temp = temp->next;
    // }

    transportList.searchBySourceDestination(sourceQuery, destinationQuery);

    int transport_number, seats_booked;
    cout << "Enter the transport number to book: ";
    cin >> transport_number;
    cout << "Enter number of seats to book: ";
    cin >> seats_booked;

    Transport *transport = transportList.head;
    bool transport_found = false;

    if (!transport)
    {
        cout << "No transport found for the specified route!" << endl;
        exit(0);
    }
    while (transport)
    {
        if (transport->number == transport_number)
        {
            transport_found = true;
            if (seats_booked <= transport->seats_left)
            {
                transport->seats_left -= seats_booked;
                string username;
                cout << "Enter passenger name: ";
                cin >> username;

                transportList.displayTicket(username, transport, seats_booked);
            }
            else
            {
                cout << "Not enough seats available!" << endl;
            }
            break;
        }
        transport = transport->next;
    }

    if (!transport_found)
    {
        cout << "Invalid transport number!" << endl;
    }
    // Save updated transport data back to file (train.txt, plane.txt, bus.txt)
    ofstream trainFileOut("train.txt");
    Transport *temp_train = transportList.head;
    while (temp_train)
    {
        trainFileOut << temp_train->number << endl;
        trainFileOut << temp_train->name << endl;
        trainFileOut << temp_train->source << endl;
        trainFileOut << temp_train->destination << endl;
        trainFileOut << temp_train->departure_time << endl;
        trainFileOut << temp_train->arrival_time << endl;
        trainFileOut << temp_train->price << endl;
        trainFileOut << temp_train->seats_left << endl;
        temp_train = temp_train->next;
    }
    trainFileOut.close();

    ofstream planeFileOut("plane.txt");
    Transport *temp_plane = transportList.head;
    while (temp_plane)
    {

        planeFileOut << temp_plane->number << endl;
        planeFileOut << temp_plane->name << endl;
        planeFileOut << temp_plane->source << endl;
        planeFileOut << temp_plane->destination << endl;
        planeFileOut << temp_plane->departure_time << endl;
        planeFileOut << temp_plane->arrival_time << endl;
        planeFileOut << temp_plane->price << endl;
        planeFileOut << temp_plane->seats_left << endl;
        temp_plane = temp_plane->next;
    }
    planeFileOut.close();
    ofstream busFileOut("bus.txt");
    Transport *temp_bus = transportList.head;
    while (temp_bus)
    {
        busFileOut << temp_bus->number << endl;
        busFileOut << temp_bus->name << endl;
        busFileOut << temp_bus->source << endl;
        busFileOut << temp_bus->destination << endl;
        busFileOut << temp_bus->departure_time << endl;
        busFileOut << temp_bus->arrival_time << endl;
        busFileOut << temp_bus->price << endl;
        busFileOut << temp_bus->seats_left << endl;
        temp_bus = temp_bus->next;
    }
    busFileOut.close();

    // here write code for dialog box for do you want to book another ticket
    return 0;
}
/*Train Number
Train Name
Source
Destination
Departure Time
Arrival Time
Price per seat
Number of seats left*/