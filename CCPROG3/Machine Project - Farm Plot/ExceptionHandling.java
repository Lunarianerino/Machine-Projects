/**
 * Class that contains all the exceptions. These exceptions are used to display error messages in the GUI whenever
 * certain conditions are met to invoke the exceptions.
 */
public class ExceptionHandling
{
    /**
     * Exception thrown when the user does not have enough coins to perform an action.
     */
    public static class InsufficientCoinsException extends Exception{}

    /**
     * Exception thrown when the plot is unable to be plowed as it is occupied
     */
    public static class PlowException extends Exception{}

    /**
     * Exception thrown when a plot cannot be watered
     */
    public static class WaterException extends Exception{}

    /**
     * Exception thrown when the user tries to water a withered plant
     */
    public static class WaterWitheredException extends Exception{}

    /**
     * Exception thrown when the user tries to fertilize a plot that does not have a plant
     */
    public static class FertilizeException extends Exception{}

    /**
     * Exception thrown when the user tries to fertilize a withered plant
     */
    public static class FertilizeWitheredException extends Exception{}

    /**
     * Exception thrown when the user tries to use the pickaxe tool on a plot that isn't in a rocky state
     */
    public static class PickaxeException extends Exception{}

    /**
     * Exception thrown when the user tries to plant a tree on the edges and corners of a plot
     */
    public static class SideException extends Exception{}

    /**
     * Exception thrown when the user tries to plant on an occupied tile (whether by a rock, plant, or withered plant)
     */
    public static class OccupiedException extends Exception{}

    /**
     * Exception thrown when the user tries to use the harvest tool on a tile that does not have a plant instance
     */
    public static class HarvestNothingException extends Exception{}

    /**
     * Exception thrown when the user tries to plant a tree adjacent to an occupied plot
     */
    public static class TreeConditionException extends Exception{}

    /**
     * Exception thrown when the user tries to plant on an uplowed tile
     */
    public static class UnplowedException extends Exception{}

    /**
     * Exception thrown when the user tries to harvest a withered plant
     */
    public static class WitheredException extends Exception{}

    /**
     * Exception thrown when the user tries to harvest a plant that is not yet ready
     */
    public static class GrowingException extends Exception{}

    /**
     * Exception thrown when the user tries to rank up without meeting the level requirement
     */
    public static class InsufficientLevelException extends Exception{}

    /**
     * Exception thrown when all the conditions for losing the game is met
     */
    public static class GameLostException extends Exception{}
}
