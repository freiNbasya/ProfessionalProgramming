public class Main {
    public static void main(String[] args) {
        Milk milk = new Milk();
        Cookies cookies = new Cookies();
        Pineapple pineapple = new Pineapple();
        PricePresenter presenter = new PricePresenter(2);

        presenter.printTotalPrice(milk, cookies);
        presenter.printTotalPrice(milk, pineapple);
        presenter.printTotalPrice(cookies, pineapple);
    }
}
