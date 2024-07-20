import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.Consumer;

public class MessageDispatcher {
    private final ConcurrentHashMap<Integer, Consumer<GreenMessage>> greenMessageSubscribers = new ConcurrentHashMap<>();
    private final ConcurrentHashMap<Integer, Consumer<BlueMessage>> blueMessageSubscribers = new ConcurrentHashMap<>();
    private final ConcurrentHashMap<Integer, Consumer<OrangeMessage>> orangeMessageSubscribers = new ConcurrentHashMap<>();
    private final BlockingQueue<GreenMessage> greenMessageQueue = new LinkedBlockingQueue<>();
    private final BlockingQueue<BlueMessage> blueMessageQueue = new LinkedBlockingQueue<>();
    private final BlockingQueue<OrangeMessage> orangeMessageQueue = new LinkedBlockingQueue<>();
    private final AtomicInteger subscriberId = new AtomicInteger(0);

    public MessageDispatcher() {
        startProcessing();
    }

    private void startProcessing() {
        new Thread(() -> {
            while (true) {
                try {
                    GreenMessage message = greenMessageQueue.take();
                    for (Consumer<GreenMessage> subscriber : greenMessageSubscribers.values()) {
                        subscriber.accept(message);
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    break;
                }
            }
        }).start();

        new Thread(() -> {
            while (true) {
                try {
                    BlueMessage message = blueMessageQueue.take();
                    for (Consumer<BlueMessage> subscriber : blueMessageSubscribers.values()) {
                        subscriber.accept(message);
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    break;
                }
            }
        }).start();

        new Thread(() -> {
            while (true) {
                try {
                    OrangeMessage message = orangeMessageQueue.take();
                    for (Consumer<OrangeMessage> subscriber : orangeMessageSubscribers.values()) {
                        subscriber.accept(message);
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    break;
                }
            }
        }).start();
    }

    public int subscribeToGreenMessage(Consumer<GreenMessage> subscriber) {
        int id = subscriberId.incrementAndGet();
        greenMessageSubscribers.put(id, subscriber);
        return id;
    }

    public int subscribeToBlueMessage(Consumer<BlueMessage> subscriber) {
        int id = subscriberId.incrementAndGet();
        blueMessageSubscribers.put(id, subscriber);
        return id;
    }

    public int subscribeToOrangeMessage(Consumer<OrangeMessage> subscriber) {
        int id = subscriberId.incrementAndGet();
        orangeMessageSubscribers.put(id, subscriber);
        return id;
    }

    public void unsubscribe(int id) {
        greenMessageSubscribers.remove(id);
        blueMessageSubscribers.remove(id);
        orangeMessageSubscribers.remove(id);
    }

    public void publishGreenMessage(GreenMessage message) {
        greenMessageQueue.offer(message);
    }

    public void publishBlueMessage(BlueMessage message) {
        blueMessageQueue.offer(message);
    }

    public void publishOrangeMessage(OrangeMessage message) {
        orangeMessageQueue.offer(message);
    }
}
