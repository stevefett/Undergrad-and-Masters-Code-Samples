/**
 * An AVL Tree for Sacramento State CSC 130
 * JAVA WITH RECURSIVE TREE INSERTION ALGORITHMS
 * OPTIMIZATION/PERFORMANCE OF EACH INSERT FOR BOTH TREES
 *
 * @author Steven Salmons
 * @param <K> Key value
 */
public class AVLTree <K extends Comparable <K>> {

    private Node root;


    /**
     * Base case method for insertion
     *
     * @param key K
     * @return Node root
     */
    public Node insert(K key) {

        root = insert(root, key);

        if(balanceCheck(root) == 1) {
            root = leftRotation(root);
        }
        else if(balanceCheck(root) == -1) {
            root = rotateRight(root);
        }

        return root;

    }


    /* Recursive insertion helper method */
    private Node insert(Node node, K key) {

        if (node == null) {
            return new Node(key);
        }

        if (node.getkey().compareTo(key) > 0) {
            node = new Node(node.getkey(), insert(node.getLeft(), key), node.getRight());
        }
        else if (node.getkey().compareTo(key) < 0) {
            node = new Node(node.getkey(), node.getLeft(), insert(node.getRight(), key));
        }

        if(balanceCheck(node) == 1) {
            node = leftRotation(node);
        }
        else if(balanceCheck(node) == -1) {
            node = rotateRight(node);
        }

        return node;
    }

    /* Balance check helper method to determine greater subtree depth */
    private int balanceCheck(Node node) {

        int left = depth(node.getLeft());
        int right = depth(node.getRight());

        if (left - right >= 2)
            return -1;

        else if (left - right <= -2)
            return 1;

        return 0;
    }

    /* Left Rotation helper method */
    private Node leftRotation(Node x) {

        Node q = x;

        Node p = q.getRight();

        Node c = q.getLeft();

        Node a = p.getLeft();

        Node b = p.getRight();

        q = new Node(q.getkey(), c, a);

        p = new Node(p.getkey(), q, b);

        return p;

    }

    /* Right Rotation helper method */
    private Node rotateRight(Node x) {

        Node q = x;

        Node p = q.getLeft();

        Node c = q.getRight();

        Node a = p.getLeft();

        Node b = p.getRight();

        q = new Node(q.getkey(), b, c);

        p = new Node(p.getkey(), a, q);

        return p;
    }

    /* Helper method to determine depth */
    private int depth(Node x) {
        if (x == null) {
            return 0;
        }
        return x.getDepth();
    }

    /* Private nested class for AVL Tree's Node */
    private class Node {

        private K key;
        private Node left;
        private Node right;
        private int depth;

        /**
         * Constructor for AVL Node
         * @param key K
         */
        public Node(K key) {
            this(key, null, null);
        }

        /**
         * Constructor for AVL Node with Override parameters.
         * @param key K
         * @param left Node
         * @param right Node
         */
        public Node(K key, Node left, Node right) {

            super();

            this.key = key;
            this.left = left;
            this.right = right;

            if (left == null && right == null) {
                setDepth(1);
            }

            else if (left == null) {
                setDepth(right.getDepth() + 1);
            }

            else if (right == null) {
                setDepth(left.getDepth() + 1);
            }
            else {
                setDepth(Math.max(left.getDepth(), right.getDepth()) + 1);
            }
        }

        private K getkey() {
            return key;
        }

        private Node getLeft() {
            return left;
        }


        private Node getRight() {
            return right;
        }

        private int getDepth() {
            return depth;
        }

        private void setDepth(int depth) {
            this.depth = depth;
        }

    }

}