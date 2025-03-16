#include "Matrix.h"
#include <exception>
using namespace std;

//TODO NU STIU CUM SE FACE THETA DE LA TASTATURA ASA CA O UL MEU E THETA :'))

// Constructor
Matrix::Matrix(int nrLines, int nrCols) {
    this->rows = nrLines;
    this->cols = nrCols;
    this->capacity = 10; // Initial capacity
    this->length = 0; // Number of non-zero elements
    this->colPointers = new int[nrCols + 1]{}; // +1 for the extra last pointer, stoc indicele de inceput al fiecarei col
    this->values = new TElem[capacity]; //stoc elem nenule
    this->rowIndices = new int[capacity]; // stoc indicii randurilor corespunz val nenule
}
/*Worst/Average/Best Case: O(nrCols)
initializarea arr colPointers cu 0 pt fiecare col +1 suplimentar= complexitate lineara in fct de nrCols.*/

// Destructor
Matrix::~Matrix() {
    delete[] colPointers;
    delete[] values;
    delete[] rowIndices;
}
//const O(1)

// Returns the number of lines
int Matrix::nrLines() const {
    return this->rows;
}
//const O(1)

// Returns the number of columns
int Matrix::nrColumns() const {
    return this->cols;
}
//const O(1)

// Returns the element from line i and column j (indexing starts from 0)
TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= this->rows || j < 0 || j >= this->cols){
        throw exception();
    }
    for (int k = this->colPointers[j]; k < this->colPointers[j + 1]; k++) {
        if (this->rowIndices[k] == i) {
            return this->values[k];
        }
    }
    return NULL_TELEM;
}
/*parcurgem elem din col j pt a gasi elem de la row i, daca il gasim il return*/

/*Worst Case: O(length)
toate elem nenule sunt în coloana j, și trebuie să le parcurgem pe toate

Average Case: O(length/cols)
Pt o distribuție uniforma a elem nenule---- numărul mediu de elem pe col

Best Case: O(1)
elem cautat este primul in intervalul col j, sau col j nu contine elem nenule*/

// Modifies the value from line i and column j
TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= this->rows || j < 0 || j >= this->cols) {
        throw exception();
    }

    // Search for the element
    for (int k = this->colPointers[j]; k < this->colPointers[j + 1]; k++) {
        if (this->rowIndices[k] == i) {   //cautam elem in col j daca il gaseste return ca oldElem
            // Element found
            TElem old = this->values[k];
            if (e == NULL_TELEM) { // daca e e 0 iteram prin matrice pornind de la k si shiftam l+1
                for (int l = k; l < this->length - 1; l++) {
                    this->values[l] = this->values[l + 1];
                    this->rowIndices[l] = this->rowIndices[l + 1];
                }
                this->length--;
                for (int l = j + 1; l <= this->cols; l++) {
                    this->colPointers[l]--; //ajustam pointerii col dupa elim e
                }
            } else {
                this->values[k] = e;
            }
            return old;
        }
    }

    if (e != NULL_TELEM) { //daca e dif de 0 si e nu e deja in matrice
        // Insert new element
        if (this->length == this->capacity) { //daca s a ajuns la capacitatea max crestem
            resizeUp();
        }
        int pos = this->colPointers[j + 1]; //index de start
        for (int k = this->length; k > pos; k--) {
            this->values[k] = this->values[k - 1];
            this->rowIndices[k] = this->rowIndices[k - 1]; //shiftem ca sa facem loc pana la pos
        }
        this->values[pos] = e;
        this->rowIndices[pos] = i; //inseram elem nou
        for (int l = j + 1; l <= this->cols; l++) {
            this->colPointers[l]++;
        }
        this->length++;
    }
    return NULL_TELEM; //daca nu se schimba nimic
}
/*Worst Case: O(length) + O(cols)
pt reindexare in cazul add sau remove unui elem,cu length nr elem nenule și cols nr col,
redimensionarea arr poate adauga si O(length) la complexitate

Average Case: ca worst case--- modificarea implica parcurgerea elem și posibil reindexarea

Best Case: O(1)
modificam primul elem al unei coloane fara reindexare sau cand e= cu o val deja stocata.*/

// Resize the arrays when capacity is reached
void Matrix::resizeUp() {
    int newCapacity = this->capacity * 2;
    TElem* newValues = new TElem[newCapacity];
    int* newRowIndices = new int[newCapacity]; //alocam arr noi
    for (int i = 0; i < this->length; i++) {
        newValues[i] = this->values[i];
        newRowIndices[i] = this->rowIndices[i]; //cop elem deja ex nenule in noile arr cu tot cu indicii lor
    }
    delete[] this->values;
    delete[] this->rowIndices; //eliberam memoria veche
    this->values = newValues;
    this->rowIndices = newRowIndices;//actualizam pointerii pt ce avem noi nou
    this->capacity = newCapacity; //acutalizam capacitatea!!!!!!
}
/*Worst/Average/Best Case: O(length)
copiem fiecare elem nenul in noile arr, deci timpul necesar creste linear cu nr de elem nenule*/

Matrix Matrix::transpose() const {
    Matrix transposed(this->cols, this->rows);

    //arr pt nr de elem pe fiecare linie noua (col intiala)
    int* count = new int[this->rows + 1]{}; // pt ultimul pointer

    // spatiu pt val transp și ind col
    TElem* newValues = new TElem[this->length];
    int* newColIndices = new int[this->length];

    //calc nr de elem pe fiecare linie noua (col initial)
    for (int i = 0; i < this->length; i++) {
        count[this->rowIndices[i] + 1]++;
    }

    // trasnf count in arr de ptr la col
    for (int i = 1; i <= this->rows; i++) {
        count[i] += count[i - 1];
    }

    //copiez count in colPtr al transp pentru a evita pierderea referinței la începutul array-ului
    for (int i = 0; i <= this->rows; i++) {
        transposed.colPointers[i] = count[i];
    }
    for (int col = 0; col < this->cols; col++) {
    }
}
    //plasam elem in noua lor pos
    //actualizam datele pt matricea transp
    //eliberam memoria aloc temporar


