package com.mycompany.a1;

public class PlayerShip extends MoveableGameObject implements ISteerable
{
	private int missileCount;
	private MissileLauncher launcher;
	
	public PlayerShip()
	{
		launcher = new MissileLauncher(0);
		missileCount = 10;
		SetLocation(512.0, 384.0);
		SetSpeed(0);
		SetDirection(0);
		SetColor(0, 255, 255);
	}
	
	public int GetMissileCount()
	{
		return missileCount;
	}
	
	public int GetLauncherDir()
	{
		return launcher.GetDirection();
	}
	
	public void Fire()
	{
		missileCount--;
	}
	
	public void Reload()
	{
		missileCount = 10;
	}
	
	public void ResetPosition()
	{
		SetLocation(512.0, 384.0);
	}
	
	public void AdjustSpeed(boolean increase)
	{
		if (increase && GetSpeed() < 15)
		{
			//Increase speed
			SetSpeed(GetSpeed() + 1);
		}
		else if (!increase && GetSpeed() > 0)
		{
			//Decrease speed
			SetSpeed(GetSpeed() - 1);
		}
	}

	@Override
	public void Move() 
	{
		super.Move();
	}
	
	@Override
	public void Steer(int amount) 
	{
		if (GetDirection() == 0 && amount < 0)
		{
			SetDirection(359);
		}
		else
		{
			SetDirection(GetDirection() + amount);			
		}
	}
	
	public void ChangeLauncherDir(int amount)
	{
		launcher.Steer(amount);
	}

	public String toString()
	{
		String parentString = super.toString();
		String thisString = " missiles = " + missileCount;
		return "Player Ship: " + parentString + thisString + launcher.toString();
	}
}
