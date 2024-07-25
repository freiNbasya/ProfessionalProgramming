public class WordThread extends Thread {
    private String word;

    public WordThread(String word) {
        this.word = word;
    }

    @Override
    public void run() {
        try {
            Thread.sleep(1000);
            char firstLetter = word.toLowerCase().charAt(0);
            Config config = Config.getInstance();
            String[] prePostWords = config.getPreAndPostWord(firstLetter);
            System.out.println(prePostWords[0] + " " + word + " " + prePostWords[1]);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
