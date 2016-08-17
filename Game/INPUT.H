#include <windows.h>
#include <math.h>
#include "macros.h"
#include "level.h"
#include "global.h"

extern int LevelX;
extern int LevelY;
extern long CameraX;
extern long CameraY;
extern struct Sprite_Info *Sprites;
extern Player_Info Player;
extern int CameraYOffset;
extern struct Sprite_Def *spritedefs;

extern void FireBullet();
extern int CanRectMove(int,int,int,int,int,int);
extern int HitSwitch();

int ControlFlag=0;
int SpaceFlag=0;
int UpFlag=0;
long ControlTimer=-1;
long VertOffsetTimer=-1;

void ProcessInput();

