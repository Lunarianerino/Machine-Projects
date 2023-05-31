import javax.swing.*;
import java.util.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Color;
import java.util.ArrayList;
public class Node extends JButton implements ActionListener {

//    Contains the parent of the current node.
    Node parent = null;

//    Contains the children of the current node.
    private List<Node> children = new ArrayList<>();

//    X and Y coordinates of the node.
    private final int xCoordinate;
    private final int yCoordinate;

//    Attributes for f(n) = g(n) + h(n).
    private int heuristicCost; // h(n)
    private int distanceFromStart; // g(n)
    private int evaluationCost; // f(n)

//    Are boolean attributes that set whether the node is the start or end node.
    private boolean isStart = false;
    private boolean isGoal = false;

//    Are node states of walls to determine if walkable or not.
    private boolean wall = false;
    private boolean walkable = true;

//    To determine if Expanded or Checked.
    private boolean inFrontier = false;
    private boolean checked =false;

//    This is a boolean used by the BFS algorithm.
    private final boolean failure;

//    Constructor for Node object that initializes parent, null, x, and y.
    Node(int x, int y){
        parent = new Node();
        this.xCoordinate = x;
        this.yCoordinate = y;
        failure = false;

        setBackground(Color.WHITE);
        setForeground(Color.BLACK);
        addActionListener(this);
    }

//    This is a constructor for node with parameter and boolean only initialized during failure.
    Node(boolean failure)
    {
        this.failure = failure;
        this.xCoordinate = -1;
        this.yCoordinate = -1;
    }

//    Constructor for Node that sets values to -1 and false.
    Node()
    {
        this.xCoordinate = -1;
        this.yCoordinate = -1;
        this.failure = false;
    }

//    Is a method to add child Node object to current nodes children list, if object is not null.
    public void addChild(Node node)
    {
        if (node != null) {
            this.children.add(node);
        }
    }

//    Method to set a parent node of the current node object to the given node object.
    public void setParent(Node node)
    {
        this.parent = null;
        this.parent = node;
    }

//    Override is for interface that listens for button press on the Node.
    @Override

//    If Node is either start or goal it returns, if it is a wall we can setWall state with true or false.
    public void actionPerformed(ActionEvent e) {

//        Ignore if start or goal state.
        if(this.isStart || this.isGoal)
            return;
//        Change to wall state.
        if (!this.wall)
            setWall(true);
        else
            setWall(false);
    }

//    Method that sets the start node to color blue.
    public void setStart(boolean start) {
        setBackground(Color.BLUE);
        setForeground(Color.WHITE);
        setText("Start");
        this.isStart = start;
    }

//    Method that sets the goal node to color green.
    public void setGoal(boolean goal) {
        setBackground(Color.GREEN);
        setForeground(Color.WHITE);
        setText("Goal");
        this.isGoal = goal;
    }

//    Method that sets wall and calls function setWalkable.
    public void setWall(boolean wall){
        this.wall = wall;
        setWalkable(!wall);
    }

//    Method that sets walkable tiles to white, and walls to orange.
    public void setWalkable(boolean walkable) {
        this.walkable = walkable;
        if (!walkable)
            setBackground(Color.ORANGE);
        else
            setBackground(Color.WHITE);
    }

//    Sets the color of the node to dark gray if its in the frontier, otherwise it turns to gray once its checked.
    public void setinFrontier(boolean inFrontier) {

//        Will not change the color of start and goal node.
        if(isStart || isGoal)
            return;
        this.inFrontier = inFrontier;
        if (inFrontier) {
            setBackground(Color.DARK_GRAY);
        } else
        {
            setBackground(Color.GRAY);
        }
    }

//    Responsible for setting checked tiles to a color.
    public void setChecked(boolean checked) {

//        Will not change the color of start and goal node.
        if(isStart || isGoal)
            return;
        this.checked = checked;
        if (checked) {
            this.setBackground(Color.PINK.brighter());
        }
    }

//    Method to remove a child node from the list of children of the current node.
    public void removeChild(Node parent)
    {
        children.remove(parent);
    }

//    Sets heuristic cost and updates evaluation cost accordingly.
    public void setHeuristicCost(int heuristicCost) {
        this.heuristicCost = heuristicCost;
        updateHeuristicEvaluation();
    }

//    Method returns heurstic cost of current node.
    public int getHeuristicCost() {
        return heuristicCost;
    }

//    Method returns if node is the goal state
    public boolean getGoal() { return isGoal; }

//    Methods sets distance from start to current.
    public void setDistanceFromStart(int distanceFromStart) {
        this.distanceFromStart = distanceFromStart;
    }

//    Gets distance from start to current.
    public int getDistanceFromStart() {
        return distanceFromStart;
    }

//    Sets color.
    public void setNodeColor(Color color){
        this.setBackground(color);
    }

//    Returns eval cost.
    public int getEvaluation() {
        return evaluationCost;
    }

//    Updates heuristic evaluation.
    public void updateHeuristicEvaluation() {
        evaluationCost = distanceFromStart + heuristicCost;
    }

//    Gets X coordinate.
    public int getXCoordinate() {
        if (parent != null)
            return xCoordinate;
        else return -1;
    }

//    Gets Y coordinate.
    public int getYCoordinate() {
        if (parent != null)
            return yCoordinate;
        else return -1;
    }

    public List<Node> getChildren()
    {
        return this.children;
    }

//    Returns list of child nodes that do not have the wall flag set to true.
    public List<Node> Expand()
    {
/*
  function EXPAND(problem, node) yields nodes
        s←node.STATE
        for each action in problem.ACTIONS(s) do
        s
        0←problem.RESULT(s, action)
        cost←node.PATH-COST + problem.ACTION-COST(s, action,s
            0
    )
        yield NODE(STATE=s
                0
                , PARENT=node, ACTION=action, PATH-COST=cost)
*/
        List<Node> result = new ArrayList<>();

        for (Node n: children)
        {
            //condition will not add nodes that have wall set to true in in the children.
            if (!n.wall)
            {

                result.add(n);
            }
        }

        return result;
    }

//    Path is set to green.
    public void getPath()
    {
        setBackground(Color.GREEN);
    }

//    Sets background color of current node to green.
    @Override
    public String toString(){
        return "{[" + xCoordinate+","+yCoordinate + "]" + " (Evaluation Function: " + getEvaluation() + " = " + getDistanceFromStart() + " + " + getHeuristicCost() + ")}";
    }

//    String representation of current node and its coordinates with eval functions.
    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Node)) {
            return false;
        }

        Node comp = (Node) obj;
        if (this.xCoordinate == comp.xCoordinate && this.yCoordinate == comp.yCoordinate)
            return true;
        return false;
    }

//    1 = h() + g(); 2 = g(); 3 = h()
    public int getEvaluationFunction(int need)
    {
        switch (need)
        {
            case 1:
                return this.getEvaluation(); //A* Search
            case 2:
                return this.getDistanceFromStart(); //Uniform-Cost Search
            case 3:
                return this.getHeuristicCost(); //Greedy Best First Search
        }

        return -1;
    }

    public boolean failed(){return failure;}

    public void setTextBox()
    {
        setText( "" + getHeuristicCost() );
    }
}
