#include <windows.h>
#include <ddraw.h>
#include <stdlib.h>
#include <malloc.h>
#include "global.h"
#include <math.h>
#include "level.h"

extern long CameraX;
extern long CameraY;
extern long OldCameraX;
extern long OldCameraY;
extern struct Sprite_Info *Sprites;
extern int NumBullets;
extern struct Sprite_Def *spritedefs;
extern HANDLE DebugFile;

Player_Info Player;
UCHAR *level;
UCHAR *physics;
int LevelX;
int LevelY;
int NumSprites;
int *Baseframes;
int NumBaseframes;
struct Chain *Chains;
int NumChains;
int NumSets;
int NumPlatforms;
struct Platform *Platforms;
struct Switch *Switches;
int NumSwitches;
struct Animset *Sets;
struct Pipe *Pipes;
int NumPipes;
int SetStart[3]={0,4,6};
struct Animset EmptySet={0,0,0,0,0};

extern DebugString(char*);
int LoadLevel();

