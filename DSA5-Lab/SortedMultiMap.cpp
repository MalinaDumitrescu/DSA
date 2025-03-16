#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;


//log in baz 2 din n -- inaltimea


SortedMultiMap::SortedMultiMap(Relation r) {
    this->root= nullptr;
    this->r=r;
    this->length=0;

}
//best-->that(1)--add in root
//worst-->that(n)-- arbore degenerat
//average-->theta(log n)-- arbore echilibrat
void SortedMultiMap::add(TKey c, TValue v) {
    Node* newNode = new Node(c, v);
    //caz1 root gol-->nod ul in adaug in head root idk
    if (this->root == nullptr) {
        this->root = newNode;
    //caz2 parcurgem arb din root -->ne legam de parinte si de la el st dr in fct de r
    } else {
        Node* parser = this->root;
        Node* parent = nullptr;
        while (parser != nullptr) {
            parent = parser;
            if (r(c, parser->key)) {
                parser = parser->left;
            } else {
                parser = parser->right;
            }
        }
        if (r(c, parent->key)) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }
    length++;
}
//best-->that(1)-- elem in root
//worst-->that(n)-- arbore degenerat
//average-->theta(log n)-- arbore echilibrat
vector<TValue> SortedMultiMap::search(TKey c) const {
	vector <TValue> values;
    Node* parser = this->root;
    while(parser != nullptr){
        if(parser->key==c){
            values.push_back(parser->element);
        }
        if(r(c, parser->key)){
            parser=parser->left;
        }else{
            parser=parser->right;
        }

    }
	return values;
}
//best-->that(1)--remove root fara copii
//worst-->that(n)-- arbore degenerat--eleim ultimul nod-->+search nod cu copii
//average-->theta(log n)---arbore echilibrat
bool SortedMultiMap::remove(TKey c, TValue v) {
    Node* parser = this->root;
    Node* parent = nullptr;
//caz1 nod fara copii
    // caz2 nod cu 1 copil
    // caz3 nod cu 2 copii
    while (parser != nullptr && !(parser->key == c && parser->element == v)) {
        parent = parser;
        if (r(c, parser->key)) {
            parser = parser->left;
        } else {
            parser = parser->right;
        }
    }

    if (parser == nullptr) return false;
    //no children
    if (parser->left == nullptr && parser->right == nullptr) {
        if (parent == nullptr) {
            delete parser;
            root = nullptr;
        } else {
            if (r(c, parent->key)) {
                delete parent->left;
                parent->left = nullptr;
            } else {
                delete parent->right;
                parent->right = nullptr;
            }
        }
        length--;
        return true;
    }
    //one child
    if (parser->left == nullptr) {
        if (parent == nullptr) {
            this->root = parser->right;
        } else {
            if (r(c, parent->key)) {
                parent->left = parser->right;
            } else {
                parent->right = parser->right;
            }
        }
        delete parser;
        length--;
        return true;
    }
    if (parser->right == nullptr) {
        if (parent == nullptr) {
            root = parser->left;
        } else {
            if (r(c, parent->key)) {
                parent->left = parser->left;
            } else {
                parent->right = parser->left;
            }
        }
        delete parser;
        length--;
        return true;
    }

    //two children
    Node* successorParent = parser;
    Node* successor = parser->right;
    while (successor->left != nullptr) {
        successorParent = successor;
        successor = successor->left;
    }

    parser->key = successor->key;
    parser->element = successor->element;

    if (successorParent->left == successor) {
        successorParent->left = successor->right;
    } else {
        successorParent->right = successor->right;
    }
    delete successor;
    length--;
    return true;
}

//const theta(1)

int SortedMultiMap::size() const {
	return length;
}

bool SortedMultiMap::isEmpty() const {
   if(length==0){
       return true;
   }else{
       return false;
   }
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
//complex temp theta(n)
SortedMultiMap::~SortedMultiMap() {
    destroyNode(this->root);
}
//theta(n)
void SortedMultiMap::destroyNode(Node *node) {
    if(node !=nullptr){
        destroyNode(node->right);
        destroyNode(node->left);
        delete node;
    }
}