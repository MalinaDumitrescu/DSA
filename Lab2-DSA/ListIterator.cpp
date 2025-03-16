#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

// toate sunt constante deci in toate cazurile complexitatea este O(1)
ListIterator::ListIterator(const IndexedList& list) : list(list){
    this->current = list.head;
}

void ListIterator::first(){
    this->current = list.head;

}

void ListIterator::next(){
    //TODO - Implementation
    if(!valid()) {
        throw std::exception();
    }
    this->current= this->current->next;
}

bool ListIterator::valid() const{
    if(this->current!= nullptr)
	    return true;
    return false;
}

TElem ListIterator::getCurrent() const{
   //TODO - Implementation
	if(!valid()){
        throw std::exception();
    }
    return this->current->data;
}