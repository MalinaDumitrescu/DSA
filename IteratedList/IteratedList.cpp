
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"
#include <iostream>

//TODO BAG PLA MERGEEEE


IteratedList::IteratedList() {
    head = -1;
    tail = -1;
    length = 0;
    capacity = 100;
    nodes = new Node[capacity];
    firstEmpty = 0;
    for (int i = 1; i < capacity; i++) {
        nodes[i].data = NULL_TELEM;
        nodes[i].next = i + 1;
        nodes[i].prev = i -1;
    }
    nodes[capacity - 1].next = -1;
    nodes[capacity - 1].prev = capacity - 2;
    nodes[0].prev = -1;
    nodes[0].next = 1;
}

int IteratedList::size() const {
    return length;
}

bool IteratedList::isEmpty() const {
    if (length == 0){
        return true;
    } else {
        return false;
    }
}

ListIterator IteratedList::first() const {
	return ListIterator(*this);
}

TElem IteratedList::getElement(ListIterator pos) const {
    if (!pos.valid())
        throw std::exception();
    return pos.getCurrent();
}

TElem IteratedList::remove(ListIterator& pos) {
    if (!pos.valid())
        throw std::exception();  // Provide more detailed error messages if possible
    int currentIndex = pos.current;
    TElem removedData = nodes[currentIndex].data;

    if (currentIndex == head) {
        head = nodes[currentIndex].next;
        if (head != -1)
            nodes[head].prev = -1;
    } else {
        nodes[nodes[currentIndex].prev].next = nodes[currentIndex].next;
        if (nodes[currentIndex].next != -1)
            nodes[nodes[currentIndex].next].prev = nodes[currentIndex].prev;
        else
            tail = nodes[currentIndex].prev;
    }

    // Reset the removed node and update firstEmpty
    nodes[currentIndex].next = firstEmpty;
    nodes[currentIndex].prev = -1;
    nodes[currentIndex].data = NULL_TELEM;
    firstEmpty = currentIndex;

    length--;
    return removedData;
}

ListIterator IteratedList::search(TElem e) const{
    ListIterator it = first();
    while (it.valid()) {
        if (it.getCurrent() == e)
            return it;
        it.next();
    }
    return it;
}

TElem IteratedList::setElement(ListIterator pos, TElem e) {
    if (!pos.valid())
        throw std::exception();
    TElem oldData = pos.getCurrent();
    nodes[pos.current].data = e;
    return oldData;
}

void IteratedList::addToBeginning(TElem e) {
    if (length >= capacity) {
               resizeUp();
    }
    int new_Pos=firstEmpty;
    firstEmpty=nodes[firstEmpty].next;
    nodes[new_Pos].data=e;
    nodes[new_Pos].next=head;
    nodes[new_Pos].prev=-1;
    if(isEmpty()){
        tail=new_Pos;
    }
    else{
        nodes[head].prev=new_Pos;
    }
    head=new_Pos;
    length++;
}

void IteratedList::addToPosition(ListIterator& pos, TElem e) {
        if (!pos.valid())
            throw std::exception();

        if (length >= capacity){
            resizeUp();
        }



//        std::cout << std::endl;
//        std::cout << firstEmpty;
//        std::cout << nodes[pos.current].next;
//        std::cout << pos.current;
//        std::cout << std::endl;
        int new_Pos = firstEmpty;
    if (firstEmpty != -1) {
        firstEmpty = nodes[firstEmpty].next;
        nodes[new_Pos].data = e;
        nodes[new_Pos].prev = pos.current;
        nodes[new_Pos].next = nodes[pos.current].next;

        if (nodes[pos.current].next != -1) {
            nodes[nodes[pos.current].next].prev = new_Pos;
        }
        nodes[pos.current].next = new_Pos;

        if (pos.current == tail) {
            tail = new_Pos;
        }

        length++;
        pos.current = new_Pos;
    } else {
        throw std::exception();
    }
}

void IteratedList::addToEnd(TElem e) {
    if (length >= capacity){
        resizeUp();
    }
    if (isEmpty()) {
        head = firstEmpty;
        tail = firstEmpty;
        firstEmpty = nodes[firstEmpty].next;
        nodes[head] = Node{e, -1, -1};
    } else {
        int new_Pos = firstEmpty;
        firstEmpty = nodes[firstEmpty].next;
        nodes[new_Pos] = Node{e, -1, tail};
        nodes[tail].next = new_Pos;
        tail = new_Pos;
        nodes[tail].next = -1;
    }
    length ++;
}

void IteratedList::resizeUp() {
    capacity *= 2;
    Node* newNodes = new Node[capacity];
    for (int i = 0; i < length; i++) {
        newNodes[i] = nodes[i];
    }
    delete[] nodes;
    nodes = newNodes;
    for (int i = length; i < capacity - 1; i++) {
        nodes[i].next = i + 1;
        nodes[i].prev = i - 1;
    }
    nodes[capacity - 1].next = -1;
    firstEmpty = length;
}

void IteratedList::resizeDown() {
    capacity /= 2;
    Node* newNodes = new Node[capacity];
    for (int i = 0; i < length; i++) {
        newNodes[i] = nodes[i];
    }
    delete[] nodes;
    nodes = newNodes;
    for (int i = length; i < capacity - 1; i++) {
        nodes[i].next = i + 1;
    }
    nodes[capacity - 1].next = -1;
    firstEmpty = length;
}

IteratedList::~IteratedList() {
    delete[] nodes;
}
