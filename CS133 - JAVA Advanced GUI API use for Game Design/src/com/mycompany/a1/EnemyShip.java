package com.mycompany.a1;

public class EnemyShip extends MoveableGameObject
{
	private int size;
	private int missileCount;
	
	/**
	 * Creates an enemy ship object in the world. Enemy ships have two sizes, small and large.
	 * Enemies also have missiles that they can fire, a total of two.
	 */
	public EnemyShip()
	{
		size = (rng.nextInt(2) + 1) * 10;
		missileCount = 2;
		SetColor(255, 0, 0);
	}
	
	/**
	 * @return integer value representing the size (10 = small / 20 = large)
	 */
	public int GetSize()
	{
		return size;
	}
	
	/**
	 * @return The current number of missiles left in this enemy ship
	 */
	public int GetMissileCount()
	{
		return missileCount;
	}

	/**
	 * Called to reduce the number of missiles in the enemy ship. to be called after a missile has been instantiated.
	 */
	public void Fire()
	{
		//Fire enemy missiles
		missileCount--;
	}

	@Override
	public void Move() 
	{
		super.Move();	
	}
	
	public String toString()
	{
		String parentString = super.toString();
		String thisString = " size = " + size;
		return "Non-Player Ship: " + parentString + thisString;
	}
}
