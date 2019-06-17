package com.mycompany.a1;

public interface ISteerable 
{
	/**
	 * All steerable objects are required to be able to change their direction
	 * @param amount - value to chance the steerable objects direction by
	 */
	public void Steer(int amount);
}
