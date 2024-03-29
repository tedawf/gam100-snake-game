#include "global.h"
#include "player.h"
#include "map.h"

// Euler method calculation for movement
static double euler = 0.0f;
static double velocity = 0.005;

int main(void)
{
	// Init console
	Console_Init();
	Random_Init();
	Console_SetTitle("Snake Game");
	Console_SetSquareFont();
	Console_SetWindowedMode(GAME_WIDTH + 1, GAME_HEIGHT + 1 + CONSOLE_HEIGHT, true);
	Console_SetCursorVisibility(0);
	bGameIsRunning = 1;

	// initialises game
	initGame();

	// moves the game towards the game menu
	StateMachine_ChangeState(State_MainMenu);
	// checks if the game state has been changed, if so load that change
	while (bGameIsRunning)
	{
	StateMachine_StartFrame();
	}
	// Shutdown game
	Console_CleanUp();

	return 0;
}

// Initialise the player and map
void initGame()
{
	// Init player
	player_Init();
	map_Init();
}

// The game loop
void runGame()
{
	// Frame Time calculation, DeltaTime      
	Clock_GameLoopStart();

	// Number of pixels to move per second
	euler = velocity * Clock_GetDeltaTime();

	// First, we record player inputs
	player_GetInput();

	// Get all objects to update their positions using SetRenderBuffer()
	player_Update(euler);
	map_Update();
	//food_Update();
}

// Forces the program to exit
void exitGame()
{
	bGameIsRunning = 0;
}
