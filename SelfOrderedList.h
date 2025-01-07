
#ifndef SELF_ORDERED_LIST_H
#define SELF_ORDERED_LIST_H

#include "SelfOrderedListADT.h"
#include <fstream>
#include <string>
#include <iostream>

// Concrete class derived from SelfOrderedListADT
template <typename E>
class SelfOrderedList : public SelfOrderedListADT<E> {
private:
    template <typename E>
    struct Link {
        E element;
        Link* next;
        int count;  // To track frequency of accesses

        Link(const E& e = E(), Link* n = nullptr) : element(e), next(n), count(0) {}
    };
    Link<E>* head;  // Points to the first node
    Link<E>* tail;  // Points to the last node
    int compareCount;  // Tracks the number of comparisons
    int listSize;  // Tracks the size of the list

public:
    SelfOrderedList() {
        head = tail = new Link<E>;  // Dummy node to make list management easier
        compareCount = 0;
        listSize = 0;
    }

    ~SelfOrderedList() {
        // Clean up memory
        Link<E>* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool find(const E& it) override {
        Link<E>* current = head->next;  // Skip dummy node

        while (current != nullptr) { // Search for the element
            compareCount++;  // Increment comparison count
            if (current->element == it) {
                current->count++;  // Increment frequency count
                return true;  // Element found
            }
            current = current->next;
        }
        // If the element was not found, add it to the list
        add(it);
        return false;  // Element not found
    }
    void clear() {
        Link<E>* current = head->next;  // Skip the dummy node
        Link<E>* temp;

        // Traverse the list and delete each node
        while (current != nullptr) {
            temp = current;
            current = current->next;
            delete temp;  // Deallocate memory for the current node
        }

        head->next = nullptr;  // Reset head to point to nothing (empty list)
        tail = head;           // Reset tail to head, indicating an empty list
        listSize = 0;          // Reset the size of the list
        compareCount = 0;      // Reset comparisons count
    }

    // Find the word specifically for counting heuristic
    bool findCount(const E& it) {
        Link<E>* current = head->next; 

        while (current != nullptr) { 
            compareCount++;  
            if (current->element == it) {
                current->count++;  
                Counting();  
                return true;  
            }
            current = current->next;
        }

        // If the element was not found, add it to the list
        add(it);
        Counting();  // Reorder the list after adding the new element
        return false;  // Element not found
    }

    // Reorder the list by frequency, putting the highest frequency words at the front
    void Counting() {
        // If the list has 0 or 1 elements, no need to reorder
        if (head->next == nullptr || head->next->next == nullptr) return;

        bool swapped;
        do {
            swapped = false;
            Link<E>* current = head->next;
            while (current != nullptr && current->next != nullptr) {
                // Compare the frequency of the current node with the next node
                if (current->count < current->next->count) {
                    // Swap the elements if current frequency is less than the next
                    E tempElement = current->element;
                    int tempCount = current->count;

                    current->element = current->next->element;
                    current->count = current->next->count;

                    current->next->element = tempElement;
                    current->next->count = tempCount;

                    swapped = true;  // A swap occurred, so we need to check again
                }
                current = current->next;
            }
        } while (swapped);  // Keep iterating until no swaps occur
    }


    void add(const E& it) override {

        Link<E>* newNode = new Link<E>(it);
        tail->next = newNode;  // Add the new node to the end of the list
        tail = newNode;        // Update the tail pointer
        listSize++;
    }

    int getCompares() const override {
        return compareCount;
    }

    int size() const override {
        return listSize;
    }

    void printlist()  override {
        Link<E>* current = head->next;  // Skip dummy head node
        while (current != nullptr) {
            cout << current->element << " ";
            current = current->next;
        }
        cout << endl;
    }

    void printlist(int n)  override {
        Link<E>* current = head->next;  // Skip dummy head node
        int count = 0;
        while (current != nullptr && count < n) {
            cout << current->element << " ";
            current = current->next;
            count++;
        }
        cout << endl;
    }
    void moveToFrontAdd(const E& it) {
        // Create a new node
        Link<E>* newNode = new Link<E>(it);

        // Insert the new node at the beginning of the list
        newNode->next = head->next;  // Point the new node's next to the current first node
        head->next = newNode;        // Point the head's next to the new node
        listSize++;                  // Increment the size of the list
        moveToFront(it);
    }
    // Method to apply the Move-to-Front heuristic
    void moveToFront(const E& it) {
        Link<E>* current = head->next;
        Link<E>* prev = nullptr;

        // Traverse the list to find the word
        while (current != nullptr) {
            if (current->element == it) {
                // Word found, move it to the front if it's not already at the front
                current->count++;  // Increment the frequency count for the word
                if (current != head->next) {
                    // Remove the word from its current position
                    prev->next = current->next;

                    // Move the word to the front
                    current->next = head->next;
                    head->next = current;
                }
                return;  // Word found and moved to the front, exit the function
            }
            prev = current;
            current = current->next;
        }
    }

    void firstTenWords() {
        Link<E>* current = head->next;  // Start from the first real element (skip dummy node)
        int count = 0;

        while (current != nullptr && count < 10) {  // Traverse up to 10 elements
            cout << current->element << "(" << current->count << ") ";  // Print word and its frequency
            current = current->next;  // Move to the next node
            count++;
        }
        cout << endl;  // End the output with a newline
    }

    void transpose(const E& it) {
        Link<E>* current = head->next;
        Link<E>* prev = nullptr;

        // Search for the element in the list
        while (current != nullptr) {
            if (current->element == it) {
                // Word is found, no need to add it, just transpose
                if (current != head->next) {
                    // Swap current node with previous node
                    prev->next = current->next;
                    current->next = prev;
                    head->next = current; // Adjust the head pointer if necessary
                }
                return;  // Element found and transposed, exit function
            }
            prev = current;
            current = current->next;
        }

        // If the word is not found, add it to the list
        add(it);

        // Now transpose the newly added node (move it closer to the front)
        current = head->next;  // This should point to the newly added word (the first node)
        if (current != nullptr && current->next != nullptr) {
            Link<E>* nextNode = current->next;
            current->next = nextNode->next;
            nextNode->next = current;
            head->next = nextNode;
        }
    }


};

#endif // SELF_ORDERED_LIST_H