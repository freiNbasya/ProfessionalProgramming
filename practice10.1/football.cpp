#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>
#include <random>
#include <ctime>
#include <iomanip>
#include <print>

class Team {
public:
    std::string name;
    int goalsScored = 0;
    int goalsMissed = 0;
    int yellowCards = 0;
    int redCards = 0;
    double topHeight = 0.0;
    double points = 0.0;

    Team(std::string n) : name(std::move(n)) {}

    void updateStats(int scored, int missed, int yellow, int red, double height, double pts) {
        goalsScored += scored;
        goalsMissed += missed;
        yellowCards += yellow;
        redCards += red;
        topHeight += height;
        points += pts;
    }

    int goalDifference() const {
        return goalsScored - goalsMissed;
    }
};

class Match {
public:
    Team& team1;
    Team& team2;
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

    Match(Team& t1, Team& t2) : team1(t1), team2(t2) {}

    void inputResult() {
        std::println("Enter goals scored by {}:", team1.name);
        std::cin >> goals1;
        std::println("Enter goals scored by {}:", team2.name);
        std::cin >> goals2;
        std::println("Enter yellow cards shown to {}:", team1.name);
        std::cin >> yellow1;
        std::println("Enter yellow cards shown to {}:", team2.name);
        std::cin >> yellow2;
        std::println("Enter red cards shown to {}:", team1.name);
        std::cin >> red1;
        std::println("Enter red cards shown to {}:", team2.name);
        std::cin >> red2;
        std::println("Enter top height reached by the ball for {}:", team1.name);
        std::cin >> height1;
        std::println("Enter top height reached by the ball for {}:", team2.name);
        std::cin >> height2;

        points1 = (goals1 > goals2) ? 3.14 : (goals1 == goals2) ? 2.71828 : -0.5;
        points2 = (goals2 > goals1) ? 3.14 : (goals2 == goals1) ? 2.71828 : -0.5;

        team1.updateStats(goals1, goals2, yellow1, red1, height1, points1);
        team2.updateStats(goals2, goals1, yellow2, red2, height2, points2);
    }

    void printResult() const {
        std::println("Match: {} vs {}", team1.name, team2.name);
        std::println("{}: Goals={}, Yellow Cards={}, Red Cards={}, Top Height={}, Points={}", 
                     team1.name, goals1, yellow1, red1, height1, points1);
        std::println("{}: Goals={}, Yellow Cards={}, Red Cards={}, Top Height={}, Points={}", 
                     team2.name, goals2, yellow2, red2, height2, points2);
    }
};

class MatchResult {
public:
    Team& team1;
    Team& team2;
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

    MatchResult(Match& match)
        : team1(match.team1), team2(match.team2), goals1(match.goals1), goals2(match.goals2),
          yellow1(match.yellow1), yellow2(match.yellow2), red1(match.red1), red2(match.red2),
          height1(match.height1), height2(match.height2), points1(match.points1), points2(match.points2) {}

    void printResult() const {
        std::println("Match: {} vs {}", team1.name, team2.name);
        std::println("{}: Goals={}, Yellow Cards={}, Red Cards={}, Top Height={}, Points={}", 
                     team1.name, goals1, yellow1, red1, height1, points1);
        std::println("{}: Goals={}, Yellow Cards={}, Red Cards={}, Top Height={}, Points={}", 
                     team2.name, goals2, yellow2, red2, height2, points2);
    }
};

void inputTeams(std::vector<Team>& teams) {
    for (int i = 0; i < 4; ++i) {
        std::string name;
        std::println("Enter name for Team {}:", i + 1);
        std::cin >> name;
        teams.emplace_back(name);
    }
}

void inputMatches(std::vector<Match>& matches, std::vector<MatchResult>& matchResults) {
    for (auto& match : matches) {
        match.inputResult();
        matchResults.emplace_back(match);
    }
}

void printRanking(const std::vector<Team>& teams) {
    auto sorted_teams = teams;

    std::ranges::sort(sorted_teams, [](const Team& a, const Team& b) {
        if (a.points != b.points) return a.points > b.points;
        if (a.topHeight != b.topHeight) return a.topHeight > b.topHeight;
        if (a.goalDifference() != b.goalDifference()) return a.goalDifference() > b.goalDifference();
        if (a.goalsScored != b.goalsScored) return a.goalsScored > b.goalsScored;
        if (a.redCards != b.redCards) return a.redCards < b.redCards;
        if (a.yellowCards != b.yellowCards) return a.yellowCards < b.yellowCards;
        return (std::rand() % 2 == 0);
    });

    std::println("Final Ranking:");
    for (const auto& team : sorted_teams) {
        std::println("{:<15}: Points={}, Top Height={}, Goal Difference={}, Goals Scored={}, Red Cards={}, Yellow Cards={}", 
                     team.name, team.points, team.topHeight, team.goalDifference(), team.goalsScored, team.redCards, team.yellowCards);
    }
}

void printMatchResults(const std::vector<MatchResult>& matchResults) {
    std::println("\nMatch Results:");
    for (const auto& matchResult : matchResults) {
        matchResult.printResult();
    }
}

int main() {
    std::srand(std::time(nullptr)); 
    std::vector<Team> teams;
    inputTeams(teams);

    std::vector<Match> matches = {
        {teams[0], teams[1]}, {teams[0], teams[2]}, {teams[0], teams[3]},
        {teams[1], teams[2]}, {teams[1], teams[3]}, {teams[2], teams[3]}
    };

    std::vector<MatchResult> matchResults;
    inputMatches(matches, matchResults);
    printMatchResults(matchResults);
    printRanking(teams);

    return 0;
}
