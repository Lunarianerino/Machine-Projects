/**
 * PlantStat class that stores the attributes of a specific plant according to its id.
 */
public class PlantStat {
    private int id;
    private String name;
    private String type;
    private int cost;
    private int sellPrice;

    private float exp;
    private int harvestTime;

    private int produceLB;
    private int produceUP;

    private int waterMin;
    private int waterLimit;

    private int fertilizerMin;
    private int fertilizerLimit;

    private String thumbnailPath;

    /**
     * Getter method that returns the id of the plant
     * @return id of the plant
     */
    public int getId() {
        return id;
    }

    /**
     * Getter method that returns the name of the plant
     * @return name of the plant
     */
    public String getName() {
        return name;
    }

    /**
     * Getter method that returns the type of the plant
     * @return type of the plant
     */
    public String getType() {
        return type;
    }

    /**
     * Method that returns the cost of the plant
     * @return cost of the plant
     */
    public int getCost() {
        return cost;
    }

    /**
     * Method that returns the selling price of the plant. Used in the method that calculate the plant's harvest price.
     * @return Plant selling price
     */
    public int getSellPrice() {
        return sellPrice;
    }

    /**
     * Method that returns the amount of exp the user will gain after harvesting the crop.
     * @return Plant exp amount
     */
    public float getExp() {
        return exp;
    }

    /**
     * Method that returns the number of days that need to be passed to harvest a plant
     * @return harvestTime
     */
    public int getHarvestTime() {
        return harvestTime;
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
    public int getProduceUP() {
        return produceUP;
    }

    /**
     * Method that returns the minimum amount of water needed a plant needs to receive.
     * @return waterMin
     */
    public int getWaterMin() {
        return waterMin;
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
     * Method that returns the minimum amount of fertilizer needed for a plant to become harvestable
     * @return minimum amount of fertilizer needed for a plant to become harvestable
     */
    public int getFertilizerMin() {
        return fertilizerMin;
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
     * Method that returns the file path of the plant's icon
     * @return string file path of the plant's icon
     */
    public String getThumbnailPath() {
        return thumbnailPath;
    }
}
