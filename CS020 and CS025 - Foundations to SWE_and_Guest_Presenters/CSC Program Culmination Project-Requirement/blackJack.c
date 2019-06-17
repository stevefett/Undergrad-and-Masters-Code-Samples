//Steven Salmons
//C programming on UNIX
//Basic text console vs. house (app)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SENTINEL 0

typedef enum
	{
		NO_FACE,
		JACK,
		QUEEN,
		KING,
		ACE
	}face;

typedef struct
	{
		int value;
		face card_face;
	}card;

void shuffle(card *deck)
{
	int counter;
	srand(time(NULL));
	for(counter=0;counter<52;counter++)
	{
		int replace = rand() % 52;
		card temp = deck[counter];
		deck[counter] = deck[replace];
		deck[replace] = temp;		
	}
}

int main ()
{
    int bankroll = 1000;
	int bet = 1;
	card deck[52];
	int counter;
	int new_value = 2;
	int player_total = 0;
	int dealer_total = 0;
	int player_aces = 0;
	int dealer_aces = 0;
	int dealer_card2;
	int hit;
	
	printf("\n\n---Welcome To Blackjack---\n\n");
	
	deck[0].card_face = KING;
	deck[1].card_face = KING;
	deck[2].card_face = KING;
	deck[3].card_face = KING;
	
	deck[4].card_face = QUEEN;
	deck[5].card_face = QUEEN;
	deck[6].card_face = QUEEN;
	deck[7].card_face = QUEEN;
	
	deck[8].card_face = JACK;
	deck[9].card_face = JACK;
	deck[10].card_face = JACK;
	deck[11].card_face = JACK;
	
	deck[12].card_face = ACE;
	deck[13].card_face = ACE;
	deck[14].card_face = ACE;
	deck[15].card_face = ACE;
	
	
	for(counter=16;counter<52;counter++)
	{
		deck[counter].value = new_value;
		deck[counter].card_face = NO_FACE;
		new_value++;
		if(new_value > 10)
		{
			new_value = 2;
		}
	}
		
	while(bet != SENTINEL)
	{
		shuffle(deck);
		printf("\nThe cards have been shuffled...\n\n");
		printf("What amount would you like to bet?  Current bankroll is $%d\n", bankroll); 
		scanf("%d", &bet);
		while(bet > bankroll)
		{
			printf("Sorry, you don't have that much...\n Please place a new bet...\n");
			scanf("%d", &bet);
		}

		counter = 0;
		while(bet > 0)
		{
			while(bet > bankroll)
			{
				printf("Sorry, you don't have that much...\n Please place a new bet...\n");
				scanf("%d", &bet);
			}
			if(bet > 0)
			{
				printf("\n\nDealer is showing:\n");
				if(deck[counter].card_face == NO_FACE)							//prints dealer's first card
				{
					printf("Card: %d\n", deck[counter].value);
					dealer_total = dealer_total + deck[counter].value;
				}
				if(deck[counter].card_face == KING)
				{
					printf("Card: KING\n");
					dealer_total = dealer_total + 10;
				}
				else if(deck[counter].card_face == QUEEN)
				{
					printf("Card: QUEEN\n");
					dealer_total = dealer_total + 10;
				}
				else if(deck[counter].card_face == JACK)
				{
					printf("Card: JACK\n");
					dealer_total = dealer_total + 10;
				}
				else if(deck[counter].card_face == ACE)
				{
					printf("Card: ACE\n");
					dealer_aces++;
					if((dealer_total + 11 )> 21)
					{
						dealer_total = dealer_total + 1;
					}
					else
					{
						dealer_total = dealer_total + 11;
					}
				}
		
				counter++;
				if(counter == 52)
				{
					shuffle(deck);
					counter = 0;
					printf("The cards have been shuffled...\n");
				}
				dealer_card2 = counter;												//saves dealers card 
				if(deck[counter].card_face == NO_FACE)								// counts dealer's second card, but doesn't show it
				{
					dealer_total = dealer_total + deck[dealer_card2].value;
				}
				else if(deck[dealer_card2].card_face == KING)
				{
					dealer_total = dealer_total + 10;
				}
				else if(deck[dealer_card2].card_face == QUEEN)
				{
					dealer_total = dealer_total + 10;
				}
				else if(deck[dealer_card2].card_face == JACK)
				{
					dealer_total = dealer_total + 10;
				}
				else if(deck[dealer_card2].card_face == ACE)
				{
					dealer_aces++;
					if((dealer_total + 11 )> 21)
					{
						dealer_total = dealer_total + 1;
					}
					else
					{
						dealer_total = dealer_total + 11;
					}
				}
				counter++;
				if(counter == 52)
				{
					shuffle(deck);
					counter = 0;
					printf("The cards have been shuffled...\n");
				}
				printf("\nYou were dealt:\n");											//prints player's first card
				if(deck[counter].card_face == NO_FACE)
				{
					printf("Card: %d\n", deck[counter].value);
					player_total =  player_total + deck[counter].value;
				}
				if(deck[counter].card_face == KING)
				{
					printf("Card: KING\n");
					player_total = player_total + 10;
				}
				else if(deck[counter].card_face == QUEEN)
				{
					printf("Card: QUEEN\n");
					player_total = player_total + 10;
				}
				else if(deck[counter].card_face == JACK)
				{
					printf("Card: JACK\n");
					player_total = player_total + 10;
				}
				else if(deck[counter].card_face == ACE)
				{
					printf("Card: ACE\n");
					player_aces++;
					if((player_total + 11 )> 21)
					{
						player_total = player_total + 1;
					}
					else
					{
						player_total = player_total + 11;
					}
				}
						counter++;
				if(counter == 52)
				{
					shuffle(deck);
					counter = 0;
					printf("The cards have been shuffled...\n");
				}
				if(deck[counter].card_face == NO_FACE)								//prints player's second card
				{
					printf("Card: %d\n", deck[counter].value);
					player_total =  player_total + deck[counter].value;
				}
				if(deck[counter].card_face == KING)
				{
					printf("Card: KING\n");
					player_total = player_total + 10;
				}
				else if(deck[counter].card_face == QUEEN)
				{
					printf("Card: QUEEN\n");
					player_total = player_total + 10;
				}
				else if(deck[counter].card_face == JACK)
				{
					printf("Card: JACK\n");
					player_total = player_total + 10;
				}
				else if(deck[counter].card_face == ACE)
				{
					printf("Card: ACE\n");
					player_aces++;
					if((player_total + 11 )> 21)
					{
						player_total = player_total + 1;
					}
					else
					{
						player_total = player_total + 11;
					}
				}
				
				printf("Your hand is %d", player_total);
				printf("\nWhat would you like to do?\nHit[1]\nStay[2]\n");
				scanf("%d", &hit);

				counter ++;
				if(counter == 52)
				{
				shuffle(deck);
				counter = 0;
					printf("The cards have been shuffled...\n");
				}
				
				while(hit == 1)
				{
					printf("You've been dealt:\n");
					if(deck[counter].card_face == NO_FACE)									//prints player's hit cards
					{
						printf("Card: %d\n", deck[counter].value);
						player_total =  + player_total + deck[counter].value;
					}
					if(deck[counter].card_face == KING)
					{
						printf("Card: KING\n");
						player_total = player_total + 10;
					}
					else if(deck[counter].card_face == QUEEN)
					{
						printf("Card: QUEEN\n");
						player_total = player_total + 10;
					}
					else if(deck[counter].card_face == JACK)
					{
						printf("Card: JACK\n");
						player_total = player_total + 10;
					}
					else if(deck[counter].card_face == ACE)
					{
						printf("Card: ACE\n");
						player_aces++;
						if((player_total + 11 )> 21)
						{
							player_total = player_total + 1;
						}
						else
						{
							player_total = player_total + 11;
						}
					}
					if((player_aces > 0) && (player_total > 21))
					{
						player_total = player_total - 10;
						player_aces = 0;
					}
					printf("Your hand is now %d\n", player_total);
					if(player_total > 21)
					{
						printf("\n\nPLAYER BUST!\n");
						hit = 2;
					}
					else if(player_total <= 21)
					{
						printf("\nWhat would you like to do?\nHit[1]\nStay[2]\n\n");
						scanf("%d", &hit);
					}
		
					counter++;
					if(counter == 52)
					{
						shuffle(deck);
						counter = 0;
						printf("The cards have been shuffled...\n");
					}
	
				}	

				if(player_total < 22)
				{
					printf("\nDealer reveals other card:\n");							// shows the second card that the dealer had been dealt
					if(deck[dealer_card2].card_face == NO_FACE)
					{
						printf("Card: %d\n", deck[dealer_card2].value);
					}
					else if(deck[dealer_card2].card_face == KING)
					{
						printf("Card: KING\n");
					}
					else if(deck[dealer_card2].card_face == QUEEN)
					{
						printf("Card: QUEEN\n");
					}
					else if(deck[dealer_card2].card_face == JACK)
					{
						printf("Card: JACK\n");
					}
					else if(deck[dealer_card2].card_face == ACE)
					{
						printf("Card: ACE\n");
					}
					
					printf("Dealer's total is %d\n", dealer_total);	                   // dealer's total
					
					while((dealer_total < 17) && (player_total < 22))				   // if the dealer must hit
					{
						printf("Dealer must hit...\nDealer dealt:\n");
						if(deck[counter].card_face == NO_FACE)
						{
							printf("Card: %d\n", deck[counter].value);
							dealer_total =  dealer_total + deck[counter].value;
						}
						if(deck[counter].card_face == KING)
						{
							printf("Card: KING\n");
							dealer_total = dealer_total + 10;
						}
						else if(deck[counter].card_face == QUEEN)
						{
							printf("Card: QUEEN\n");
							dealer_total = dealer_total + 10;
						}
						else if(deck[counter].card_face == JACK)
						{
							printf("Card: JACK\n");
							dealer_total = dealer_total + 10;
						}
						else if(deck[counter].card_face == ACE)
						{
							printf("Card: ACE\n");
							dealer_aces++;
							if((dealer_total + 11 )> 21)
							{
								dealer_total = dealer_total + 1;
							}
							else
							{
								dealer_total = dealer_total + 11;
							}
						}
						if((dealer_aces > 0) && (dealer_total > 21))
						{
							dealer_total = dealer_total - 10;
							dealer_aces = 0;
						}
						printf("Dealer's new total is %d\n", dealer_total);
						counter++;
						if(counter == 52)
						{
							shuffle(deck);
							counter = 0;
							printf("The cards have been shuffled...\n");
						}
					}		
				}
		
		
				if(dealer_total == player_total)							// the results of the hand and the adjustment of the bankroll
				{
					printf("\nHand is a push\n\n");
				}
				else if((dealer_total < player_total) && (player_total < 22))
				{
					printf("\nYou Win!\n\n");
					bankroll = bankroll + bet;
				}
				else if((dealer_total > player_total) && (dealer_total < 22))
				{
					printf("You Lose!\n\n");
					bankroll = bankroll - bet;
				}
				else if(player_total > 21)
				{
					printf("\nYou Lose!\n\n");
					bankroll = bankroll - bet;
				}
				else if(dealer_total > 21)
				{
					printf("\n\nDEALER BUSTS!");
					printf("\nYou Win!\n\n");
					bankroll = bankroll + bet;
				}
				player_total = 0;    //resets everything for next loop
				dealer_total = 0;
				player_aces  = 0;
				dealer_aces  = 0;
				printf("What amount would you like to bet?  Current bankroll is $%d\n", bankroll);
				scanf("%d", &bet);
			}
		}							
	}
}
	

