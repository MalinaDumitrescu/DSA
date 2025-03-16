#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0


class Matrix {

private:
	//TODO - Representation
    TElem* values; // pointer -> arr dinamic care va stoca val nenule ale matricei
    int* colPointers; // pointer -> arr dinamic care stochează indicii unde încep coloanele din matrice
    int* rowIndices; // pointer -> arr dinamic care  memorează indicii unde încep elementele în fiecare coloană
    int rows;
    int cols;
    int capacity;
    int length;
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	[[nodiscard]] int nrLines() const;

	//returns the number of columns
	[[nodiscard]] int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	[[nodiscard]] TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

    void resizeUp();

    Matrix transpose() const;


	// destructor
	~Matrix();


};
