#include "game.h"

//#define FunctionLog
int Game_Init()
{
	int result;
	DebugFile=CreateFile("debug.log",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	#ifdef FunctionLog
	DebugString("SetupDirectDraw()\n");
	#endif
	SetupDirectDraw();
	#ifdef FunctionLog
	DebugString("LoadSpriteDefs()\n");
	#endif
	LoadSpriteDefs();

	#ifdef FunctionLog
	DebugString("LoadLevel()\n");
	#endif
	if(LoadLevel())
		{
			DebugString("LoadLevel() failed...exiting\n");
			PostQuitMessage(0);
			return 1;
		}

	#ifdef FunctionLog
	DebugString("LoadBlocks()\n");
	#endif
	LoadBlocks();
	#ifdef FunctionLog
	DebugString("LoadSprites()\n");
	#endif
	LoadSprites();
	#ifdef FunctionLog
	DebugString("LoadSystem()\n");
	#endif
	LoadSystem();
	#ifdef FunctionLog
	DebugString("LoadBackground()\n");
	#endif
	//LoadBackground();
	#ifdef FunctionLog
	DebugString("PreComputeBlocks()\n");
	#endif
	PreComputeBlocks();

	CameraX=0;
	CameraY=0;
	CameraYOffset=0;

	srand(GetCurrentThreadId());
	Player.frametimer=GetTickCount();
	Player.health=5;
	Player.direction=1;
	bullets=NULL;
	#ifdef FunctionLog
	DebugString("DrawEntireBackground()\n");
	#endif
	DrawEntireBackground();
	//StartMusic();
	DebugString("Made it through Game_Init\n");
	return 0;
}

void Game_Main()
{
	char buffer[100];
	long time;

	timer=GetTickCount();
	#ifdef FunctionLog
	DebugString("CheckPlayerLandWater()\n");
	#endif
	Player.CheckLandWater();
	#ifdef FunctionLog
	DebugString("ProcessInput()\n");
	#endif
	ProcessInput();
//	ProcessPhysics();
    #ifdef FunctionLog
	DebugString("UpdatePlayer()\n");
	#endif
	Player.Update();

	#ifdef FunctionLog
	DebugString("HandlePlayerCollisions()\n");
	#endif
	Player.HandleCollisions();

	#ifdef FunctionLog
	DebugString("UpdatePlatforms()\n");
	#endif
	UpdatePlatforms();
	#ifdef FunctionLog
	DebugString("UpdateSprites()\n");
	#endif
	UpdateSprites();
	#ifdef FunctionLog
	DebugString("UpdateSwitches()\n");
	#endif
	UpdateSwitches();
	#ifdef FunctionLog
	DebugString("UpdateCameraPosition()\n");
	#endif
	UpdateCameraPosition();
	#ifdef FunctionLog
	DebugString("UpdateBullets()\n");
	#endif
	UpdateBullets();
	#ifdef FunctionLog
	DebugString("CheckBulletCollisions()\n");
	#endif
	CheckBulletCollisions();

	#ifdef FunctionLog
	DebugString("DrawBackground()\n");
	#endif
	DrawBackground();

	#ifdef FunctionLog
	DebugString("DrawSwitches()\n");
	#endif
	DrawSwitches();
	#ifdef FunctionLog
	DebugString("DrawPlatforms()\n");
	#endif
	DrawPlatforms();

	#ifdef FunctionLog
	DebugString("DrawSprites()\n");
	#endif
	DrawSprites();


	#ifdef FunctionLog
	DebugString("DrawPlayer()\n");
	#endif
	Player.Draw();


	#ifdef FunctionLog
	DebugString("DrawBullets()\n");
	#endif
	DrawBullets();
	#ifdef FunctionLog
	DebugString("DrawChains()\n");
	#endif
	DrawChains();

	#ifdef FunctionLog
	DebugString("RedrawFrontBlocks()\n");
	#endif
	//RedrawFrontBlocks();
	#ifdef FunctionLog
	DebugString("DrawStatusBar()\n");
	#endif
	DrawStatusBar();


	//DrawPlayerPositionPixel();

	#ifdef FunctionLog
	DebugString("FlipSurfaces()\n");
	#endif
	FlipSurfaces();

	#ifdef FunctionLog
	DebugString("Computing fps\n");
	#endif

	while(GetTickCount()<timer+30);


}

void Game_Shutdown()
{
	CleanupDirectDraw();
	//CleanupDirectMusic();
	CloseHandle(DebugFile);
}

