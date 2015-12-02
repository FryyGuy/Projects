/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Matt Fry
 */

//necessary library imports
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Player
{
    //fields
    public int x;
    public int y;
    Game game;
    
    //constructor
    public Player(Game game)
    {
        this.x = 0;
        this.y = 0;
        
        this.game = game;
    }
    
    //override the paint method
    public void paint(Graphics g)
    {
        //create a circle
        g.setColor(Color.blue);
        g.fillOval(getX(), getY(), 30, 30);
    }
    
    //accessor methods
    public int getX()
    {
        return x;
    }
    
    public int getY()
    {
        return y;
    }
    
    //the fall method will implement gravity for the game
    public void fall()
    {
        y += 5;
    }
    
    //the stop method will stop the player from being affected by gavity
    public void stop()
    {
        y += 0;
    }
    
    //functionality for key presses
    public void keyPressed(KeyEvent e)
    {
        //move the ball 10 pixels up
        if(e.getKeyCode() == KeyEvent.VK_W)
            y -= 50;            
        
        //move the ball 10 pixels down
        if(e.getKeyCode() == KeyEvent.VK_S)
            y += 10;
        
        //move the ball 10 pixels left
        if(e.getKeyCode() == KeyEvent.VK_A)
            x -= 10;
        
        //move the ball 10 pxiels right
        if(e.getKeyCode() == KeyEvent.VK_D)
            x += 10;
    }
    
}
