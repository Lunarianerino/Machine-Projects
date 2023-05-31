

/**
 * Driver Class
 */
public class main {
    public static void main(String[] args) {
        MyFarmView.addFont();
        RockData.generateRockFile();
        MyFarmView.start();
    }

    /**
     * Method that resets the MVC architecture.
     */
    public static void reset(){
        RockData.generateRockFile();

        GameManager game = new GameManager();
        MyFarmView view = new MyFarmView(game);
        MyFarmController fc = new MyFarmController(view,game);
    }

    /**
     * Method that initializes the MVC architecture, plant data, and rock sequence data.
     */
    public static void start()
    {
        GetData.init();
        RockData.initializeFromFile();
        GameManager gm = new GameManager();
        MyFarmView fv = new MyFarmView(gm);
        MyFarmController fc = new MyFarmController(fv,gm);
    }

}
