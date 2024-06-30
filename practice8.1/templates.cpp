#include <iostream>
#include <print>

template<typename T>
concept Prices = requires(T t) {
    { t.getCoefficient() } -> std::convertible_to<double>;
    { t.getBasePrice() } -> std::convertible_to<double>;
};

template<size_t PRIORITY>
class PricePresenter {
public:
    template<Prices T1, Prices T2>
    void printTotalPrice(const T1& item1, const T2& item2) const {
        double total_price = PRIORITY * item1.getCoefficient() * item1.getBasePrice() + item2.getCoefficient() * item2.getBasePrice();
        std::println("Total Price: {}", total_price);
    }
};

class Milk {
public:
    double getCoefficient() const {
        return 0.5;
    }

    double getBasePrice() const {
        return 4.0;
    }
};

class Cookies {
public:
    double getCoefficient() const {
        return 0.7;
    }

    double getBasePrice() const {
        return 5.0;
    }
};

class Pineapple {
public:
    double getCoefficient() const {
        return 0.9;
    }

    double getBasePrice() const {
        return 7.0;
    }
};

int main() {
    Milk milk;
    Cookies cookies;
    Pineapple pineapple;
    PricePresenter<2> presenter;

    presenter.printTotalPrice(milk, cookies);
    presenter.printTotalPrice(milk, pineapple);
    presenter.printTotalPrice(cookies, pineapple);

    return 0;
}
