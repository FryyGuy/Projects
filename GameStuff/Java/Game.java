/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Matt Fry
 */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Game extends JPanel
{
    //create a new player object, passing this instance of the Game class to it's constructor
    Player player = new Player(this);
    
    //constructor adds a Controller Key Listener class and gives it focus
    public Game()
    {
        addKeyListener(new Controller());
        setFocusable(true);
    }
    
    //the paint method repaints the screen, paints the player, and updates the player for gravity.
    public void paint(Graphics g)
    {
        super.paint(g);
        player.paint(g);
        
        if(player.y < 500)
            player.fall();
        else if(player.y == 500)
            player.stop();
    }
    
    //the controller class is responsible for handling key events.
    private class Controller implements KeyListener
    {
        public void keyPressed(KeyEvent e)
        {
            player.keyPressed(e);
        }
    
        public void keyReleased(KeyEvent e)
        {
        
        }
    
        public void keyTyped(KeyEvent e)
        {
        
        }   
    }
    
    //the main method adds a frame, creates a game object, and repaints the player on the screen.
    public static void main(String[] args) throws InterruptedException
    {
        JFrame frame = new JFrame("Player Demo");
        Game game = new Game();
        frame.add(game);
        frame.setSize(500, 500);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
        
        //Game Loop
        while(true)
        {       
            game.repaint(); 
            Thread.sleep(10);
        }
    }
}
