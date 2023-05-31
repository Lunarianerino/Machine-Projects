import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.EtchedBorder;
import javax.swing.event.ChangeListener;
import javax.swing.text.AbstractDocument;
import javax.swing.text.AttributeSet;
import javax.swing.text.BadLocationException;
import javax.swing.text.DocumentFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

/**
 * MyFarmView class that handles all the GUI methods
 */
public class MyFarmView {
    //List of colors
    static Color grassColor = new Color(103,170,101);
    static Color coinColor = new Color(255,204,51);
    static Color soilColor = new Color(172,114,64);
    static Color uiColor = new Color(255, 210, 132);
    static Color dayTextColor = new Color(222,160,6);

    //Border
    Border uiBorder = BorderFactory.createEtchedBorder(EtchedBorder.LOWERED);

    //Font
    private static Font pixelFont18;//size 18
    static Font pixelFont48;//size 48
    private static Font statusFont;//Emojis

    //objects for game
    private GameManager game;
    private FarmerStats fStats;
    private Coins coins;
    private FarmPlot[][] plots;

    //JFrames
    JFrame myFarmWindow = new JFrame();
    JFrame loseScreen = new JFrame();
    //JPanels
    private JPanel dayPanel = new JPanel();
    private JPanel plotPanel = new JPanel();
    private JPanel toolPanel = new JPanel();
    private JPanel seedPanel = new JPanel();
    private JPanel statusPanel = new JPanel();
    private JPanel coinsLevelPanel = new JPanel();
    private JPanel shopDetailPanel = new JPanel();
    private JPanel sleepPanel = new JPanel();
    private JPanel rankPanel = new JPanel();
    private JPanel rankDetailsPanel = new JPanel();

    //JTextPanes
    private JTextPane dayText = new JTextPane();
    private JTextPane plantStatus = new JTextPane();
    private JTextPane waterStatus = new JTextPane();
    private JTextPane fertilizerStatus = new JTextPane();
    private JTextPane shopText = new JTextPane();
    private JTextPane shopPlantName = new JTextPane();
    private JTextPane shopPlantCost = new JTextPane();
    private JTextPane farmerLevelText = new JTextPane();
    private JTextPane farmerRankText = new JTextPane();
    private JTextPane farmerCoinsText = new JTextPane();
    private JTextPane rankText = new JTextPane();
    private JTextPane rankCoin = new JTextPane();
    private JTextPane rankLevel = new JTextPane();

    private JTextPane updateText = new JTextPane();

    //JButtons
    private JButton sleepButton = new JButton();
    private JButton rankUpButton = new JButton();

    //Arraylist of JButtons for seed area
    private ArrayList<JButton> seedButtons = new ArrayList<>();
    //ArrayList of JButtons for tool area
    private ArrayList<JButton> toolButtons = new ArrayList<>();
    //Tool String List
    String[] tools = {"plow", "water", "fertilizer", "pickaxe", "shovel", "harvest"};

    //Button Dimensions
    private final int buttonWidth = 50;
    private final int buttonHeight = 50;
    //Cursor ID (used for identifying which cursor the mouse is currently on)
    private int cursorId = 0;

    /**
     * MyFarmView constructor method that sets up all the components in the GUI.
     * @param game GameManager instance used for getter methods for attributes such as farmer level and coins
     */
    public MyFarmView(GameManager game){
        this.game = game;

        this.fStats = game.getFarmerStats();
        this.coins = game.getCoins();
        this.plots = game.getPlots();

        //initializes the windows, panels, and buttons
        initializeComponents();

        myFarmWindow.setLocationRelativeTo(null);
        myFarmWindow.setVisible(true);
    }

    //Initialize all components
    private void initializeComponents(){
        //JPanels
        createMainWindow();
        createDayPanel();
        createStatsPanel();
        createPlotPanel();
        createSeedPanel();
        createCoinsLevelPanel();
        createToolPanel();
        createSleepPanel();
        createRankUpPanel();
        createShopDetailPanel();

        //JTextPanes
        addTextPanes();

        //JButtons
        addButtons();

        //initialize cursor to plow cuz msg will just display "0" if cursor is default mouse cursor
        setCursor("plow", 0);
    }


    /**
     * Method that sets the main window's configurations
     */
    private void createMainWindow(){
        myFarmWindow = new JFrame("MyFarm");
        myFarmWindow.setSize(785,700);
        myFarmWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        myFarmWindow.setResizable(false);


        myFarmWindow.getContentPane().setBackground(grassColor);
        myFarmWindow.setLayout(null);
    }

    //JPanels

    private void createDayPanel(){
        setPanelSetting(dayPanel,225,5,200,50, grassColor);
        myFarmWindow.add(dayPanel);
    }

    private void createStatsPanel(){
        statusPanel.setBackground(uiColor);
        statusPanel.setBorder(uiBorder);

        myFarmWindow.add(statusPanel, 0);
    }

    private void createPlotPanel(){
        System.out.println("Plots Initialized");
        setUIPanelSetting(plotPanel,20,140,600,400);
        plotPanel.setBackground(soilColor);
        plotPanel.setLayout(null);

        updateText.setBounds(buttonWidth, 6 * buttonHeight, 400,30);
        updateText.setEditable(false);
        updateText.setBackground(soilColor);
        updateText.setForeground(Color.white);

        updateText.setText("Game Start!");
        plotPanel.add(updateText);

        myFarmWindow.add(plotPanel);
    }

    private void createSeedPanel(){
        System.out.println("Seed Panel Ready");

        setUIPanelSetting(seedPanel,640,15,110,635);
        seedPanel.add(shopText);

        myFarmWindow.add(seedPanel);
    }

    private void createCoinsLevelPanel(){
        System.out.println("Farmer Profile Panel Ready");
        setUIPanelSetting(coinsLevelPanel,20,8,200,110);
        myFarmWindow.add(coinsLevelPanel);
    }

    private void createToolPanel(){
        System.out.println("Tool Bar Ready");
        setUIPanelSetting(toolPanel, 20,570,600,80);

        myFarmWindow.add(toolPanel);
    }


    private void createRankUpPanel(){
        System.out.println("Rank up Button Ready");
        setUIPanelSetting(rankPanel, 520, 15, 80, 40);

        myFarmWindow.add(rankPanel);

        System.out.println("Rank up details Ready");
        rankDetailsPanel.setBackground(uiColor.darker());
        rankDetailsPanel.setBorder(uiBorder);

        myFarmWindow.add(rankDetailsPanel);
    }


    private void createSleepPanel(){
        System.out.println("Sleep Button Ready");
        setUIPanelSetting(sleepPanel, 430, 15, 80, 40);

        myFarmWindow.add(sleepPanel);
    }


    private void createShopDetailPanel(){
        shopDetailPanel.setBackground(uiColor.darker());
        shopDetailPanel.setBorder(uiBorder);

        myFarmWindow.add(shopDetailPanel,0);
    }

    //JPanel utility functions
    private void setUIPanelSetting(JPanel panel, int x, int y, int width, int height){
        setPanelSetting(panel,x,y,width,height, uiColor);
        panel.setBorder(uiBorder);
    }
    private void setPanelSetting(JPanel panel, int x, int y, int width, int height, Color color){
        panel.setBounds(x,y,width,height);
        panel.setBackground(color);
    }

    //JTextPanes
    private void addTextPanes(){
        //dayText for dayPanel
        dayText.setBackground(grassColor);
        dayText.setForeground(dayTextColor.brighter());
        dayText.setFont(pixelFont48);
        dayText.setText("DAY " + game.getDay());
        dayText.setEditable(false);
        dayPanel.add(dayText);

        //plantStatus,waterStatus, and fertilizerStatus for statusPanel
        setStatusFormat(plantStatus);
        setStatusFormat(waterStatus);
        setStatusFormat(fertilizerStatus);

        //shopText for seedPanel
        setUIPanelContents(seedPanel,shopText,"shop");

        //seed details for shopDetailsPanel
        setShopStatusFormat(shopPlantName);
        setShopStatusFormat(shopPlantCost);

        //texts for coinsLevelPanel
        setUIPanelContents(coinsLevelPanel,farmerRankText,""+ fStats.getName());
        setUIPanelContents(coinsLevelPanel,farmerLevelText, "level: " + fStats.getFarmerLevel() + " (" + String.format("%.2f",fStats.getFarmerExp()) + " exp)", coinColor.darker());
        setUIPanelContents(coinsLevelPanel,farmerCoinsText, "coins: " + String.format("%.2f",coins.getAmount()), Color.cyan.darker());

        //texts for rankDetailsPanel
        setRankTextFormat(rankText, ""  + fStats.getName());
        setRankTextFormat(rankLevel, "level: " + fStats.getFarmerLevel() + " (" + String.format("%.2f",fStats.getFarmerExp()) + " exp)");
        setRankTextFormat(rankCoin, "coins: " + String.format("%.2f",coins.getAmount()));


    }

    //utility func for shopPanel elements
    private void setShopStatusFormat(JTextPane textPane){
        textPane.setFont(statusFont);
        textPane.setBackground(uiColor.darker());

        shopDetailPanel.add(textPane);
    }

    //utility func for statusPanel elements
    private void setStatusFormat(JTextPane textPane){
        textPane.setFont(statusFont);
        textPane.setBackground(uiColor);

        statusPanel.add(textPane);
    }

    //utility func for rankup texts
    private void setRankTextFormat(JTextPane textPane, String text){
        textPane.setBackground(uiColor.darker());
        textPane.setFont(statusFont);
        textPane.setText(text);
        textPane.setEditable(false);
        rankDetailsPanel.add(textPane);
    }
    //utility func for adding UI text
    private void setUIPanelContents(JPanel panel,JTextPane textPane, String text){
        textPane.setBackground(uiColor);
        textPane.setForeground(soilColor);
        textPane.setFont(pixelFont18);
        textPane.setText(text);
        textPane.setEditable(false);
        panel.add(textPane);
    }

    private void setUIPanelContents(JPanel panel,JTextPane textPane, String text, Color color){
        textPane.setBackground(uiColor);
        textPane.setForeground(color);
        textPane.setFont(pixelFont18);
        textPane.setText(text);
        textPane.setEditable(false);

        panel.add(textPane, BorderLayout.WEST);
    }

    //JButtons
    private void addButtons(){
        //JButton for sleep
        setButtonSettings(sleepPanel, sleepButton, "sleep");
        //JButton for ranking up
        setButtonSettings(rankPanel, rankUpButton, "rank up");

        //JButtons for seed area/shop
        for(int i = 1; i < GetData.getDataAmount(); i++){
            JButton seedButton = new JButton();

            seedButton.setIcon(new ImageIcon(GetData.getThumbnailPath(i)));
            seedButton.setBounds(0, (i - 1) * buttonHeight, buttonWidth - 20, buttonHeight - 20);
            seedButton.setContentAreaFilled(false);
            seedButton.setBorderPainted(false);


            seedPanel.add(seedButton);
            seedButtons.add(seedButton);
        }

        //JButtons for tools
        for(int i = 0; i < tools.length; i ++){
            JButton toolButton = new JButton();

            String name = tools[i];
            toolButton.setIcon(new ImageIcon("./Tools/" + name + ".png"));
            toolButton.setContentAreaFilled(false);
            toolButton.setBorderPainted(false);
            toolButton.setBounds(0, (i - 1) * buttonHeight, buttonWidth - 20, buttonHeight - 20);

            toolPanel.add(toolButton);
            toolButtons.add(toolButton);
        }

        //JButtons for FarmPlot
        plots = game.getPlots();
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 5; j++) {
                plots[i][j].setBounds((i + 1) * buttonHeight, (j + 1) * buttonWidth, buttonWidth, buttonWidth);
                initPlots(plots[i][j]);
                plotPanel.add(plots[i][j]);
            }
        }

    }

    private void initPlots(FarmPlot p){
        switch(p.getState()) {
            case -1 -> {
                p.setIcon(p.getRocky());
                getStatusPanel().setVisible(false);
            }
            case 0 -> {
                p.setIcon(p.getUntilled());
                getStatusPanel().setVisible(false);
            }
        }

    }

    /**
     * Method that sets the button listener for the JButton sent as a parameter
     * @param button JButton to override
     * @param actionListener overrides the default behavior of the JButton actionListener
     */
    public void setBtnListener(JButton button, ActionListener actionListener){
        button.addActionListener(actionListener);
    }


    /**
     * Method that adds a ChangeListener for the JButton sent as a parameter
     * @param button JButton to add a ChangeListener to
     * @param changeListener adds a changeListener to the JButton
     */
    public void addBtnChangeListener(JButton button, ChangeListener changeListener){
        button.getModel().addChangeListener(changeListener);
    }


    /**
     * Getter method that returns the array of tools
     * @return String array of tools
     */
    public String[] getTools() {
        return tools;
    }

    /**
     * Getter method for the list of seed buttons
     * @return ArrayList of JButtons that stores the instantiated JButtons for the seeds
     */
    public ArrayList<JButton> getSeedButtons() {
        return seedButtons;
    }

    /**
     * Getter method for the list of tool buttons
     * @return ArrayList of JButtons that stores the instantiated JButtons for the tools
     */
    public ArrayList<JButton> getToolButtons() {
        return toolButtons;
    }

    /**
     * Getter method that returns the current cursor's ID
     * @return current cursor's ID
     */
    public int getCursorId(){
        return cursorId;
    }

    /**
     * Getter method that returns statusPanel
     * @return statusPanel JPanel
     */
    public JPanel getStatusPanel() {
        return statusPanel;
    }

    /**
     * Getter method that returns rankDetailsPanel
     * @return rankDetailsPanel JPanel
     */
    public JPanel getRankDetailsPanel() {
        return rankDetailsPanel;
    }

    /**
     * Getter method that returns getDayText
     * @return dayText JTextPane
     */
    public JTextPane getDayText() {
        return dayText;
    }

    /**
     * Getter method that returns plantStatus
     * @return plantStatus JTextPane
     */
    public JTextPane getPlantStatus() {
        return plantStatus;
    }

    /**
     * Getter method that returns waterStatus
     * @return waterStatus JTextPane
     */
    public JTextPane getWaterStatus() {
        return waterStatus;
    }

    /**
     * Getter method that returns fertilizerStatus
     * @return fertilizerStatus JTextPane
     */
    public JTextPane getFertilizerStatus() {
        return fertilizerStatus;
    }

    /**
     * Getter method that returns shopPlantName
     * @return shopPlantName JTextPane
     */
    public JTextPane getShopPlantName() {
        return shopPlantName;
    }

    /**
     * Getter method that returns shopPlantCost
     * @return shopPlantCost JTextPane
     */
    public JTextPane getShopPlantCost() {
        return shopPlantCost;
    }

    /**
     * Getter method that returns farmerLevelText
     * @return farmerLevelText JTextPane
     */
    public JTextPane getFarmerLevelText() {
        return farmerLevelText;
    }

    /**
     * Getter method that returns farmerRankText
     * @return farmerRankText JTextPane
     */
    public JTextPane getFarmerRankText() {
        return farmerRankText;
    }

    /**
     * Getter method that returns farmerCoinsText
     * @return farmerCoinsText JTextPane
     */
    public JTextPane getFarmerCoinsText() {
        return farmerCoinsText;
    }

    /**
     * Getter method that returns rankText
     * @return rankText JTextPane
     */
    public JTextPane getRankText() {
        return rankText;
    }

    /**
     * Getter method that returns rankCoin
     * @return rankCoin JTextPane
     */
    public JTextPane getRankCoin() {
        return rankCoin;
    }

    /**
     * Getter method that returns rankLevel
     * @return rankLevel JTextPane
     */
    public JTextPane getRankLevel() {
        return rankLevel;
    }

    /**
     * Getter method that returns updateText
     * @return updateText JTextPane
     */
    public JTextPane getUpdateText() {
        return updateText;
    }

    /**
     * Getter method that returns sleepButton
     * @return sleepButton JButton
     */
    public JButton getSleepButton() {
        return sleepButton;
    }

    /**
     * Getter method that returns shopDetailPanel
     * @return shopDetailPanel JPanel
     */
    public JPanel getShopDetailPanel() {
        return shopDetailPanel;
    }

    /**
     * Getter method that returns rankUpButton
     * @return rankUpButton JButton
     */
    public JButton getRankUpButton() {
        return rankUpButton;
    }

    //Utility method for changing the mouse cursor's image

    /**
     * Method that sets the cursor to the specified name and cursorID. Changes the
     * cursor image to the ImageIcon based on the name passed as a parameter
     * @param name name of the cursor
     * @param cursorId id of the cursor.
     */
    public void setCursor(String name, int cursorId) //name
    {
        this.cursorId = cursorId;
        Image cursor = new ImageIcon("./Cursor/" + name + ".png").getImage();

        //we rely on the name parameter for the actions since Cursor.getName exists
        Cursor customCursor = Toolkit.getDefaultToolkit().createCustomCursor(cursor, new Point(0, 0), name);
        myFarmWindow.setCursor(customCursor);
    }

    /**
     * Method that sets the configurations of a JButton
     * @param panel JPanel to add the button to
     * @param button JButton to configure
     * @param text text displayed on the JButton
     */
    private void setButtonSettings(JPanel panel, JButton button, String text){
        button.setFont(pixelFont18);
        button.setText(text);
        button.setBackground(uiColor);
        button.setContentAreaFilled(false);
        button.setOpaque(false);
        button.setBorderPainted(false);

        panel.add(button);
    }

    //Sets up fonts

    /**
     * Method to add the fonts used in MyFarmView.
     */
    public static void addFont()
    {
        try {
            pixelFont18 = Font.createFont(Font.TRUETYPE_FONT, new File("font\\PixelGameFont.ttf")).deriveFont(18f);
            GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
            ge.registerFont(pixelFont18);
        } catch (IOException | FontFormatException e) {
            e.printStackTrace();
        }
        try {
            pixelFont48 = Font.createFont(Font.TRUETYPE_FONT, new File("font\\PixelGameFont.ttf")).deriveFont(48f);
            GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
            ge.registerFont(pixelFont48);
        } catch (IOException | FontFormatException e) {
            e.printStackTrace();
        }
        statusFont = new Font("Segoe UI Emoji", Font.PLAIN, 10);
    }

    /**
     * Method that handles all the exceptions from GameManager. Sets the message that will be displayed through
     * updateText.
     * @param e Exception thrown
     */
    public void exceptionHandler (Exception e)
    {
        String msg = "0";
        if (e instanceof ExceptionHandling.InsufficientCoinsException)
        {
            System.out.println("EXCEPTION: NOT ENOUGH COINS TO PERFORM ACTION");
            msg = "Insufficient Coins!";
            blinkText(farmerCoinsText, Color.cyan.darker());
        }
        if (e instanceof ExceptionHandling.PlowException)
        {
            System.out.println("EXCEPTION: CANT PLOW OCCUPIED SPACES");
            msg = "Cannot plow occupied spaces!";
        }
        if (e instanceof ExceptionHandling.WaterException)
        {
            System.out.println("EXCEPTION: CANT WATER");
            msg = "Cannot water plot since it does not have growing plants!";
        }
        if (e instanceof ExceptionHandling.WaterWitheredException){
            System.out.println("EXCEPTION: CANT WATER WITHERED PLANT");
            msg = "Cannot water a withered plant!";
        }
        if (e instanceof ExceptionHandling.FertilizeException)
        {
            System.out.println("EXCEPTION: CANT FERTILIZE");
            msg = "Cannot fertilize plot since it does not have growing plants!";
        }
        if (e instanceof ExceptionHandling.FertilizeWitheredException){
            System.out.println("EXCEPTION: CANNOT FERTILIZE WITHERED PLANT");
            msg = "Cannot fertilize a withered plant!";
        }
        if (e instanceof ExceptionHandling.PickaxeException)
        {
            System.out.println("EXCEPTION: THERES NOTHING TO PICK");
            msg = "Cannot use pickaxe on a plot that is not rocky!";
        }
        if (e instanceof ExceptionHandling.SideException)
        {
            System.out.println("EXCEPTION: CANNOT PLANT ON THE SIDES");
            msg = "Cannot plant a tree on the sides of the plot area!";
        }
        if (e instanceof ExceptionHandling.OccupiedException)
        {
            System.out.println("EXCEPTION: CANNOT PLANT ON OCCUPIED TILES");
            msg = "Cannot plant anything on occupied tiles!";
        }
        if (e instanceof ExceptionHandling.TreeConditionException)
        {
            System.out.println("EXCEPTION: CANNOT PLANT TREE NEXT TO OCCUPIED TILES");
            msg = "Cannot plant a tree next to an occupied plot!";
        }
        if (e instanceof ExceptionHandling.UnplowedException)
        {
            System.out.println("EXCEPTION: CAN ONLY PLANT ON PLOWED TILES");
            msg = "Cannot plant here!";
        }
        if (e instanceof ExceptionHandling.WitheredException)
        {
            System.out.println("EXCEPTION: CANNOT HARVEST A WITHERED PLANT");
            msg = "Cannot harvest a withered plant!";
        }
        if (e instanceof ExceptionHandling.GrowingException)
        {
            System.out.println("EXCEPTION: PLANT NOT READY TO HARVEST");
            msg = "Cannot harvest a plant that is not ready to harvest!";
        }
        if (e instanceof ExceptionHandling.HarvestNothingException)
        {
            System.out.println("EXCEPTION: THERE IS NOTHING TO HARVEST");
            msg = "Cannot harvest anything without a plant!";
        }
        if (e instanceof ExceptionHandling.InsufficientLevelException)
        {
            System.out.println("EXCEPTION: INSUFFICIENT LEVELS TO RANK UP");
            msg = "Cannot rank up, required level: " + fStats.getNextLevelReq() + ", current level: " + fStats.getFarmerLevel();
            blinkText(farmerLevelText, coinColor.darker());
        }
        if (e instanceof ExceptionHandling.GameLostException)
        {
            showLoseScreen();
            msg = "Game Over!";
        }

        if (!msg.equals("0"))
            setUpdateText(msg, true);
    }

    /**
     * Setter function for updateText
     * @param msg The error message to be displayed to the GUI
     * @param isError boolean value that indicates if the message is an error to trigger blinkText
     */
    private void setUpdateText (String msg, boolean isError)
    {
        if (isError)
            blinkText(updateText, Color.white);
        updateText.setText(msg);
    }

    /**
     * Utility function to make the given JTextPane blink a few times indicating the user
     * that an exception is being caused by the current action that is being attempted to act.
     * @param text JTextPane to set the blinking action on
     * @param original Original Color object of the JTextPane
     */
    private void blinkText (JTextPane text, Color original)
    {
        ActionListener blinker = new ActionListener() {
            boolean isRed = true;
            int counter = 0;
            public void actionPerformed(ActionEvent ae) {
                if (isRed) {
                    text.setForeground(original);
                    if (counter >= 5)
                    {
                        Timer timer = (Timer)ae.getSource();
                        timer.stop();
                    }
                } else {
                    text.setForeground(Color.red.darker());
                }
                counter ++;
                isRed = !isRed;
            }
        };
        Timer timer = new Timer(100, blinker);
        timer.start();
    }

    /**
     * Method that shows the lose screen window once all lose conditions are met.
     * Disables interaction with myFarmWindow so the user can only choose to exit or restart the game.
     */
    private void showLoseScreen ()
    {
        myFarmWindow.setEnabled(false);
        loseScreen = new JFrame("You Lose!");
        loseScreen.setSize(400,200);
        loseScreen.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        loseScreen.setResizable(false);
        loseScreen.setLocationRelativeTo(myFarmWindow);

        loseScreen.getContentPane().setBackground(grassColor);
        loseScreen.setLayout(null);
        loseScreen.setVisible(true);


        JPanel lsPanel = new JPanel();

        lsPanel.setBounds(loseScreen.getBounds().width / 4,
                loseScreen.getBounds().height / 4,
                loseScreen.getBounds().width / 2,
                loseScreen.getBounds().height / 2);

        JButton playAgain = new JButton();
        playAgain.setText("PLAY AGAIN");
        playAgain.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                myFarmWindow.dispose();
                loseScreen.dispose();

                main.reset();
                System.out.println("RESTART GAME");
            }
        });

        JButton exit = new JButton();
        exit.setText("EXIT");
        exit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });

        lsPanel.add (playAgain);
        lsPanel.add(exit);
        loseScreen.add (lsPanel);
    }

    /**
     * Method that shows the start screen that allows the players to start the game or go to a new window where they can change some settings
     * Window gets disposed when user enters a new game or sets its visibility to false if user enters the settings screen
     */
    public static void start()
    {
        JFrame startScreen = new JFrame("MyFarm");
        JPanel menuContainer = new JPanel();

        JPanel startContainer = new JPanel();
        JPanel rockContainer = new JPanel();
        JPanel titleContainer = new JPanel();
        JButton startButton = new JButton();
        JButton rockSettings = new JButton();
        JTextPane gameTitle = new JTextPane();

        startScreen.setLayout(new FlowLayout(FlowLayout.CENTER));
        startScreen.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        startScreen.getContentPane().setBackground(grassColor);
        startScreen.setSize(300,200);
        startScreen.setResizable(false);
        startScreen.setLocationRelativeTo(null);

        titleContainer.setBackground(grassColor);
        //titleContainer.setLayout(new BoxLayout(menuContainer, BoxLayout.Y_AXIS));

        //game title
        gameTitle.setText("MYFARM");
        gameTitle.setEditable(false);
        gameTitle.setForeground(uiColor);
        gameTitle.setBackground(grassColor);
        gameTitle.setFont(pixelFont48);

        titleContainer.add(gameTitle);

        //menuContainer.setLayout(null);
        menuContainer.setBackground(grassColor);
        menuContainer.setLayout(new BoxLayout(menuContainer, BoxLayout.Y_AXIS));

        startContainer.setSize(menuContainer.getWidth(), 50);
        startContainer.setBackground(grassColor);
        startButton.setText("START GAME");
        startButton.setSize(100, 50);
        startButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                main.start();
                startScreen.dispose();
            }
        });

        rockContainer.setSize(menuContainer.getWidth(), 50);
        rockContainer.setBackground(grassColor);
        rockSettings.setText("ROCK SETTINGS");
        rockSettings.setSize(100, 50);
        rockSettings.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                startScreen.setVisible(false);
                MyFarmView.settingsScreen(startScreen);
            }
        });

        startScreen.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.out.println("Window closed!");
                System.exit(0);
            }
        });

        startContainer.add(startButton);
        rockContainer.add(rockSettings);
        menuContainer.add(startContainer);
        menuContainer.add(rockContainer);
        startScreen.add(titleContainer);
        startScreen.add(menuContainer);
        startScreen.setVisible(true);
    }

    /**
     * Method that shows a window where the user can change the rock settings through user input or generating a new random binary setting for the rocks
     * When player presses the back button, this window gets disposed and the source screen is set to visible again
     * @param startScreen - the source screen
     */
    public static void settingsScreen(JFrame startScreen)
    {
        JFrame settingsScreen = new JFrame("ROCK SETTINGS");
        JPanel settingsPane = new JPanel();
        JButton randomButton = new JButton();
        JButton backButton = new JButton();
        JTextArea rockBinary = new JTextArea(RockData.getRockSequenceString(),1, 1);

        settingsScreen.setSize(300,270);
        settingsScreen.setLayout(null);
        settingsScreen.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        settingsScreen.setResizable(false);

        settingsScreen.getContentPane().setBackground(grassColor);
        settingsScreen.setVisible(true);

        settingsScreen.setLocationRelativeTo(null);

        settingsPane.setBounds(
                (settingsScreen.getBounds().width / 4) -20,
                (settingsScreen.getBounds().height / 4) -20,
                (settingsScreen.getBounds().width / 2) + 20,
                (settingsScreen.getBounds().height / 2) + 20
        );
        settingsPane.setForeground(Color.green.brighter());

        rockBinary.setLayout(null);
        rockBinary.setLineWrap(true);
        rockBinary.setWrapStyleWord(true);
        rockBinary.setBounds(0,0, 75, 50);
        ((AbstractDocument)rockBinary.getDocument()).setDocumentFilter(new DocumentFilter(){
            @Override
            public void insertString(FilterBypass fb, int offset, String string, AttributeSet attr) throws BadLocationException {
                StringBuilder buffer = new StringBuilder(string.length());
                for (int i = string.length() - 1; i >= 0; i--) {
                    char c = string.charAt(i);
                    //limits the player to only 1 and 0 inputs as well as making sure the limit stays at 50 characters
                    if ((c == '0' || c == '1') && rockBinary.getDocument().getLength() < 50)
                    {
                        buffer.append(c);
                        System.out.println("Count: " + rockBinary.getDocument().getLength());
                    }
                }
                super.insertString(fb, offset, buffer.toString(), attr);
                RockData.updateData(rockBinary.getText());
            }

            @Override
            public void replace(DocumentFilter.FilterBypass fb, int offset, int length, String text, AttributeSet attrs) throws BadLocationException {
                if (length > 0)
                    fb.remove(offset, length);
                insertString(fb, offset, text, attrs);
            }
        });


        randomButton.setText("RANDOMIZE");
        randomButton.setSize(100, 50);
        randomButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                RockData.generateRockFile();
                rockBinary.setText(RockData.getRockSequenceString());
            }
        });

        backButton.setText("BACK");
        backButton.setSize(100, 50);
        backButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                startScreen.setVisible(true);
                settingsScreen.dispose();
            }
        });

        settingsScreen.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.out.println("Window closed!");
                System.exit(0);
            }
        });

        settingsPane.add(rockBinary);
        settingsPane.add(randomButton);
        settingsPane.add(backButton);
        settingsScreen.add(settingsPane);

    }
}
