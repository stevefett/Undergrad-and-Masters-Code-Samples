package com.mycompany.a1;

import com.codename1.ui.geom.Point2D;

public class Missile extends MoveableGameObject
{
	public enum MissileType { PLAYER, ENEMY }
	private MissileType type;
	private int fuelLevel;
	
	/**
	 * 
	 * @param missileLauncherDir - The direction to fire the missile
	 * @param speed - The speed of the ship currently firing the missile, missiles always need to be faster than the firing ship
	 * @param loc - the location of the ship firing the missile
	 * @param type - The type of ship firing the missile (Player or Enemy)
	 */
	public Missile(int missileLauncherDir, int speed, Point2D loc, MissileType type)
	{
		fuelLevel = 10;
		SetLocation(loc);
		SetSpeed(speed);
		SetDirection(missileLauncherDir);
		
		this.type = type;
		switch (type)
		{
			case PLAYER:
				SetColor(0, 255, 255);
				break;
				
			case ENEMY:
				SetColor(255, 0, 0);
				break;
		}
	}
	
	/**
	 * @return The current fuel level associated with this missile
	 */
	public int GetFuel()
	{
		return fuelLevel;
	}
	
	/**
	 * @return The type of missile that was fired, either Player or Enemy
	 */
	public MissileType GetType()
	{
		return type;
	}

	@Override
	public void Move() 
	{
		fuelLevel--;
		super.Move();
	}
	
	public String toString()
	{
		String parentString = super.toString();
		String thisString = " fuel = " + fuelLevel;
		if (type == MissileType.PLAYER)
		{
			return "PS's Missile: " + parentString + thisString;			
		}
		else
		{
			return "NPS's Missile: " + parentString + thisString;
		}
	}
}
