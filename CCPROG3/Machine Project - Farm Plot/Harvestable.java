/**
 * Harvestable interface for the AbstractPlant subclasses.
 */
public interface Harvestable {
    /**
     * Interface method for AbstractPlant. This method makes it so that each subclass of AbstractPlant will have a
     * method that would calculate its harvest price.
     * @return float value of the total harvest price.
     */
    default float calculateHarvestPrice(){
        return 0;
    }
}