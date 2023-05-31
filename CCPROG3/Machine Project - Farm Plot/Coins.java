/**
 * Class for coins (Object representation of the user's currency)
 */
public class Coins {
    private float amount;

    /**
     * Constructor method for the Coins class
     * @param amount is the initial amount set by the game
     */
    public Coins(int amount){
        this.amount = amount;
    }



    /**
     * method that adds an amount of coins to the current amount of coins
     * @param amount amount of coins added to the current amount of coins
     */
    public void addAmount(float amount){
        this.amount += amount;
    }

    /**
     * Getter method for the amount of coins
     * @return amount of coins
     */
    public float getAmount() {
        return amount;
    }

    /**
     * Checks if the c amount of coins is greater than the user's total amount of coins
     * @param c is the amount of coins being tested
     * @return return true if c is greater than amount, otherwise return false.
     */
    public boolean isEnough(float c){
        return this.amount >= c;
    }
}
