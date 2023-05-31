import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Collections;
import java.awt.Color;

public class GamebotControl implements ActionListener {

    //    Instance variables,flags, buttons, and labels.
    private JFrame frame;
    boolean isStart = false;
    boolean isSwitched = false;
    boolean isFinished = false;
    private JButton Start = new JButton();
    private JButton Switch = new JButton();
    private JButton Confirm = new JButton();
    private JButton Reset = new JButton();
    public JLabel statusMessage;
    public JLabel stepCounter;
    public JLabel currentHeuristic = new JLabel();
    private JTextField userInput = new JTextField(15);
    private int inputToInt;
    private int fValue = 3;
    private GamebotWindow window = null;
    private Node result;
    public ArrayList<Node> path = new ArrayList<>();

    //    Class for the GamebotControls.
    public GamebotControl() {

//        Main Frame.
        frame = new JFrame("Controls");
        frame.setSize(400, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new BorderLayout());

//        Status Message.
        statusMessage = new JLabel();
        statusMessage.setText(" ");
        stepCounter = new JLabel();
        if (window == null)
            stepCounter.setText("Steps: 0");
        else
            stepCounter.setText("Steps: " + window.getGrid().getStepCounter()); //Grid.getStepCount

//        Button names.
        Confirm.setText("Confirm");
        Start.setText("Start");
        Switch.setText("Switch");
        Reset.setText("Reset");

//        Heuristic current label.
        currentHeuristic.setText(" Heuristic Selected: " + fValuetoString());

//        Tooltips for buttons.
        userInput.setToolTipText("Enter size of maze (8-64).");
        Confirm.setToolTipText("This is used to confirm/change the size.");
        Start.setToolTipText("This is used to start the search.");
        Reset.setToolTipText("This is used to reset the grid in the same size.");
        Switch.setToolTipText("This is used to switch the heuristic used.");

//        Top panel.
        JPanel topPanel = new JPanel();
        topPanel.setLayout(new GridLayout(3, 1, 10, 0));
        topPanel.add(statusMessage);
        topPanel.add(stepCounter);
        topPanel.add(currentHeuristic);
        frame.add(topPanel, BorderLayout.NORTH);

//        Center panel.
        JPanel centerPanel = new JPanel();
        centerPanel.setLayout(new FlowLayout());
        centerPanel.add(userInput);
        centerPanel.add(Confirm);
        frame.add(centerPanel, BorderLayout.CENTER);

//        Bottom panel.
        JPanel bottomPanel = new JPanel();
        setActionListener(this);
        bottomPanel.add(Start);
        bottomPanel.add(Switch);
        bottomPanel.add(Reset);
        frame.add(bottomPanel, BorderLayout.SOUTH);
        frame.setVisible(true);
    }

    //    Actions performed based on buttons pressed, with validity checking.
    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == getStart()) {
            Confirm.setEnabled(true);
            if (window == null) {
                setStatusMessage(" Please press CONFIRM to set up maze.");
            } else if (!isFinished || this.result != null) {
                runMaze();
            }
            Switch.setEnabled(false);
        } else if (e.getSource() == getSwitch()) {
            isSwitched = true;
            fValue++;
            if (fValue > 3)
                fValue = 1;
            setStatusMessage("Changed Search.");
            currentHeuristic.setText("Current Heuristic: " + fValuetoString());
        } else if (e.getSource() == getConfirm()) {
            if (!userInput.getText().isEmpty()) {
                inputToInt = Integer.parseInt(userInput.getText());
            } else {
                JOptionPane.showMessageDialog(frame, "Please enter a valid number.");
            }
            if (verify()) {
                if (window != null) {
                    window.dispose();
                }
                setStatusMessage(" The entered value is: " + inputToInt); //maze size
                window = new GamebotWindow(inputToInt);
            }
            Confirm.setEnabled(false);
            Switch.setEnabled(false);
        } else if (e.getSource() == getReset()) {
            window.dispose();
            window = new GamebotWindow(inputToInt);
            Confirm.setEnabled(true);
            Start.setEnabled(true);
            Reset.setEnabled(false);
            Switch.setEnabled(true);
            if (window != null) {
                window.getGrid().resetStepCounter();
                stepCounter.setText("Steps: " + window.getGrid().getStepCounter());
            }
        }
    }

    //    Boolean condition to verify if entry is within bounds.
    private boolean verify() {
        try {
            if (!userInput.getText().isEmpty() && inputToInt < 8 || inputToInt > 64) {
                JOptionPane.showMessageDialog(frame, "Please enter a number between 8-64.");
                return false;
            }
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(frame, "Please enter a valid number.");
            return false;
        }
        return true;
    }

    //    Method to run maze.
    public void runMaze() {
        isStart = true;
        if (result == null) {
            result = new Node(0, 0);
        }
        setStatusMessage(" Maze Start.");

//        Disables user interaction when button is pressed.
        window.setEnabled(false);

//        Starts the A* algorithm.
        new Thread(new StartAStar()).start();
        Start.setEnabled(false);
        Reset.setEnabled(true);
    }

    //    Setting action listeners.
    public void setActionListener(ActionListener listener) {
        Start.addActionListener(listener);
        Switch.addActionListener(listener);
        Confirm.addActionListener(listener);
        Reset.addActionListener(listener);
    }

    //    Setting text.
    public void setStatusMessage(String status) {
        statusMessage.setText(status);
    }

    //    Getters.
    public JButton getConfirm() {
        return Confirm;
    }

    public JButton getStart() {
        return Start;
    }

    public JButton getSwitch() {
        return Switch;
    }

    public JButton getReset() {
        return Reset;
    }

    //    Uses value of fValue to determine switch case and returned heuristic.
    public String fValuetoString() {
        switch (this.fValue) {
            case 1:
                return "A* Search";
            case 2:
                return "Uniform-Cost Search";
            case 3:
                return "Greedy Search";
        }
        return "?";
    }

    //    Implements runnable interface to allow run method in a seperate thread, calls bfs with windowgetgrid and fvalue.
    class StartAStar implements Runnable {
        public void run() {
            try {
                path.clear(); //clears the path arraylist whenever the program is restarted
                result = BestFirstSearch.BestFirstSearch(window.getGrid(), fValue);
                if (!result.failed()) {
                    setStatusMessage("Goal Found in: " + result.toString());
                    while (result.parent != null) {
                        result.getPath();
                        path.add(result);
                        result = result.parent;

                    }
                    if (window != null) {
                        stepCounter.setText("Steps: " + window.getGrid().getStepCounter());

                        Collections.reverse(path);

                        //changes each tile starting from the start node to blink blue until it reaches the goal node
                        setStatusMessage(" Pathing to goal.");
                        try {
                            for (Node n : path) {
                                if (n.getGoal() == false) {
                                    Thread.sleep(100);
                                    n.setNodeColor(Color.BLUE);
                                    Thread.sleep(250);
                                    n.setNodeColor(Color.GREEN);
                                }
                                else{
                                    n.setNodeColor(Color.BLUE);
                                }
                            }
                            setStatusMessage(" The Goal was reached in " + path.size() + " moves.");
                        } catch (Exception e) {
                            System.out.println(e);
                        }
                    }
                }else{
                    setStatusMessage("Goal state is unreachable.");
                }
            } catch (Exception e) {
                System.out.println("Exception is caught");
            }
        }
    }
}
