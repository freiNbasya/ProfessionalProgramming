#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <print>

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
    void subscribeToGreenMsg(const std::function<void(const GreenMsg&)>& subscriber) {
        std::lock_guard<std::mutex> lock(mutex_);
        GreenMsgSubscribers_.push_back(subscriber);
    }

    void subscribeToBlueMsg(const std::function<void(const BlueMsg&)>& subscriber) {
        std::lock_guard<std::mutex> lock(mutex_);
        BlueMsgSubscribers_.push_back(subscriber);
    }

    void subscribeToOrangeMsg(const std::function<void(const OrangeMsg&)>& subscriber) {
        std::lock_guard<std::mutex> lock(mutex_);
        OrangeMsgSubscribers_.push_back(subscriber);
    }

    void publishGreenMsg(const GreenMsg& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        for (const auto& subscriber : GreenMsgSubscribers_) {
            subscriber(message);
        }
    }

    void publishBlueMsg(const BlueMsg& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        for (const auto& subscriber : BlueMsgSubscribers_) {
            subscriber(message);
        }
    }

    void publishOrangeMsg(const OrangeMsg& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        for (const auto& subscriber : OrangeMsgSubscribers_) {
            subscriber(message);
        }
    }

private:
    std::vector<std::function<void(const GreenMsg&)>> GreenMsgSubscribers_;
    std::vector<std::function<void(const BlueMsg&)>> BlueMsgSubscribers_;
    std::vector<std::function<void(const OrangeMsg&)>> OrangeMsgSubscribers_;
    std::mutex mutex_;
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
        std::println("GreenMsg received: {}, {}", msg.text, msg.counter);
    });

    dispatcher.subscribeToBlueMsg([](const BlueMsg& msg) {
       std::println("BlueMsg received: {}, {}", msg.value1,msg.value2);
    });

    dispatcher.subscribeToOrangeMsg([](const OrangeMsg& msg) {
        std::println("OrangeMsg received: {}, {}, {}, {}",msg.text1, msg.text2, msg.number, msg.value);
    });

    std::thread thread1(generateMsg, std::ref(dispatcher));
    std::thread thread2(generateMsg, std::ref(dispatcher));

    thread1.join();
    thread2.join();

    return 0;
}
