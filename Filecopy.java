
import java.io.*;
import java.util.*;

class filecopy {
    public static void main(String[] args) {

        try {
            File file = new File("random.txt");
            Scanner sc = new Scanner(file);
            int wordCount = 0;
            int lineCount = 0;
            while (sc.hasNextLine()) {
                String line = sc.nextLine();
                lineCount++;

                String words[] = line.split(" ");
                for (String word : words) {
                    wordCount++;
                }
            }
            System.out.println("Number of words: " + wordCount);
            System.out.println("Number of lines: " + lineCount);
            System.out.println("Number of characters: " + file.length());
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
}
