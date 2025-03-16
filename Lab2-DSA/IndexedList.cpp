#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"

//TODO NU STIU CUM SE FACE THETA DE LA TASTATURA ASA CA O UL MEU E THETA :'))

//costructor
IndexedList::IndexedList() {
    this->head = nullptr;
}

int IndexedList::size() const {  // Worst/Average/Best Case: O(n)--- const

    int count=0; //count starts from--> nod 0 is this->head
    Node *parsingNode = this->head; // inițializam ptr de tip Node* cu nume si ii atribuim val ptr head din crobj (this)
    while(parsingNode != nullptr){
        count++;
        parsingNode = parsingNode->next;
    }
	return count; //loop ends before count+1!!!
}


bool IndexedList::isEmpty() const {  //Worst/Average/Best Case: O(n)--- const
    if(head==nullptr)
        return true;
	return false;
}

TElem IndexedList::getElement(int pos) const {
    if(this->head== nullptr || pos<0){
        throw std::exception();
    }

    //todo check size for pos use maybe above method idk
    Node *parsingNode =this->head;
    for(int idx=0 ; idx<pos; idx++){
        parsingNode = parsingNode->next;
        if(parsingNode== nullptr){
            throw std::exception();
        }
    }

	return parsingNode->data;
}
/* si pt getElen si pt setElem
Worst Case: O(n)
poziția pos este la capatul listei, tr sa parcurgem toata lista
Average Case: O(n)
de obicei poziția va fi undeva la mijlocul listei, ceea ce inseamnă ca tot trebuie sa parcurgem jumatate din lista
Best Case: O(1)
Daca pos este 0, adica elementul de la începutul listei, operația se execută în timp constant */

TElem IndexedList::setElement(int pos, TElem e) {
    if(this->head== nullptr || pos<0){
        throw std::exception();
    }
    //todo exception daca e e nullptr

    Node *parsingNode =this->head;
    for(int idx=0 ; idx<pos; idx++){
        parsingNode = parsingNode->next;
        if(parsingNode== nullptr){
            throw std::exception();
        }
    }
    TElem oldValue = parsingNode->data;
    parsingNode->data = e;
	return oldValue;
}

void IndexedList::addToEnd(TElem e) { //Worst/Average/Best Case: O(n)parc mereu toata lista pt a ajunge la ultimul nod și a adauga un nou nod la sf
    //todo if head is empty
    //todo destruct the nN

    Node *newNode = new Node();
    newNode->data=e;
    newNode->next= nullptr;

    if(this->head==nullptr){  //if list empty, the head->newNode, newNode 1st pos
        this->head=newNode;
    }
    else{
    Node *parsingNode = this->head;
    while(parsingNode->next != nullptr){
        parsingNode = parsingNode-> next;
    }
    parsingNode->next=newNode;
    }
}

void IndexedList::addToPosition(int pos, TElem e) {
    /* Worst Case: O(n)
Dacă adaugi un element la finalul listei, trebuie parcursa intreaga lista.
Average Case: O(n)- in medie elem pe la mij
Best Case: O(1)
Dacă adaugi un element la începutul listei (pos == 0), operatia este constanta,fara a mai parcuge lista*/

    if(pos<0||pos>this->size()) {
        throw std::exception();
    }
    Node* newNode=new Node{e, nullptr};
    if(pos==0){
        newNode->next=this->head;
        this->head=newNode;
    }
    else {
        Node *parsingNode = this->head;
        for (int idx = 0; idx < pos - 1; idx++) {
            parsingNode = parsingNode->next;
        }
        newNode->next = parsingNode->next;
        parsingNode->next = newNode;
    }
}

TElem IndexedList::remove(int pos) {

    /*Worst Case: O(n)
     ștergi un element de la sfârșitul listei,deci parcurgem toata lista
Average Case: O(n)
Best Case: O(1)*/

    if(this->head == nullptr || pos<0){
        throw std::exception();
    }
    Node* parsingNode= this->head;
    TElem removedValue; //stocheaza val nodului care va fi eliminat

    if(pos==0){
        removedValue=this->head->data;
        this->head=this->head->next;
        delete parsingNode;
        return removedValue;
    }
    for(int idx=0;idx<pos-1;idx++){
        parsingNode=parsingNode->next;
        if(parsingNode== nullptr || parsingNode->next== nullptr){
            throw std::exception();
        }
    }
    Node* nodeToDelete=parsingNode->next;
    parsingNode->next=nodeToDelete->next;
    removedValue= nodeToDelete->data;
    delete nodeToDelete;

    return removedValue;
}

int IndexedList::search(TElem e) const{   //Worst/Average/Best Case: O(n)/O(n)/O(1)
    //TODO - Implementation
    //just like every delete and add see above
    Node* parsingNode=this->head;
    int idx=0;
    while (parsingNode!= nullptr){
        if(parsingNode->data==e){
            return idx;
        }
        idx++;
        parsingNode=parsingNode->next;
    }
    return -1; //e nowhere to be found
}

ListIterator IndexedList::iterator() const {
    return ListIterator(*this);
}
//ma folosesc de aceeasi lista
//pre cond- IndexList ordonata
//post cond- IndexList inversata
void IndexedList::reverse() {
    Node* prevNode = nullptr;
    Node* parsingNode = this->head;
    Node* nextNode = nullptr;

    while (parsingNode != nullptr) {
        //salvez urmatorul nod
        nextNode = parsingNode->next;

        //inversam pointerul
        parsingNode->next = prevNode;

        //mut prevNode si parsingNode un pas înainte
        prevNode = parsingNode;
        parsingNode = nextNode;
    }

    //prevNode va fi head al listei-- la final
    this->head = prevNode;
}

//complexitatea va fi O(n) in toate cazurile ca trebuie sa facem o parcurgere completa

IndexedList::~IndexedList() {  //Worst/Average/Best Case: O(1)--- const
	//TODO - Implementation
    //todo delete everything with a parse like above...
    Node* parsingNode= this->head;
    while (parsingNode!= nullptr){
        Node* next=parsingNode->next;
        delete parsingNode;
        parsingNode=next;
    }
}


