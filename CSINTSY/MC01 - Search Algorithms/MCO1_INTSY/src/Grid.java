import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class Grid extends JPanel {
    private Node[][] nodeGrid;
    public int stepCount = 0;
    private int size;
    private final int maxSize = 64;
    private final int nodeSize = 15;
    private final Dimension gridUISize = new Dimension(maxSize*nodeSize, maxSize*nodeSize);

//    Stores the start and goal states.
    private Node startNode;
    private Node goalNode;

//    Getters for both states.
    public Node getstartNode(){
        return this.startNode;
    }
    public Node getgoalNode(){
        return this.goalNode;
    }

//    Methods and variables.
    public Grid(int n){

//        Window setup.
        this.setPreferredSize(gridUISize);
        this.setBackground(Color.BLACK);
        this.setLayout(new GridLayout(maxSize,maxSize));

//        Grid setup.
        nodeGrid = new Node[n][n];
        this.size = n;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){

//                Start state at 0,0.
                if (i == 0 && j == 0)
                {
                    this.nodeGrid[0][0] = new Node(0,0);
                    this.nodeGrid[0][0].setStart(true);
                    startNode = this.nodeGrid[0][0];
                    this.add(nodeGrid[0][0]);
                    nodeGrid[0][0].setDistanceFromStart(0);
                    this.nodeGrid[n - 1][n - 1] = new Node(n - 1 , n - 1);
                    this.nodeGrid[n - 1][n - 1].setGoal(true);
                    goalNode = this.nodeGrid[n - 1][n - 1];
                }
                else if (i < n - 1 || j < n - 1)
                {
                    this.nodeGrid[i][j] = new Node(i,j);
//                    Adds nodes to the UI.
                    this.add(nodeGrid[i][j]);
                }
                else {
                    this.add(nodeGrid[n - 1][n - 1]);
                }
//                Calculates actual cost and heuristic cost.
                Heuristic.calculateHeuristic(this.nodeGrid[i][j], getgoalNode());
                this.nodeGrid[i][j].setTextBox();

//                Add children to the nodes, current node is a parent of the previous but the previous is also a parent of the child.
                if (i > 0)
                {
                    this.nodeGrid[i][j].addChild(this.nodeGrid[i - 1][j]);
                    this.nodeGrid[i - 1][j].addChild(this.nodeGrid[i][j]);
                }

                if (j > 0) {
                    this.nodeGrid[i][j].addChild(this.nodeGrid[i][j - 1]);
                    this.nodeGrid[i][j - 1].addChild(this.nodeGrid[i][j]);
                }
            }
            this.add(nodeGrid[n - 1][n - 1]);
        }
    }

//    Incrementing steps.
    public void incrementStepCounter(){
        stepCount++;
    }

//    Resets step counter.
    public void resetStepCounter() { stepCount = 0; }

//    Returns the steps counted.
    public int getStepCounter(){
        return stepCount;
    }
}
