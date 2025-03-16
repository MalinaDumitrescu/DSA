#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>

ListIterator::ListIterator(const IteratedList& list) : list(list) {
    current = list.head;
}

void ListIterator::first() {
    current = list.head;
}

void ListIterator::next() {
    if(valid())
    {
        current = list.nodes[current].next;
    }
    else {
        throw std::exception();
    }
}

bool ListIterator::valid() const {
    if (current != -1){
        return true;
    }
	return  false;
}

TElem ListIterator::getCurrent() const {
    if(valid()){
        return list.nodes[current].data;
    } else {
        throw std::exception();
    }
}



