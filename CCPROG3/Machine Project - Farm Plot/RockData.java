import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

/**
 * Class responsible for the rock generation feature of the game.
 */
public class RockData {

    private static final String rockFilePath = "./rockFileIO/rockIO.txt";
    private static int[] rockSequence = new int[50];
    private static int rockAmount;
    private static Scanner s;

    private static FileWriter w;

    /**
     * Method that initializes the rock sequence from the file rockIO.txt. Stores the sequence
     * into an int Array rockSequence
     */
    public static void initializeFromFile(){
        Arrays.fill(rockSequence, 0);
        File file = new  File(rockFilePath);

        try {
            s = new Scanner(file);
            for(int i =0; i <50 ; i++){
                rockSequence[i] = s.nextInt();

            }
            System.out.println("Current rockSequenceArray:");
            System.out.println("" + Arrays.toString(rockSequence));
            s.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        } finally{
            s.close();
        }

    }

    /**
     * Getter method that returns the presence of rock based on parameter i as the index of the
     * rockSequence array
     * @param i index of rockSequence
     * @return 1 if rock, 0 if not
     */
    public static int getRockData(int i){
        return rockSequence[i];
    }

    /**
     * Method that generates a random sequence of 1s and 0s such that each sequence will consist
     * of at least 10 1s and a maximum of 30 1s. The generated sequence will be written into
     * rockIO.txt for the method initializeFromFile() to read.
     */
    public static void generateRockFile(){
        Arrays.fill(rockSequence, 0);
        //minimum 10 rocks, maximum 30 rocks
        Random rand = new Random();

        //generates a random number from min to max amount of rocks
        rockAmount = rand.nextInt(10,31);

        //loop to generate a random index until rockAmount reaches 0
        while(rockAmount != 0){
            int r = rand.nextInt(0,49);
            if(rockSequence[r] == 0){ //decrements rockAmount if loop finds an unplowed tile
                rockSequence[r] = 1;
                rockAmount--;
            }
        }

        try {
            w = new FileWriter(rockFilePath);
            for (int j : rockSequence) {
                w.write(j + " ");
            }
            w.close();
        } catch (IOException e) {
            System.out.println("error:\n" + e);
        }
    }

    public static int[] getRockSequence(){return rockSequence;}
    public static String getRockSequenceString ()
    {
        return Arrays.toString(RockData.getRockSequence())
                .replace("[", "")
                .replace("]", "")
                .replace(",", "")
                .replace(" ", "")
                .trim();
    }

    /**
     * Method to overwrite the current rockIO file to the new generated data
     * @param data String of numbers from the JTextPane rockBinary in MyFarmView
     */
    public static void updateData(String data)
    {
        //pad with 0's if it is less than 50 characters to prevent errors
        while (data.length() < 50)
        {
            data = data.concat("0");
        }
        data = data.replaceAll(".", "$0 "); //adds spaces in between characters
        try{
            Files.write(Paths.get(rockFilePath), data.getBytes());
        }catch (IOException ex)
        {
            System.out.println("Invalid Path");
        }

        initializeFromFile();

    }
}
