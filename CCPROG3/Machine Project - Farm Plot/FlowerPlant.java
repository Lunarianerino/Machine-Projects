import javax.swing.*;

/**
 * FlowerPlant Subclass of AbstractPlant. Contains its respective ImageIcons and an override method for calculating price harvest
 */
public class FlowerPlant extends AbstractPlant{

    /**
     * Constructor method of FlowerPlant
     * @param id ID of the plant
     */
    public FlowerPlant(int id) {
        super(id);
        System.out.println("Type: " + this.getType());

        this.setGrowing(new ImageIcon("./Dirt Asset/growingFlower.png"));
        this.setHarvestable(new ImageIcon("./Dirt Asset/harvestableFlower.png"));
    }

    /**
     * Method to calculate the harvest selling price of a flower crop
     * @param stats FarmerStats instance to obtain the bonuses of the farmer's current farmer rank.
     * @return float value of a FlowerPlant instance harvest price
     */
    @Override
    public float calculateHarvest(FarmerStats stats){

        float harvestTotal = this.getProductsProduced() * (getSellPrice() + stats.getBonusEarnings());
        float waterBonus = harvestTotal * 0.2F * calculateWater();
        float fertilizerBonus = harvestTotal * 0.5F * getFertilizerReceived();

        return (harvestTotal + waterBonus + fertilizerBonus) * 1.1F; //Specific calculation for flowers
    }

}
