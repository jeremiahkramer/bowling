/***************************
 ** Program: bowling
 ** Author: Jeremiah Kramer
 ** Date: 2/26/17
 ** Description: This program is the programming behind a bowling game.
 ** Input: Names of players, enter (to bowl), and integers.
 ** Output: How much the player bowled, the scoreboard/ frame, winner or the game.
 **************************/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

/***************************
 ** Function: num_players
 ** Description: gets the number of players for the game
 ** Parameters: *players
 ** Pre- Conditions: none
 ** Post- Conditions: begin_game, get_players_name
 ** Return: none
 **************************/
void num_players(int *players){

	cout << "How many players? (1-5) ";
	cin >> *players; //this is a pointer so we can use throughout code
	if (*players > 5 || *players < 1){ //has to be between 1-5 players
		cout << "Try again." << endl;
		num_players(players);
	}	
	else
		cout << endl;
}

/***************************
 ** Function: get_players_name_calc
 ** Description: checks if length of name is longer than 7 characters
 ** Parameters: *players, player_name[]
 ** Pre- Conditions: a prompt that tells the user to input name
 ** Post- Conditions: get_players_name
 ** Return: none
 **************************/
void get_players_name_calc(int *players, char player_name[]){

	cin >> player_name;
	
	if(strlen(player_name) > 7){ //makes sure name isn't longer than 7 characters
		cout << "retry" << endl;
		get_players_name_calc(players, player_name);
	}		
}

/***************************
 ** Function: get_players_name
 ** Description: gets the players name using c style strings
 ** Parameters: *players, player(1,2,3,4,5)_name[]
 ** Pre- Conditions: get_players_name_calc, num_players
 ** Post- Conditions: begin_game
 ** Return: none
 **************************/
void get_players_name(int *players, char player1_name[], char player2_name[], char player3_name[], char player4_name[], char player5_name[]){

	for (int i = 1; i <= *players; i++){ //loop player number
		cout << "Enter Player " << i << " 's name (up to 7 characters long): ";
		if (i == 1)
			get_players_name_calc(players, player1_name);
		if (i == 2)
			get_players_name_calc(players, player2_name);
		if (i == 3)
			get_players_name_calc(players, player3_name);
		if (i == 4)
			get_players_name_calc(players, player4_name);
		if (i == 5)
			get_players_name_calc(players, player5_name);
	}
	cout << endl;
}

/***************************
 ** Function: begin_game
 ** Description: calls two functions to set up the game (used for simplicity)
 ** Parameters: *players, player(1,2,3,4,5)_name
 ** Pre- Conditions: num_players, get_players_name
 ** Post- Conditions: main
 ** Return: none
 **************************/
void begin_game(int *players, char player1_name[], char player2_name[], char player3_name[], char player4_name[], char player5_name[]){

	num_players(players);
	get_players_name(players, player1_name, player2_name, player3_name, player4_name, player5_name);

}	

/***************************
 ** Function: bowl
 ** Description: picks a random number between 10 
 ** Parameters: *score, *current_player
 ** Pre- Conditions: bowl_calc
 ** Post- Conditions: score_array[][] and related functions
 ** Return: none
 **************************/
void bowl(int *score, int *current_player){

	cout << "Player " << *current_player << " , press enter to bowl: ";
	cin.get();
	if (cin.get() == '\n'){ //user press enter
		srand(time(NULL));
		*score = rand() % (11 - *score); //for second bowl, you can't get higher than 10 - score on first bowl
	}
	else {
		cout << "Wrong key, try again." << endl; //if not enter, try again
		bowl(score, current_player);
	}
}

/***************************
 ** Function: bowl_calc
 ** Description: tells user what they bowled
 ** Parameters: *score, *current_player
 ** Pre- Conditions: bowl
 ** Post- Conditions: none
 ** Return: none
 **************************/
void bowl_calc(int *score, int *current_player){

	bowl(score, current_player); //calls bowl to randomize number
	if (*score == 0)
		cout << "Too bad! Gutter ball, 0 pins." << endl;
	else if (*score == 10)
		cout << "Nice! You got a strike, 10 pins." << endl;			//checks what they bowled, and prints it out
	else if (*score == 1)
		cout << "You knocked down " << *score << " pin." << endl;
	else
		cout << "You knocked down " << *score << " pins." << endl;
}


/***************************
 ** Function: top_frame
 ** Description: prints the top of scoreboard
 ** Parameters: none
 ** Pre- Conditions:none 
 ** Post- Conditions: each_score
 ** Return: none
 **************************/
void top_frame(){

	cout << "Name		|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   10   | Total" << endl;

}

/***************************
 ** Function: total_score
 ** Description: calculates the total score, including if the user got a spare or a strike
 ** Parameters: *a, *tot_score, score_array[][21], z
 ** Pre- Conditions: score
 ** Post- Conditions: frame_gen
 ** Return: none
 **************************/
void total_score(int *a, int *tot_score, int score_array[][21], int z){

	//this calculates the total score
	*tot_score = score_array[z][0] + score_array[z][1] + score_array[z][2] + score_array[z][3] + score_array[z][4] + score_array[z][5] + score_array[z][6] + score_array[z][7] +score_array[z][8] + score_array[z][9] + score_array[z][10] + score_array[z][11] + score_array[z][12] + score_array[z][13] + score_array[z][14] + score_array[z][15] + score_array[z][16] + score_array[z][17] + score_array[z][18] + score_array[z][19] + score_array[z][20];

	for (int q = 0; q < 21; q++){
		if (score_array[z][q] == 10){ //if the user got a strike
			*tot_score += (score_array[z][q + 2] + score_array[z][q + 3]); //add next two bowls
			if (score_array[z][q + 2] == 10){ //if they got another strike (two in a row)
				*tot_score += score_array[z][q + 4];
			}
		}
		if ((score_array[z][q] + score_array[z][q + 1]) == 10 && (q % 2 == 0)){ //if the user got a spare
			*tot_score += (score_array[z][q + 1]); //add next bowl
		}
	}
	
}

/***************************
 ** Function: player_frame_gen
 ** Description: prints out the frame/ socreboard for that specified player
 ** Parameters: player_name[], *tot_score, score_array[][21], *a, z
 ** Pre- Conditions: total_socre
 ** Post- Conditions: player_frame_finish
 ** Return: none
 **************************/
void player_frame_gen(char player_name[], int *tot_score, int score_array[][21], int *a, int z){

	total_score(a, tot_score, score_array, z);

	//this prints each bowl within each frame
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	cout << player_name << "		| " << score_array[z][0] << "  " << score_array[z][1] << " | " << score_array[z][2] << "  " << score_array[z][3] << " | " << score_array[z][4] << "  " << score_array[z][5] << " | " << score_array[z][6] << "  " << score_array[z][7] << " | " << score_array[z][8] << "  " << score_array[z][9] << " | " << score_array[z][10] << "  " << score_array[z][11] << " | " << score_array[z][12] << "  " << score_array[z][13] << " | " << score_array[z][14] << "  " << score_array[z][15] << " | " << score_array[z][16] << "  " << score_array[z][17] << " |  " << score_array[z][18] << " " << score_array[z][19] << " " << score_array[z][20] << " |  " << endl;

	cout << "		|   " << (score_array[z][0] + score_array[z][1]) << "  |   " << (score_array[z][2] + score_array[z][3]) << "  |   " << (score_array[z][4] + score_array[z][5]) << "  |   " << (score_array[z][6] + score_array[z][7]) << "  |   " << (score_array[z][8] + score_array[z][9]) << "  |   " << (score_array[z][10] + score_array[z][11]) << "  |   " << (score_array[z][12] + score_array[z][13]) << "  |   " << (score_array[z][14] + score_array[z][15]) << "  |   " << (score_array[z][16] + score_array[z][17]) << "  |    " << (score_array[z][18] + score_array[z][19] + score_array[z][20]) << "   |   " << *tot_score << endl;
	//this prints the sum of the two bowls in that frame
	//note: I did it this way to keep it formatted as best possible


}

/***************************
 ** Function: player_frame_finish
 ** Description: determines the size of the board, if you will (i.e. if players == 3, the scoreboard will contain space for 3 players
 ** Parameters: *players, player(1,2,3,4,5)_name[], *score, *p(1,2,3,4,5)_score, *a, score_array[][21]
 ** Pre- Conditions: player_frame_gen and num_players
 ** Post- Conditions: each_score
 ** Return: none
 **************************/
void player_frame_finish(int *players, char player1_name[], char player2_name[], char player3_name[], char player4_name[], char player5_name[], int *score, int *p1_score, int *p2_score, int *p3_score, int *p4_score, int *p5_score, int *a, int score_array[][21]){


	//fairly self- explanatory but it determines size of board
	
	if (*players == 1){
		player_frame_gen(player1_name, p1_score, score_array, a, 0);
	}
	if (*players == 2){
		player_frame_gen(player1_name, p1_score, score_array, a, 0);
		player_frame_gen(player2_name, p2_score, score_array, a, 1);
	}
	if (*players == 3){
		player_frame_gen(player1_name, p1_score, score_array, a, 0);
		player_frame_gen(player2_name, p2_score, score_array, a, 1);
		player_frame_gen(player3_name, p3_score, score_array, a, 2);
	}
	if (*players == 4){
		player_frame_gen(player1_name, p1_score, score_array, a, 0);
		player_frame_gen(player2_name, p2_score, score_array, a, 1);
		player_frame_gen(player3_name, p3_score, score_array, a, 2);
		player_frame_gen(player4_name, p4_score, score_array, a, 3);
	}
	if (*players == 5){
		player_frame_gen(player1_name, p1_score, score_array, a, 0);
		player_frame_gen(player2_name, p2_score, score_array, a, 1);
		player_frame_gen(player3_name, p3_score, score_array, a, 2);
		player_frame_gen(player4_name, p4_score, score_array, a, 3);
		player_frame_gen(player5_name, p5_score, score_array, a, 4);
	}
}


/***************************
 ** Function: each_score
 ** Description: goes thorugh all the iterations of the 2d array (i.e. allows the user(s) to play the game, bowl, and prints out the updated scoreboard)
 ** Parameters: *players, *current_player, *score, player(1,2,3,4,5)_name, *p(1,2,3,4,5)_score, score_array[][21], *a
 ** Pre- Conditions: bowl_calc, score_array, top_frame, player_frame_finish
 ** Post- Conditions: current_p
 ** Return: none
 **************************/
void each_score(int *players, int *current_player, int *score, char player1_name[], char player2_name[], char player3_name[], char player4_name[], char player5_name[], int *p1_score, int *p2_score, int *p3_score, int *p4_score, int *p5_score, int score_array[][21], int *a){


	for (int i = 0; i < *players; i++){ //num rows = num players
		for (int j = 0; j < 21; j++){ //21 bowls
			bowl_calc(score, current_player); //calls bowl_calc that prompts user to bowl and will print out how many pins they got
			score_array[*a][j] = *score; //at each iteration = *score
			top_frame(); //top of board
			player_frame_finish(players, player1_name, player2_name, player3_name, player4_name, player5_name, score, p1_score, p2_score, p3_score, p4_score, p5_score, a, score_array);	//rest of board
		}
		*a += 1; //change row
		*current_player += 1; //next player
	}
}



/***************************
 ** Function: current_p
 ** Description: calls each_score, but resets/ sets *current_player = 1 and *score = 0
 ** Parameters: *players, *current_player, *score, player(1,2,3,4,5)_name, *p(1,2,3,4,5)_score, score_array[][21], *a
 ** Pre- Conditions: each_score
 ** Post- Conditions: none/ main
 ** Return: none
 **************************/
void current_p(int *players, int *current_player, int *score, char player1_name[], char player2_name[], char player3_name[], char player4_name[], char player5_name[], int *p1_score, int *p2_score, int *p3_score, int *p4_score, int *p5_score, int score_array[][21], int *a){

	*current_player = 1; //set current_player = 1

	*score = 0; //reset *score = 0

	each_score(players, current_player, score, player1_name, player2_name, player3_name, player4_name, player5_name, p1_score, p2_score, p3_score, p4_score, p5_score, score_array, a);
	
}

/***************************
 ** Function: winner
 ** Description: determines winner by using if/ else statements to check players total score
 ** Parameters: player(1,2,3,4,5)_name[], *p(1,2,3,4,5)_score
 ** Pre- Conditions: names of players and their score
 ** Post- Conditions: none/ main
 ** Return: none
 **************************/
void winner(char player1_name[], char player2_name[], char player3_name[], char player4_name[], char player5_name[], int *p1_score, int *p2_score, int *p3_score, int *p4_score, int *p5_score){

	if (*p1_score > *p2_score && *p1_score > *p3_score && *p1_score > *p4_score && *p1_score > *p5_score){
		cout << player1_name << " is the Winner!" << endl; //p1 wins
	}
	else if (*p2_score > *p1_score && *p2_score > *p3_score && *p2_score > *p4_score && *p2_score > *p5_score){
		cout << player2_name << " is the Winner!" << endl; //p2 wins
	}
	else if (*p3_score > *p2_score && *p3_score > *p1_score && *p3_score > *p4_score && *p3_score > *p5_score){
		cout << player3_name << " is the Winner!" << endl; //p3 wins
	}
	else if (*p4_score > *p2_score && *p4_score > *p3_score && *p4_score > *p1_score && *p4_score > *p5_score){
		cout << player4_name << " is the Winner!" << endl; //p4 wins
	}
	else if (*p5_score > *p2_score && *p5_score > *p3_score && *p5_score > *p4_score && *p5_score > *p1_score){
		cout << player5_name << " is the Winner!" << endl; //p5 wins
	}
	else {
		cout << "Tie!" << endl; //if any or all tie, it's a tie
	}
}

/***************************
 ** Function: play_again
 ** Description: prompts user to play again, and returns their answer
 ** Parameters: again
 ** Pre- Conditions: none
 ** Post- Conditions: in main (while loop)
 ** Return: again (char)
 **************************/
char play_again(char again){

	cout << "Do you want to play again? (y/n): ";
	cin >> again;
		if (again == 'y') //if y return y
			return again;
		if (again == 'n') //if n return n
			return again;
		else if (again != 'y' || again != 'n'){ //if they aren't y//n, retry
			cout << "retry" << endl;
			play_again(again);
		}

	return again;
}




int main(){

	int players, gen_score, current_player;
	char player1_name[7], player2_name[7], player3_name[7], player4_name[7], player5_name[7], again = 'y';


	//loop until user inputs 'n'
	while (again == 'y'){
	
	int p1_score = 0, p2_score = 0, p3_score = 0, p4_score = 0, p5_score = 0, score_array[5][21] = {0}, a = 0;

	begin_game(&players, player1_name, player2_name, player3_name, player4_name, player5_name);


	current_p(&players, &current_player, &gen_score, player1_name, player2_name, player3_name, player4_name, player5_name, &p1_score, &p2_score, &p3_score, &p4_score, &p5_score, score_array, &a);
	
	winner(player1_name, player2_name, player3_name, player4_name, player5_name, &p1_score, &p2_score, &p3_score, &p4_score, &p5_score);

	again = play_again(again);
	}

	return 0; 
}
