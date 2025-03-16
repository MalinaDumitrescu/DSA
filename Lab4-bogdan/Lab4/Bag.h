#pragma once
#include <utility>
#include <cmath>
using namespace std;
//DO NOT INCLUDE BAGITERATOR

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111
#define DELETED_TELEM -111112
typedef int TElem;

class BagIterator; 
class Bag {

private:

    pair<TElem ,int>* hashTable;

    int capacity;
    int length;

    int h1(TElem elem) const{
        return abs(elem % capacity);
    }
    int h(TElem elem, int i) const{
        return (h1(elem) + i + i * i) % capacity;
    }

    void rehash(pair<TElem, int>* newHashTable, int new_capacity);
    void rezise();

	friend class BagIterator;
public:

	//constructor
	Bag();


	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();

};