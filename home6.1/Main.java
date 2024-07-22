import java.util.Random;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        MsgDispatcher dispatcher = new MsgDispatcher();

        int greenId = dispatcher.subscribeToGreenMsg(msg -> 
            System.out.println("GreenMsg received: " + msg.text + ", " + msg.counter)
        );

        int blueId = dispatcher.subscribeToBlueMsg(msg -> 
            System.out.println("BlueMsg received: " + msg.value1 + ", " + msg.value2)
        );

        int orangeId = dispatcher.subscribeToOrangeMsg(msg -> 
            System.out.println("OrangeMsg received: " + msg.text1 + ", " + msg.text2 + ", " + msg.number + ", " + msg.value)
        );

        Runnable generateMsg = () -> {
            Random random = new Random();
            String[] texts = {"Limbus", "Company", "Wahoo"};
            for (int i = 0; i < 10; i++) {
                int type = random.nextInt(3) + 1;
                if (type == 1) {
                    GreenMsg msg = new GreenMsg(texts[random.nextInt(texts.length)], random.nextInt(100));
                    dispatcher.publishGreenMsg(msg);
                } else if (type == 2) {
                    BlueMsg msg = new BlueMsg(random.nextDouble() * 100, random.nextDouble() * 100);
                    dispatcher.publishBlueMsg(msg);
                } else {
                    OrangeMsg msg = new OrangeMsg(
                        texts[random.nextInt(texts.length)], 
                        texts[random.nextInt(texts.length)], 
                        random.nextInt(100), 
                        random.nextDouble() * 100
                    );
                    dispatcher.publishOrangeMsg(msg);
                }
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        };

        Thread thread1 = new Thread(generateMsg);
        Thread thread2 = new Thread(generateMsg);

        dispatcher.unsubscribe(greenId);
        
        thread1.start();
        thread2.start();

        thread1.join();
        thread2.join();

    }
}
