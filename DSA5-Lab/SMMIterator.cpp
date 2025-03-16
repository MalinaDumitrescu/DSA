#include "SMMIterator.h"
#include "SortedMultiMap.h"

#include <exception>

//best theta(1)--arb gol
//worst-- theta(h)-- pana jos-- degenerat
// average-- theta(logn)-- arb echiilbrat
SMMIterator::SMMIterator(const SortedMultiMap &d) : map(d) {
    this->stackCapacity = 100;
    this->stackLength = 0;
    this->stack = new Node *[stackCapacity];
    current = nullptr;
    first();
}

//const theta(1)
bool SMMIterator::valid() const {
    if (current == nullptr)
        return false;
    else
        return true;

}
//best: theta(1)--> de ex daca e first ul
//worst: theta(h)--> cauta hopa topa prin arbore al doileaa nod in ordine
//average--> theta(logn)--daca arb e echilibrat
void SMMIterator::previous() {
    if (!valid()) {
        throw std::exception();
    }

    if (current->left != nullptr) {
        current = current->left;
        while (current->right != nullptr) {
            current = current->right;
        }
        return;
    }

    int i = stackLength - 1;
    while (i >= 0 && stack[i] == current) {
        i--;
    }
    current = (i >= 0) ? stack[i] : nullptr;
    while (i >= 0 && stack[i]->left == current) {
        current = stack[i--];
    }
    if (i >= 0 && stack[i]->left != nullptr) {
        current = stack[i]->left;
    } else {
        current = nullptr;
    }
}
//best: theta(1)--> un sg elem in arb
//worst: theta(h)--> arbore degenerat, parg pana la cel mai mic nod pe cea mai lunga cale posibila
//average--> theta(logn)--daca arb e echilibrat

void SMMIterator::first() {
    while (stackLength > 0) {
        pop();
    }
    current = map.root;
    while (current != nullptr) {
        push(current);
        current = current->left;
    }
    if (stackLength > 0) {
        current = pop();
    } else {
        current = nullptr;
    }
}

//best: theta(1)--> urm nod dupa direct dupa first e liber
//worst: theta(h)--> cauta hopa topa prin arbore al doileaa nod in ordine
//average--> theta(logn)--daca arb e echilibrat
void SMMIterator::next() {
    if (!valid()) {
        throw exception();
    }
    if (current->right != nullptr) {
        current = current->right;
        while (current != nullptr) {
            push(current);
            current = current->left;
        }
    }
    if (stackLength > 0) {
        current = pop();
    } else {
        current = nullptr;
    }
}

//const theta(1)
TElem SMMIterator::getCurrent() const {
    if (!valid()) {
        throw exception();
    }
    return {current->key, current->element};
}

//best theta(1)-- sad in stiva chill cand exista spatiu fara resize
//worst theta(n)--se umpel stiva-->resize
//average ca best ul
void SMMIterator::push(Node *node) {
    if (stackLength == stackCapacity) {
        stackCapacity *= 2;
        Node **newStack = new Node *[stackCapacity];
        for (int i = 0; i < stackLength; ++i) {
            newStack[i] = stack[i];
        }
        delete[] stack;
        stack = newStack;
    }
    stack[stackLength++] = node;
}

//const theta(1)
Node *SMMIterator::pop() {
    if (stackLength == 0) {
        throw exception();
    }
    return stack[--stackLength];
}

//const theta(1)
SMMIterator::~SMMIterator() {
    delete[] stack;
}


//todo shit with Node* stack---> bleh doesn't work :/
/*
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    this->stackLength = 0;
    this->stack = nullptr;
    this->current = nullptr;

    first();
}

void SMMIterator::first() {
    while (this->stackLength > 0) {
        pop();
    }
    this->current = map.root;
    while (this->current != nullptr) {
        push(this->current);
        this->current = this->current->left;
    }
    if (stackLength > 0) {
        this->current = pop();
    } else {
        this->current = nullptr;
    }
}

bool SMMIterator::valid() const{
    if(this->current == nullptr)
        return false;
    else
        return true;
}

void SMMIterator::next() {
    if (!valid()) {
        throw std::exception();
    }
    // if there is a right subtree, process the leftmost node of the right subtree
    if (this->current->right != nullptr) {
        this->current = this->current->right;
        while (this->current != nullptr) {
            push(this->current);
            this->current = this->current->left;
        }
    }
    // if no right subtree, process the next node from the stack
    if (stackLength > 0) {
        this->current = pop();
    } else {
        this->current = nullptr;
    }
}

TElem SMMIterator::getCurrent() const {
    if (!valid()) {
        throw std::exception();
    }
    return {this->current->key, this->current->element};
}

SMMIterator::~SMMIterator() {
    while (stackLength > 0) {
        pop();
    }
}

void SMMIterator::push(Node* node) {
    Node* newNode = new Node(node->key, node->element);
    newNode->left = node->left;
    newNode->right = stack;
    stack = newNode;
    stackLength++;
}

Node* SMMIterator::pop() {
    if (this->stackLength == 0) {
        throw std::exception();
    }
    Node* topNode = stack;
    stack = stack->right;
    topNode->right = nullptr;
    stackLength--;
    return topNode;
} */
