//-----------------------------------------------------------------------------
//  List.java
//  Name: Eric Mar
//  CruzID: emmar
//
//  List ADT with get functions, comparison function, list modification function
//  List transversal function, list copy function, and print function.
//-----------------------------------------------------------------------------

public class List {

	private Node cursor;
	private Node front;
	private Node back;
	private int index;
	private int length;

	// Constructor
	// Creates a new empty list.
	List() {
		cursor = null;
		front = null;
		back = null;
		index = -1;
		length = 0;
	}

	// Access functions

	// Returns the number of elements in this List.
	int length() {
		return length;
	}

	// If cursor is defined, returns the index of the cursor element,
	// otherwise returns -1.
	int index() {
		return index;
	}

	// Returns front element. Pre: length()>0
	Object front() {
		if (!(length > 0)){
			System.err.println("No Elements in List");
			return null;
		}
		return front.data;
	}

	// Returns back element. Pre: length()>0
	Object back() {
		if (!(length > 0)){
			System.err.println("No Elements in List");
			return null;
		}
		return back.data;
	}

	// Returns cursor element. Pre: length()>0, index()>=0
	Object get() {
		if (!(length > 0)){
			System.err.println("No Elements in List");
			return null;
		}
		return cursor.data;
	}

	// Returns true if and only if this List and L are the same
	// integer sequence. The states of the cursors in the two Lists
	// are not used in determining equality.
	public boolean equals(Object X) {
		if (X instanceof List){
			List L = (List)X;

			Node p = this.front;
			Node q = L.front;

			
			if (this.length() != L.length())
				return false;
			while(p != null && q != null){
				if (p.data != q.data)
					return false;
				p = p.next;
				q = q.next;
			}
			return true;
		}

		return false;
	}

	// Manipulation procedures

	// Resets this List to its original empty state.
	void clear() {
		this.cursor = null;
		this.front = null;
		this.back = null;
		this.index = -1;
		this.length = 0;
	}

	// If List is non-empty, places the cursor under the front element,
	// otherwise does nothing.
	void moveFront() {
		if (length != 0) {
			cursor = front;
			index = 0;
		}
	}

	// If List is non-empty, places the cursor under the back element,
	// otherwise does nothing.
	void moveBack() {
		if (length != 0) {
			cursor = back;
			index = length - 1;
		}
	}

	// If cursor is defined and not at front, moves cursor one step toward
	// front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void movePrev() {
		if (cursor != null){
			if (cursor == front){
				cursor = null;
				index = -1;
			}
			else{
				cursor = cursor.prev;
				index--;
			}
		}
	}

	// If cursor is defined and not at back, moves cursor one step toward
	// back of this List, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void moveNext() {
		if (cursor != null){
			if (cursor == back){
				cursor = null;
				index = -1;
			}
			else{
				cursor = cursor.next;
				index++;
			}
		}
	}

	// Insert new element into this List. If List is non-empty,
	// insertion takes place before front element.
	void prepend(Object data) {
		Node insert = new Node (data, front, null);
		if (front != null)
			this.front.prev = insert;
		if (back == null)
			this.back = insert;
		this.front = insert;
		this.length++;
		if (cursor != null)
			index++;
	}

	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element.
	void append(Object data) {
		Node insert = new Node (data, null, back);
		if (back != null)
			this.back.next = insert;
		if (front == null)
			this.front = insert;
		this.back = insert;
		this.length++;
	}

	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	void insertBefore(Object data) {
		if (!(length > 0))
			System.err.println("No Elements in List");
		else if (!(index >= 0))
			System.err.println("No Cursor Identified");
		else {
			if (cursor == front)
				prepend(data);
			else {
				Node insert = new Node (data, cursor, cursor.prev);
				this.cursor.prev.next = insert;
				this.cursor.prev = insert;
				this.length++;
				index++;
			}
		}
	}

	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0
	void insertAfter(Object data) {
		if (!(length > 0))
			System.err.println("No Elements in List");
		else if (!(index >= 0))
			System.err.println("No Cursor Identified");
		else {
			if (cursor == back)
				append(data);
			else {
				Node insert = new Node (data, cursor.next, cursor);
				this.cursor.next.prev = insert;
				this.cursor.next = insert;
				this.length++;
			}
		}
	}

	// Deletes the front element. Pre: length()>0
	void deleteFront() {
		if (!(length > 0))
			System.err.println("No Elements in List");
		else{
			if (cursor == front){
				cursor = null;
				index = -1;
			}
			if (back == front)
				this.back = null;
			this.front = front.next;
			if (index >= 0)
				index--;
			length--;
		}
	}

	// Deletes the back element. Pre: length()>0
	void deleteBack() {
		if (!(length > 0))
			System.err.println("No Elements in List");
		else{
			if (cursor == back){
				cursor = null;
				index = -1;
			}
			if (front == back)
				this.front = null;
			this.back = back.prev;
			length--;
		}
	}

	// Deletes cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0

	void delete() {
		if (!(length > 0))
			System.err.println("No Elements in List");
		else if (!(index >= 0))
			System.err.println("No Cursor Identified");
		else{
			if (cursor == front)
				deleteFront();
			else if (cursor == back)
				deleteBack();
			else{
				cursor.prev = cursor.next;
				cursor.next.prev = cursor.prev;
				cursor = null;
				index = -1;
				length--;
			}
		}
	}

	// Other methods

	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space
	// separated sequence of integers, with front on left.
	public String toString() {
		if (front != null){
			String s = front.toString();
			Node temp = front.next;
			while (temp != null){
				s += " " + temp.toString();
				temp = temp.next;
			}
			return s;
		}
		return "";
	}

	private class Node {
		private Object data;
		private Node next;
		private Node prev;

		Node(Object d, Node n, Node p){
			data = d;
			next = n;
			prev = p;
		}

		public String toString() {
			return "" + data;
		}
	}
}