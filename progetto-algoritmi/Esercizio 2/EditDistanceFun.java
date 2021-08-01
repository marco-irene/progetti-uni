
import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class EditDistanceFun {
   
    /**
     * Wrap function for edit_distance(String s1, String s2, int canc, int ins)
     *
     * @param s1: first string to compare
     * @param s2: second string to compare
     * @return: integer representing the edit distance between the two strings as described by the exercise requirements
     */

    public static int edit_distance(String s1, String s2) {
        return edit_distance(s1, s2, 0, 0);
    }

    /**
     * @param s1:   first string to compare
     * @param s2:   second string to compare
     * @param canc: integer to keep track of how many cancellations happened
     * @param ins:  integer to keep track of how many cancellations happened
     * @return: integer representing the edit distance between the two strings as described by the exercise requirements
     * (minimum between canc and ins)
     */
    public static int edit_distance(String s1, String s2, int canc, int ins) {
        if (s1.length() == 0) {
            return s2.length();
        } else if (s2.length() == 0) {
            return s1.length();
        } else { //confronta le stringhe caso per caso
            if (s1.charAt(0) == s2.charAt(0)) { //se uguali richiama la funzione togliendo il primo elem
                return edit_distance(s1.substring(1), s2.substring(1), canc, ins);
            } else { //richiama 2 volte la funzione con canc e ins
                canc = 1 + edit_distance(s1, s2.substring(1), canc, ins);
                ins = 1 + edit_distance(s1.substring(1), s2, canc, ins);
            }
        }
        return Math.min(canc, ins);
    }

    /**
     * Wrap function for edit_distance_dyn(String s1, String s2, int i, int j, int[][] mem)
     *
     * @param s1: first string to compare
     * @param s2: second string to compare
     * @return: integer representing the edit distance between the two strings obtained through dynamic programming (memoization)
     */
    //questa è come una tabella di battaglia navale con s1 ed s2 che si incrociano
    public static int edit_distance_dyn(String s1, String s2) {
        int[][] mem = new int[s1.length()][s2.length()];
        for (int i = 0; i < s1.length(); i++) {
            for (int j = 0; j < s2.length(); j++) {
                mem[i][j] = -1;
            }
        }
        return edit_distance_dyn(s1, s2, s1.length() - 1, s2.length() - 1, mem);
    }

    /**
     * @param s1:  first string to compare
     * @param s2:  second string to compare
     * @param i:   index to keep track of the position within s1
     * @param j:   index to keep track of the position within s2
     * @param mem: memoization matrix to keep track of the edit distance between substrings
     * @return: integer representing the edit distance between the two strings obtained through dynamic programming (memoization)
     */
    public static int edit_distance_dyn(String s1, String s2, int i, int j, int[][] mem) {
        //se i < 0 significa che i aveva un solo elemento quindi servono j cancellazioni
        //se j > i ecco quante cancellazione servono
        if (i < 0) {
            return j + 1;
        }
        //se j < 0 significa che j aveva un solo elemento quindi servono i cancellazioni
        if (j < 0) {
            return i + 1;
        }
        //deve essereci scritto il risultato!!
        if (mem[i][j] != -1) {
            return mem[i][j];
        }
        if (Character.toLowerCase(s1.charAt(i)) == Character.toLowerCase(s2.charAt(j))) {
            mem[i][j] = edit_distance_dyn(s1, s2, i - 1, j - 1, mem);
            //in questo modo è giusto che venga ritornata j+1 al primo controllo
        } else {
            //altrimenti ritorna il minimo +1 delle chiamate ricorsive della stessa funzione
            mem[i][j] = 1 + Math.min(edit_distance_dyn(s1, s2, i, j - 1, mem), edit_distance_dyn(s1, s2, i - 1, j, mem));
        }
        return mem[i][j];
    }
}



