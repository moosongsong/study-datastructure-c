package Stack;

public class StackMain {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Stack st = new Stack();
		
		for (int i = 0; i < 10; i++) {
			st.push(i);
		}
		while (!st.isEmpty()) {
			System.out.println(st.pop());
		}
	}

}
