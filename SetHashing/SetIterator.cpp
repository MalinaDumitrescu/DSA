#include "SetIterator.h"
#include "Set.h"


SetIterator::SetIterator(const Set &m) : set(m) {
    this->currentIndex = 0;
    for (int parser = 0; parser < this->set.primeNumber; parser++) {
        if (this->set.values[parser] != DELETED_TELEM && this->set.values[parser] != NULL_TELEM) {
            this->currentIndex = parser;
            return;
        }
    }
    this->currentIndex = -1;
}


void SetIterator::first() {
    for (int parser = 0; parser < this->set.primeNumber; parser++) {
        if (this->set.values[parser] != DELETED_TELEM && this->set.values[parser] != NULL_TELEM) {
            this->currentIndex = parser;
            return;
        }
    }
}


void SetIterator::next() {
    if (valid()) {
        for (int parser = this->currentIndex+1; parser < this->set.primeNumber; parser++) {
            if (this->set.values[parser] != DELETED_TELEM && this->set.values[parser] != NULL_TELEM) {
                this->currentIndex = parser;
                return;
            }
        }
        this->currentIndex = -1;
    } else {
        throw std::exception();
    }
}


TElem SetIterator::getCurrent() {
    if (valid()) {
        return this->set.values[this->currentIndex];
    } else {
        throw std::exception();
    }

}

bool SetIterator::valid() const {
    if (this->currentIndex == -1) {
        return false;
    }
    return true;
}



