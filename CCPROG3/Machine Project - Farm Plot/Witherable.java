/**
 * Interface that implements the checkWither method
 */
public interface Witherable {
    /**
     * Interface method for AbstractPlant. This method makes it so that every subclass of AbstractPlant is subject
     * to withering once the implemented conditions for a plant to wither are met.
     */
    default void checkWither(){}
}
