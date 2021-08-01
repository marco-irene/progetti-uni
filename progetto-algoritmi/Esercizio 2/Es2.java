import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

import static java.lang.Character.isLetter;

public class Es2 {

    /**
     * The method reads all the dictionary words from file and puts them into a dynamic array
     *
     * @param path: String indicating the location of the file to read from
     * @return: an ArrayList in which each entry is a word from the given dictionary
     */


    public static ArrayList <String> load_dictionary_arr(String path) {
        String line;
        ArrayList <String> dictionary = new ArrayList <String>();
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            while ((line = br.readLine()) != null) {
                dictionary.add(line);
            }
            br.close();
        } catch ( IOException e ) {
            e.printStackTrace();
        }
        return dictionary;
    }

    /**
     * The method fills a dynamic array with dynamic arrays each containing in their first position a word from the given text
     *
     * @param path: String indicating the location of the file to read from
     * @return: ArrayList of ArrayList of strings
     */
    public static ArrayList <ArrayList <String>> load_text(String path) {
        File text_file = new File(path);
        ArrayList <ArrayList <String>> to_correct_arr = new ArrayList <ArrayList <String>>();
        try {
            Scanner sc = new Scanner(text_file);
            while (sc.hasNext()) {
                String word = sc.next();
                if (!isLetter(word.charAt(word.length() - 1))) {
                    word = word.substring(0, word.length() - 1);
                }
                ArrayList <String> tmp = new ArrayList <>();
                tmp.add(word);
                to_correct_arr.add(tmp);
            }
        } catch ( FileNotFoundException e ) {
            e.printStackTrace();
        }
        return to_correct_arr;
    }

    public static void printArray(ArrayList <ArrayList <String>> text){
	    for (ArrayList <String> word : text) {
            System.out.print(word.get(0) + " ==> ");
            for (int i = 1; i < word.size(); i++) {
                System.out.print(word.get(i));
                if (word.size() - i > 1) {
                    System.out.print(", ");
                }
            }
            System.out.println();
        }
    }

    /**
     * For every word absent from the dictionary (every wrong word) finds the words in the dictionary
     * that have an edit distance of less than 3 saving them in the text ArrayList following the wrong word they correct
     *
     * @param dictionary: dictionary ArrayList
     * @param text: text ArrayList
     */
    public static void suggestion(ArrayList <String> dictionary, ArrayList <ArrayList <String>> text) {

        for (int i = 0; i < text.size(); i++) {
            int min = 3;
            boolean min_found = false;
            boolean correct_word = false;
            String wrong_word = text.get(i).get(0);
            for (int j = 0; !correct_word && j < dictionary.size(); j++) {
                String current_dictionary_word = dictionary.get(j);
                int edit_distance = EditDistanceFun.edit_distance_dyn(wrong_word, current_dictionary_word);
                //int edit_distance = EditDistanceFun.edit_distance(wrong_word, current_dictionary_word);
                if (edit_distance == 0) {
                    text.remove(i);
                    i--;
                    correct_word = true;
                } else if (edit_distance < min) {
                    if (!min_found) {
                        text.get(i).clear();
                        text.get(i).add(wrong_word);
                        text.get(i).add(current_dictionary_word);
                        min = edit_distance;
                        if (min == 2) {
                            min_found = true;
                        }
                    } else {
                        text.get(i).add(current_dictionary_word);
                    }
                } else if (edit_distance == min) {
                    text.get(i).add(current_dictionary_word);
                }
            }
        }
    }


    //come funzionano i test??            UnitTest.java
    public static void main(String[] args) {
        String s1 = "cassa";
        String s2 = "casa";
        Chrono cronometro = new Chrono();
        //System.out.println(EditDistanceFun.edit_distance(s1, s2, 0, 0));
        //System.out.println(EditDistanceFun.edit_distance(s1, s2));
        String dictionary_path = "data/dictionary.txt";
        String text_path = "data/correctme.txt";
        ArrayList <String> dictionary = load_dictionary_arr(dictionary_path);
        ArrayList <ArrayList <String>> text = load_text(text_path);
        cronometro.start();
        suggestion(dictionary, text);
        cronometro.stop();
        System.out.println("Tempo di calcolo: " + cronometro);
        printArray(text);
    }
}
