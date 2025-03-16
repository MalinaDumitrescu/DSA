//problema 11- ADT IndexList cu SLL

#pragma once
#include "IndexedList.h"

class ListIterator{
    //DO NOT CHANGE THIS PART
	friend class IndexedList;
private:
	const IndexedList& list;
	//TODO - Representation
    IndexedList::Node* current; // Pointer to the current node

    ListIterator(const IndexedList& lista);

public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;

};

