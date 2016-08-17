#include <windows.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include "global.h"
#include "macros.h"

struct Sprite_Def *spritedefs;
struct Bullet *bullets;
int NumSpriteDefs;
int NumBullets;
struct Sprite_Info *Sprites;

extern int *Baseframes;
extern struct Animset *Sets;
extern struct Switch *Switches;
extern int NumSwitches;
extern int UpFlag;
extern struct Player_Info Player;
extern int NumPlatforms;
extern struct Platform *Platforms;
extern long CameraX;
extern long CameraY;
extern int  CameraYOffset;
extern UCHAR *physics;
extern int LevelX;
extern int NumSprites;

void LoadSpriteDefs();
void UpdateSprites();
void UpdateBullets();
void CreateBullet(int,int,int,int,int);
void CheckBulletCollisions();
struct Sprite_Info *GetSprite(int);
void DeleteSprite(struct Sprite_Info*);
struct Bullet *GetBullet(int);
void UpdatePlatforms();
void UpdateSwitches();
int HitSwitch();

extern int RectsOverlap(int,int,int,int,int,int,int,int);
extern void MoveRect(int*,int*,int,int,int,int,int);
extern int CanRectMove(int,int,int,int,int,int);
extern void DebugString(char*);
extern void DeleteBullet(Bullet*);
