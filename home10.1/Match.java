import java.util.Scanner;

public class Match {
    Team team1;
    Team team2;
    int goals1;
    int goals2;
    int yellow1;
    int yellow2;
    int red1;
    int red2;
    double height1;
    double height2;
    double points1;
    double points2;

    public Match(Team team1, Team team2) {
        this.team1 = team1;
        this.team2 = team2;
    }

    public void inputResult(Scanner scanner) {
        System.out.println("Enter goals scored by " + team1.name + ": ");
        goals1 = scanner.nextInt();
        System.out.println("Enter goals scored by " + team2.name + ": ");
        goals2 = scanner.nextInt();
        System.out.println("Enter yellow cards shown to " + team1.name + ": ");
        yellow1 = scanner.nextInt();
        System.out.println("Enter yellow cards shown to " + team2.name + ": ");
        yellow2 = scanner.nextInt();
        System.out.println("Enter red cards shown to " + team1.name + ": ");
        red1 = scanner.nextInt();
        System.out.println("Enter red cards shown to " + team2.name + ": ");
        red2 = scanner.nextInt();
        System.out.println("Enter top height reached by the ball for " + team1.name + ": ");
        height1 = scanner.nextDouble();
        System.out.println("Enter top height reached by the ball for " + team2.name + ": ");
        height2 = scanner.nextDouble();

        points1 = (goals1 > goals2) ? 3.14 : (goals1 == goals2) ? 2.71828 : -0.5;
        points2 = (goals2 > goals1) ? 3.14 : (goals2 == goals1) ? 2.71828 : -0.5;

        team1.updateStats(goals1, goals2, yellow1, red1, height1, points1);
        team2.updateStats(goals2, goals1, yellow2, red2, height2, points2);
    }

    public void printResult() {
        System.out.println("Match: " + team1.name + " vs " + team2.name);
        System.out.println(team1.name + ": Goals=" + goals1 + ", Yellow Cards=" + yellow1 + ", Red Cards=" + red1 + ", Top Height=" + height1 + ", Points=" + points1);
        System.out.println(team2.name + ": Goals=" + goals2 + ", Yellow Cards=" + yellow2 + ", Red Cards=" + red2 + ", Top Height=" + height2 + ", Points=" + points2);
        System.out.println();
    }
}
