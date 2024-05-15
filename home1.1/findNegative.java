import java.util.Arrays;
import java.util.OptionalInt;
import java.util.Scanner;
import java.util.InputMismatchException;

public class findNegative {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter integers separated by spaces:");

        String input = scanner.nextLine();
        String[] strArray = input.split(" ");
        int[] numArray = new int[strArray.length];
        try {
            for (int i = 0; i < strArray.length; i++) {
                numArray[i] = Integer.parseInt(strArray[i]);
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Enter integers separated by spaces.");
            System.exit(1);
        }

        OptionalInt biggestNegative = Arrays.stream(numArray)
                .filter(num -> num < 0)
                .max();

        if (biggestNegative.isPresent()) {
            System.out.println("The biggest negative value is: " + biggestNegative.getAsInt());
        } else {
            System.out.println("There are no negative numbers in the array.");
        }

    }
}
