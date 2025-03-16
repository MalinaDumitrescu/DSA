#include "SetIterator.h"
#include "Set.h"
#include <exception>

// toate sunt constante deci in toate cazurile complexitatea este O(1)
SetIterator::SetIterator(const Set& m) : set(m){
    this->current=m.head;
}


void SetIterator::first() {
	this->current=set.head;
}


void SetIterator::next() {
    if(!valid()) {
        throw std::exception();
    }
    this->current=set.next[current];
}


TElem SetIterator::getCurrent(){
    if(!valid())
        throw std::exception();
	return set.elements[current];
}

bool SetIterator::valid() const {
    return this->current!=-1;
}



