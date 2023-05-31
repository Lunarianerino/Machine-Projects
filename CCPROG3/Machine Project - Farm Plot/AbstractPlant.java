import javax.swing.*;
import java.util.Random;

/**
 * Abstract class for plant
 */
public abstract class AbstractPlant implements Witherable, Harvestable {
    //plant identification, stats
    private int id = 0;
    private String name;
    /*
        0 = Planted
        1 = Growing
        2 = Harvestable
        3 = Withered
     */
    private int state = 0;
    private String type;
    private int sellPrice;
    private float exp;

    private int produceLB;
    private int produceUB;

    private int harvestTime;

    private int waterMin;
    private int waterLimit;
    private int waterReceived = 0;

    private int fertilizerMin;
    private int fertilizerLimit;
    private int fertilizerReceived = 0;
    private int productsProduced;

    //ImageIcons set by classes that inherit this class in its constructor method.
    private ImageIcon growing;
    private ImageIcon harvestable;

    //constructors

    /**
     * Constructor class for AbstractPlant. This method gets all data of a plant specified by the id.
     *
     * @param id ID of the selected plant
     */
    public AbstractPlant(int id) {
        PlantStat data = GetData.getPlantStats(id);

        this.id = data.getId();
        this.name = data.getName();
        this.type = data.getType();
        this.sellPrice = data.getSellPrice();
        this.exp = data.getExp();
        this.harvestTime = data.getHarvestTime();
        this.produceLB = data.getProduceLB();
        this.produceUB = data.getProduceUP();
        this.waterMin = data.getWaterMin();
        this.fertilizerMin = data.getFertilizerMin();
        this.waterLimit = data.getWaterLimit() + FarmerStats.getWaterBonusLimitIncrease();
        this.fertilizerLimit = data.getFertilizerLimit() + FarmerStats.getFertilizerBonusLimitIncrease();
        generateProductAmount(); //generates its number of crops produced here so other classes can use getProductAmount() before the harvest method is called.
        System.out.println("Plant Data extracted");
    }

    /**
     * Method to calculate the amount of water the plant has received.
     *
     * @return waterReceived - 1 if the minimum water requirement contained by attribute waterMin is met, otherwise
     * return 0
     */
    public int calculateWater() {
        if (this.waterReceived > this.waterMin) {
            return this.waterReceived - 1;
        }
        return 0;
    }

    /**
     * Method to add the amount of water received by the plant by 1
     *
     * @return true if the limit of water a plant could take is not yet reached, otherwise return false.
     */
    public boolean addWater() {
        if (this.waterReceived < this.waterLimit) {
            this.waterReceived++;
            return true;
        }
        return false;
    }

    /**
     * Method to add the amount of fertilizer received by the plant by 1
     * @return true if the limit of fertilizer a plant could take is not yet reached, otherwise return false
     */
    public boolean addFertilizer() {
        if (this.fertilizerReceived < this.fertilizerLimit) {
            this.fertilizerReceived++;
            return true;
        }
        return false;
    }

    /**
     * Method to decrement the harvest time of the plant. This method is called everytime the user presses the sleep button.
     * The state of the plant is set to 1 if harvestTime is not yet 0, and when harvestTime reaches 0, the state of the plant
     * will change to 2 (harvestable).
     */
    public void nextDay() {
        if (this.state == 3) return; //plant withered, do nothing
        if (this.id > 0) {
            this.harvestTime--;
            if (this.harvestTime == 0)
                this.state = 2;
            else
                this.state = 1;
        }
    }

    /**
     * Method that generates a random integer between produceLB and produceUB which are the lower and upper bounds of the
     * amount of products the crop can yield.
     */
    public void generateProductAmount() { // utility method for calculateHarvest
        Random r = new Random();
        if (this.getProduceLB() == this.getProduceUB()) {
            this.productsProduced = getProduceLB();
            return;
        }
        productsProduced = r.nextInt(this.getProduceLB(), this.getProduceUB() + 1);

    }

    /**
     * Method to calculate the total selling price of the crop. The calculation already includes the bonuses given by
     * the farmer's specific farmer rank.
     *
     * @param stats FarmerStats instance to obtain the bonuses of the farmer's current farmer rank.
     * @return float value of the total coins gained from harvesting.
     */
    public float calculateHarvest(FarmerStats stats) {

        float harvestTotal = this.productsProduced * (getSellPrice() + stats.getBonusEarnings());
        float waterBonus = harvestTotal * 0.2F * calculateWater();
        float fertilizerBonus = harvestTotal * 0.5F * getFertilizerReceived();

        return harvestTotal + waterBonus + fertilizerBonus;
    }

    /**
     * Method that checks the conditions for plant withering.
     */
    @Override
    public void checkWither() {
        if (this.harvestTime == 0 && (this.waterReceived < this.waterMin || this.fertilizerReceived < this.fertilizerMin)) {
            this.state = 3;
            System.out.println(this.name + " " + this.type + " withered due to minimum requirements not met.");
            return;
        }
        if (this.harvestTime == -1) {
            this.state = 3;
            System.out.println(this.name + " " + this.type + " withered due to not harvesting in time.");
        }

    }

    /**
     * Method that returns the state of the plant for updateStats() method to use.
     *
     * @return State of the plant
     */
    public String toStringState() {
        return switch (this.state) {
            case 0 -> "Seed";
            case 1 -> "Growing...";
            case 2 -> "Harvestable";
            case 3 -> "Withered";
            default -> "?";
        };
    }

    //Getter methods

    /**
     * Method that returns the name of the plant
     *
     * @return Plant name
     */
    public String getName() {
        return name;
    }

    /**
     * Method that returns the state of the plant
     *
     * @return Plant state
     */
    public int getState() {
        return state;
    }

    /**
     * Method that returns the type of the plant
     *
     * @return Plant type
     */
    public String getType() {
        return type;
    }

    /**
     * Method that returns the selling price of the plant. Used in the method that calculate the plant's harvest price.
     *
     * @return Plant selling price
     */
    public int getSellPrice() {
        return sellPrice;
    }

    /**
     * Method that returns the amount of exp the user will gain after harvesting the crop.
     *
     * @return Plant exp amount
     */
    public float getExp() {
        return exp;
    }

    /**
     * Method that returns the minimum amount of yielded products a crop can produce.
     *
     * @return Plant produce lower bound limit
     */
    public int getProduceLB() {
        return produceLB;
    }

    /**
     * Method that returns the maximum amount of yielded products a crop can produce.
     *
     * @return Plant produce upper bound limit
     */
    public int getProduceUB() {
        return produceUB;
    }

    /**
     * Method that returns the maximum amount of water the plant can take before the farmer stops receiving exp
     *
     * @return Plant water limit
     */
    public int getWaterLimit() {
        return waterLimit;
    }
    /**
     * Method that returns the minimum amount of water the plant needs to be harvestable
     *
     * @return Plant water minimum
     */
    public int getWaterMin() {
        return waterMin;
    }

    /**
     * Method that returns the amount of water the plant has currently received.
     *
     * @return Plant amount of water received
     */
    public int getWaterReceived() {
        return waterReceived;
    }

    /**
     * Method that returns the maximum amount of fertilizer
     *
     * @return Plant maximum amount of fertilizer
     */
    public int getFertilizerLimit() {
        return fertilizerLimit;
    }
    /**
     * Method that returns the minimum amount of fertilizer required for the plant to be harvestable
     *
     * @return Plant minimum amount of fertilizer
     */
    public int getFertilizerMin() {
        return fertilizerMin;
    }

    /**
     * Method that returns the amount of fertilizer the plant has currently received.
     *
     * @return Plant amount of fertilizer received
     */
    public int getFertilizerReceived() {
        return fertilizerReceived;
    }

    /**
     * Method that returns the amount of products that will be produced by harvesting the crop
     *
     * @return Plant amount of products produced
     */
    public int getProductsProduced() {
        return productsProduced;
    }

    /**
     * Method that returns the image icon of the plant in its growing state
     *
     * @return image icon of the plant in its growing state
     */
    public ImageIcon getGrowing() {
        return this.growing;
    }

    /**
     * Method that returns the image icon of the plant in its harvestable state
     *
     * @return image icon of the plant in its harvestable state
     */
    public ImageIcon getHarvestable() {
        return this.harvestable;
    }

    /**
     * Method that sets the plant's image icon in its growing state
     *
     * @param growing image icon of the plant in its growing state
     */
    public void setGrowing(ImageIcon growing) {
        this.growing = growing;
    }

    /**
     * Method that sets the plant's image icon in its harvestable state
     *
     * @param harvestable image icon of the plant in its harvestable state
     */
    public void setHarvestable(ImageIcon harvestable) {
        this.harvestable = harvestable;
    }

}
