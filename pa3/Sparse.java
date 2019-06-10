//-----------------------------------------------------------------------------
//  Sparse.java
//  Name: Eric Mar
//  CruzID: emmar
//
//  Top level client module for this project
//-----------------------------------------------------------------------------

import java.util.*;
import java.io.*;

public class Sparse {
	public static void main(String[] args) throws IOException {

		//Pre: args == 2
		if (args.length != 2) {
			System.err.println("Requires 2 Args");
			System.exit(1);
		}

		Scanner in = new Scanner(new File(args[0]));
    	PrintWriter out = new PrintWriter(new FileWriter(args[1]));
    	int n, a, b = 0;
    	String line = "";
    	String[] tokens = new String[3];

    	line = in.nextLine();
    	tokens = line.split(" ");

    	n = Integer.parseInt(tokens[0]);
    	a = Integer.parseInt(tokens[1]);
    	b = Integer.parseInt(tokens[2]);

    	Matrix A = new Matrix(n);
    	Matrix B = new Matrix(n);

    	in.nextLine();
    	line = in.nextLine();

    	while (!line.isEmpty()) {
    		tokens = line.split(" ");
    		A.changeEntry(Integer.parseInt(tokens[0]), Integer.parseInt(tokens[1]), Double.parseDouble(tokens[2]));
    		line = in.nextLine();
    	}

    	while (in.hasNext()) {
    		line = in.nextLine();
    		tokens = line.split(" ");
    		B.changeEntry(Integer.parseInt(tokens[0]), Integer.parseInt(tokens[1]), Double.parseDouble(tokens[2]));
    	}

    	out.print("A has " + a + " non-zero entries:");
    	out.println(A + "\n");

    	out.print("B has " + b + " non-zero entries:");
    	out.println(B + "\n");

    	out.print("(1.5)*A =");
    	out.println(A.scalarMult(1.5));

    	out.print("A+B =");
    	out.println(A.add(B) + "\n");

    	out.print("A+A =");
    	out.println(A.add(A) + "\n");

    	out.print("B-A =");
    	out.println(B.sub(A) + "\n");

    	out.print("A-A =");
    	out.println(A.sub(A) + "\n");

    	out.print("Transpose(A) =");
    	out.println(A.transpose() + "\n");

    	out.print("A*B =");
    	out.println(A.mult(B) + "\n");

    	out.print("B*B =");
    	out.println(B.mult(B) + "\n");

    	in.close();
		out.close();
	}
}