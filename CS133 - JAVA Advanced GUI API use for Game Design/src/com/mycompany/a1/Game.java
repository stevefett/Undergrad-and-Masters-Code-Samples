package com.mycompany.a1;
import com.codename1.ui.Form;
import com.codename1.ui.Label;
import com.codename1.ui.TextField;
import com.codename1.ui.events.ActionListener;
import com.mycompany.a1.GameWorld.EntityType;
import com.codename1.ui.events.ActionEvent;
import java.lang.String;

public class Game extends Form 
{
	private GameWorld gw;
	
	public Game()
	{
		gw = new GameWorld();
		gw.init();
		play();
	}
	
	private void play()
	{
		this.setScrollable(false);
		
		Label textLabel = new Label ("Enter a command: ");
		this.addComponent(textLabel);
		
		final TextField myTextField = new TextField();
		this.addComponent(myTextField);
				
		this.show();
		myTextField.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent evt)
			{
				String command = myTextField.getText().toString();
				myTextField.clear();
				if (!command.equals(null) && command.length() > 0 && !gw.GameOver())
				{
					switch (command.charAt(0))
					{
						case 's':
							gw.SpawnPlayer();
							break;	
							
						case 'y':
							gw.SpawnEnemy();
							break;
							
						case 'a':
							gw.SpawnAsteroid();
							break;
							
						case 'b':
							gw.SpawnStation();
							break;
							
						case 'i':
							//Increase player speed
							gw.ChangeSpeed(true);
							break;
							
						case 'd':
							//decrease player speed
							gw.ChangeSpeed(false);
							break;
							
						//Lowercase L
						case 'l':
							//turn player left
							gw.TurnPlayer(false);
							break;
							
						case 'r':
							//Turn player right
							gw.TurnPlayer(true);
							break;
							
						case '>':
							//rotates the missile launcher
							gw.RotateLauncher();
							break;
							
						case 'f':
							//fire a missile from player
							gw.FirePlayerMissile();
							break;
							
						case 'L':
							//Fire a missile out of enemy
							gw.FireEnemymissile();
							break;
							
						case 'j':
							//Move player back to origin position
							gw.ResetPosition();
							break;
							
						case 'n':
							//Reload missiles
							gw.ReloadMissiles();
							break;
						
						case 'k':
							//player missile hits asteroid
							gw.DestroyEnemy(EntityType.ASTEROID);
							break;
							
						case 'e':
							//player missile hits enemy
							gw.DestroyEnemy(EntityType.ENEMY);
							break;
						
						case 'E':
							//enemy missile hits player
							gw.KillPlayerWithEnemyMissile();
							break;
						
						case 'c':
							//Player crashes into asteroid
							gw.Collision(EntityType.PLAYER, EntityType.ASTEROID);
							break;
							
						case 'h':
							//Player ship runs into the enemy ship
							gw.Collision(EntityType.PLAYER, EntityType.ENEMY);
							break;
							
						case 'x':
							//Two asteroids collide
							gw.Collision(EntityType.ASTEROID, EntityType.ASTEROID);
							break;
							
						case 'I':
							//Asteroid collides with enemy ship
							gw.Collision(EntityType.ASTEROID, EntityType.ENEMY);
							break;
							
						case 't':
							//game clock as ticked, update all positions,
							//missile fuel reduced
							//toggle light
							//elapsed game time incremented
							gw.AdvanceGameClock();
							break;
							
						case 'p':
							//print display of game state values
							//current score
							//number of missiles in ship
							//current elapsed time
							gw.DisplayGameValues();
							break;
							
						case 'm':
							gw.PrintMap();
							break;
							
						case 'q':
							System.exit(0);
							break;
							
						default:
							System.err.println("Damn son");
							break;
					}
				}
			}
		});
	}
}
