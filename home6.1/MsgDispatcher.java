import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.Consumer;

public class MsgDispatcher {
    private final ConcurrentHashMap<Integer, Consumer<GreenMsg>> greenMsgSubscribers = new ConcurrentHashMap<>();
    private final ConcurrentHashMap<Integer, Consumer<BlueMsg>> blueMsgSubscribers = new ConcurrentHashMap<>();
    private final ConcurrentHashMap<Integer, Consumer<OrangeMsg>> orangeMsgSubscribers = new ConcurrentHashMap<>();
    private final AtomicInteger subscriberId = new AtomicInteger(0);

    public int subscribeToGreenMsg(Consumer<GreenMsg> subscriber) {
        int id = subscriberId.incrementAndGet();
        greenMsgSubscribers.put(id, subscriber);
        return id;
    }

    public int subscribeToBlueMsg(Consumer<BlueMsg> subscriber) {
        int id = subscriberId.incrementAndGet();
        blueMsgSubscribers.put(id, subscriber);
        return id;
    }

    public int subscribeToOrangeMsg(Consumer<OrangeMsg> subscriber) {
        int id = subscriberId.incrementAndGet();
        orangeMsgSubscribers.put(id, subscriber);
        return id;
    }

    public void unsubscribe(int id) {
        greenMsgSubscribers.remove(id);
        blueMsgSubscribers.remove(id);
        orangeMsgSubscribers.remove(id);
    }

    public void publishGreenMsg(GreenMsg message) {
        for (Consumer<GreenMsg> subscriber : greenMsgSubscribers.values()) {
            subscriber.accept(message);
        }
    }

    public void publishBlueMsg(BlueMsg message) {
        for (Consumer<BlueMsg> subscriber : blueMsgSubscribers.values()) {
            subscriber.accept(message);
        }
    }

    public void publishOrangeMsg(OrangeMsg message) {
        for (Consumer<OrangeMsg> subscriber : orangeMsgSubscribers.values()) {
            subscriber.accept(message);
        }
    }
}
