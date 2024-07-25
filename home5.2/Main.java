import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String[] favouriteWords = new String[5];

        System.out.println("Enter your 5 favorite words:");
        for (int i = 0; i < 5; i++) {
            favouriteWords[i] = scanner.nextLine();
        }

        for (String word : favouriteWords) {
            WordThread wordThread = new WordThread(word);
            wordThread.start();
        }

        scanner.close();
    }
}
