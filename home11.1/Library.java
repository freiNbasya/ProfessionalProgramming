import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class Library {
    private List<Book> books;
    private Random random;

    public Library() {
        books = new ArrayList<>();
        books.add(new Book("The Topographer’s Clown"));
        books.add(new Book("The Chamber of Beaver"));
        books.add(new Book("The Ironer of Kanban"));
        books.add(new Book("The Piglet of Tire"));
        books.add(new Book("The Border of the Unix"));
        books.add(new Book("The Half-Time Convince"));
        books.add(new Book("The Earthly Pillows"));
        books.add(new Book("The Censorship of the Ping"));
        books.add(new Book("The True Powers"));
        books.add(new Book("The Overturn of the Ling"));

        random = new Random();
    }

    public boolean proposeBook() {
        if (books.isEmpty()) {
            return false;
        }

        int index = random.nextInt(books.size());
        Book book = books.get(index);

        Scanner scanner = new Scanner(System.in);
        System.out.println("The magic of random offered you this book: " + book.getTitle() + "? (y/n): ");
        String response = scanner.nextLine();

        if (response.equalsIgnoreCase("y")) {
            System.out.println("Great pick, don't forget to return it.");
            return true;
        } else {
            books.remove(index);
            return false;
        }
    }

    public boolean isEmpty() {
        return books.isEmpty();
    }
}
