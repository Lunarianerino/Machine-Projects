import javax.swing.*;

/**
 * Subclass of AbstractPlant that sets the unique icons for trees in its constructor method.
 */
public class TreePlant extends AbstractPlant{
    /**
     * Constructor method for TreePlant that sets the ImageIcons for its growing and harvestable state.
     * @param id id of the plant
     */
    public TreePlant(int id) {
        super(id);
        System.out.println("Type: " + this.getType());

        this.setGrowing(new ImageIcon("./Dirt Asset/growingTree.png"));
        this.setHarvestable(new ImageIcon("./Dirt Asset/harvestableTree.png"));
    }


}
