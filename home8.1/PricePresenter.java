class PricePresenter {
    private int priority;

    public PricePresenter(int priority) {
        this.priority = priority;
    }

    public <T1 extends Prices, T2 extends Prices> void printTotalPrice(T1 item1, T2 item2) {
        double totalPrice = priority * item1.getCoefficient() * item1.getBasePrice() + item2.getCoefficient() * item2.getBasePrice();
        System.out.println("Total Price: " + totalPrice);
    }
}

