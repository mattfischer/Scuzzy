#include <windows.h>
#include <ddraw.h>
#include <stdlib.h>

int SetupDirectDraw();
void CleanupDirectDraw();
void HandleBadResult(int,int);
void ClearSurface(LPDIRECTDRAWSURFACE);
void FlipSurfaces();
void LoadBlocks();
void LoadSprites();
void LoadSystem();
void LoadBackground();

extern HWND hMainWindow;
extern HANDLE DebugFile;

char buff[100];
LPDIRECTDRAW lpDD;
LPDIRECTDRAWSURFACE lpDDSPrimary;
LPDIRECTDRAWSURFACE lpDDSBack;
LPDIRECTDRAWSURFACE lpDDSBack2;
LPDIRECTDRAWSURFACE lpDDSBlocks;
LPDIRECTDRAWSURFACE lpDDSSprites;
LPDIRECTDRAWSURFACE lpDDSSystem;
LPDIRECTDRAWPALETTE lpDDPal;
LPDIRECTDRAWCLIPPER lpDDClipper;
LPDIRECTDRAWSURFACE lpDDSBackground;

