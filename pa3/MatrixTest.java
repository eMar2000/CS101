//-----------------------------------------------------------------------------
//  MatrixTest.java
//  Name: Eric Mar
//  CruzID: emmar
//
//  Matrix adt test client
//-----------------------------------------------------------------------------

import java.util.*;
import java.io.*;

public class MatrixTest {

	MatrixTest(){}

	public static void main(String[] args) {
		MatrixTest l = new MatrixTest();
		l.run();
	}

	public void run(){
		Matrix A = new Matrix(3);
		A.changeEntry(1, 2, 1.0);
		Matrix B = A.copy();
		System.out.println(A.equals(B));
		System.out.println(A);
		System.out.println(A.getNNZ() + " || " + A.getSize());

		A = A.scalarMult(2.0);
		System.out.println(A);
		A.changeEntry(2, 3, 5.0);
		System.out.println(A);
		A = A.add(A);
		System.out.println(A);
		A = A.sub(B);
		System.out.println(A);
		A = A.transpose();
		System.out.println(A);
		A = A.mult(B);
		System.out.println(A);

		A.makeZero();
		System.out.println(A);
		System.out.println(A.getNNZ() + " || " + A.getSize());
	}

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
}