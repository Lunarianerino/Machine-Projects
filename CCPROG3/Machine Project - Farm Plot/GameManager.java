import java.util.Objects;

/**
 * GameManager class that contains the attributes and methods to run the simulation with all the features
 * interacting with each other. This class will also contain the actions a player can do to a plot.
 */
public class GameManager {
    private Coins coins = new Coins(100);
    private FarmerStats stats = new FarmerStats();
    private FarmPlot[][] Plots = new FarmPlot[10][5]; //initializes as null
    private int day = 1;

    /**
     * Constructor method of GameManager. This is where the farm plots are instantiated.
     */
    public GameManager()
    {
        System.out.println("GM INITIATED");

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                Plots[i][j] = new FarmPlot(RockData.getRockData(i + j * 10), i ,j);
            }
        }
    }

    /**
     * Method to change the plot status from "unplowed" to "plowed".
     * Gives 0.5 exp.
     * @param p Plot to perform the action on
     */

    /**
     * Method to change the plot status from "unplowed" to "plowed".
     * Gives 0.5 exp.
     * @param p Plot to perform the action on
     * @throws ExceptionHandling.PlowException when the user tries to plow anything aside from an untilled plot
     */
    public void plow (FarmPlot p) throws ExceptionHandling.PlowException
    {
        if (p.getState() == 0){
            p.setState(1);
            stats.addExp(0.5F);
        }

        else throw new ExceptionHandling.PlowException();
    }

    /**
     * Getter method for the instance of FarmerStats
     * @return FarmerStats object
     */
    public FarmerStats getFarmerStats(){
        return this.stats;
    }

    /**
     * Getter method for the instance of Coins
     * @return Coins object
     */
    public Coins getCoins(){
        return this.coins;
    }

    /**
     * Method to water the plant instance. Increments the waterReceived attribute of a Plant object as long as
     * the attribute does not exceed past the water limit.
     * The method will not add exp once the water limit is reached.
     * @param p Plot to perform the action on
     * @throws ExceptionHandling.WaterException when a plot cannot be watered
     * @throws ExceptionHandling.WaterWitheredException when the user tries to water a withered plant
     */
    public void water(FarmPlot p) throws ExceptionHandling.WaterException, ExceptionHandling.WaterWitheredException
    {
        if(p.getPlant() == null || p.getPlant().getName().equals("Empty Plot")){
            throw new ExceptionHandling.WaterException();
        }

        if(p.getPlant().getState() == 3){
            throw new ExceptionHandling.WaterWitheredException();
        }

        //does not add exp if there is no plant
        if(p.getPlant().getState() >= 0) {
            //does not add exp if waterLimit is reached
            if(p.getPlant().addWater()){
                stats.addExp(0.5F);
            }
        }
    }

    /**
     * Method to fertilize a Plant object. Increments the fertilizerReceived attribute of a plant object.
     * The method will continue to deduct coins if the fertilizer limit is already reached.
     * @param p FarmPlot object to perform the action on
     * @throws ExceptionHandling.FertilizeException when the user tries to fertilize a plot that does not have a plant
     * @throws ExceptionHandling.InsufficientCoinsException when the user does not have enough coins to perform the action
     * @throws ExceptionHandling.FertilizeWitheredException when the user tries to fertilize a withered plant
     */
    public void fertilize(FarmPlot p) throws ExceptionHandling.FertilizeException, ExceptionHandling.InsufficientCoinsException, ExceptionHandling.FertilizeWitheredException {
        if(p.getPlant() == null || p.getState() != 2){
            throw new ExceptionHandling.FertilizeException();
        }
        if(p.getPlant().getState() == 3){
            throw new ExceptionHandling.FertilizeWitheredException();
        }
        //if out of coins, do not carry out function
        if (!coins.isEnough(10)) {
            throw new ExceptionHandling.InsufficientCoinsException();
        }

        //does not add exp if there is no plant
        if(p.getPlant().getState() >= 0) {
            //does not add exp if waterLimit is reached
            if(p.getPlant().addFertilizer()){
                coins.addAmount(-10);
                stats.addExp(4.0F);
            }
        }
    }

    /**
     * Method to remove rocks from a plot
     * @param p FarmPlot object to perform the action on
     * @throws ExceptionHandling.PickaxeException when the user tries to use the pickaxe tool on a plot that isn't in a rocky state.
     * @throws ExceptionHandling.InsufficientCoinsException when the user does not have enough coins to perform the action
     */
    public void pickaxe(FarmPlot p) throws ExceptionHandling.PickaxeException, ExceptionHandling.InsufficientCoinsException
    {
        if (p.getState() == -1)
        {
            //if out of coins, do not carry out function
            if (!coins.isEnough(50)) {
                throw new ExceptionHandling.InsufficientCoinsException();
            }
            coins.addAmount(-50);
            p.setState(0);
            stats.addExp(15.0F);
        }else{
            throw new ExceptionHandling.PickaxeException();
        }

    }

    /**
     * Method to use the shovel feature. This method resets the state of the plot by setting the plant to null
     * and reverting the plot's state to 0 (untilled)
     * @param p FarmPlot object to perform the action on
     * @throws ExceptionHandling.InsufficientCoinsException when the user does not have enough coins to perform the action
     */
    public void shovel(FarmPlot p) throws ExceptionHandling.InsufficientCoinsException
    {
        //if out of coins, do not carry out function, this action DOES NOT check if the action is valid/useful first
        if (!coins.isEnough(7)) {
            throw new ExceptionHandling.InsufficientCoinsException();
        }
        coins.addAmount(-7);
        //waste of money: use shovel on rock
        if(p.getState() == -1)
            return;
        //removes plant
        p.setPlant(null);
        //reverts state to unplowed
        p.setState(0);
        //add exp
        stats.addExp(2.0F);
    }

    /**
     * Method that checks a FarmPlot if it eligible for planting
     * @param p FarmPlot object
     * @return boolean value whether a plot is eligible for planting
     */
    public boolean canPlant(FarmPlot p){
        return p.getState() != -1 && p.getState() != 2;
    }

    /**
     * Method to plant a seed into an empty plowed lot.
     * @param p FarmPlot object to perform the action on
     * @param id ID of the seed that will be planted
     * @throws ExceptionHandling.SideException when the user tries to plant a tree on the edges and corners of a plot
     * @throws ExceptionHandling.OccupiedException when the user tries to plant on an occupied tile (whether by a rock, plant, or withered plant)
     * @throws ExceptionHandling.UnplowedException when the user tries to plant on an uplowed tile
     * @throws ExceptionHandling.InsufficientCoinsException when the user does not have enough coins to perform an action.
     * @throws ExceptionHandling.TreeConditionException when the user tries to plant a tree adjacent to an occupied plot
     */
    public void plant (FarmPlot p, int id) throws ExceptionHandling.SideException, ExceptionHandling.OccupiedException, ExceptionHandling.UnplowedException, ExceptionHandling.InsufficientCoinsException, ExceptionHandling.TreeConditionException {
        //check tree
        if(Objects.equals(GetData.getPlantType(id), "Tree")){
            //get row and col of current plant
            for(int i=p.getRow() - 1; i < p.getRow() + 2;i++){
                for(int j= p.getCol() - 1;j< p.getCol() + 2;j++){
                    try{
                        //tests if this plot exists; will throw exception if index out of array
                        FarmPlot tester = Plots[i][j];
                    } catch(ArrayIndexOutOfBoundsException e){
                        throw new ExceptionHandling.SideException();
                    }
                    if(!canPlant(Plots[i][j])){ //check if occupied
                        throw new ExceptionHandling.TreeConditionException();
                    }
                }
            }
        }
        if (p.getState() == 1)
        {
            //calculates cost of plant with the reduced cost
            int cost = GetData.getPrice(id);
            if (!coins.isEnough(cost + FarmerStats.getSeedCostReduction())) {
                throw new ExceptionHandling.InsufficientCoinsException();
            }
            coins.addAmount(-(cost + FarmerStats.getSeedCostReduction()) );

           p.plant(id, GetData.getPlantType(id));
        }
        else if (p.getState() == 2){
            throw new ExceptionHandling.OccupiedException();
        }
        else
        {
            throw new ExceptionHandling.UnplowedException();
        }

    }

    /**
     * Method to harvest a fully grown plant. This method computes for the total amount of coins gained from harvesting
     * a fully-grown crop. The bonuses are acquired from getter methods from a FarmerStats object.
     * @param p FarmPlot object to perform the action on
     * @throws ExceptionHandling.WitheredException when the user tries to harvest a withered plant
     * @throws ExceptionHandling.GrowingException when the user tries to harvest a plant that is not yet ready
     * @throws ExceptionHandling.HarvestNothingException when the user tries to use the harvest tool on a tile that does not have a plant instance
     */
    public void harvest(FarmPlot p) throws ExceptionHandling.WitheredException, ExceptionHandling.GrowingException, ExceptionHandling.HarvestNothingException
    {
        if(p.getPlant() == null){
            throw new ExceptionHandling.HarvestNothingException();
        }
        if (p.getPlant().getState() == 2)
        {
            float harvestPrice = p.getPlant().calculateHarvest(stats);

            //Add final harvest price to coins
            coins.addAmount(harvestPrice);

            //Increase exp
            stats.addExp(p.getPlant().getExp() * p.getPlant().getProductsProduced());

            //remove plant object
            p.setPlant(null);
            p.setState(0);

        }else if(p.getPlant().getState() == 3){
            System.out.println("Your " + p.getPlant().getName() + " has already withered.");
            throw new ExceptionHandling.WitheredException();
        }
        else {
            System.out.println("Plant cannot be harvested yet.");
            throw new ExceptionHandling.GrowingException();
        }
    }

    /**
     * Method that increases the day attribute to simulate the advancing of days. This will call the nextDay and
     * checkWither methods of the Plant object to perform the changes advancing a day would cause.
     * @param p Plot to perform the action on
     */
    public void nextDay(FarmPlot[][] p)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if(p[i][j].getPlant() != null)
                {
                    p[i][j].getPlant().nextDay();
                    p[i][j].getPlant().checkWither();
                }
            }
        }
        day++;

    }

    /**
     * Method to increase the rank of the farmer.
     * @param stats FarmerStats object that will perform the rankup method
     * @throws ExceptionHandling.InsufficientCoinsException when the user does not have enough coins to perform an action.
     * @throws ExceptionHandling.InsufficientLevelException when the user tries to rank up without meeting the level requirement
     */
    public void rankUp(FarmerStats stats) throws ExceptionHandling.InsufficientCoinsException, ExceptionHandling.InsufficientLevelException {
        //checks if farmer is eligible for rank up
        if(coins.isEnough(stats.getRankUpFee()) && stats.getFarmerLevel() >= stats.getNextLevelReq()){
            //check if max rank already
            System.out.println(stats.getRankUpFee());
            if(Objects.equals(stats.getName(), "Legendary Farmer")){
                System.out.println("You have already achieved the highest rank!");
                return;
            }
            coins.addAmount(-stats.getRankUpFee());
            stats.rankUp();
        }else{
            System.out.println("You do not meet the requirements to rank up.");
            if (!coins.isEnough(stats.getRankUpFee()))
            {
                throw new ExceptionHandling.InsufficientCoinsException();
            }
            if (stats.getFarmerLevel() < stats.getNextLevelReq())
            {
                throw new ExceptionHandling.InsufficientLevelException();
            }
        }
    }

    /**
     * Getter method that returns the 2D array of FarmPlots instantiated in GameManager
     * @return 2D array of FarmPlot objects
     */
    public FarmPlot[][] getPlots()
    {
        return Plots;
    }

    /**
     * Getter method that returns the current day in game
     * @return int value of current day
     */
    public int getDay() {
        return day;
    }

    /**
     * Method to check all the lose conditions
     * @param plots 2D array of FarmPlot objects to check if all conditions for losing are met
     * @throws ExceptionHandling.GameLostException when all the conditions for losing the game is met
     */
    public void checkLoseCondition (FarmPlot[][] plots) throws ExceptionHandling.GameLostException
    {
        //5 is the cheapest seed amount
        //Condition 1: not enough money to buy new seeds
        if (coins.getAmount() < 5)
        {
            System.out.println("Passed first condition");
            //condition 2: no active plants
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 5 ; j++)
                {
                    if (plots[i][j].getState() == 2)
                    {
                        System.out.println("pass second condition");
                        if (plots[i][j].getPlant().getState() != 3) //if not withered
                        {
                            System.out.println("Pass third condition");
                            return;
                        }
                    }
                }
            }
            //if it does not find any plot with active/growing plants
            throw new ExceptionHandling.GameLostException();
        }
    }
}
