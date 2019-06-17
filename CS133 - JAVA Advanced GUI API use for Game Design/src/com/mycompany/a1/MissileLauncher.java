package com.mycompany.a1;

public class MissileLauncher extends MoveableGameObject implements ISteerable
{	
	/**
	 * @param startDir - The starting direction of the launcher, will typically be zero unless stated otherwise
	 */
	public MissileLauncher(int startDir)
	{
		SetDirection(startDir);
	}
	
	/**
	 * @return The current direction of the launcher
	 */
	public int GetLauncherDir()
	{
		return GetDirection();
	}
	
	/**
	 * @param amount - Value to set the launcher direction too
	 */
	public void SetLauncherDir(int amount)
	{
		SetDirection(amount);
	}
		
	@Override
	public void Steer(int amount)
	{
		SetDirection(GetDirection() + amount);
	}

	public String toString()
	{
		return " Missile Launcher Direction = " + GetDirection();
	}
}
