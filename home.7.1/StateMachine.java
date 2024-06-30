import java.util.HashMap;
import java.util.Map;

public class StateMachine {
    private State currentState;
    private final Map<State, Map<String, State>> transitions;

    public StateMachine() {
        currentState = State.INTRO;

        transitions = new HashMap<>();

        Map<String, State> introTransitions = new HashMap<>();
        introTransitions.put("dangerous", State.LET_IT_BE);
        introTransitions.put("fun", State.STARMAN);
        introTransitions.put("sad", State.IN_THE_END);
        transitions.put(State.INTRO, introTransitions);

        Map<String, State> starmanTransitions = new HashMap<>();
        starmanTransitions.put("silly", State.INTRO);
        starmanTransitions.put("dangerous", State.SHOW_MUST_GO_ON);
        starmanTransitions.put("fun", State.IN_THE_END);
        transitions.put(State.STARMAN, starmanTransitions);

        Map<String, State> showMustGoOnTransitions = new HashMap<>();
        showMustGoOnTransitions.put("sad", State.LET_IT_BE);
        showMustGoOnTransitions.put("fun", State.STARMAN);
        transitions.put(State.SHOW_MUST_GO_ON, showMustGoOnTransitions);

        Map<String, State> letItBeTransitions = new HashMap<>();
        letItBeTransitions.put("dangerous", State.INTRO);
        letItBeTransitions.put("silly", State.SHOW_MUST_GO_ON);
        transitions.put(State.LET_IT_BE, letItBeTransitions);
    }

    public String getCurrentSong() {
        return currentState.getSong();
    }

    public boolean handleCommand(String command) {
        if (transitions.containsKey(currentState)) {
            Map<String, State> stateTransitions = transitions.get(currentState);
            if (stateTransitions.containsKey(command)) {
                currentState = stateTransitions.get(command);
                if (currentState == State.IN_THE_END) {
                    return false;
                }
                return true; 
            }
        }
        return true; 
    }
}
