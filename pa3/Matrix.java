//-----------------------------------------------------------------------------
//  Matrix.java
//  Name: Eric Mar
//  CruzID: emmar
//
//  Matrix adt with matrix manipulation functions
//-----------------------------------------------------------------------------

public class Matrix {
	private List[] row;

	private class Entry {
		private int column;
		private double value;

		Entry(int c, double v){
			column = c;
			value = v;
		}

		public String toString() {
			return "(" + this.column + ", " + this.value + ")";
		}

		public boolean equals(Object X) {
			if (X instanceof Entry) {
				Entry E = (Entry)X;
				if (this.column == E.column && this.value == E.value)
					return true;
			}
			return false;
		}
	}

	// Constructor
	// Makes a new n x n zero Matrix. pre: n>=1
	Matrix(int n) {
		row = new List[n];
		for (int i = 0; i < n; i++)
			row[i] = new List();
	}

	// Access functions

	// Returns n, the number of rows and columns of this Matrix
	int getSize() {
		return this.row.length;
	}
	// Returns the number of non-zero entries in this Matrix
	int getNNZ() {
		int nnz = 0;
		for (int i = 0; i < row.length; i++) {
			nnz += row[i].length();
		}
		return nnz;
	}
	// overrides Object's equals() method
	public boolean equals(Object x) {
		if (x instanceof Matrix) {
			Matrix A = (Matrix)x;
			if (this.row.length != A.row.length)
				return false;
			for (int i = 0; i < this.row.length; i++) {
				this.row[i].moveFront();
				A.row[i].moveFront();
				if (this.row[i].length() != A.row[i].length())
					return false;
				while (this.row[i].index() != -1 && A.row[i].index() != -1) {
					if (!(((Entry)this.row[i].get()).equals((Entry)A.row[i].get()))){
						return false;
					}
					this.row[i].moveNext();
					A.row[i].moveNext();
				}
				
			}
			return true;
		}
		return false;
	}

	// Manipulation procedures

	// sets this Matrix to the zero state
	void makeZero() {
		for (int i = 0; i < this.row.length; i++) {
			row[i].clear();
		}
	}
	// returns a new Matrix having the same entries as this Matrix
	Matrix copy() {
		Matrix A = new Matrix(this.getSize());
		for (int i = 0; i < this.row.length; i++) {
			row[i].moveFront();
			while (row[i].index() != -1) {
				Entry temp = (Entry)row[i].get();
				A.row[i].append(new Entry(temp.column, temp.value));
				row[i].moveNext();
			}
		}
		return A;
	}
	// changes ith row, jth column of this Matrix to x
	// pre: 1<=i<=getSize(), 1<=j<=getSize()
	void changeEntry(int i, int j, double x) {
		boolean listEnd = false;

		if (!(1<=i && i<=getSize() && 1<=j && j<=getSize())) {
			System.err.println("Invalid index");
			return;
		}

		row[i-1].moveFront();
		while (row[i-1].index() != -1 && ((Entry)row[i-1].get()).column < j)
			row[i-1].moveNext();

		if (row[i-1].index() == -1)
			listEnd = true;

		if ((listEnd || ((Entry)row[i-1].get()).column != j) && x == 0.0)
			return;
		else if ((listEnd || ((Entry)row[i-1].get()).column != j) && x != 0.0){
			if (listEnd)
				row[i-1].append(new Entry(j, x));
			else
				row[i-1].insertBefore(new Entry(j, x));
		}
		else if (((Entry)row[i-1].get()).column == j && x == 0.0)
			row[i-1].delete();
		else if (((Entry)row[i-1].get()).column == j && x != 0.0)
			((Entry)row[i-1].get()).value =  x;
	}
	// returns a new Matrix that is the scalar product of this Matrix with x
	Matrix scalarMult(double x) {
		Matrix A = new Matrix(this.row.length);
		for (int i = 0; i < this.row.length; i++) {
			this.row[i].moveFront();
			while (this.row[i].index() != -1) {
				A.row[i].append(new Entry(((Entry)this.row[i].get()).column, x*((Entry)this.row[i].get()).value));
				row[i].moveNext();
			}
		}
		return A;
	}
	// returns a new Matrix that is the sum of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix add(Matrix M) {
		if (this.getSize() != M.getSize()) {
			System.err.println("Matrix size missmatch");
			return null;
		}

		Matrix A = new Matrix(this.row.length);
		M = M.scalarMult(1.0);
		for (int i = 0; i < this.row.length; i++) {
			addList(A.row[i], this.row[i], M.row[i]);
		}
		return A;
	}
	// returns a new Matrix that is the difference of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix sub(Matrix M) {
		if (this.getSize() != M.getSize()) {
			System.err.println("Matrix size missmatch");
			return null;
		}

		Matrix A = new Matrix(this.row.length);
		M = M.scalarMult(-1.0);
		for (int i = 0; i < this.row.length; i++) {
			addList(A.row[i], this.row[i], M.row[i]);
		}
		return A;
	}
	// returns a new Matrix that is the transpose of this Matrix
	Matrix transpose() {
		Matrix A = new Matrix(this.row.length);
		for (int i = 0; i < this.row.length; i++) {
			this.row[i].moveFront();
			while (this.row[i].index() != -1) {
				A.row[((Entry)this.row[i].get()).column-1].append(new Entry(i+1, ((Entry)this.row[i].get()).value));
				this.row[i].moveNext();
			}
		}
		return A;
	}
	// returns a new Matrix that is the product of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix mult(Matrix M) {
		if (this.getSize() != M.getSize()) {
			System.err.println("Matrix size missmatch");
			return null;
		}

		Matrix A = new Matrix(this.row.length);
		M = M.transpose();
		for (int i = 0; i < this.row.length; i++) {
			for (int j = 0; j < M.row.length; j++) {
				A.changeEntry(i+1, j+1, dot(this.row[i], M.row[j]));
			}
		}
		return A;
	}

	// Other functions

	// overrides Object's toString() method
	public String toString() {
		String A = "";
		int c = 0;
		for (int i = 0; i < this.row.length; i++) {
			if (row[i].length() != 0) {
				c = i + 1;
				A += "\n" + c + ":";
				this.row[i].moveFront();
				while (this.row[i].index() != -1) {
					A += " " + ((Entry)this.row[i].get());
					this.row[i].moveNext();
				}
			}
		}
		return A;
	}

	private static double dot(List P, List Q) {
		double dotProduct = 0.0;
		P.moveFront();
		Q.moveFront();
		while (Q.index() != -1 && P.index() != -1) {
			if (((Entry)P.get()).column < ((Entry)Q.get()).column)
				P.moveNext();
			else if (((Entry)P.get()).column > ((Entry)Q.get()).column)
				Q.moveNext();
			else if (((Entry)P.get()).column == ((Entry)Q.get()).column){
				dotProduct += (((Entry)P.get()).value * ((Entry)Q.get()).value);
				P.moveNext();
				Q.moveNext();
			}
		}
		return dotProduct;
	}

	private void addList(List L, List P, List Q) {
		P.moveFront();
		Q.moveFront();
		while (Q.index() != -1 || P.index() != -1) {
			if (Q.index() == -1) {
				L.append(new Entry(((Entry)P.get()).column, ((Entry)P.get()).value));
				P.moveNext();
			}
			else if (P.index() == -1) {
				L.append(new Entry(((Entry)Q.get()).column, ((Entry)Q.get()).value));
				Q.moveNext();
			}
			else if (((Entry)P.get()).column < ((Entry)Q.get()).column) {
				L.append(new Entry(((Entry)P.get()).column, ((Entry)P.get()).value));
				P.moveNext();
			}
			else if (((Entry)P.get()).column > ((Entry)Q.get()).column) {
				L.append(new Entry(((Entry)Q.get()).column, ((Entry)Q.get()).value));
				Q.moveNext();
			}
			else if (((Entry)P.get()).column == ((Entry)Q.get()).column){
				if (((Entry)P.get()).value + ((Entry)Q.get()).value != 0.0)
					L.append(new Entry(((Entry)P.get()).column, ((Entry)P.get()).value + ((Entry)Q.get()).value));
				P.moveNext();
				Q.moveNext();
			}
		}
	}
}