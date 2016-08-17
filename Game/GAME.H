#include <windows.h>
#include <stdlib.h>

#include "macros.h"
#include "level.h"
#include "global.h"

int Game_Init();
void Game_Main();
void Game_Shutdown();

extern void SetupDirectDraw();
extern void LoadSpriteDefs();
extern int LoadLevel();
extern void LoadBlocks();
extern void LoadSprites();
extern void LoadSystem();
extern void LoadBackground();
extern void PreComputeBlocks();
extern void DrawEntireBackground();
extern void DebugString(char*);
extern void CheckPlayerLandWater();
extern void ProcessInput();
extern void UpdatePlayer();
extern void HandlePlayerCollisions();
extern void UpdatePlatforms();
extern void UpdateSprites();
extern void UpdateSwitches();
extern void UpdateCameraPosition();
extern void UpdateBullets();
extern void CheckBulletCollisions();
extern void DrawBackground();
extern void DrawSwitches();
extern void DrawPlatforms();
extern void DrawSprites();
extern void DrawPlayer();
extern void DrawBullets();
extern void DrawChains();
extern void RedrawFrontBlocks();
extern void DrawStatusBar();
extern void FlipSurfaces();
extern void CleanupDirectDraw();
extern void StartMusic();
extern void CleanupDirectMusic();

unsigned long timer;
DWORD dummy;
HANDLE DebugFile;

extern long CameraX;
extern long CameraY;
extern int CameraYOffset;
extern Player_Info Player;
extern struct Bullet *bullets;

