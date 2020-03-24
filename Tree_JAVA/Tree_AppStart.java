package Tree;

public class Tree_AppStart {

	public static void main(String[] args) {
		BinaryTree btree = new BinaryTree();
		btree.add(5);
		btree.add(100);
		btree.add(1);
		btree.add(120);
		btree.add(120);//fail
		btree.add(70);
		
		btree.searchStart();
	}

}
