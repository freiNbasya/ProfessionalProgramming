#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <queue>
#include <random>
#include <chrono>
#include <condition_variable>

class GreenMsg {
public:
    std::string text;
    int counter;

    GreenMsg(const std::string& t, int c) : text(t), counter(c) {}
};

class BlueMsg {
public:
    double value1;
    double value2;

    BlueMsg(double v1, double v2) : value1(v1), value2(v2) {}
};

class OrangeMsg {
public:
    std::string text1;
    std::string text2;
    int number;
    double value;

    OrangeMsg(const std::string& t1, const std::string& t2, int n, double v) 
        : text1(t1), text2(t2), number(n), value(v) {}
};

class MsgDispatcher {
public:
    MsgDispatcher() {
        startDispatchers();
    }

    ~MsgDispatcher() {
        stopDispatchers();
    }

    void subscribeToGreenMsg(const std::function<void(const GreenMsg&)>& subscriber) {
        std::lock_guard<std::mutex> lock(greenMutex_);
        greenMsgSubscribers_.push_back(subscriber);
    }

    void subscribeToBlueMsg(const std::function<void(const BlueMsg&)>& subscriber) {
        std::lock_guard<std::mutex> lock(blueMutex_);
        blueMsgSubscribers_.push_back(subscriber);
    }

    void subscribeToOrangeMsg(const std::function<void(const OrangeMsg&)>& subscriber) {
        std::lock_guard<std::mutex> lock(orangeMutex_);
        orangeMsgSubscribers_.push_back(subscriber);
    }

    void publishGreenMsg(const GreenMsg& message) {
        std::lock_guard<std::mutex> lock(greenQueueMutex_);
        greenMsgQueue_.push(message);
        greenCv_.notify_one();
    }

    void publishBlueMsg(const BlueMsg& message) {
        std::lock_guard<std::mutex> lock(blueQueueMutex_);
        blueMsgQueue_.push(message);
        blueCv_.notify_one();
    }

    void publishOrangeMsg(const OrangeMsg& message) {
        std::lock_guard<std::mutex> lock(orangeQueueMutex_);
        orangeMsgQueue_.push(message);
        orangeCv_.notify_one();
    }

private:
    std::vector<std::function<void(const GreenMsg&)>> greenMsgSubscribers_;
    std::vector<std::function<void(const BlueMsg&)>> blueMsgSubscribers_;
    std::vector<std::function<void(const OrangeMsg&)>> orangeMsgSubscribers_;

    std::queue<GreenMsg> greenMsgQueue_;
    std::queue<BlueMsg> blueMsgQueue_;
    std::queue<OrangeMsg> orangeMsgQueue_;

    std::mutex greenMutex_;
    std::mutex blueMutex_;
    std::mutex orangeMutex_;

    std::mutex greenQueueMutex_;
    std::mutex blueQueueMutex_;
    std::mutex orangeQueueMutex_;

    std::condition_variable greenCv_;
    std::condition_variable blueCv_;
    std::condition_variable orangeCv_;

    bool stop_ = false;

    void startDispatchers() {
        std::thread([this]() {
            while (true) {
                std::unique_lock<std::mutex> lock(greenQueueMutex_);
                greenCv_.wait(lock, [this]() { return !greenMsgQueue_.empty() || stop_; });
                if (stop_ && greenMsgQueue_.empty()) break;
                GreenMsg msg = greenMsgQueue_.front();
                greenMsgQueue_.pop();
                lock.unlock();

                std::lock_guard<std::mutex> subLock(greenMutex_);
                for (const auto& subscriber : greenMsgSubscribers_) {
                    subscriber(msg);
                }
            }
        }).detach();

        std::thread([this]() {
            while (true) {
                std::unique_lock<std::mutex> lock(blueQueueMutex_);
                blueCv_.wait(lock, [this]() { return !blueMsgQueue_.empty() || stop_; });
                if (stop_ && blueMsgQueue_.empty()) break;
                BlueMsg msg = blueMsgQueue_.front();
                blueMsgQueue_.pop();
                lock.unlock();

                std::lock_guard<std::mutex> subLock(blueMutex_);
                for (const auto& subscriber : blueMsgSubscribers_) {
                    subscriber(msg);
                }
            }
        }).detach();

        std::thread([this]() {
            while (true) {
                std::unique_lock<std::mutex> lock(orangeQueueMutex_);
                orangeCv_.wait(lock, [this]() { return !orangeMsgQueue_.empty() || stop_; });
                if (stop_ && orangeMsgQueue_.empty()) break;
                OrangeMsg msg = orangeMsgQueue_.front();
                orangeMsgQueue_.pop();
                lock.unlock();

                std::lock_guard<std::mutex> subLock(orangeMutex_);
                for (const auto& subscriber : orangeMsgSubscribers_) {
                    subscriber(msg);
                }
            }
        }).detach();
    }

    void stopDispatchers() {
        stop_ = true;
        greenCv_.notify_all();
        blueCv_.notify_all();
        orangeCv_.notify_all();
    }
};

void generateMsg(MsgDispatcher& dispatcher) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 3);
    std::uniform_int_distribution<> intDis(0, 100);
    std::uniform_real_distribution<> doubleDis(0.0, 100.0);
    std::vector<std::string> texts = {"Limbus", "Company", "Wahoo"};

    for (int i = 0; i < 10; ++i) {
        int type = dis(gen);
        if (type == 1) {
            GreenMsg msg(texts[intDis(gen) % texts.size()], intDis(gen));
            dispatcher.publishGreenMsg(msg);
        } else if (type == 2) {
            BlueMsg msg(doubleDis(gen), doubleDis(gen));
            dispatcher.publishBlueMsg(msg);
        } else if (type == 3) {
            OrangeMsg msg(texts[intDis(gen) % texts.size()], texts[intDis(gen) % texts.size()], intDis(gen), doubleDis(gen));
            dispatcher.publishOrangeMsg(msg);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    MsgDispatcher dispatcher;

    dispatcher.subscribeToGreenMsg([](const GreenMsg& msg) {
        std::cout << "GreenMsg received: " << msg.text << ", " << msg.counter << std::endl;
    });

    dispatcher.subscribeToBlueMsg([](const BlueMsg& msg) {
        std::cout << "BlueMsg received: " << msg.value1 << ", " << msg.value2 << std::endl;
    });

    dispatcher.subscribeToOrangeMsg([](const OrangeMsg& msg) {
        std::cout << "OrangeMsg received: " << msg.text1 << ", " << msg.text2 << ", " << msg.number << ", " << msg.value << std::endl;
    });

    std::thread thread1(generateMsg, std::ref(dispatcher));
    std::thread thread2(generateMsg, std::ref(dispatcher));

    thread1.join();
    thread2.join();

    return 0;
}
