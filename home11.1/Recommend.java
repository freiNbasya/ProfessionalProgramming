import java.util.Scanner;

public class Recommend {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your name: ");
        String name = scanner.nextLine();

        Library library = new Library();

        while (!library.isEmpty()) {
            if (library.proposeBook()) {
                return;
            }
        }

        System.out.println("Au revoir, " + name + "!");
    }
}
