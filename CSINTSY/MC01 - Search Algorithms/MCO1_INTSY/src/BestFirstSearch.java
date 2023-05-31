import java.util.*;

//    Class for Best First Search.
public class BestFirstSearch {
/*
    Algorithm in Pseudocode.

     function BEST-FIRST-SEARCH(problem, f) returns a solution node or failure
    function BestFirstSearch(problem, f):
     create a new node with the initial state of the problem
    node = Node(problem.getInitialState())
     create a frontier as a priority queue ordered by evaluation function f
    frontier = PriorityQueue<Node>(key=lambda n: n.getEvaluationFunction(f))
             add the initial node to the frontier
            frontier.add(node)
     create a dictionary to store reached nodes and their path costs
    reached = {node.getState(): node.getPathCost()}

     while the frontier is not empty
    while not frontier.isEmpty():
     remove the node with the lowest evaluation function from the frontier
    node = frontier.poll()
             if the node is a goal state, return it
            if problem.isGoalState(node.getState()):
            return node
     expand the node to get its child nodes
        for child in problem.getSuccessors(node.getState()):
     get the child node's state and path cost
    childState, actionCost = child
             calculate the total path cost to the child node
            totalCost = node.getPathCost() + actionCost
     if the child node has not been reached before, or if it has been reached but with a higher path cost
            if childState not in reached or totalCost < reached[childState]:
     create a new child node with the state, parent, action, and path cost
    childNode = Node(childState, node, child[1], totalCost)
     add the child node to the frontier and the reached dictionary
                frontier.add(childNode)
    reached[childState] = totalCost
     if the frontier is empty and no goal state was found, return failure
    return None
*/
//    The main function is called BestFirstSearch and takes a Grid object and an integer f as inputs.
    public static Node BestFirstSearch(Grid problem, int f) throws InterruptedException {
        Node node = problem.getstartNode();
        System.out.println("Initial: " + node.toString());
        PriorityQueue<Node> frontier = new PriorityQueue<>(
                new Comparator<Node>() {
                    public int compare(Node a, Node b)
                    {
                        if (a.getEvaluationFunction(f) >= b.getEvaluationFunction(f))
                            return 1;
                        else if (a.getEvaluationFunction(f) == b.getEvaluationFunction(f))
                            if (a.getHeuristicCost() > b.getHeuristicCost()) return 1;
                            else return -1;
                        else
                            return -1;
                    }
                });
        System.out.println("Initialized: frontier");
        Map<Node, Integer> reached = new HashMap<>();
        System.out.println("Initialized: reached");
        frontier.add(node);
        reached.put(node, node.getEvaluationFunction(f));

//        The while loop that follows executes as long as the frontier is not empty.
        while (!frontier.isEmpty())
        {
            System.out.println("Frontier: ");
            System.out.print(frontier);
            System.out.println();
            System.out.println("Node " + node.toString() + " popped from frontier");
            System.out.println("Parent: " + node.getParent().toString());
            node = frontier.remove();
            node.setinFrontier(false);

            if (node.equals(problem.getgoalNode())) {
                node.setinFrontier(true);
                return node;
            }

//            The code checks if it has already been reached or if its distance from the start node is less than the current distance stored in the reached map.
            for (Node child: node.Expand())
            {
//                Child expanded: step counter + 1.
                problem.incrementStepCounter();
                if (!reached.containsKey(child) ||  child.getDistanceFromStart() < reached.get(child))
                {
//                    Child checked: step counter + 1.
                    problem.incrementStepCounter();
                    reached.put(child, child.getDistanceFromStart());
                    child.setChecked(true);
                    child.setParent(node);
                    Heuristic.calculateActualCost(child, child.parent);
                    child.removeChild(node);
                    System.out.print("Added " + child);
                    System.out.println("Children: " + child.getChildren());

//                    Child checked: step counter + 1.
                    problem.incrementStepCounter();
                    frontier.add(child);
                    child.setinFrontier(true);
                    Thread.sleep(50);
                }
            }
        }
        Node failure = new Node(true);
        System.out.println("Goal state not found, returning failure!");
        return failure;
    }
}
