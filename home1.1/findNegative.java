import java.util.Scanner;
import java.util.InputMismatchException;

public class findNegative {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter integers separated by spaces:");

        String input = scanner.nextLine();
        String[] strArray = input.split(" ");
        int[] numArray = new int[strArray.length];
        // are you sure that try block should be so big? it is better to cover only the relevant part of scope
        try {
            // regarding parsing filtereng and other logic it is better to use tools available in language
            // for example https://www.geeksforgeeks.org/stream-map-java-examples/
            // and https://www.geeksforgeeks.org/stream-filter-java-examples/
            for (int i = 0; i < strArray.length; i++) {
                numArray[i] = Integer.parseInt(strArray[i]);
            }

            Integer biggestNegative = null;

            for (int num : numArray) {
                if (num < 0 && (biggestNegative == null || num > biggestNegative)) {
                    biggestNegative = num;
                }
            }

            if (biggestNegative != null) {
                System.out.println("The biggest negative value is: " + biggestNegative);
            } else {
                System.out.println("There are no negative numbers in the array.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Enter integers separated by spaces.");
        }
    }
}
