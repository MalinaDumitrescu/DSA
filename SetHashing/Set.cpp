#include "Set.h"
#include "SetIterator.h"

Set::Set() {
    this->length = 0;
    this->primeNumber = 1153;  //cap?
    this->values = new TElem [this->primeNumber];
    this->initArray();
}

void Set::initArray() {
    for(int parser = 0 ; parser < this->primeNumber ; parser++){
        this->values[parser] = NULL_TELEM;
    }
}

bool isPrime(int n)
{
    // Corner case
    if (n <= 1)
        return false;

    // Check from 2 to n-1
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;

    return true;
}

int nextPrime (int n){
    int i= 2*n+1;
    while(!isPrime(i)){
        i++;
    }
    return i;
}

void Set::resizeAndRehash() {
    int previousPrime = this->primeNumber;
    this->primeNumber = nextPrime(previousPrime);

    TElem *auxValues = new TElem [this->primeNumber];
    //init the auxValues
    for(int parser = 0 ; parser < this->primeNumber ; parser++){
        auxValues[parser] = NULL_TELEM;
    }
    for(int valueIndex = 0 ; valueIndex < previousPrime ; valueIndex++){
        if(this->values[valueIndex] != NULL_TELEM){
            int startPosition = this->hash(this->values[valueIndex] , 0);
            int parser = this->hash(this->values[valueIndex] , 0);
            int incrementor = 0;
            while(true){
                if(auxValues[parser] == NULL_TELEM){
                    auxValues[parser] = this->values[valueIndex];
                    break;
                }
                incrementor++;
                parser = this->hash(this->values[valueIndex] , incrementor);
                if(incrementor == this->primeNumber){
                    delete[] auxValues;
                    this->resizeAndRehash();
                    return;
                }
            }
        }
    }
    delete[] this->values;
    this->values = auxValues;

}

int Set::hash(TElem key , int index) const {
    if(key < 0){
        key = -key;
    }
    return (key % this->primeNumber + index * ( 1 + key%(this->primeNumber - 1)))% this->primeNumber;
}
bool Set::add(TElem elem) {
    int incrementor = 0;
	int startPosition = this->hash(elem , 0);
    int parser = this->hash(elem , 0);
    if(this->search(elem)){
        //already inside
        return false;

    }
    //check the population
    if(this->length / (this->primeNumber *1.) > 0.75){
        this->resizeAndRehash();
    }
    while(true){
        //check if the position we are at is an ok position to insert
        if(this->values[parser] == NULL_TELEM || this->values[parser] == DELETED_TELEM){
            this->values[parser] = elem;
            this->length++;
            return true;
        }
        //check further
        incrementor++;
        parser = this->hash(elem , incrementor);

        if(parser == startPosition){
            this->resizeAndRehash();
            return this->add(elem);
        }
    }
    return false;
}


bool Set::remove(TElem elem) {
	int parser = hash(elem , 0);
    int counter = 0;
    while (counter < this->primeNumber){
        if(this->values[parser] == elem){
            this->values[parser] = DELETED_TELEM;
            this->length--;
            return true;
        }
        counter++;
        parser = this->hash(elem , counter);

    }
	return false;
}

bool Set::search(TElem elem) const {
    int parser = hash(elem , 0);
    int counter = 0;
    while(counter < this->primeNumber){
        if(this->values[parser] == elem){
            return true;
        }
        counter++;
        parser = this->hash(elem , counter);


    }
	return false;
}


int Set::size() const {
    return this->length;
}


bool Set::isEmpty() const {
	if(this->length == 0){
        return true;
    }
    return false;
}


Set::~Set() {
	delete[] this->values;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}


