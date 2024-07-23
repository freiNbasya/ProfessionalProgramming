import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class FootballTournament {

    public static void inputTeams(List<Team> teams, Scanner scanner) {
        for (int i = 0; i < 4; ++i) {
            System.out.println("Enter name for Team " + (i + 1) + ": ");
            String name = scanner.next();
            teams.add(new Team(name));
        }
    }

    public static void inputMatches(List<Match> matches, List<MatchResult> matchResults, Scanner scanner) {
        for (Match match : matches) {
            match.inputResult(scanner);
            matchResults.add(new MatchResult(match));
        }
    }

    public static void printRanking(List<Team> teams) {
        Collections.sort(teams, new Comparator<Team>() {
            @Override
            public int compare(Team a, Team b) {
                if (a.name.equals("404")) return 1;
                if (b.name.equals("404")) return -1;
                if (a.points != b.points) return Double.compare(b.points, a.points);
                if (a.topHeight != b.topHeight) return Double.compare(b.topHeight, a.topHeight);
                if (a.goalDifference() != b.goalDifference()) return Integer.compare(b.goalDifference(), a.goalDifference());
                if (a.goalsScored != b.goalsScored) return Integer.compare(b.goalsScored, a.goalsScored);
                if (a.redCards != b.redCards) return Integer.compare(a.redCards, b.redCards);
                if (a.yellowCards != b.yellowCards) return Integer.compare(a.yellowCards, b.yellowCards);
                return (new Random().nextInt(2) == 0) ? -1 : 1;  // Random choice
            }
        });

        System.out.println("Final Ranking:");
        for (Team team : teams) {
            System.out.printf("%-15s: Points=%.2f, Top Height=%.2f, Goal Difference=%d, Goals Scored=%d, Red Cards=%d, Yellow Cards=%d%n",
                    team.name, team.points, team.topHeight, team.goalDifference(), team.goalsScored, team.redCards, team.yellowCards);
        }
    }

    public static void printMatchResults(List<MatchResult> matchResults) {
        System.out.println("\nMatch Results:");
        for (MatchResult matchResult : matchResults) {
            matchResult.printResult();
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<Team> teams = new ArrayList<>();
        inputTeams(teams, scanner);

        List<Match> matches = new ArrayList<>();
        List<MatchResult> matchResults = new ArrayList<>();
        matches.add(new Match(teams.get(0), teams.get(1)));
        matches.add(new Match(teams.get(0), teams.get(2)));
        matches.add(new Match(teams.get(0), teams.get(3)));
        matches.add(new Match(teams.get(1), teams.get(2)));
        matches.add(new Match(teams.get(1), teams.get(3)));
        matches.add(new Match(teams.get(2), teams.get(3)));

        inputMatches(matches, matchResults, scanner);
        printMatchResults(matchResults);
        printRanking(teams);
    }
}
