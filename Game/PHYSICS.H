#include <windows.h>
#include <stdlib.h>
#include <math.h>

#include "level.h"
#include "global.h"

extern Player_Info Player;
extern int LevelX;
extern int LevelY;
extern UCHAR *physics;

void MoveRect(int*,int*,int,int,int,int,int);
int CanRectMove(int,int,int,int,int,int);
int RectsOverlap(int,int,int,int,int,int,int,int);

