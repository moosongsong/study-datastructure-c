package Tree;

public class BinaryTree {
	private Node root;
	
	public boolean add(int num) {
		return add(new Node(num, null, null));
	}
	
	public boolean add(Node node) {
		if(root==null) {
			root=node;
			return true;
		}
		else {
			Node current = root;
			Node preNode = current;
			
			while(current!=null) {
				preNode = current;
				if(current.getValue()>node.getValue()) {
					current = current.getLeft();
				}
				else if(current.getValue()<node.getValue()) {
					current = current.getRight();
				}
				else {
					System.out.println("Fail");
					return false;
				}
			}
			
			if(preNode.getValue()>node.getValue()) {
				preNode.setLeft(node);
				System.out.println(node.getValue()+", "+ preNode.getValue()+"'s left");
			}
			else {
				preNode.setRight(node);
				System.out.println(node.getValue()+", "+preNode.getValue()+"'s right");
			}
		}
		return true;
	}
	
	public void searchNode(Node node) {
		if(node == null) {
			return;
		}else {
			searchNode(node.getLeft());
			System.out.println(node.getValue()+" ");
			searchNode(node.getRight());
		}
	}
	
	public void searchStart() {
		searchNode(root);
	}
}
