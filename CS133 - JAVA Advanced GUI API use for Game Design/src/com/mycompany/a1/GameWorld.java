package com.mycompany.a1;

import java.util.ArrayList;
import java.util.Iterator;

import com.mycompany.a1.Missile.MissileType;

public class GameWorld	
{
	public enum EntityType { PLAYER, ASTEROID, ENEMY, MISSILE }
	private ArrayList<GameObject> list;
	private GameObjectIterator iterator;
	
	private int score;
	private int elapsedTime;
	private int playerLives;
	
	private boolean gameOver;
	
	public void init()
	{
		list = new ArrayList<GameObject>();
		iterator = new GameObjectIterator();
		
		score = 0;
		elapsedTime = 0;
		playerLives = 3;
		
		gameOver = false;
	}
	
	/**
	 * Spawn an asteroid object in the game world
	 */
	public void SpawnAsteroid()
	{
		Asteroid ast = new Asteroid();
		list.add(ast);
	}
	
	/**
	 * Spawn a Non-Player Ship in the game world
	 */
	public void SpawnEnemy()
	{
		EnemyShip enemy = new EnemyShip();
		list.add(enemy);
	}
	
	/**
	 * Spawn a player ship in the game world
	 */
	public void SpawnPlayer()
	{
		if (!FindInstanceOfPlayer())
		{
			PlayerShip player = new PlayerShip();
			list.add(player);
		}
		else
		{
			System.err.println("There is already an instance of player");
		}
	}
	
	/**
	 * Spawn a space station in the game world
	 */
	public void SpawnStation()
	{
		SpaceStation station = new SpaceStation();
		list.add(station);
	}
	
	/**
	 * @param speedUp - A boolean value to determine if player is to increase or decrease in speed. True is speed up
	 */
	public void ChangeSpeed(boolean speedUp)
	{
		PlayerShip playerObj = FindPlayer();
		if (playerObj != null)
		{
			playerObj.AdjustSpeed(speedUp);
		}
	}
	
	/**
	 * @param turnRight - A boolean value to determine if we are to turn player left or right.
	 * True means we are to turn player right.
	 */
	public void TurnPlayer(boolean turnRight)
	{
		/* For reference the headings of the direction is as follows
		 * 
		 * 	North - direction = 0
		 * 	East - direction = 90
		 * 	South - direction = 180
		 * 	West - direction = 270
		 * 
		 * 	If turning left and direction is currently zero, heading directly north, change the 
		 * 	direction value to 359 instead. Value must always be positive and within the range
		 * 	of 0 and 359 both inclusive.
		 */
		PlayerShip playerObj = FindPlayer();
		if (playerObj != null)
		{
			if (turnRight)
			{
				//Rotate player clockwise (right)
				playerObj.Steer(1);
			}
			else
			{
				//Rotate player counter-clockwise (left)
				playerObj.Steer(-1);
			}
		}
	}
	
	/**
	 * Rotates the launcher attached to the PlayerShip. We are only able to rotate counter clockwise
	 */
	public void RotateLauncher()
	{
		PlayerShip playerObj = FindPlayer();
		playerObj.ChangeLauncherDir(1);
	}
	
	/**
	 * Fires a missile from player if player is in game and has missiles to fire.
	 */
	public void FirePlayerMissile()
	{
		PlayerShip playerObj = FindPlayer();
		if (playerObj != null)
		{
			if (playerObj.GetMissileCount() > 0)
			{				
				Missile missile = new Missile(playerObj.GetLauncherDir(), playerObj.GetSpeed() + 2, playerObj.GetFullLocation(), MissileType.PLAYER);
				list.add(missile);
				playerObj.Fire();
			}
			else
			{
				System.err.println("No more missiles time to reload");
			}
		}
	}
	
	/**
	 * Fires a missile from Enemy Ship if one exists with missiles to fire.
	 */
	public void FireEnemymissile()
	{
		EnemyShip enemyObj = FindEnemyWithMissiles();
		if (enemyObj != null)
		{
			Missile missile = new Missile(enemyObj.GetDirection(), enemyObj.GetSpeed() + 2, enemyObj.GetFullLocation(), MissileType.ENEMY);
			list.add(missile);
			enemyObj.Fire();
		}
		else
		{
			System.err.println("Spawn a new enemy");
		}
	}
	
	/**
	 * Reset the player position to origin
	 */
	public void ResetPosition()
	{
		PlayerShip playerObj = FindPlayer();
		playerObj.ResetPosition();
	}
	
	/**
	 * Reload the player with more missiles up to max.
	 */
	public void ReloadMissiles()
	{
		//Reset missile count to 10
		PlayerShip playerObj = FindPlayer();
		SpaceStation stationObj = FindStation();
		if (playerObj != null && stationObj != null) { playerObj.Reload(); }
	}
	
	/**
	 * Used to destroy asteroids and enemy ships with missiles depending on the command.
	 * Will also increment the player score based on predetermined values depending on
	 * the enemy as well. A value of true indicates an asteroid was struck, a value of false
	 * indicates that an enemy ship was struck instead.
	 * @param entity - entity as listed in the EntityType enumeration. Select either asteroid or enemy ship
	 */
	public void DestroyEnemy(EntityType entity)
	{
		//Destroy asteroid or enemy ship with player missile
		//increment score based on which enemy was destroyed
		Missile missileObj = FindMissile(MissileType.PLAYER);
		GameObject enemy = null;
		if (missileObj != null) 
		{	
			switch (entity)
			{
				case ASTEROID:
					enemy = FindAsteroid();
					score += 10;
					break;
					
				case ENEMY:
					enemy = FindEnemy();
					score += 20;
					break;
					
				default:
					System.err.println("Wrong enemy selected");
			}
			
			if (enemy != null)
			{
				list.remove(missileObj);
				list.remove(enemy);
			}
		}
	}
	
	/**
	 * Destroys the player with an enemy missile if there is an instance of both.
	 */
	public void KillPlayerWithEnemyMissile()
	{
		Missile missileObj = FindMissile(MissileType.ENEMY);
		if (missileObj != null)
		{
			PlayerShip playerObj = FindPlayer();
			if (playerObj != null)
			{
				list.remove(playerObj);
				list.remove(missileObj);
				ReduceLives();
			}
		}
		
	}
	
	/**
	 * Handles all collision variations within the game world.
	 * 	- Player crashes into asteroid
	 *  - Player crashes into enemy ship
	 *  - Two asteroids collide together
	 *  - Asteroid collides with enemy ship
	 * @param entityOne - Determines collider, must be of type PLAYER or type ASTEROID
	 * @param entityTwo - Determines collidee, must be of type ASTEROID or type ENEMY
	 */
	public void Collision(EntityType entityOne, EntityType entityTwo)
	{
		//When two entities collide perform necessary actions based on 
		//what happened.
		/* Variations of collisions
		 * 	- Player crashes into asteroid
		 *  - Player crashes into enemy ship
		 *  - Two asteroids collide with each other
		 *  - Asteroid collides with enemy ship 
		 */
		GameObject objectOne = null;
		GameObject objectTwo = null;
		if (entityOne != null && entityTwo != null)
		{
			switch (entityOne)
			{
				case PLAYER:
					objectOne = FindPlayer();
					break;
					
				case ASTEROID:
					objectOne = FindAsteroid();
					break;
					
				default:
					System.err.println("Poor value passed");
					break;
			}
			
			if (objectOne != null)
			{
				switch (entityTwo)
				{
					case ASTEROID:
						int i = -1;
						while (iterator.hasNext())
						{
							i++;
							if (iterator.next() instanceof Asteroid)
							{
								objectTwo = (Asteroid) list.get(i);
								if (!objectTwo.equals(objectOne))
								{
									iterator.ResetIndex();
									break;									
								}
								else
								{
									objectTwo = null;
								}
								
							}
						}
						break;
						
					case ENEMY:
						objectTwo = FindEnemy();
						break;
						
					default:
						System.err.println("Poor value passed");
						break;
				}
				
				if (objectTwo != null)
				{
					list.remove(objectOne);
					list.remove(objectTwo);
					if (objectOne instanceof PlayerShip)
					{
						ReduceLives();
					}
				}
				else
				{
					System.err.println("No instance of " + entityTwo);
				}
			}
			else
			{
				System.err.println("No instance of " + entityOne);
			}
		}
		else
		{
			System.err.println("A value of null was passed to method");
			System.err.println("Entity one = " + entityOne + "\nEntity two = " + entityTwo);
		}
	}
	
	/**
	 * Displays the player's score, missile count, and the current elapsed time in game
	 */
	public void DisplayGameValues()
	{
		PlayerShip playerObj = FindPlayer();
		
		if (FindInstanceOfPlayer())
		{
			System.out.println("Player Score = " + score);
			System.out.println("Player missile count = " + playerObj.GetMissileCount());
			System.out.println("Current elapsed time = " + elapsedTime);
			System.out.println();
		}
		
	}
	
	/**
	 * Advance the game forward by one frame
	 */
	public void AdvanceGameClock()
	{
		int i = -1;
		while (iterator.hasNext())
		{
			i++;
			if (iterator.next() instanceof IMoveable)
			{
				IMoveable moveObj = (IMoveable) list.get(i);
				moveObj.Move();
				if (iterator.current() instanceof Missile)
				{
					Missile missileObj = (Missile) list.get(i);
					if (missileObj.GetFuel() == 0)
					{
						iterator.remove();
						i--;
					}
				}
			}
			else if (iterator.current() instanceof SpaceStation)
			{
				SpaceStation stationObj = (SpaceStation) list.get(i);
				stationObj.IncreaseBlinkTime();
			}
		}
		elapsedTime++;
	}
	
	/**
	 * Prints all of the objects currently instantiated in the game world
	 */
	public void PrintMap()
	{
		System.out.flush();
		while (iterator.hasNext())
		{
			System.out.println(iterator.next());
		}
		System.out.println();
	}
	
	/**
	 * Reduces number of player lives left. If that value hits zero, set gameOver to true and prevent further action
	 */
	public void ReduceLives()
	{
		playerLives--;
		
		if (playerLives == 0)
		{
			gameOver = true;
		}
	}
	
	//Used to Find the playerShip for the various commands above
	/**
	 * When called searches through the list to find an instance of PlayerShip
	 * @return Reference to PlayerShip location in list if it exists, null otherwise.
	 */
	private PlayerShip FindPlayer()
	{
		int i = -1;
		PlayerShip temp = null;
		while (iterator.hasNext())
		{
			i++;
			if (iterator.next() instanceof PlayerShip)
			{
				temp = (PlayerShip) list.get(i);
				iterator.ResetIndex();
				break;
			}
		}
		
		if (temp == null)
		{
			System.err.println("No player ship has been spawned yet"); 
			return null;
		}
		else { return temp; }
	} 
	
	/**
	 * When called searches through the list to find an instance of Asteroid
	 * @return Reference to Asteroid location in list if it exists, null otherwise.
	 */
	private Asteroid FindAsteroid()
	{
		int i = -1;
		Asteroid temp = null;
		while (iterator.hasNext())
		{
			i++;
			if (iterator.next() instanceof Asteroid)
			{
				temp = (Asteroid) list.get(i);
				iterator.ResetIndex();
				break;
			}
		}
		
		if (temp == null) 
		{
			System.err.println("No asteroid has been spawned yet"); 
			return null;
		}
		else { return temp; }
	}
	
	/**
	 * When called searches through the list to find an instance of EnemyShip
	 * @return Reference to EnemyShip location in list if it exists, null otherwise.
	 */
	private EnemyShip FindEnemy()
	{
		int i = -1;
		EnemyShip temp = null;
		while (iterator.hasNext())
		{
			i++;
			if (iterator.next() instanceof EnemyShip)
			{
				temp = (EnemyShip) list.get(i);
				iterator.ResetIndex();
				break;
			}
		}
		
		if (temp == null) 
		{
			System.err.println("No enemy ship has been spawned yet"); 
			return null;
		}
		else { return temp; }
	}
	/**
	 * When called searches through the list to find an instance of EnemyShip similar to FindEnemy(),
	 * the difference with this method, however, is that it searches for an EnemyShip with a missile count
	 * over zero. Meant purely for firing missiles from enemy ship.
	 * @return Reference to EnemyShip location in list if it exists and has missiles to fire, null otherwise.
	 */
	private EnemyShip FindEnemyWithMissiles()
	{
		int i = -1;
		EnemyShip temp = null;
		while (iterator.hasNext())
		{
			i++;
			if (iterator.next() instanceof EnemyShip)
			{
				temp = (EnemyShip) list.get(i);
				if (temp.GetMissileCount() > 0)
				{
					iterator.ResetIndex();
					break;					
				}
				else
				{
					temp = null;
				}
			}
		}
		
		if (temp == null) 
		{
			System.err.println("No enemy ship has been spawned yet or there are no ships with missiles to fire."); 
			return null;
		}
		else { return temp; }
	}
	
	/**
	 * When called searches through the list to find an instance of Missile based on passed type.
	 * @param type - Determines the missile type to search for, either PLAYER or ENEMY
	 * @return Reference to Missile location in list if type matches, null otherwise
	 */
	private Missile FindMissile(MissileType type)
	{
		int i = -1;
		Missile temp = null;
		while (iterator.hasNext())
		{
			i++;
			if (iterator.next() instanceof Missile)
			{
				temp = (Missile) list.get(i);
				if (temp.GetType().equals(type))
				{
					iterator.ResetIndex();
					break;					
				}
				else
				{
					temp = null;
				}
			}
		}
		
		if (temp == null) 
		{
			System.err.println("No missile of type " + type.toString() + " has been spawned yet"); 
			return null;
		}
		else { return temp; }
	}
	
	/**
	 * When called searches through the list to find an instance of SpaceStation.
	 * @return Reference to the Station location in list if one exists, null otherwise
	 */
	private SpaceStation FindStation()
	{
		int i = -1;
		SpaceStation temp = null;
		while (iterator.hasNext())
		{
			i++;
			if (iterator.next() instanceof SpaceStation)
			{
				temp = (SpaceStation) list.get(i);
				iterator.ResetIndex();
				break;
			}
		}
		
		if (temp == null) 
		{
			System.err.println("No space station has been spawned yet"); 
			return null;
		}
		else { return temp; }
	}
	
	/**
	 * @return true if there exists an instance of player and lives are not 0, false otherwise.
	 */
	private boolean FindInstanceOfPlayer()
	{
		if (list.size() > 0 && !gameOver)
		{
			while (iterator.hasNext())
			{
				if (iterator.next() instanceof PlayerShip)
				{
					iterator.ResetIndex();
					return true;
				}
			}
		}
		return false;
	}
	
	/**
	 * @return true if player lives is zero
	 */
	public boolean GameOver()
	{
		if (gameOver) { System.out.println("Player has run out of lives time to restart"); }
		return gameOver;
	}
	
	private class GameObjectIterator implements Iterator<Object>
	{
		private int index;
		
		public GameObjectIterator() 
		{
			index = -1;
		}
		
		@Override
		public boolean hasNext() 
		{
			if (list.size() <= 0) return false;
			if (index == list.size() - 1) 
			{
				index = -1;
				return false;
			}
			return true;
		}

		@Override
		public Object next() 
		{
			index++;
			return list.get(index);
		}

		@Override
		public void remove() 
		{
			list.remove(index);
			index--;
		}
		
		/**
		 * Resets the iterator index. To be used if you break out of a loop early
		 */
		public void ResetIndex()
		{
			index = -1;
		}
		
		/**
		 * @return The object located at the current position in the list
		 */
		public Object current()
		{
			if (index >= 0)
			{
				return list.get(index);
			}
			else
			{
				return null;
			}
		}
	}
}