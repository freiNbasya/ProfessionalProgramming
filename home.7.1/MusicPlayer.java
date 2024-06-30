import java.util.Scanner;

public class MusicPlayer {
    public static void main(String[] args) {
        StateMachine stateMachine = new StateMachine();
        Scanner scanner = new Scanner(System.in);
        boolean running = true;

        while (running) {
            System.out.println("Current song: " + stateMachine.getCurrentSong());
            System.out.println("Enter a command (sad, fun, silly, dangerous):");
            String command = scanner.nextLine().trim().toLowerCase();
            running = stateMachine.handleCommand(command);
        }

        System.out.println("Program terminated. Final song: " + stateMachine.getCurrentSong());
    }
}
