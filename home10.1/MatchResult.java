public class MatchResult {
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

    public MatchResult(Match match) {
        this.team1 = match.team1;
        this.team2 = match.team2;
        this.goals1 = match.goals1;
        this.goals2 = match.goals2;
        this.yellow1 = match.yellow1;
        this.yellow2 = match.yellow2;
        this.red1 = match.red1;
        this.red2 = match.red2;
        this.height1 = match.height1;
        this.height2 = match.height2;
        this.points1 = match.points1;
        this.points2 = match.points2;
    }

    public void printResult() {
        System.out.println("Match: " + team1.name + " vs " + team2.name);
        System.out.println(team1.name + ": Goals=" + goals1 + ", Yellow Cards=" + yellow1 + ", Red Cards=" + red1 + ", Top Height=" + height1 + ", Points=" + points1);
        System.out.println(team2.name + ": Goals=" + goals2 + ", Yellow Cards=" + yellow2 + ", Red Cards=" + red2 + ", Top Height=" + height2 + ", Points=" + points2);
        System.out.println();
    }
}
