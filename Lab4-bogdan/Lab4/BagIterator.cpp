#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

//best case: theta(1), there is an elem on the first position
//worst case: theta(n), we have to go through all the elements
//general case: O(n)
// average case: theta(n)
BagIterator::BagIterator(const Bag& c): bag(c)
{
    first();
}

//best case: theta(1), there is an elem on the first position
//worst case: theta(n), we have to go through all the elements
//general case: O(n)
// average case: theta(n)
void BagIterator::first() {

   index_elem = 0;
   index_freq = 0;
   while( index_elem < bag.capacity && (bag.hashTable[index_elem].first == NULL_TELEM || bag.hashTable[index_elem].first == DELETED_TELEM) )
       index_elem ++;
   if (index_elem < bag.capacity)
       index_freq = 1;
}


//best case: theta(1),
//worst case: theta(n),
//general case: O(n)
// average case: theta(n)
void BagIterator::next() {
	if (valid())
    {
        if ( index_freq < bag.hashTable[index_elem].second)
            index_freq ++;
        else
        {
            index_elem++;
            index_freq = 1;

            while(index_elem < bag.capacity && (bag.hashTable[index_elem].first == NULL_TELEM || bag.hashTable[index_elem].first == DELETED_TELEM))
                index_elem++;

        }
    }
    else
        throw exception();

}

//complexity: theta(1)
bool BagIterator::valid() const {

	return index_elem < bag.capacity && bag.hashTable[index_elem].first != NULL_TELEM && bag.hashTable[index_elem].first != DELETED_TELEM;

}

//complexity: theta(1)
TElem BagIterator::getCurrent() const
{

    if (!valid()) {
        throw exception();
    }
    return bag.hashTable[index_elem].first;
}
