package Tree;

public class Node {
	private int value;
	private Node right;
	private Node left;
	
	
	
	public Node(int value, Node left, Node right) {
		this.value = value;
		this.right = right;
		this.left = left;
	}

	public int getValue() {
		return value;
	}

	public Node getRight() {
		return right;
	}

	public Node getLeft() {
		return left;
	}

	public void setValue(int value) {
		this.value = value;
	}

	public void setRight(Node right) {
		this.right = right;
	}

	public void setLeft(Node left) {
		this.left = left;
	}

	@Override
	public String toString() {
		return "Node [value=" + value + "]";
	} 	
	
}
