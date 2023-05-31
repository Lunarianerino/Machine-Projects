/**
 * FarmerStats Class contains the attributes and methods to represent the experience and leveling features of MyFarm
 * as well as the ranks give bonuses that contribute to the calculation of the final harvest price of each plot.
 */
public class FarmerStats {
    private float farmerExp = 0;
    private int farmerLevel = 0;

    FarmerType type = new FarmerType();

    /**
     * Empty Constructor method for FarmerStats
     */
    public FarmerStats(){}

    /**
     * Getter method for the farmer's level
     * @return farmerLevel
     */
    public int getFarmerLevel() {
        return this.farmerLevel;
    }

    /**
     * Getter method for the farmer's exp
     * @return farmer's exp
     */
    public float getFarmerExp(){
        return this.farmerExp;
    }
    /**
     * Method for adding exp. Calls addLevel method to reset EXP to 0 everytime it reaches 100.
     * @param value amount of EXP that will be added to the farmer's current EXP.
     */
    public void addExp(float value){
        this.farmerExp += value;
        addLevel();
    }

    /**
     * Private utility method used by addExp to increase the farmer's level
     * whenever the farmer's current EXP exceeds 100.
     */
    private void addLevel(){
        /*
        This loop will repeatedly subtract 100 from EXP until it is a value less than 100.
         */
        while(this.farmerExp >= 100){
            this.farmerExp -= 100;
            this.farmerLevel ++;
        }
    }

    /**
     * Method for changing the farmer type into a higher type
     */
    public void rankUp(){
        type.rankUp();
    }
    
    /**
     * Getter method for FarmerType's name
     * @return String for the farmer rank's name
     */
    public String getName() {
        return type.name;
    }

    /**
     * Getter method for FarmerType's required level for upgrading to the next rank
     * @return Value of FarmerType's next required level for upgrading to the next rank
     */
    public int getNextLevelReq() {
        return type.nextLevelReq;
    }

    /**
     * Getter method for the required price for FarmerType's next rank
     * @return Value of the required price for FarmerType's next rank
     */
    public int getRankUpFee() {
        return type.rankUpFee;
    }

    /**
     * Getter method for the bonus earnings of the farmer's current rank
     * @return Value of the bonus earnings of the farmer's current rank
     */
    public int getBonusEarnings() {
        return type.bonusEarnings;
    }

    /**
     * Getter method for the seed cost reduction of the farmer's current rank
     * @return Value of the seed cost reduction of the farmer's current rank
     */
    public static int getSeedCostReduction() {
        return FarmerType.seedCostReduction;
    }

    /**
     * Getter method for the water bonus limit increase of the farmer's current rank
     * @return Value of the water bonus limit increase of the farmer's current rank
     */
    public static int getWaterBonusLimitIncrease() {
        return FarmerType.waterBonusLimitIncrease;
    }

    /**
     * Getter method for the fertilizer bonus limit increase of the farmer's current rank
     * @return Value of the fertilizer bonus limit increase of the farmer's current rank
     */
    public static int getFertilizerBonusLimitIncrease() {
        return FarmerType.fertilizerBonusLimitIncrease;
    }


    /**
     * Private class Farmertype used by FarmerStats
     */
    private class FarmerType{
        //Stats for Farmer(default)
        private int type = 0;
        private String name = "Farmer";
        private int nextLevelReq = 5;
        private int bonusEarnings = 0;
        private static int seedCostReduction = 0;
        private static int waterBonusLimitIncrease = 0;
        private static int fertilizerBonusLimitIncrease = 0;
        private int rankUpFee = 200;

        /**
         * Empty constructor method for the FarmerType class.
         */
        private FarmerType(){
        }

        /**
         * Method that increases the rank of the farmer everytime it is called.
         * Increasing the rank will change the attribute values of the instantiated FarmerTypes as well.
         */
        private void rankUp(){
            //increments rank whenever the method is called
            type++;
            //returns when Legendary Farmer is already obtained.
            if (type>3) {return;}

            switch(type){ //changes the bonuses to the corresponding rank of the farmer.
                case 1:
                    //Registered Farmer
                    this.name = "Registered Farmer";
                    this.nextLevelReq = 10;
                    this.bonusEarnings = 1;
                    seedCostReduction = -1;
                    fertilizerBonusLimitIncrease = 0;
                    this.rankUpFee = 300;
                    break;
                case 2:
                    //Distinguished Farmer
                    this.name = "Distinguished Farmer";
                    this.nextLevelReq = 15;
                    this.bonusEarnings = 2;
                    seedCostReduction = -2;
                    waterBonusLimitIncrease = 1;
                    this.rankUpFee = 400;
                    break;
                case 3:
                    //LegendaryFarmer
                    this.name = "Legendary Farmer";
                    this.bonusEarnings = 4;
                    seedCostReduction = -3;
                    waterBonusLimitIncrease = 2;
                    fertilizerBonusLimitIncrease = 1;
                    this.rankUpFee = 0;
                    break;
            }
        }
    }
}
