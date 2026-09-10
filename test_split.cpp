/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ split.cpp test_split.cpp -o test_split
*/

#include "split.h"
#include <iostream>


Node* buildList(int values[], int size){
    Node* head = nullptr; 
    Node *tail = nullptr; 
    for(int i = 0; i < size; i++){
        Node* n = new Node(values[i], nullptr);

        if(head == nullptr){
            head = n; 
        } else {
            tail->next = n; 
        }
        tail = n; 
    }
    return head; 
}

void print(){
    for(Node* p = head; p!= nullptr; p = p->next){
        cout << p->value << " "; 
    }
    cout << endl; 

}



int main(int argc, char* argv[])
{

    int values[] = {1, 2, 3, 4, 5};
    Node* in = buildList(values, 5);

    Node* odds = nullptr; 
    Node* evens = nullptr; 

    split(in, odds, evens); 

    cout << "odds: ";
    printList(odds); 

    cout << "evens: ";
    printList(evens); 

    cout << "in should be null: "<< (in == nullptr ? "yes" : "no") << endl;
    
    return 0; 
}
