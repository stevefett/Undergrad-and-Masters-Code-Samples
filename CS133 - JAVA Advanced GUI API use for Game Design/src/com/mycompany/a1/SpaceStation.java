package com.mycompany.a1;

public class SpaceStation extends FixedGameObject
{
	private int thisId;
	private int blinkRate;
	private int timeSinceBlink;
	private boolean lightsOn;
	
	/**
	 * Creates a fixed Space Station object that doesn't move
	 */
	public SpaceStation()
	{
		thisId = GetId();
		blinkRate = rng.nextInt(4) + 1;
		lightsOn = true;
		timeSinceBlink = 0;
		SetColor(255, 0, 255);	
	}
	
	/**
	 * @return Blink rate associated with space station
	 */
	public int GetRate()
	{
		return blinkRate;
	}
	
	/**
	 * @return The ID associated to the space station
	 */
	public int GetId()
	{
		return thisId;
	}
	
	/**
	 * Increases the counter since the last blink of the lights, turning on and off, resets to zero when toggle
	 */
	public void IncreaseBlinkTime()
	{
		timeSinceBlink++;
		if (timeSinceBlink == blinkRate)
		{
			lightsOn = !lightsOn;
			timeSinceBlink = 0;
		}
	}
	
	public String toString()
	{
		String parentString = super.toString();
		String thisString = " rate = " + blinkRate;
		return "Station: " + parentString + thisString;
	}
}
