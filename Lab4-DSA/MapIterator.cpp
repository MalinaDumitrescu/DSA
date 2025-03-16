#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;

//daca e del teoretic eu pot sa inserez in slot
//todo slot marked with del --> available for insert, unavailable for search

MapIterator::MapIterator(const Map& d) : map(d){
    //theta(1)--best--primul slot verifcat nu i nici deleted nici gol
    //thata(n)-worst-->it prin tot arr pt a gasi un slot liber
    //average--theta(1)-- depinde de distrib elem in T
    this->first();

    this->currentIndex=0;
    for(int parser=0; parser<this->map.capacity; parser++){
        if(this->map.HashTable[parser]!=DELETED_TELEM && this->map.HashTable[parser]!=NULL_TELEM){
            this->currentIndex=parser;
            return;
        }
    }
    this->currentIndex=-1; //end
}
//best theta(1)-- prima pos
//worst average theta(n)--it prin tot tab pt a gasi un index valid
void MapIterator::first() {
   for(int parser = 0; parser < this->map.capacity;parser++){
       if(this->map.HashTable[parser]!=DELETED_TELEM && this->map.HashTable[parser]!=NULL_TELEM){
           this->currentIndex=parser;
           return;
       }
   }
    this->currentIndex=-1;
}
//best theta(1)-- prima pos
//worst average theta(n)--it prin arr cam ca la first doar ca -1
void MapIterator::previous() {
    if (!valid()) {
        throw std::exception();
    }
    for (int parser = this->currentIndex - 1; parser >= 0; parser--) {
        if (this->map.HashTable[parser] != DELETED_TELEM && this->map.HashTable[parser] != NULL_TELEM) {
            this->currentIndex = parser;
            return;
        }
    }
    this->currentIndex = -1;
}

//ca mai sus complex -- variaza average ul?
void MapIterator::next() {
    if(valid()) {
        for (int parser = this->currentIndex + 1; parser < this->map.capacity; parser++) {
            if (this->map.HashTable[parser] != DELETED_TELEM && this->map.HashTable[parser] != NULL_TELEM) {
                this->currentIndex = parser;
                return;
            }
        }
        this->currentIndex = -1;
    } else{
        throw std::exception();

    }

}


//const theta(1)

TElem MapIterator::getCurrent(){
    if(valid()){
        return this->map.HashTable[currentIndex];
    }else{
        throw std::exception();
    }

}


bool MapIterator::valid() const {
    if(this->currentIndex==-1){
        return false;
    }
    return true;
}
