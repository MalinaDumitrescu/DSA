#include "Bag.h"
#include "BagIterator.h"
#include <exception>

using namespace std;

// complexity: theta(n)
Bag::Bag() {

    capacity = 17;
    length = 0;
    hashTable = new pair<TElem ,int>[capacity];

    for ( int i = 0; i < capacity; i++){
        hashTable[i].first = NULL_TELEM;
        hashTable[i].second = 0;
    }
}

//complexity: best case: theta(1) worst case: theta(n)-amortizat average case: theta(1)-amortizat
void Bag::add(TElem elem) {
    // we make a loop because for very big number there is no more space
    int put = 0;
    while(put == 0){
       int i = 0;
       int position = h(elem, i);
       while( i < capacity && hashTable[position].first != NULL_TELEM && hashTable[position].first != DELETED_TELEM && hashTable[position].first != elem )
       {
           i++;
           position = h(elem, i);
       }
       if( i < capacity){
           if (hashTable[position].first != elem )
               hashTable[position].first = elem;
           hashTable[position].second ++;
           length ++;
           put = 1;
       }
       else rezise(); // if there was no space
   }

}

//complexity: best case: theta(1) worst case: theta(n) average case: theta(1)
bool Bag::remove(TElem elem) {
	if (! search(elem) )
        return false;

    int i = 0;
    int position = h(elem, i);

    while (i < capacity && hashTable[position].first != elem && hashTable[position].first != NULL_TELEM) {
        i++;
        position = h(elem, i);
    }
    if (i < capacity && hashTable[position].first == elem) {
        if (hashTable[position].second > 1)
            hashTable[position].second--;
        else {
            hashTable[position].second = 0;
            hashTable[position].first = DELETED_TELEM;
        }
        length--;
        return true;
    }
    return false;
}

//complexity: best case: theta(1) worst case: theta(n) average case: theta(1)
bool Bag::search(TElem elem) const {

    int i = 0;
    int position = h(elem,i);

    while( i < capacity && hashTable[position].first != elem && hashTable[position].first != NULL_TELEM )
    {
        i++;
        position = h(elem,i);
    }

    if( i< capacity && hashTable[position].first == elem)
        return true;
    else return false;
}

//complexity: best case: theta(1) worst case: theta(n) average case: theta(1)
int Bag::nrOccurrences(TElem elem) const {
     int i = 0;
     int position =h(elem,i);

     while( i < capacity && hashTable[position].first != elem && hashTable[position].first != NULL_TELEM)
     {
         i++;
         position = h(elem,i);
     }

     if( i<capacity && hashTable[position].first == elem)
         return hashTable[position].second;
     else return 0;


}

//complexity: theta(1)
int Bag::size() const {
    return length;
}

//complexity: theta(1)
bool Bag::isEmpty() const {
	return length == 0;
}

//complexity: theta(1)
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

//complexity: theta(1)
Bag::~Bag() {
	delete[] hashTable;
}

//complexity: best case: theta(n) worst case theta(n) average case: theta(n)
void Bag::rezise() {
    int new_capacity = capacity * 2;
    pair<TElem, int>* newHashTable = new pair<TElem, int>[new_capacity];

    for (int i = 0; i < new_capacity; i++) {
        newHashTable[i].first = NULL_TELEM;
        newHashTable[i].second = 0;
    }

    rehash(newHashTable,new_capacity);

    delete[] hashTable;
    hashTable = newHashTable;

}

//complexity: best case: theta(n) worst case theta(n) average case: theta(n)
void Bag::rehash(pair<TElem, int>* newHashTable, int new_capacity) {
    int old_cap = capacity;
    capacity = new_capacity;
    for (int i = 0; i < old_cap; i++) {
        if (hashTable[i].first != NULL_TELEM && hashTable[i].first != DELETED_TELEM) {
            TElem elem = hashTable[i].first;
            int freq = hashTable[i].second;

            int j = 0;
            int position = h(elem, j);
            while (j < capacity && newHashTable[position].first != NULL_TELEM) {
                j++;
                position = h(elem, j);
            }

            if (j < capacity) {
                newHashTable[position].first = elem;
                newHashTable[position].second = freq;
            }
        }
    }


}