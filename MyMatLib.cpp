// MyMatLb.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
using namespace std;


// matlib.cpp : A simple matrix library program.
// Written by Prof Richard Mitchell    7/1/22
//



struct myMat {			// allows for matrices up to size 4*4
	int numRows;		// number of rows
	int numCols;		// number of columns
	int data[16];		// data are stored in row order
};

myMat zeroMat(int r, int c) {
	// create a matrix with r rows and c columns, filled with zeros
	myMat m;			// define matrix
	m.numRows = r;		// set size
	m.numCols = c;
	for (int ct = 0; ct < 16; ct++) m.data[ct] = 0;	// set elems to 0
	return m;			// return matrix
}

int getElem(myMat m, int r, int c) {
	// return the item at m[r,c]   where r is 0..m.numRows-1 etc
	return m.data[r * m.numCols + c];
}

void setElem(myMat& m, int r, int c, int val) {
	// set element m[r,c] to val
	m.data[r * m.numCols + c] = val;
}

myMat mFromStr(string s) {
	// create a matrix from string s
	// string of form "1,2;3,4;5,6"   ; separates rows and , separates columns ... No error check
	int ms;
	if (s.length() > 0) ms = 1; else ms = 0;
	myMat m = zeroMat(ms, ms);						// is s empty create 0*0 matrix, else start with 1*1 matrix
	int mndx = 0;									// used to index into array
	string sub = "";								// sub string - numbers between , or ; set empty
	for (int ct = 0; ct < s.length(); ct++) {		// each char in turn
		if ((s[ct] == ',') || (s[ct] == ';')) {	// if , or ; then sub contains number
			m.data[mndx++] = stoi(sub);				// convert number to integer, put in data array
			sub = "";								// clear sub string
			if (s[ct] == ';') m.numRows++;			// if found ; indicates an extra row
			else if (m.numRows == 1) m.numCols++;	// if , then (if in row 1) increase count of columns
		}
		else sub = sub + s[ct];						// add character to sub string
	}
	if (sub.length() > 0) m.data[mndx++] = stoi(sub);// add last sub string
	return m;
}

myMat mGetRow(myMat m, int row) {
	// create a matrix from m, having one row
	myMat res = zeroMat(1, m.numCols);		// create a matrix of 1 row
	for (int col = 0; col < m.numCols; col++)		// for each element in row
		res.data[col] = getElem(m, row, col);		// copy col element to res
	return res;
}


myMat mGetCol(myMat m, int col) {					// create a matrix from m which only includes one column
	myMat res = zeroMat(m.numRows, 1);				// create a matrix of 1 column
	for (int row = 0; row < m.numRows; row++)		// for each element in the column ...
		res.data[row] = getElem(m, row, col);		// ... copy row element to res
	return res;										// returns matrix res
}

int mdotProd(myMat v1, myMat v2) {					 // outputs the dot product from matrices v1 and v2
	int dotprod = 0;								 // initialises dotprod integer					
	int size = v1.numCols * v1.numRows;				 // creates size to make sure all the number are added
	for (int i = 0; i < size; i++)					 // for every element in the matrix ...
		dotprod = dotprod + v1.data[i] * v2.data[i]; // ... multiplies the two corresponding data values, adding them to dotprod
	return dotprod;									 // returns the dotproduct
}

myMat mTranspose(myMat m) {												// outputs the transposition of matrix m
	myMat res = zeroMat(m.numCols, m.numRows);							// creates a matrix where the values of the column and rows are swapped
	for (int row = 0; row < res.numRows; row++)							// for each element in the number of rows in res ...		
		for (int col = 0; col < res.numCols; col++)						// ... for each element in the number of columns in res ...
			res.data[(row * res.numCols + col)] = getElem(m, col, row); /* ... ... loops through each rowand column, copying the data from that position
																					 into its corresponding position in the new matrix */
	return res;															// returns matrix res
}

myMat mAdd(myMat v1, myMat v2) {					// outputs the matrix addition of v1 and v2
	myMat res = zeroMat(v1.numRows, v1.numCols);	// creating the matrix, with the same numCols and numRows of v1
	int size = v1.numRows * v1.numCols;				// creates integer size that is the multiplication of the numRows and numCols of v1
	for (int i = 0; i <= size; i++)					// for the size of size ...
		res.data[i] = v1.data[i]+v2.data[i];		// ... add all the corresponding
	return res;										// returns matrix res
}

myMat mMult(myMat v1, myMat v2) {										  // outputs the matrix multiplication of matrices v1 and v2
	int x = 0;															  // creates an integer x and assigns value 0 to it
	myMat res = zeroMat(v1.numRows, v2.numCols);						  // creating the matrix with the numRows of v1 and numCols of v2
	for (int row = 0; row < v1.numRows; row++) {						  // for each element in the row of v1...
		for (int col = 0; col < v2.numCols; col++) {					  // ... for each element in the column of v2 ...
			for (int i = 0; i < v1.numCols; i++) {						  // ... ... for each element in the column of v1 ...
				res.data[x] += getElem(v1, row, i) * getElem(v2, i, col); /* ... ... ... add the multiplication of each corresponding 
																						element in m1 and m2 to res.data position*/
			}
			x++;														  // add a value to x to go to the next value of res.data 
		}
	}
	return res;															  // returns matrix res
}

myMat mMultScalar(myMat m, int s) {								// outputs the scalar multiplication of matrix m by factor s
	myMat res = zeroMat(m.numRows, m.numCols);					// creating the matrix res with same rows and cols as m
	for (int row = 0; row < m.numRows; row++) {					// for each element in the rows of m ...
		for (int col = 0; col < m.numCols; col++) {				// ... for each element in the column of m ...
			setElem(res, row, col, getElem(m, row, col) * s);	// ... ... set the elements of res as the corresponding element in m multiplied by s
		}
	}
	return res;													//returns matrix res
}

void printMat(const char* mess, myMat m) {
	// mess is string to be printed, followed by matrix m
	cout << mess << " = " << "\n";				// print message
	for (int r = 0; r < m.numRows; r++) {		// do each row
		for (int c = 0; c < m.numCols; c++)		// do each column
			cout << getElem(m, r, c) << "\t";	// outputing the element then tab
		cout << "\n";							// output new line at end of row
	}
	cout << "\n";								// and end of Matrix
}

int main()
{
	cout << "Aadil's adaptation of Ric's Matrix Example Program\n";
	myMat m1, m2, m3, m4, m5, m6, m7;									// configures matrices to be used in the equations
	m1 = mFromStr("1,2,7;6,10,2");										// sets m1/A
	m2 = mFromStr("10,7;10,10;1,6");									// sets m2/C
	printMat("A", m1);													// display m1/A
	printMat("C", m2);													// display m2/C
	printMat("A row 0", mGetRow(m1, 0));								// display row 0 of m1/A
	printMat("A column 0", mGetCol(m1, 0));								// display row 0 of m1/C
	cout << "Dot Product of A and C is " << mdotProd(m1, m2) << "\n";	// display the dot product of m1&m2/A&C
	cout << endl;
	m3 = mAdd(m1, mTranspose(m2));										
	printMat("A+C^T", m3);												// calculate then display the answer to m1+m2^T/A+C^T
	m4 = mMult(m1, m2);													
	printMat("A*C", m4);												// calculate then display the answer to m1*m2/A*C
	m5 = mMult(m2, m1);
	printMat("C*A", m5);												// calculate then display the answer to m2*m1/C*A
	m6 = mMultScalar(m1, 5);											// increases m1/A by 5
	m7 = mMultScalar(m2, -4);											// increase m2/C by -4
	printMat("5A-4C^T", mAdd(m6, mTranspose(m7)));						// uses the bigger values to work out the answer to 5A-4C^T
	system("pause");
	return 0;
}
