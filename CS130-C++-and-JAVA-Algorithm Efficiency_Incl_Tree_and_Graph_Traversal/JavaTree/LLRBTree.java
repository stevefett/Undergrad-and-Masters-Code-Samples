/**
 *  A Left Leaning Red Black Tree for
 *  Sacramento State CSC 130 Home Work 3
 *
 * @author Steven Salmons
 * @param <K>
 */

public class LLRBTree<K extends Comparable<K>> {

    private static final boolean RED = true;
    private static final boolean BLACK = false;

    private Node root;

    /**
     * Base case method for insertion
     *
     * @param key K
     */
    public void insert(K key) {
        root = insert(root, key);
        root.color = BLACK;
    }

    /* Recursive insertion helper method */
    private Node insert(Node h, K key) {

        if (h == null) {
            return new Node(key, 1, RED);
        }

        int cmp = key.compareTo(h.key);

        if (cmp < 0) {
            h.left = insert(h.left, key);
        }

        else if (cmp > 0) {
            h.right = insert(h.right, key);
        }

        if (isRed(h.right) && !isRed(h.left)) {
            h = leftRotation(h);
        }

        if (isRed(h.left) && isRed(h.left.left)){
            h = rightRotation(h);
        }

        if (isRed(h.left) && isRed(h.right)) {
            flipColors(h);
        }

        h.depth = depth(h.left) + depth(h.right) + 1;

        return h;
    }

    /* Helper Method for subtree depth */
    private int depth(Node x) {
        if(x==null) {
            return 0;
        }
        return x.depth;
    }

    /* Helper method for color check */
    private boolean isRed(Node x) {
        return x != null && x.color == RED;
    }

    /* Helper method to flip noe colors */
    private void flipColors(Node h) {
        h.color = RED;
        h.left.color = BLACK;
        h.right.color = BLACK;
    }

    /* Right Rotation helper method */
    private Node rightRotation(Node h) {
        Node x = h.left;
        h.left = x.right;
        x.color = h.color;
        h.color = RED;
        x.depth = h.depth;
        h.depth = 1 + depth(h.left) + depth(h.right);
        return x;

    }

    /* Left Rotation helper method */
    private Node leftRotation(Node h ) {
        Node x = h.right;
        h.right = x.left;
        x.left = h;
        x.color = h.color;
        h.color = RED;
        x.depth = h.depth;
        h.depth = 1 + depth(h.left) + depth(h.right);
        return x;
    }

    /* Private nested class for LLRB Tree's Node */
    private class Node {

        private K key;
        private Node left;
        private Node right;
        private int depth;
        private boolean color;

        /**
         * Constructor for LLRBTree Node
         * @param key K
         * @param depth int
         * @param color boolean
         */
        public Node(K key, int depth, boolean color) {
            this.key = key;
            this.depth = depth;
            this.color = color;
        }

    }

}