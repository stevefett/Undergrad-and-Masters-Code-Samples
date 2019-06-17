package com.mycompany.a1;
import java.util.Random;
import com.codename1.charts.util.ColorUtil;
import com.codename1.ui.geom.Point2D;

public abstract class GameObject 
{
	public Random rng = new Random();
	private Point2D location;
	private int rgb;
	
	/**
	 * The base constructor for all game objects. Randomizes the location values.
	 */
	public GameObject()
	{
		double x = Math.round((1025.0 * rng.nextDouble() * 10.0)) / 10.0;
		double y = Math.round((769.0 * rng.nextDouble() * 10.0)) / 10.0;
		
		//These two tests are only for the EXTREMELY rare instances where x or y will be greater than the max values
		//of 1024 and 768 respectively. 
		if (x > 1024.0) { x = 1024.0; }
		if (y > 768.0) { y = 768.0; }
		
		location = new Point2D(x, y);
	}
	
	/**
	 * @return the integer value representing the color associated with the current object
	 */
	public int GetColor()
	{
		return rgb;
	}
	
	/**
	 * Changes the color of this object
	 * @param r - The red value
	 * @param g - The green value
	 * @param b - The blue value
	 */
	public void SetColor(int r, int g, int b)
	{
		rgb = ColorUtil.rgb(r, g, b);
	}
	
	/**
	 * @return The double value for the X location in world space
	 */
	public double GetLocationX()
	{
		return location.getX();
	}
	
	/**
	 * @return The double value for the Y location in world space
	 */
	public double GetLocationY()
	{
		return location.getY();
	}
	
	/**
	 * @return The Point2D object representing the entire location of the object
	 */
	public Point2D GetFullLocation()
	{
		return location;
	}
	
	/**
	 * Changes the X and Y values of the objects location
	 * @param x - X location in world space on screen
	 * @param y - Y location in world space on screen
	 */
	public void SetLocation(double x, double y)
	{
		location.setX(Math.round((x * 10.0)) / 10.0);
		location.setY(Math.round((y * 10.0)) / 10.0);
	}
	
	/**
	 * @param loc - the full location of the object in world space
	 */
	public void SetLocation(Point2D loc)
	{
		location.setX(Math.round((loc.getX() * 10.0)) / 10.0);
		location.setY(Math.round((loc.getY() * 10.0)) / 10.0);
	}
	
	public String toString()
	{
		return "loc = " + location.getX() + ", " + location.getY() +  
				" color = [" + ColorUtil.red(rgb) + ", " +  
							   ColorUtil.green(rgb) + ", " +
							   ColorUtil.blue(rgb) + "] ";
	}
}
