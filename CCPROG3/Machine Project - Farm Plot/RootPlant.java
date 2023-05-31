import javax.swing.*;

/**
 * Subclass of AbstractPlant that sets the unique icons for root crops in its constructor method.
 */
public class RootPlant extends AbstractPlant{
    /**
     * Constructor method for RootPlant that sets the ImageIcons for its growing and harvestable state.
     * @param id id of the plant
     */
    public RootPlant(int id){
        super(id);
        System.out.println("Type: " + this.getType());

        this.setGrowing(new ImageIcon("./Dirt Asset/growingRoot Crop.png"));
        this.setHarvestable(new ImageIcon("./Dirt Asset/harvestableRoot Crop.png"));
    }
}
