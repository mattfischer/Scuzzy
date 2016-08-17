#include <windows.h>
#include "global.h"
#include "macros.h"

extern Player_Info Player;
extern long CameraX;
extern long CameraY;
extern struct Sprite_Def *spritedefs;
extern int CameraYOffset;
extern int NumSprites;
extern int NumChains;
extern struct Chain *Chains;
extern int NumPipes;
extern struct Pipe *Pipes;
extern long ControlTimer;
extern int LevelX;
extern int LevelY;
extern UCHAR *physics;
extern void BlitSprite(int,int,int);
extern int CanRectMove(int,int,int,int,int,int);
extern void MoveRect(int*,int*,int,int,int,int,int);
extern int RectsOverlap(int,int,int,int,int,int,int,int);
extern struct Sprite_Info *GetSprite(int);
extern int *Baseframes;
extern int NumPlatforms;
extern int Score;
extern struct Platform *Platforms;
extern struct Animset EmptySet;
extern struct Animset *Sets;
extern struct Sprite_Info *Sprites;

extern void DeleteSprite(struct Sprite_Info*);
extern void CreateBullet(int,int,int,int,int);
extern void DebugString(char*);

int SnapResolution=15;
char buffer[100];

void DrawPlayer();
void UpdatePlayer();
void CheckPlayerLandWater();
void HandlePlayerCollisions();
void DoDamage();
void FireBullet();
void CreateFloatingScore(int,int,int);
