import javax.swing.*;

/**
 * FarmPlot class simulates the states of a plot, whether it is rocky, unplowed, plowed, or planted with a plant.
 * This class contains an instance of a Plant class.
 */
public class FarmPlot extends JButton {
    private final Icon untilled = new ImageIcon("./Dirt Asset/dirt.png");
    private final Icon rocky = new ImageIcon("./Dirt Asset/rocky.png");
    private final Icon tilled = new ImageIcon("./Dirt Asset/FarmLand.png");
    /*
        States:
        -1 = rocky
        0 = unplowed
        1 = plowed
        2 = planted
     */
    private int state = 0;
    private AbstractPlant plant;
    private int row;
    private int col;

    /**
     * Constructor method of FarmPlot. Takes in an int that indicates whether the FarmPlot object's initial state is
     * rocky or not. The row and col attributes are for storing the position of the instantiated FarmPlot as these
     * values are assigned and given from the instantiation of FarmPlots in the GameManager class.
     * @param i status indicator of rocky state
     * @param row row position of this FarmPlot
     * @param col column position of this FarmPlot
     */
    public FarmPlot(int i, int row, int col){
        if(i == 1){
            state = -1;
        }
        this.row = row;
        this.col = col;
    }
    /**
     * Getter method that returns the state of the plant
     * @return Value of the plant's current state
     */
    public int getState() {return state;}

    /**
     * Setter method that sets the state attribute by the provided value from the parameter
     * @param state Value of the plant's new state
     */
    public void setState(int state) {this.state = state;}

    /**
     * Constructor method that takes in an ID of a specific plant.
     * Changes the plot's state to 2 (planted)
     * @param id Value of the plant's specific ID
     * @param type Type of plant. Used for instantiating the respective subclass of the plant type.
     */
    public void plant(int id, String type) {
        switch (type) {
            case "Root Crop" -> plant = new RootPlant(id);
            case "Flower" -> plant = new FlowerPlant(id);
            case "Tree" -> plant = new TreePlant(id);
        }
        setState(2);
    }

    /**
     * Method that returns the icon of an untilled plot
     * @return image icon of an untilled plot
     */
    public Icon getUntilled() {
        return untilled;
    }

    /**
     * Method that returns the icon of a rocky plot
     * @return image icon of a rocky plot
     */
    public Icon getRocky() {
        return rocky;
    }

    /**
     * Method that returns the icon of a tilled plot
     * @return image icon of a tilled plot
     */
    public Icon getTilled() {
        return tilled;
    }

    /**
     * Method that returns the row coordinate of the plot
     * @return integer row coordinate of the plot
     */
    public int getRow() {
        return row;
    }

    /**
     * Method that returns the column coordinate of the plot
     * @return integer col coordinate of the plot
     */
    public int getCol() {
        return col;
    }

    /**
     * Method that returns the plant object currently instantiated in the plot
     * @return subclass of AbstractPlant object (root crop, flower, or tree)
     */
    public AbstractPlant getPlant() {
        return plant;
    }

    /**
     * Method sets the plant with the given plant object. All uses of this method is to delete the current plant object
     * by setting to null
     * @param plant plant object
     */
    public void setPlant(AbstractPlant plant) {
        this.plant = plant;
    }
}
