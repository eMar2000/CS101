//-----------------------------------------------------------------------------
//  Lex.java
//  Name: Eric Mar
//  CruzID: emmar
//
//  Creates lexographically ordered list derived from given set of elements
//-----------------------------------------------------------------------------

import java.util.*;
import java.io.*;

public class Lex {
	public static void main(String[] args) throws IOException {

		//Pre: args == 2
		if (args.length != 2) {
			System.err.println("Requires 2 Args");
			System.exit(1);
		}
		Scanner file = new Scanner(new File(args[0]));
		Scanner in = new Scanner(new File(args[0]));
    	PrintWriter out = new PrintWriter(new FileWriter(args[1]));
   		int n = 0;
		List L = new List();
		String[] A;
		
		while(file.hasNextLine()){
			n++;
			file.nextLine();
		}
		
		A = new String[n];
		for(int i = 0; i < n; i++)
			A[i] = in.nextLine();
		
		for(int i = 1; i < n; i++){
			if (L.length() == 0)
				L.prepend(0);
			L.moveFront();
			do{
				int x = A[i].compareTo(A[L.get()]);
				if (x <= 0){
					L.insertBefore(i);
					break;                                            // Break
				}
				else
					L.moveNext();
				if (L.index() == -1) {
					L.append(i);
				}
			}while (L.index() != -1);
			
		}

		L.moveFront();
		while(L.index() != -1) {                                      //Print
			out.println(A[L.get()]);
			L.moveNext();
		}

		in.close();
		file.close();
		out.close();
	}
}