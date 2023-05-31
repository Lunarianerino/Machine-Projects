import javax.swing.*;
import java.awt.*;
public class GamebotWindow extends JFrame {
    private int nodeSize = 15;
    Grid mazeGrid;
    Dimension windowSize = new Dimension(nodeSize*64,nodeSize*64);

//    Layout and format for GamebotWindow within size of n.
    public GamebotWindow(int n){
        setTitle("Gamebot");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(true);
        setSize(windowSize);
        mazeGrid = new Grid(n);
        mazeGrid.getstartNode();
        mazeGrid.getgoalNode();
        mazeGrid.setLayout(new GridLayout(n,n));
        add(mazeGrid);
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

//    Getter for Grid.
    public Grid getGrid()
    {
        return mazeGrid;
    }
}
