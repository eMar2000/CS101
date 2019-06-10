//-----------------------------------------------------------------------------
//  ListTest.java
//  Name: Eric Mar
//  CruzID: emmar
//
//  List adt test client
//-----------------------------------------------------------------------------

import java.util.*;
import java.io.*;

public class ListTest {

	ListTest(){}

	public static void main(String[] args) {
		ListTest l = new ListTest();
		l.run();
	}

	public void run(){
		List A = new List();
		List B = new List();
		A.append(new Entry(1, 1.0));
		B.append(new Entry(1, 1.0));
		System.out.println(A.equals(B));
		A.moveFront();
		A.prepend(new Entry(2, 2.0));
		A.insertBefore(new Entry(3, 3.0));
		A.insertAfter(new Entry(4, 4.0));
		System.out.println(A);
		A.moveFront();
		System.out.println(A.get() + " || " + A.length() + " || " + A.index() + " || " + A.front() + " || " + A.back());
		A.moveNext();
		System.out.println(A.get());
		A.movePrev();
		System.out.println(A.get());
		A.moveBack();
		System.out.println(A.get());

		A.deleteFront();
		System.out.println(A);
		A.deleteBack();
		System.out.println(A);
		A.moveFront();
		A.delete();
		System.out.println(A);
		A.clear();
		System.out.println(A);
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