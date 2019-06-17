package com.mycompany.a1;

import com.codename1.ui.geom.Point2D;

public abstract class MoveableGameObject extends GameObject implements IMoveable
{
	private int speed;
	private int direction;
	
	/**
	 * Indicates that an object is moveable. Randomizes the speed and direction of the object
	 */
	public MoveableGameObject()
	{
		speed = rng.nextInt(16);
		direction = rng.nextInt(360);
	}
	
	/**
	 * @return The speed associated with this object
	 */
	public int GetSpeed()
	{
		return speed;
	}
	
	/**
	 * @param s - set the speed of this object to s
	 */
	public void SetSpeed(int s)
	{
		speed = s;
	}
	
	/**
	 * @return the integer value indicating the direction.
	 */
	public int GetDirection()
	{
		return direction;
	}
	
	/**
	 * @param d - set direction to value d
	 */
	public void SetDirection(int d)
	{
		direction = d;
	}
	
	@Override
	public void Move()
	{
		Point2D newLoc = new Point2D(0.0, 0.0);
		Point2D oldLoc = GetFullLocation();
		double deltaX = 0.0;
		double deltaY = 0.0;
		
		//If going directly north or south only affect Y
		if (direction == 0 || direction == 180)
		{
			deltaY = Math.sin( Math.toRadians(90 - direction) ) * speed;
		}
		else if (direction == 90 || direction == 270)
		{
			deltaX = Math.cos( Math.toRadians(90 - direction) ) * speed;
		}
		else
		{
			deltaX = Math.cos( Math.toRadians(90 - direction) ) * speed;
			deltaY = Math.sin( Math.toRadians(90 - direction) ) * speed;
		}
		
		newLoc.setX(deltaX + oldLoc.getX());
		newLoc.setY(deltaY + oldLoc.getY());
		
		SetLocation(newLoc);
	}

	public String toString()
	{
		String parentString = super.toString();
		String thisString = "speed = " + speed + " direction = " + direction + " ";
		return parentString + thisString;
	}
}