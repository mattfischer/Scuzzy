#include "debug.h"

void DebugString(char *buffer)
{
	DWORD dummy;

	WriteFile(DebugFile,buffer,strlen(buffer),&dummy,NULL);
}

void DrawPlayerPositionPixel()
{
	DDSURFACEDESC ddsDesc;

	ZeroMemory(&ddsDesc,sizeof(ddsDesc));

	ddsDesc.dwSize=sizeof(ddsDesc);

	IDirectDrawSurface_Lock(lpDDSBack,NULL,&ddsDesc,DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,NULL);

	*((UCHAR*)ddsDesc.lpSurface+(Player.y-(CameraY-CameraYOffset))*ddsDesc.lPitch+Player.x-CameraX)=66;

	IDirectDrawSurface_Unlock(lpDDSBack,NULL);
}

