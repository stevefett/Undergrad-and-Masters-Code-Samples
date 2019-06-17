package com.mycompany.a1;

public abstract class FixedGameObject extends GameObject
{
	private static int id = 0;
	
	public FixedGameObject()
	{
		id++;
	}
	
	/**
	 * @return Returns the next id for the station to distinguish
	 */
	public int GetId()
	{
		return id;
	}
}
