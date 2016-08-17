#include <windows.h>
#include <ddraw.h>
#include "global.h"

extern HANDLE DebugFile;
extern struct Player_Info Player;
extern LPDIRECTDRAWSURFACE lpDDSBack;
extern int CameraX, CameraY, CameraYOffset;

void DebugString(char*);
void DrawPlayerPositionPixel();

