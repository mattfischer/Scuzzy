#include "ddraw.h"

int SetupDirectDraw()
 {


	HRESULT ddrval;
	DDSURFACEDESC ddSD;
	DDSCAPS ddsCaps;
	UCHAR   *rgndata;
	RECT	ClipRect;
	RGNDATAHEADER rdh;

	DDCOLORKEY ddck;

	ddrval=DirectDrawCreate(NULL,&lpDD,NULL);

	if(ddrval!=DD_OK)
		{
			HandleBadResult(ddrval,1);
			return 0;
		}

	ddrval=lpDD->SetCooperativeLevel(hMainWindow,DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_NOWINDOWCHANGES);

	if(ddrval!=DD_OK)
		{
			HandleBadResult(ddrval,2);
			return 0;
		}
	ddrval=lpDD->SetDisplayMode(640,480,32);

	if(ddrval!=DD_OK)
		{
				HandleBadResult(ddrval,3);
				return 0;
		}
	ZeroMemory((LPVOID)&ddSD,(DWORD)sizeof(ddSD));
	ddSD.dwSize=sizeof(ddSD);
	ddSD.dwFlags=DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddSD.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP;
	ddSD.dwBackBufferCount=1;


	ddrval=lpDD->CreateSurface(&ddSD,&lpDDSPrimary,NULL);

	if(ddrval!=DD_OK)
		{
				HandleBadResult(ddrval,4);
				return 0;
		}
	ddsCaps.dwCaps=DDSCAPS_BACKBUFFER;

	ddrval=lpDDSPrimary->GetAttachedSurface(&ddsCaps,&lpDDSBack);

	if(ddrval!=DD_OK)
		{

			HandleBadResult(ddrval,5);
			return 0;
		}



	ZeroMemory((LPVOID)&ddSD,(DWORD)sizeof(ddSD));
	ddSD.dwSize=sizeof(ddSD);
	ddSD.dwFlags=DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddSD.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN;
	ddSD.dwWidth=640;
	ddSD.dwHeight=480;

	ddrval=lpDD->CreateSurface(&ddSD,&lpDDSBack2,NULL);

	if(ddrval!=DD_OK)
		{
			HandleBadResult(ddrval,7);
			return 0;
		}



	ZeroMemory((LPVOID)&ddSD,(DWORD)sizeof(ddSD));
	ddSD.dwSize=sizeof(ddSD);
	ddSD.dwFlags=DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddSD.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN;
	ddSD.dwWidth=640;
	ddSD.dwHeight=480;

	ddrval=lpDD->CreateSurface(&ddSD,&lpDDSBlocks,NULL);

	if(ddrval!=DD_OK)
		{
			HandleBadResult(ddrval,7);
			return 0;
		}

	ZeroMemory((LPVOID)&ddSD,(DWORD)sizeof(ddSD));
	ddSD.dwSize=sizeof(ddSD);
	ddSD.dwFlags=DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddSD.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN;
	ddSD.dwWidth=640;
	ddSD.dwHeight=480;

	ddrval=lpDD->CreateSurface(&ddSD,&lpDDSSprites,NULL);

	if(ddrval!=DD_OK)
		{
			HandleBadResult(ddrval,7);
			return 0;
		}


	ZeroMemory((LPVOID)&ddSD,(DWORD)sizeof(ddSD));
	ddSD.dwSize=sizeof(ddSD);
	ddSD.dwFlags=DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddSD.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN;
	ddSD.dwWidth=640;
	ddSD.dwHeight=480;

	ddrval=lpDD->CreateSurface(&ddSD,&lpDDSSystem,NULL);

	ZeroMemory((LPVOID)&ddSD,(DWORD)sizeof(ddSD));
	ddSD.dwSize=sizeof(ddSD);
	ddSD.dwFlags=DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddSD.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN;
	ddSD.dwWidth=640;
	ddSD.dwHeight=480;

	ddrval=lpDD->CreateSurface(&ddSD,&lpDDSBackground,NULL);

	if(ddrval!=DD_OK)
		{
			HandleBadResult(ddrval,7);
			return 0;
		}

	lpDD->CreateClipper(0,&lpDDClipper,NULL);

	ClipRect.top=0;
	ClipRect.bottom=480;
	ClipRect.left=0;
	ClipRect.right=640;

	rgndata=(UCHAR*)malloc(sizeof(RGNDATAHEADER)+sizeof(RECT));
	rdh.dwSize=sizeof(RGNDATAHEADER);
	rdh.iType=RDH_RECTANGLES;
	rdh.nCount=1;
	rdh.nRgnSize=0;
	rdh.rcBound=ClipRect;
	memcpy(rgndata,&rdh,sizeof(RGNDATAHEADER));
	memcpy(rgndata+sizeof(RGNDATAHEADER),&ClipRect,sizeof(RECT));

	lpDDClipper->SetClipList((RGNDATA*)rgndata,0);
	lpDDSBack->SetClipper(lpDDClipper);

	ddck.dwColorSpaceLowValue=0;
	ddck.dwColorSpaceHighValue=0;

	lpDDSSprites->SetColorKey(DDCKEY_SRCBLT,&ddck);
	lpDDSSystem->SetColorKey(DDCKEY_SRCBLT,&ddck);



	ClearSurface(lpDDSBack);


	FlipSurfaces();

	ClearSurface(lpDDSBack);




	return 1;

}


void CleanupDirectDraw()
{
	if(lpDD!=NULL)
		{
			if(lpDDSPrimary!=NULL)
				{
					lpDDSPrimary->Release();
					lpDDSPrimary=NULL;
				}
			if(lpDDSBack2!=NULL)
				{
					lpDDSBack2->Release();
					lpDDSBack2=NULL;
				}

			if(lpDDSBlocks!=NULL)
				{
					lpDDSBlocks->Release();
					lpDDSBlocks=NULL;
				}
			if(lpDDSSprites!=NULL)
				{
					lpDDSSprites->Release();
					lpDDSSprites=NULL;
				}
			if(lpDDSSystem!=NULL)
				{
					lpDDSSystem->Release();
					lpDDSSystem=NULL;
				}
			if(lpDDSBackground!=NULL)
				{
					lpDDSBackground->Release();
					lpDDSBackground=NULL;
				}

			lpDD->Release();
			lpDD=NULL;
		}
}

void HandleBadResult(int ddrval,int level)
{

	char buff2[100];
	wsprintf(buff2,"Level %i:",level);

	WriteFile(DebugFile,"Error:",6,(LPDWORD)buff,(LPOVERLAPPED)NULL);
	WriteFile(DebugFile,buff2,strlen(buff2),(LPDWORD)buff,(LPOVERLAPPED)NULL);

	switch(ddrval)
	{
		case DDERR_DCALREADYCREATED:
			WriteFile(DebugFile,"DC already created",18,(LPDWORD)buff,(LPOVERLAPPED)NULL);
			break;
		case DDERR_CANTCREATEDC:
			WriteFile(DebugFile,"Cant make DC",12,(LPDWORD)buff,(LPOVERLAPPED)NULL);
			break;
		case DDERR_DIRECTDRAWALREADYCREATED:
			WriteFile(DebugFile,"Already created",15,(LPDWORD)buff,(LPOVERLAPPED)NULL);
			break;

		case DDERR_INVALIDCAPS:
			WriteFile(DebugFile,"Invalid caps",12,(LPDWORD)buff,(LPOVERLAPPED)NULL);
			break;
		case DDERR_INVALIDPARAMS:
			WriteFile(DebugFile,"Invalid params",14,(LPDWORD)buff,(LPOVERLAPPED)NULL);
			break;
		case DDERR_INVALIDRECT:
			WriteFile(DebugFile,"Invalid rect\n",12,(LPDWORD)buff,(LPOVERLAPPED)NULL);
			break;

	}
}


void ClearSurface(LPDIRECTDRAWSURFACE Surface)
{
	DDBLTFX Fx;
	Fx.dwSize=sizeof(DDBLTFX);

	Fx.dwFillColor=0;

	Surface->Blt(NULL,NULL,NULL,DDBLT_COLORFILL,&Fx);

}


void FlipSurfaces()
{
	int ddrval;

					while(1)
						{

							ddrval=lpDDSPrimary->Flip(NULL,0);
							if(ddrval==DD_OK) break;
							if(ddrval==DDERR_SURFACELOST)
								{
									ddrval=lpDDSPrimary->Restore();
									if(ddrval==DD_OK) break;



								}
							if(ddrval!=DDERR_WASSTILLDRAWING) break;
						}

}


void LoadBlocks()
{
	HANDLE BitmapFile;
	DDSURFACEDESC ddsDesc;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	RGBQUAD          colors[256];
	DWORD			 dummy;
	int 			 y,x;
	UCHAR			 *data;
	UCHAR 			 tempdata[640];
	PALETTEENTRY	 entries[256];

	ZeroMemory(&ddsDesc,sizeof(ddsDesc));

	ddsDesc.dwSize=sizeof(ddsDesc);

	lpDDSBlocks->Lock(NULL,&ddsDesc,DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,NULL);

	BitmapFile=CreateFile("blocks.dat",GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
//	ReadFile(BitmapFile,&bmfh,sizeof(bmfh),&dummy,NULL);
//	ReadFile(BitmapFile,&bmih,sizeof(bmih),&dummy,NULL);
	//ReadFile(BitmapFile,&colors,sizeof(RGBQUAD)*256,&dummy,NULL);

	data=(UCHAR*)ddsDesc.lpSurface+ddsDesc.lPitch*479;
	for(y=0;y<480;y++)
		{
			for(x=0;x<4;x++)
				{
					ReadFile(BitmapFile,tempdata,640,&dummy,NULL);
					memcpy(data+640*x,tempdata,640);
				}


			data-=ddsDesc.lPitch;
		}

	lpDDSBlocks->Unlock(NULL);
	/*
	for(y=0;y<256;y++)
		{
			entries[y].peRed=colors[y].rgbRed;
			entries[y].peGreen=colors[y].rgbGreen;
			entries[y].peBlue=colors[y].rgbBlue;
			entries[y].peFlags=PC_NOCOLLAPSE;
		}

	lpDD->CreatePalette(DDPCAPS_8BIT | DDPCAPS_ALLOW256 | DDPCAPS_INITIALIZE,entries,&lpDDPal,NULL);
	lpDDSPrimary->SetPalette(lpDDPal);
*/
	CloseHandle(BitmapFile);
}

void LoadSprites()
{
	HANDLE BitmapFile;
	DDSURFACEDESC ddsDesc;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	RGBQUAD          colors[256];
	DWORD			 dummy;
	int 			 y,x;
	UCHAR			 *data;
	UCHAR 			 tempdata[640];
	PALETTEENTRY	 entries[256];


	ZeroMemory(&ddsDesc,sizeof(ddsDesc));

	ddsDesc.dwSize=sizeof(ddsDesc);

	lpDDSSprites->Lock(NULL,&ddsDesc,DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,NULL);

	BitmapFile=CreateFile("sprites.dat",GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
//	ReadFile(BitmapFile,&bmfh,sizeof(bmfh),&dummy,NULL);
//	ReadFile(BitmapFile,&bmih,sizeof(bmih),&dummy,NULL);
//	ReadFile(BitmapFile,&colors,sizeof(RGBQUAD)*256,&dummy,NULL);

	data=(UCHAR*)ddsDesc.lpSurface+ddsDesc.lPitch*479;
	for(y=0;y<480;y++)
		{
	for(x=0;x<4;x++)
				{
					ReadFile(BitmapFile,tempdata,640,&dummy,NULL);
					memcpy(data+640*x,tempdata,640);
				}

			data-=ddsDesc.lPitch;
/*			ReadFile(BitmapFile,tempdata,1920,&dummy,NULL);
			memcpy(data,tempdata,1920);
			data-=ddsDesc.lPitch;
*/
		}


	lpDDSSprites->Unlock(NULL);

	CloseHandle(BitmapFile);
}


void LoadSystem()
{
	HANDLE BitmapFile;
	DDSURFACEDESC ddsDesc;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	RGBQUAD          colors[256];
	DWORD			 dummy;
	int 			 y,x;
	UCHAR			 *data;
	UCHAR 			 tempdata[640];


	ZeroMemory(&ddsDesc,sizeof(ddsDesc));

	ddsDesc.dwSize=sizeof(ddsDesc);

	lpDDSSystem->Lock(NULL,&ddsDesc,DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,NULL);

	BitmapFile=CreateFile("system.dat",GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
//	ReadFile(BitmapFile,&bmfh,sizeof(bmfh),&dummy,NULL);
//  ReadFile(BitmapFile,&bmih,sizeof(bmih),&dummy,NULL);
//	ReadFile(BitmapFile,&colors,sizeof(RGBQUAD)*256,&dummy,NULL);

	data=(UCHAR*)ddsDesc.lpSurface+ddsDesc.lPitch*479;
	for(y=0;y<480;y++)
		{
			for(x=0;x<4;x++)
				{
					ReadFile(BitmapFile,tempdata,640,&dummy,NULL);
					memcpy(data+640*x,tempdata,640);
				}
			data-=ddsDesc.lPitch;

//			ReadFile(BitmapFile,tempdata,1920,&dummy,NULL);
//			memcpy(data,tempdata,1920);
//			data-=ddsDesc.lPitch;
		}


	lpDDSSystem->Unlock(NULL);

	CloseHandle(BitmapFile);
}


void LoadBackground()
{
	HANDLE BitmapFile;
	DDSURFACEDESC ddsDesc;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	RGBQUAD          colors[256];
	DWORD			 dummy;
	int 			 y,x;
	UCHAR			 *data;
	UCHAR 			 tempdata[640];
	PALETTEENTRY	 entries[256];

	ZeroMemory(&ddsDesc,sizeof(ddsDesc));

	ddsDesc.dwSize=sizeof(ddsDesc);

	lpDDSBackground->Lock(NULL,&ddsDesc,DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,NULL);

	BitmapFile=CreateFile("background.bmp",GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
	ReadFile(BitmapFile,&bmfh,sizeof(bmfh),&dummy,NULL);
	ReadFile(BitmapFile,&bmih,sizeof(bmih),&dummy,NULL);
	ReadFile(BitmapFile,&colors,sizeof(RGBQUAD)*256,&dummy,NULL);

	data=(UCHAR*)ddsDesc.lpSurface+ddsDesc.lPitch*479;
	for(y=0;y<480;y++)
		{
			ReadFile(BitmapFile,tempdata,640,&dummy,NULL);
			memcpy(data,tempdata,640);
			data-=ddsDesc.lPitch;
		}


	lpDDSBackground->Unlock(NULL);

	CloseHandle(BitmapFile);
}

