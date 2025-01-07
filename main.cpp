
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "llist.h"
#include "SelfOrderedList.h"

using namespace std;

int main() {

	cout << "<Tirza Wilson> -- CSIS 215 Programming Assignment 4 -- Self Organinzing List" << endl;

	fstream fileName;
	string word;
	
	cout << "First test, adding (A, B, C, D, E, F, G, H) to the list: " << endl;

	SelfOrderedList<char> newList; 
	
	newList.add('a');
	newList.add('b');
	newList.add('c');
	newList.add('d');
	newList.add('e');
	newList.add('f');
	newList.add('g');
	newList.add('h');
	
	newList.find('i');
	newList.printlist();

	cout << endl << "Number of compares when searching for 'i': " << newList.getCompares() << endl << endl;
	cout << endl << "Adding (F, D, F, G, E, G, F, A, D, F, G, E, H, I) to the list: " << endl;
	cout << "Count Heuristic: ";
	newList.clear(); // Clear the list to start fresh for the next heuristic
	newList.findCount('f'); // Find and add are built into the same function for this heuristic
	newList.findCount('d');
	newList.findCount('f');
	newList.findCount('g');
	newList.findCount('e');
	newList.findCount('g');
	newList.findCount('f');
	newList.findCount('a');
	newList.findCount('d');
	newList.findCount('f');
	newList.findCount('g');
	newList.findCount('e');
	newList.findCount('h');
	newList.findCount('i');
	
	newList.printlist();
	cout << "Number of compares: " << newList.getCompares() << endl;
	newList.clear(); // Clear the list to start fresh for the next heuristic

	cout << "Move to Front Heuristic: ";

	newList.moveToFrontAdd('f'); newList.find('f'); // seperate functions were needed for this heuristic
	newList.moveToFrontAdd('d'); newList.find('d');
	newList.moveToFrontAdd('f'); newList.find('g');
	newList.moveToFrontAdd('g'); newList.find('e');
	newList.moveToFrontAdd('e'); newList.find('a');
	newList.moveToFrontAdd('g'); newList.find('h');
	newList.moveToFrontAdd('f'); newList.find('i');
	newList.moveToFrontAdd('a');
	newList.moveToFrontAdd('d');
	newList.moveToFrontAdd('f');
	newList.moveToFrontAdd('g');
	newList.moveToFrontAdd('e');
	newList.moveToFrontAdd('h');
	newList.moveToFrontAdd('i');

	newList.printlist();
	cout << "Number of compares: " << newList.getCompares() << endl;
	newList.clear(); // Clear the list to start fresh for the next heuristic 

	cout << "transpose Heuristic: ";

	newList.transpose('f'); newList.find('f'); // seperate functions were needed for this heuristic
	newList.transpose('d'); newList.find('d');
	newList.transpose('f'); newList.find('g');
	newList.transpose('g'); newList.find('e');
	newList.transpose('e'); newList.find('a');
	newList.transpose('g'); newList.find('h');
	newList.transpose('f'); newList.find('i');
	newList.transpose('a');
	newList.transpose('d');
	newList.transpose('f');
	newList.transpose('g');
	newList.transpose('e');
	newList.transpose('h');
	newList.transpose('i');

	newList.printlist();
	cout << "Number of compares: " << newList.getCompares() << endl;


	SelfOrderedList<string> newTest;
	fileName.open("test.txt"); // Open the file
	
	if (!fileName.is_open()) {
		cerr << "Error: Could not open file " << endl;
		// Handle error (throw an exception or exit)
		return 1;
	}

	// Count
	cout << endl << setw(36) << "Count Heuristic" << endl;
	while (fileName >> word) {
		newTest.add(word);
		newTest.findCount(word);
	}

	cout << "Words in list: " << newTest.size() << endl;
	cout << "Number of compares: " << newTest.getCompares() << endl;
	cout << "First 10 words in list: ";
	newTest.firstTenWords();
	cout << endl << endl;


	// Move to front
	// Reset file pointer before next heuristic
	fileName.clear();
	fileName.seekg(0, ios::beg);

	cout << setw(44) << "Move to Front Heuristic" << endl;
	
	SelfOrderedList<string> newTestMove; // start a new list to transpose
	while (fileName >> word) {
		newTestMove.moveToFrontAdd(word);
		newTestMove.find(word);
	}

	cout << "Words in list: " << newTestMove.size() << endl;
	cout << "Number of compares: " << newTestMove.getCompares() << endl;
	cout << "First 10 words in list: ";
	newTestMove.firstTenWords();
	cout << endl << endl;


	// Transpose
	// Reset file pointer before next heuristic
	fileName.clear(); 
	fileName.seekg(0, ios::beg);

	cout << setw(40) << "Transpose Heuristic" << endl;
	
	SelfOrderedList<string> newTestTranspose; // start a new list to transpose
	while (fileName >> word) {
		newTestTranspose.transpose(word);
		newTestTranspose.find(word);
	}

	cout << "Words in list: " << newTestTranspose.size() << endl;
	cout << "Number of compares: " << newTestTranspose.getCompares() << endl;
	cout << "First 10 words in list: ";
	newTestTranspose.firstTenWords();
	cout << endl << endl;

	fileName.close();
	return 0;
}

