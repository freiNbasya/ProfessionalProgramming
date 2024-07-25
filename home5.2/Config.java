import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class Config {
    private static Config instance;
    private Map<String, String[]> configMap;

    private Config() {
        configMap = new HashMap<>();
        loadConfig();
    }

    public static Config getInstance() {
        if (instance == null) {
            synchronized (Config.class) {
                if (instance == null) {
                    instance = new Config();
                }
            }
        }
        return instance;
    }

    private void loadConfig() {
        try (BufferedReader reader = new BufferedReader(new FileReader("config.txt"))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(" ");
                String range = parts[0];
                String preWord = parts[1];
                String postWord = parts[2];
                configMap.put(range, new String[]{preWord, postWord});
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String[] getPreAndPostWord(char firstLetter) {
        for (String range : configMap.keySet()) {
            if (isInRange(firstLetter, range)) {
                return configMap.get(range);
            }
        }
        return new String[]{"", ""}; 
    }

    private boolean isInRange(char letter, String range) {
        char start = range.charAt(0);
        char end = range.charAt(2);
        return letter >= start && letter <= end;
    }
}
