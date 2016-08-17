#include <windows.h>
#include <ddraw.h>
#include "level.h"
#include "global.h"

extern LPDIRECTDRAWSURFACE lpDDSPrimary;
extern LPDIRECTDRAWSURFACE lpDDSBlocks;
extern LPDIRECTDRAWSURFACE lpDDSBack;
extern LPDIRECTDRAWSURFACE lpDDSBack2;
extern LPDIRECTDRAWSURFACE lpDDSSprites;
extern LPDIRECTDRAWSURFACE lpDDSSystem;
extern LPDIRECTDRAWSURFACE lpDDSBackground;
extern UCHAR *level;
extern UCHAR *physics;
extern int LevelX;
extern int LevelY;
extern struct Sprite_Def *spritedefs;
extern int NumSprites;
extern struct Sprite_Info *Sprites;
extern Player_Info Player;
extern struct Bullet *bullets;

extern struct Chain *Chains;
extern struct Platform *Platforms;
extern int NumPlatforms;
extern int NumChains;
extern struct Switch *Switches;
extern int NumSwitches;
extern int *Baseframes;

extern struct Sprite_Info *GetSprite(int);
extern void ClearSurface(LPDIRECTDRAWSURFACE);
extern void DrawPlayer();
extern void DebugString(char*);
extern void DeleteBullet(struct Bullet*);
extern int CanRectMove(int,int,int,int,int,int);
extern void MoveRect(int*,int*,int,int,int,int,int);
extern void HandleBadResult(int,int);

long CameraX;
long CameraY;
long OldCameraX;
long OldCameraY;
int  Score=0;
int  Realscore=0;
int  CameraYOffset;
RECT PreComp[255];

void PreComputeBlocks();
void BlitBlock();
void BlitSprite();
void DrawParallaxBackground();
void BlitBackground();
void DrawSprites();
void DrawChains();
void DrawPlatforms();
void DrawSwitches();
void UpdateCameraPosition();
void RedrawFrontBlocks();
void DrawStatusBar();
void DrawHealthBar();
void DrawCharacter(int,int,int,char);
void DrawString(int,int,int,char*);
void DrawScore();
void DrawBullets();
void DrawAmmo();
void DrawBulletType();
void DrawBackground();

