import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

/**
 * GetData obtains data from a json file to store in an instance of PlantStats.
 */
public class GetData {

    private static BufferedReader br;
    private static Gson gson = new Gson();
    private static ArrayList<PlantStat> plantStats;

    /**
     * Method that obtains plant data from json file and stores into an ArrayList of PlantStat objects
     */
    public static void init()
    {
        //get plants data from json file
        try {
            br = new BufferedReader(new FileReader("plant-info.json"));
            plantStats = gson.fromJson(br, new TypeToken<List<PlantStat>>(){}.getType());
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }

    }

    /**
     * Getter method that retrieves the stats of a plant according to its id
     * @param id ID value for plant identification
     * @return PlantStat object containing the attributes of the specific plant id
     */
    public static PlantStat getPlantStats(int id) {
        return plantStats.get(id);
    }

    /**
     * Getter method that retrieves the price of a plant according to its id
     * @param id ID value for plant identification
     * @return Amount of coins to plant a specific plant
     */
    public static int getPrice(int id) {
        return plantStats.get(id).getCost();
    }

    /**
     * Getter method for the thumbnail path of a plant
     * @param id ID of the plant
     * @return string of the path of the plant's thumbnail
     */
    public static String getThumbnailPath(int id) {return plantStats.get(id).getThumbnailPath();}

    /**
     * Getter method for the amount of plants there are in the JSON file
     * @return amount of crops stored in plant-info.json
     */
    public static int getDataAmount() {return plantStats.size();}

    /**
     * Getter method for the name of the plant according to its id
     * @param id ID of the plant
     * @return plant name String
     */
    public static String getPlantName(int id) {return plantStats.get(id).getName();}

    /**
     * Getter method for the plant type according to its id
     * @param id ID of the plant
     * @return plant type String
     */
    public static String getPlantType(int id) {return plantStats.get(id).getType();}
}
