import java.util.*;


/**
 * AVL versus Left Leaning Red Black Tree 
   Insertion Performance Analysis
 * JAVA W/ RECURSIVE, SHIFT SORTS 
 * for CSC130 Sacramento State University
 *
 * @author Steven Salmons
 */
public class Main {

    private int[] ascending;
    private int[] descending;
    private int[] random;

    private AVLTree<Integer> avlTree;
    private LLRBTree<Integer> rbTree;


    /**
     * Constructor for Tree Insertion Performance Analysis
     *
     */
    public Main() {

        int s = 0;

        ascending   = new int[1000000];
        descending  = new int[1000000];
        random      = new int[1000000];

        avlTree = new AVLTree<>();
        rbTree = new LLRBTree<>();

        for(int c = 0; c < 1000000; c++) {
            ascending[c] = c;
        }

        for(int c = 1000000-1; c > 0; c--) {
            descending[c] = s;
            s++;
        }

        random = ascending;
        random = randomize(random);

    }


    /**
     * Performance For AVL Tree Insertion
     *
     */
    public void avl() {

        long startTime;
        long stopTime;

        System.out.println("====== Building AVL Tree ======\n");

        /* Test Ascending Order */
        System.out.print("Ascending Order: ");
        startTime = System.nanoTime();
        for (int i : ascending) {
            avlTree.insert(i);
        }
        stopTime = System.nanoTime();
        System.out.println( (stopTime - startTime)*0.000000001 + " seconds.");

        avlTree = new AVLTree<>(); // Reset Tree


        /* Test Descending Order */
        System.out.print("Descending Order: ");
        startTime = System.nanoTime();
        for (int i : descending) {
            avlTree.insert(i);
        }
        stopTime = System.nanoTime();
        System.out.println( (stopTime - startTime)*0.000000001 + " seconds.");


        avlTree = new AVLTree<>(); // Reset Tree


        /* Test Random Order */
        System.out.print("Random Order: ");
        startTime = System.nanoTime();
        for (int i : random) {
            avlTree.insert(i);
        }
        stopTime = System.nanoTime();
        System.out.println( (stopTime - startTime)*0.000000001 + " seconds.");


    }

    /**
     * Performance of Left Leaning RB Tree Insertion
     *
     */
    public void rbt() {

        long startTime;
        long stopTime;


        System.out.println("\n\n====== Building Left Leaning Red-Black Tree ======\n");

        /* Test Ascending Order */
        System.out.print("Ascending Order: ");
        startTime = System.nanoTime();
        for (int i : ascending) {
           rbTree.insert(i);
        }
        stopTime = System.nanoTime();
        System.out.println( (stopTime - startTime)*0.000000001 + " seconds.");


        rbTree = new LLRBTree<>();

        /* Test Random Order */
        System.out.print("Descending Order: ");
        startTime = System.nanoTime();
        for (int i : descending) {
            rbTree.insert(i);
        }
        stopTime = System.nanoTime();
        System.out.println( (stopTime - startTime)*0.000000001 + " seconds.");



        rbTree = new LLRBTree<>();

        /* Test Random Order */
        System.out.print("Random Order: ");
        startTime = System.nanoTime();
        for (int i : random) {
            rbTree.insert(i);
        }
        stopTime = System.nanoTime();
        System.out.println( (stopTime - startTime)*0.000000001 + " seconds.");

    }


    /* Helper Method to Shuffle the Array */
    private static int[] randomize(int[] arr) {

        Random r = new Random();

        for (int c = arr.length - 1; c > 0; c--) {
            int i = r.nextInt(c + 1);
            int a = arr[i];
            arr[i] = arr[c];
            arr[c] = a;
        }

        return arr;
    }

    /**
     * Main Method for Performance Testing.
     *
     * @param args Array[String]
     */
    public static void main(String[] args) {
        Main test = new Main();
        test.avl();
        test.rbt();
    }

}
