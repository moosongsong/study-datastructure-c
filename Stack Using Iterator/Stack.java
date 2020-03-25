package Stack;

public class Stack {
	//private int[] members;
	private Node members;
	private int top;
	
	public Stack() {
		members = null;
		top=0;
	}
	
	public void push(int value) {
		members = new Node(value, members);
		top++;
	}
	
	public int pop() {
		top--;
		int tmp = members.getData();
		members=members.getNextNode();
		return tmp;
	}
	
	public int getSize() {
		return top;
	}
	
	public boolean isEmpty() {
		return(top==0);
	}
}
