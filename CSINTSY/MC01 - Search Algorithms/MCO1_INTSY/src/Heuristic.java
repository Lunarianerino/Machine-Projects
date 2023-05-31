import java.lang.Math;

//    Class for heuristics.
public class Heuristic {

//    Utility function for computing distance from start node (g cost).
    public static void calculateActualCost(Node currentNode, Node parentNode){
        int actualCost = parentNode.getDistanceFromStart() + 1;
        for(Node child: parentNode.getChildren()){
            if(child == currentNode) {
                actualCost += child.getDistanceFromStart();
                break;
            }
        }
        currentNode.setDistanceFromStart(actualCost);
        currentNode.updateHeuristicEvaluation(); //updates f(n)
    }

//    Utility function to calculate manhattan distance.

    /*
        Manhattan Distance
        h = abs (current_cell.x – goal.x) +
                abs (current_cell.y – goal.y)*/
    public static void calculateHeuristic(Node currentNode, Node goalNode){
        int xDistance = Math.abs(currentNode.getXCoordinate() - goalNode.getXCoordinate());
        int yDistance = Math.abs(currentNode.getYCoordinate() - goalNode.getYCoordinate());
        currentNode.setHeuristicCost(xDistance + yDistance);
    }
}
