import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

/**
 * Class that controls the actions and events that happens when the user interacts with the GUI
 */
public class MyFarmController {

    private MyFarmView view;
    private GameManager game;
    private FarmerStats stats;

    /**
     * Constructor method for MyFarmController. Takes in an instance of MyFarmView and GameManager to serve
     * as a mediator between the two instances of these classes. This method contains all the ActionListeners and
     * ChangeListeners that modify the behavior of JButtons to perform the specific actions each JButton object does.
     * @param view MyFarmView GUI instance
     * @param game GameManager instance
     */
    public MyFarmController(MyFarmView view, GameManager game) {
        this.view = view;
        this.game = game;
        this.stats = game.getFarmerStats();

        //sleep button
        this.view.setBtnListener(this.view.getSleepButton(),new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent e){
                System.out.println("Sleep to the next day!");
                game.nextDay(game.getPlots());
                updateDay(game.getPlots());
                try
                {
                    game.checkLoseCondition(game.getPlots());
                } catch (Exception ex)
                {
                    view.exceptionHandler(ex);
                }
            }
        });

        this.view.myFarmWindow.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.out.println("Window closed!");
                System.exit(0);
            }
        });

        //rank up button
        this.view.setBtnListener(this.view.getRankUpButton(), new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("Confirm to rank up window set visible");
                if (true) {
                    try {
                        game.rankUp(game.getFarmerStats());
                    } catch (Exception ex) {
                        view.exceptionHandler(ex);
                    }
                    updateCL();
                }
            }
        });
        this.view.addBtnChangeListener(this.view.getRankUpButton(), new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                ButtonModel m = (ButtonModel) e.getSource();
                if(m.isRollover()){
                    displayRankUpDetails(m.isRollover(),520,60,  game.getFarmerStats().getNextLevelReq(), game.getFarmerStats().getRankUpFee());
                }else{
                    displayRankUpDetails(m.isRollover(),520,60,  game.getFarmerStats().getNextLevelReq(), game.getFarmerStats().getRankUpFee());
                }
            }
        });

        //seed area buttons (for buying seeds)
        for(JButton b: view.getSeedButtons()){
            int i = view.getSeedButtons().indexOf(b) + 1;
            String name = GetData.getPlantName(i);
            String type = GetData.getPlantType(i);
            int cost = GetData.getPrice(i) + game.getFarmerStats().getSeedCostReduction();

            view.setBtnListener(b, new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    view.setCursor(name.toLowerCase(), i);
                    System.out.println("Selected " + name + " Id: " + i);
                }
            });

            view.addBtnChangeListener(b, new ChangeListener() {
                @Override
                public void stateChanged(ChangeEvent e) { //displays details if mouse is hovering
                    ButtonModel m = (ButtonModel) e.getSource();
                    if (m.isRollover()){
                        displayShopDetails(m.isRollover(), 640, 590, name, type, cost);
                    }else{
                        displayShopDetails(m.isRollover(), 600, 590, name, type, cost);
                    }
                }
            });
        }

        //tool buttons (selecting tools)
        for(JButton b: view.getToolButtons()){
            int i = view.getToolButtons().indexOf(b);
            String name = view.getTools()[i];

            view.setBtnListener(b, new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    view.setCursor(name, 0);
                    System.out.println("Selected " + name);
                }
            });
        }

        //FarmPlot buttons
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 5; j++) {

                int row = i;
                int col = j;

                int x = game.getPlots()[i][j].getX();
                int y = game.getPlots()[i][j].getY();

                view.setBtnListener(game.getPlots()[i][j], new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        FarmPlot p = (FarmPlot) e.getSource();
                        action(p);

                    }
                });

                view.addBtnChangeListener(game.getPlots()[i][j], new ChangeListener() {
                    @Override
                    public void stateChanged(ChangeEvent e) {
                        ButtonModel m = (ButtonModel) e.getSource();
                        if (game.getPlots()[row][col].getState() == 2)
                        {
                            if (m.isRollover()) {
                                updateStats(m.isRollover(), x-5, y+20, game.getPlots()[row][col]);
                            }
                            else{
                                updateStats(m.isRollover(), x-5, y+20, game.getPlots()[row][col]);
                            }
                        }
                    }
                });
            }
        }
    }

    /**
     * Private method that displays a panel whenever the user hovers over the rank up button to display the
     * next rank's requirements for levels and coins.
     * @param hover boolean value that indicates whenever the mouse cursor is hovering the JButton
     * @param posX X coordinate position in the game window
     * @param posY Y coordinate position in the game window
     * @param levelCost level requirement of the next rank
     * @param coinCost price of the next rank
     */
    private void displayRankUpDetails(boolean hover, int posX, int posY, int levelCost, int coinCost){
        if(game.getFarmerStats().getName().equals("Legendary Farmer")){
            view.getRankDetailsPanel().setBounds(posX,posY, 80,60);
            view.getRankText().setText("maximum\nrank\nachieved!");
            view.getRankLevel().setVisible(false);
            view.getRankCoin().setVisible(false);
            view.getRankDetailsPanel().setVisible(hover);

            return;
        }

        view.getRankDetailsPanel().setBounds(posX,posY, 80, 90);
        view.getRankText().setText("Next Rank");
        view.getRankLevel().setText("level: " + levelCost);
        view.getRankCoin().setText("cost: " + coinCost);

        view.getRankDetailsPanel().setVisible(hover);

    }

    /**
     * Method that updates the text that displays the day whenever the sleep JButton is pressed. This method
     * also calls the utility method updatePlot to update all FarmPlot objects if the state of each FarmPlot has changed.
     * @param p FarmPlot 2D array to update using updatePlot
     */
    private void updateDay(FarmPlot[][] p){
        view.getDayText().setText("DAY " + game.getDay());
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                updatePlot(p[i][j]);
            }
        }
    }

    /**
     * Method that calls the corresponding GameManager action method depending on the current cursor. The method
     * calls GameManager's checkLoseCondition before the method ends to check if all losing conditions are passed.
     * @param p FarmPlot object to perform the action on
     */
    private void action(FarmPlot p) {
        String tool = view.myFarmWindow.getCursor().getName();
        String msg = "0";
        if (view.getCursorId() == 0)
        {
            try
            {

                switch (tool) {
                    case "water" -> {
                        game.water(p);
                        msg = "Watered " + p.getPlant().getName() + " plant!";
                    }
                    case "fertilizer" -> {
                        game.fertilize(p);
                        msg = "Fertilized " + p.getPlant().getName() + " plant!";
                    }
                    case "plow" -> {
                        game.plow(p);
                        updatePlot(p);
                        msg = "Plowed plot (" + (p.getRow() + 1) + "," +(p.getCol() + 1) + ")!";
                    }
                    case "pickaxe" -> {
                        game.pickaxe(p);
                        updatePlot(p);
                        msg = "Removed rock from plot (" + (p.getRow() + 1) + "," + (p.getCol() + 1) + ")!";
                    }
                    case "shovel" -> {
                        if (p.getState() == 2)
                            msg = "Dug " + p.getPlant().getName() + " plant! Reduced 7 coins and gained 2.0 exp";
                        else
                            msg = "Nothing happened (" + (p.getRow() + 1) + "," + (p.getCol() + 1) + ") but still reduced 7 coins!";

                        game.shovel(p);
                        updatePlot(p);
                    }
                    case "harvest" -> {
                        if(p.getPlant() != null)
                            //added this conditional statement to prevent
                            msg = "Harvested " + p.getPlant().getProductsProduced() + " " + p.getPlant().getName()
                                    + " plant! Gained " + p.getPlant().calculateHarvest(stats) +
                                    " coins and " + p.getPlant().getExp() + " exp";
                        game.harvest(p);
                        updatePlot(p);

                    }
                }
                game.checkLoseCondition(game.getPlots());
                setUpdateText(msg, false);


            }
            catch (Exception e)
            {
                view.exceptionHandler(e);
            }
        } else
        {
            try {
                game.plant(p, view.getCursorId()); //since cursorID is also equivalent to the selected seed ID
                msg = "Planted " + GetData.getPlantName(view.getCursorId()) + " " + GetData.getPlantType(view.getCursorId()) +
                        " (" +(p.getRow() + 1) + "," + (p.getCol() + 1) + ")" +
                        " for " + (GetData.getPrice(view.getCursorId()) + FarmerStats.getSeedCostReduction()) + " Coins!";
                setUpdateText(msg, false);
            } catch (Exception e){
                view.exceptionHandler(e);
            }
            updatePlot(p);
        }
        updateCL();
    }

    /**
     * Method to change UpdateText to the given message parameter.
     * @param msg Message displayed in the GUI
     * @param isError will make the message blink in red indicating that the updated text is an error
     */
    private void setUpdateText (String msg, boolean isError)
    {
        if (isError)
            blinkText(view.getUpdateText(), Color.white);
        view.getUpdateText().setText(msg);
    }

    /**
     * Method that setUpdateText uses if the given text prompt is an error (isError = true). This method will flash the
     * UpdateText JTextPane to red a few times to indicate to the user that they have performed something that isn't allowed
     * @param text Message displayed in the GUI
     * @param original Original color of UpdateText (Color.white)
     */
    private void blinkText (JTextPane text, Color original)
    {
        ActionListener blinker = new ActionListener() {
            boolean isRed = true;
            int counter = 0;
            public void actionPerformed(ActionEvent ae) {
                if (isRed) {
                    text.setForeground(original);
                    if (counter >= 5)
                    {
                        Timer timer = (Timer)ae.getSource();
                        timer.stop();
                    }
                } else {
                    text.setForeground(Color.red.darker());
                }
                counter ++;
                isRed = !isRed;
            }
        };
        Timer timer = new Timer(100, blinker);
        timer.start();
    }

    /**
     * Method to update a FarmPlot JButton, changing its ImageIcon depending on its state or if there is a plant.
     * @param p FarmPlot to update its ImageIcon
     */
    private void updatePlot(FarmPlot p)
    {
        switch (p.getState()) {
            case -1 -> {
                p.setIcon(p.getRocky());
                view.getStatusPanel().setVisible(false);
            }
            case 0 -> {
                p.setIcon(p.getUntilled());
                view.getStatusPanel().setVisible(false);
            }
            case 1 -> {
                p.setIcon(p.getTilled());
                view.getStatusPanel().setVisible(false);
            }
            case 2 -> {
                if(view.getCursorId() > 0) { //will only change if not on tools
                    p.setIcon(new ImageIcon("./Seeds/" + GetData.getPlantName(view.getCursorId()) + ".png"));
                }
                switch (p.getPlant().getState()) {
                    case 3 -> p.setIcon(new ImageIcon("./Dirt Asset/wither.png"));
                    case 1 -> p.setIcon(p.getPlant().getGrowing());
                    case 2 -> p.setIcon(p.getPlant().getHarvestable());
                }
            }

        }
    }

    /**
     * Method that sets a panel visible that shows the name, type, and price of a seed whenever the mouse cursor is hovering
     * above the JButton of the respective seed.
     * @param hover boolean value that indicates whenever the mouse cursor is hovering the JButton
     * @param posX X coordinate position in the game window
     * @param posY Y coordinate position in the game window
     * @param name name of the selected seed
     * @param type type of the selected seed
     * @param cost price of the selected seed
     */
    private void displayShopDetails(boolean hover, int posX, int posY, String name,String type, int cost){

        view.getShopDetailPanel().setBounds(posX, posY, 110, 60);

        view.getShopPlantName().setText(name + " " + type);

        int newCost = cost + FarmerStats.getSeedCostReduction();
        view.getShopPlantCost().setText("Price: " + newCost);

        view.getShopDetailPanel().setVisible(hover);
    }

    /**
     * Method that updates the rank, level, and coins panel found in the top-left corner of the GUI.
     */
    private void updateCL(){
        view.getFarmerRankText().setText(""  + game.getFarmerStats().getName());
        view.getFarmerLevelText().setText("level: " + game.getFarmerStats().getFarmerLevel()
                + " (" + String.format("%.2f",game.getFarmerStats().getFarmerExp()) + " exp)");
        view.getFarmerCoinsText().setText("coins: " + String.format("%.2f",game.getCoins().getAmount()));
    }

    /**
     * Method that sets a panel visible that shows a FarmPlot object's state and other statuses that are necessary to
     * achieve all the necessary requirements for the plant to grow to a harvestable state.
     * @param hover boolean value that indicates whenever the mouse cursor is hovering the JButton
     * @param posX X coordinate position in the game window
     * @param posY Y coordinate position in the game window
     * @param p FarmPlot instance that is being checked
     */
    private void updateStats(boolean hover, int posX, int posY, FarmPlot p)
    {
        view.getStatusPanel().setBounds(posX, posY, 100, 100);
        view.getPlantStatus().setText("🌱: " + p.getPlant().toStringState());
        view.getWaterStatus().setText("💦: " + p.getPlant().getWaterReceived() + "/" + p.getPlant().getWaterMin() + "(" + p.getPlant().getWaterLimit() + ")");
        view.getFertilizerStatus().setText("💩: " + p.getPlant().getFertilizerReceived() + "/" + p.getPlant().getFertilizerMin() + "(" + p.getPlant().getFertilizerLimit() + ")");

        view.getStatusPanel().setVisible(hover);

    }
}
