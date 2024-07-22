public class Team {
    String name;
    int goalsScored = 0;
    int goalsMissed = 0;
    int yellowCards = 0;
    int redCards = 0;
    double topHeight = 0.0;
    double points = 0.0;

    public Team(String name) {
        this.name = name;
    }

    public void updateStats(int scored, int missed, int yellow, int red, double height, double pts) {
        goalsScored += scored;
        goalsMissed += missed;
        yellowCards += yellow;
        redCards += red;
        topHeight += height;
        points += pts;
    }

    public int goalDifference() {
        return goalsScored - goalsMissed;
    }
}
