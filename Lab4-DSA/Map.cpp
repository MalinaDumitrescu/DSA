#include "Map.h"
#include "MapIterator.h"
#include <iostream >

//std::make_pair(c,v) / T[index]=std::pair<TKey,TValue>(c,v) / std::pair<TKey,TValue> p(c,v); T[index]=p / T[index] = {c, v};
//todo slot marked with del --> available for insert, unavailable for search
Map::Map() {
    this->capacity = 512; //colisions
    this->length = 0;
    this->HashTable = new TElem[capacity];
    for (int parser = 0; parser < capacity; parser++)
        this->HashTable[parser] = NULL_TELEM;
    this->h = ptrHashFuncKol;
}

Map::~Map() {
    delete[] HashTable;
}
//resize--->theta(new cap)
//rehash--->theta(old cap)
void Map::reSizeHash() {
    //resize hash table

    int oldCapacity = capacity;
    TElem* oldHashTable = HashTable;
    capacity = capacity*2;
    HashTable = new TElem[capacity]; //alloc memory for new table
    for (int idx = 0; idx < capacity; idx++) {
        HashTable[idx] = NULL_TELEM; //init all elements to empty
    }
    int oldLen = length;
    length = 0;

    //rehash
    for(int parser=0; parser<oldCapacity; parser++){
        if(oldHashTable[parser]!=NULL_TELEM){
            add(oldHashTable[parser].first,oldHashTable[parser].second);
        }
    }

    delete[] oldHashTable;
}


//viteaza-- derivata t timp x var sd--- modelul dezintegrarii radioactive

//average: theta(1)- amortizat--> redimensionari const, tratarea coliziuni--> timp constant
//best: theat(1)- inserata din prima, fara trat coliz
//worst: theta(n)- parcurgem tot arr intram in ciclu-->apelam resize
TValue Map::add(TKey c, TValue v) {
    int parser = 0;
    int index = h(c, parser, capacity);
    int startIndex = index;
    while(HashTable[index].first!=-111111 && HashTable[index].first != c && parser<capacity) {
        parser++;
        index = h(c, parser, capacity);

    }
    //add value to an existing key
    if (HashTable[index].first == c && parser<capacity) {
        TValue oldValue = HashTable[index].second;
        HashTable[index].second = v;
        return oldValue;
    }
    else if(HashTable[index].first== -111111 || HashTable[index]==DELETED_TELEM){
        //add on an available slot or marked as deleted slot---> mark as used
        HashTable[index] = std::make_pair(c, v);
        length++;
        if (length / (capacity * 1.0) > 0.75){
            reSizeHash();
        }
        return NULL_TVALUE;

    }
    return NULL_TVALUE;
}
    /*else if(T[index]==T[startIndex]){
        reSizeHash();
        add(c,v); */


//best case: theta(1)---> gaseste din prima la idx de hash
//average: theta(1)--> daca se face bine hash ul
//worst: theta(n)--> rata mare de coliziune, si clustering
TValue Map::search(TKey c) const {
    int parser = 0;
    int index = h(c, parser, capacity);
    while (HashTable[index].first != -111111 && parser<capacity) {
        if (HashTable[index].first == c && HashTable[index] != DELETED_TELEM) {   //slide met remove?
            return HashTable[index].second;
        }
        parser++;
        index = h(c, parser, capacity);

    }
    return NULL_TVALUE;
}

//best: theta(1)--> prim pos idx hash
//average: theta(1)--> ca la search
//worst: theta(1)--> rata mare de coliziune, multe slot uri marcate cu deleted
TValue Map::remove(TKey c) {
    //TODO - Implementation
    int parser = 0;
    int index = h(c, parser, capacity);
    while (HashTable[index].first!= -111111 && parser < capacity) {
        if (HashTable[index].first == c && HashTable[index] != DELETED_TELEM) {
            TValue v = HashTable[index].second;
            HashTable[index] = DELETED_TELEM;
            length--;
            //std::cout << "Removed key " << c << " from index " << index << std::endl;
            return v;

        }
        parser++;
        index = h(c, parser, capacity);
    }
    return NULL_TVALUE;
}

//constante theta(1)

int Map::size() const {
    return length;
}

bool Map::isEmpty() const {
    return length == 0;
}

MapIterator Map::iterator() const {
    return MapIterator(*this);
}



