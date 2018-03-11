/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hw08;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;
import javax.swing.border.LineBorder;

/**
 *
 * @author burak demir
 */
public class ConnectFourGui implements ActionListener{
    
    private JFrame frame;
    private JPanel topPanel;
    private JPanel midPanel;
    private JButton[] buttons;
    private JLabel[][] gameCells;
    private JTextField infoMessage;
    private int size = 10;
    private final Color p1 = Color.red;
    private final Color p2 = Color.black;
    private int turn=1;
    private JLabel lastMove;
    private final int MAX_SIZE = 25;
    private final int MIN_SIZE = 4;
    private int gamemode;
    private int chain;

    /**
     * @param args the command line arguments.
     */
    public static void main(String[] args) {
        ConnectFourGui cfGui = new ConnectFourGui();
        cfGui.launch();
    }
    
    /**
     * Launch the Application.
     */
    public void launch() {
        newGame();

    }
    /**
     * Starts a new game.
     */
    private void newGame(){

        try {
            getGameMode();
            getGameSize();
        } catch (Exception e) {
            System.err.println("Game is closed");
            return;
        }
        initiateComponents();
    
    }
    /**
     * Plays computer's move
     */
    private void play() {

        char target = 'A';
        while(!isMoveLegal(String.valueOf(target))){
            target++;
        }

        int col = target-'A';
        int row = makeMove(p2, col, size);
        gameCells[row][col].setBackground(p2);
        infoMessage.setText(infoMessage(String.valueOf(target)));
        lastMove = gameCells[row][col];
        if(checkRow(row, col) > 0 || turn >= size*size) {
            showWinnerAndExit();
            newGame();
        }
        else
            turn++;
    }
    
   
    /**
     * Plays player move.
     * @param command target column that player want
     */
    private void play(String command) {

        int col = command.charAt(0) - 'A';
        int row = makeMove(turn % 2 == 1 ? p1 : p2, col, size);
        gameCells[row][col].setBackground(turn %2 == 1?p1:p2);
        infoMessage.setText(infoMessage(command));
        lastMove = gameCells[row][col];
        if(checkRow(row, col) > 0 || turn >= size*size) {
            showWinnerAndExit();
            newGame();
        }
        else
            turn++;

    }
    /**
     * Shows winner and delete all components.
     */
    private void showWinnerAndExit(){
        if(turn < size * size){
        String winner = turn%2 == 1 ? "PLAYER 1":gamemode==1?"PLAYER 2" : "COMPUTER";
        JOptionPane.showMessageDialog(null,  winner + " WON");
        }
        else
            JOptionPane.showMessageDialog(null, "TIE");
        frame.dispose();
    }
    /**
     * 
     * @param col target col
     * @return Info message
     */
    private String infoMessage(String col) {

        String player = turn%2 == 1 ? "PLAYER 1":gamemode==1?"PLAYER 2" : "COMPUTER";
        String str = "Turn: " + turn + " --> " + player + " played to " + col + "\n";
        return str;

    }
    /**
     * 
     * @param player which player's move
     * @param col which target to move
     * @param size Board size
     * @return return row
     */
    private int makeMove(Color player, final int col, int size){


        if(gameCells[size-1][col].getBackground() != Color.WHITE)
            return makeMove(player, col, size-1);
        else
            gameCells[size-1][col].setBackground(player);

        return size - 1;
    }
    /**
     * 
     * @param actionEvent click
     */
    @Override
    public void actionPerformed(ActionEvent actionEvent) {

        if (isMoveLegal(actionEvent.getActionCommand())) {
            play(actionEvent.getActionCommand());
            if (gamemode == 2 && turn != 1)
                play();

        }
    }
    /**
     * gets game mode
     * @throws Exception if string is null
     */
    private void getGameMode() throws Exception {

        do {

            String gameMode = JOptionPane.showInputDialog("Select the GameMode\n"+
                        "1 - Versus Player\n2 - Versus Computer");
            if (gameMode == null)
                throw new Exception();

            gamemode = Integer.parseInt(gameMode);

        }while (gamemode < 1 || gamemode > 2);
    }
    /**
     * Gets game size
     * @throws Exception if string is null
     */
    private void getGameSize() throws Exception{
        do {

            String gameSize = JOptionPane.showInputDialog("Enter the Size\n");
            if (gameSize == null)
                throw new Exception();
            size = Integer.parseInt(gameSize);

        }while (size < 0 || size > MAX_SIZE);
    }
    /**
     * Initiates all components(panels, buttons etc).
     */
     private void initiateComponents(){

        
        frame = new JFrame();
        buttons = new JButton[size];
        
        topPanel = new JPanel();
        topPanel.setSize(frame.getWidth(), 50);
        topPanel.setLayout(new GridLayout(0, size));
        for (int i = 0; i < buttons.length; i++) {
            buttons[i] = new JButton(new Character((char) ('A' + i)).toString());
            buttons[i].addActionListener((ActionListener) this);
            topPanel.add(buttons[i]);

        }


        midPanel = new JPanel();
        midPanel.setLayout(new GridLayout(size, size));
        gameCells = new JLabel[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                gameCells[i][j] = new JLabel();
                gameCells[i][j].setBackground(Color.WHITE);
                gameCells[i][j].setBorder(new LineBorder(Color.ORANGE, 2));
                gameCells[i][j].setOpaque(true);
                midPanel.add(gameCells[i][j]);
            }
        }
        turn = 1;    
        infoMessage = new JTextField();
        infoMessage.setFont(new Font("Verdana", Font.BOLD, 15));

        frame.getContentPane().add(topPanel, BorderLayout.NORTH);
        frame.getContentPane().add(infoMessage, BorderLayout.SOUTH);
        frame.getContentPane().add(midPanel, BorderLayout.CENTER);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setPreferredSize(new Dimension(640, 640));
        frame.pack();
        frame.setVisible(true);

    }
    /**
     * 
     * @param row target row
     * @param col target column
     * @return check the cell returns whether it is valid
     */ 
    private boolean isPosValid(int row, int col){
        return !(row >= size || row < 0
                || col >= size || col < 0);

    }
    /**
     * 
     * @param target traget column
     * @return true or false
     */
    private boolean isMoveLegal(String target){

        boolean status = true;

        if(gameCells[0][target.charAt(0)-'A'].getBackground()!=Color.WHITE){
            infoMessage.setText("Wrong move! Be sure your target column is not complete full.\n");
            status = false;
        }


        return status;
    }
    /**
     * check the game is ended.
     * @param row target row
     * @param col target col
     * @return the direction
     */
    private int checkRow(int row, int col){

      int check = 0;

      if(countRowSouth(row, col) >= 4){
          check = 1;
      }
      else if((countRowSouthEast(row, col) +
              countRowNorthWest(row, col)) >= 3){
          check = 2;
      }
      else if((countRowWest(row, col) +
              countRowEast(row, col)) >= 3){
          check = 3;
      }
      else if((countRowSouthWest(row, col) +
              countRowNorthEast(row, col)) >= 3){
          check = 4;
      }

      return check;
  }
    /**
     * 
     * @param row target tow
     * @param col target col
     * @return how many in a row
     */
    private int countRowSouth(int row, int col){

        int count = 0;
        int tempChain = 0;

        while(isPosValid(row, col) && gameCells[row][col].getBackground() == lastMove.getBackground()){
            tempChain++;
            count++;
            row++;

        }

        if(chain < tempChain)
            chain = tempChain;

        return count;

    }
    /**
     * 
     * @param row target tow
     * @param col target col
     * @return how many in a row
     */
    private int countRowEast(int row, int col){

        int count = 0;
        int tempChain = 0;
        col++;

        while(isPosValid(row, col) && gameCells[row][col].getBackground() == lastMove.getBackground()){
            tempChain++;
            count++;
            col++;
        }
        if(chain < tempChain)
            chain = tempChain;

        return count;
    }
    /**
     * 
     * @param row target tow
     * @param col target col
     * @return how many in a row
     */
    private int countRowWest(int row, int col){

        int count = 0;
        int tempChain = 0;
        col--;

        while(isPosValid(row, col) && gameCells[row][col].getBackground() == lastMove.getBackground()){
            tempChain++;
            count++;
            col--;
        }
        if(chain < tempChain)
            chain = tempChain;

        return count;
    }
    /**
     * 
     * @param row target tow
     * @param col target col
     * @return how many in a row
     */
    private int countRowSouthWest(int row, int col){

        int count = 0;
        int tempChain = 0;
        row++;
        col--;

        while(isPosValid(row, col) && gameCells[row][col].getBackground() == lastMove.getBackground()){
            tempChain++;
            count++;
            row++;
            col--;
        }
        if(chain < tempChain)
            chain = tempChain;

        return count;
    }
    /**
     * 
     * @param row target tow
     * @param col target col
     * @return how many in a row
     */
    private int countRowSouthEast(int row, int col){

        int count = 0;
        int tempChain = 0;
        row++;
        col++;

        while(isPosValid(row, col) && gameCells[row][col].getBackground() == lastMove.getBackground()){
            tempChain++;
            count++;
            row++;
            col++;
        }
        if(chain < tempChain)
            chain = tempChain;

        return count;
    }
    /**
     * 
     * @param row target tow
     * @param col target col
     * @return how many in a row
     */

    private int countRowNorthEast(int row, int col){

        int count = 0;
        int tempChain = 0;
        row--;
        col++;

        while(isPosValid(row, col) && gameCells[row][col].getBackground() == lastMove.getBackground()){
            tempChain++;
            count++;
            row--;
            col++;
        }
        if(chain < tempChain)
            chain = tempChain;

        return count;
    }

    /**
     * 
     * @param row target tow
     * @param col target col
     * @return how many in a row
     */
    private int countRowNorthWest(int row, int col){

        int count = 0;
        int tempChain = 0;
        row--;
        col--;

        while(isPosValid(row, col) && gameCells[row][col].getBackground() == lastMove.getBackground()){
            tempChain++;
            count++;
            row--;
            col--;
        }
        if(chain < tempChain)
            chain = tempChain;

        return count;
    }   
    
}
