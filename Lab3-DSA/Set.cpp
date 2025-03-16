#include "Set.h"
#include "SetIterator.h"
#include <exception>
#include <iostream>
//TODO SHIT RESIZE FOR ADD
Set::Set() {
    this->currentSize=0;
    this->capacity=10;
    this->firstEmpty=0;
    this->head=-1;

    this->elements=new TElem[this->capacity];
    this->next=new int[this->capacity];

    for(int idx=0; idx< this->capacity; idx++){
        this->elements[idx]=NULL_TELEM;
    }
    for(int idx=0; idx< this->capacity-1; idx++){
        this->next[idx]=idx+1;
    }
    this->next[this->capacity-1]=-1;
}
// Theta(n)- const, complex liniara, n e cap init, initializam tot in constructor

void Set::resize() {
    int newCapacity=2*capacity;
    TElem* newElements=new TElem[newCapacity];
    int* newNext=new int[newCapacity];

    for(int idx=0; idx<capacity; idx++){
        newElements[idx]=elements[idx];
        newNext[idx]=next[idx];
    }
    for(int idx=capacity; idx<newCapacity-1; idx++) {
        newNext[idx] = idx + 1;
    }
    newNext[newCapacity-1]=-1;

    delete[] elements;
    delete[] next;
    this->elements=newElements;
    this->next=newNext;
    this->firstEmpty=this->capacity;
    this->capacity=newCapacity;
}
//Theta(n)- const, complex liniara, 2*cap init
//TODO exception Set- elem unique, unordered--> add anywhere(first), no space left
bool Set::add(TElem elem) {
    if(search(elem))
        return false;

    if(firstEmpty==-1)
        resize();

    int newPos=firstEmpty;
    firstEmpty=next[firstEmpty];
    elements[newPos]=elem;
    next[newPos]=head;
    head=newPos;
    currentSize++;

    return true;
}
/*add-worst: theta(n)- parcurget tot pt a verifica unicitatea elem
-average:theta(n)- distributie uniforma cazurilor
-best:theta(1)- firstEmpty ul e imediat la indemana si elem e unic*/
bool Set::remove(TElem elem) {
	int parser=this->head;
    int previous=-1;  //aux

    while(parser!=-1 && this->elements[parser]!=elem){
        previous=parser;
        parser= this->next[parser];
    }
    if(parser==-1) //elem not found, remove failed
        return false;
    if(previous!=-1)
    //if parser somewhere over the rainbow uuuu
        this->next[previous]=this->next[parser];
    else
    //if parser is head---> head=next idx
        this->head=this->next[this->head];

    this->next[parser]= this->firstEmpty;
    this->firstEmpty=parser; //il setam ca prim elem in partea goala a listei
    this->currentSize--;

    return true;
}
/*remove- worst: theta(n)- elem e la sf listei sau nu exista
average: theta(n)-same pos for all elem to be removed
best: theta(1)- elem e in head*/

bool Set::search(TElem elem) const {
	int parser=head;
    while(parser!=-1){
        if(elements[parser]==elem) {
            return true;
        }else {
            parser = next[parser];
        }
    }
    return false;
}
//theta(n)-trebuie sa trav toata lista const

int Set::size() const {
	return currentSize;
}
//Theta(1)-return val unei var-> const


bool Set::isEmpty() const {
    if (currentSize==0)
        return true;
    return false;
}
//Theta(1)-const

//implementare

// Best, average and worst case: Theta(n^2)
Set Set::unionWith(const Set& other) const {
    Set unionSet;
    SetIterator it = this->iterator();
    while (it.valid()) {
        unionSet.elements[unionSet.firstEmpty] = it.getCurrent();
        unionSet.next[unionSet.firstEmpty] = unionSet.head;
        unionSet.head = unionSet.firstEmpty;
        unionSet.firstEmpty++;
        unionSet.currentSize++;
        it.next();
    }
    SetIterator itTwo = other.iterator();
    while (itTwo.valid()) {
        TElem elem = itTwo.getCurrent();
        bool found = false;
        int current = unionSet.head;
        while (current != -1 && !found) {
            if (unionSet.elements[current] == elem) {
                found = true;
            }
            current = unionSet.next[current];
        }
        if (!found) {
            unionSet.elements[unionSet.firstEmpty] = elem;
            unionSet.next[unionSet.firstEmpty] = unionSet.head;
            unionSet.head = unionSet.firstEmpty;
            unionSet.firstEmpty++;
            unionSet.currentSize++;
        }
        itTwo.next();
    }
    return unionSet;
}

void Set::print() const {
    std::cout << "{ ";
    if (isEmpty()) {
        std::cout << " }";
        return;
    }
    SetIterator it = this->iterator();
    while (it.valid()) {
        std::cout << it.getCurrent() << ", ";
        it.next();
    }
    std::cout << "\b\b }" << std::endl;
}

Set::~Set() {
	delete[] elements;
    delete[] next;
}
//Theta(1)- const


SetIterator Set::iterator() const {
	return SetIterator(*this);
}
//Theta(1)- const

