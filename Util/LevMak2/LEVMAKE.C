#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <stdlib.h>

#include "c:\lcc\Projects\Scuzzy\Game\level.h"
#include "c:\lcc\Projects\Scuzzy\Game\global.h"

void main()
{
	int LevelX;
	int LevelY;
	int cx,cy;

	BITMAPFILEHEADER bmFileHeader;
	BITMAPINFOHEADER bmInfoHeader;
	BITMAP			 TheBitmap;
	RGBQUAD          colors[256];
	struct Sprite_Def TempDef;
	int NumSprites;
	int NumBaseframes;
	int Baseframe;
	HANDLE Level;
	HANDLE Sprites2;
	FILE *SpritesIn;
	DWORD dummy;
	FILE *DataBitmap;
	FILE *SpriteFile;
	FILE *BaseframesFile;

	BYTE *TempStore;

	SFFileHeader FileHeader;
	SFLevelHeader LevelHeader;
	SFSpriteInfo	SpriteInfo;
	char 			buffer[20];
	int i;

	FileHeader.id[0]='S';
	FileHeader.id[1]='F';
	FileHeader.id[2]='L';

	FileHeader.numlevels=1;

	DataBitmap=fopen("Data.bmp","r");


	SpriteFile=fopen("sprites.txt","r");
	BaseframesFile=fopen("baseframes.txt","r");

	fgets(buffer,20,SpriteFile);
	LevelHeader.PlayerX=atoi(buffer);
	fgets(buffer,20,SpriteFile);
	LevelHeader.PlayerY=atoi(buffer);

	fgets(buffer,20,SpriteFile);
	LevelHeader.numsprites=atoi(buffer);

	//fread(&TheBitmap,sizeof(TheBitmap),1,DataBitmap);
	fread(&bmFileHeader,sizeof(bmFileHeader),1,DataBitmap);
	fread(&bmInfoHeader,sizeof(bmInfoHeader),1,DataBitmap);
	fread(colors,sizeof(RGBQUAD),256,DataBitmap);

	LevelX=bmInfoHeader.biWidth;
	LevelY=bmInfoHeader.biHeight/2;



	LevelHeader.id[0]='L';
	LevelHeader.id[1]='E';
	LevelHeader.id[2]='V';

	LevelHeader.x=LevelX;
	LevelHeader.y=LevelY;


	printf("Level is %i x %i\n",LevelX,LevelY);
	printf("Sprites: %i\n",LevelHeader.numsprites);
	//Level=fopen("c:\\lcc\\Projects\\Scuzzy\\Game\\lcc\\level.dat","w");
	Level=CreateFile("c:\\lcc\\Projects\\Scuzzy\\Game\\lcc\\level.dat",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
	//fwrite(&FileHeader,sizeof(SFFileHeader),1,Level);
	WriteFile(Level,&FileHeader,sizeof(SFFileHeader),&dummy,NULL);

	//fwrite(&LevelHeader,sizeof(SFLevelHeader),1,Level);
	WriteFile(Level,&LevelHeader,sizeof(SFLevelHeader),&dummy,NULL);
	TempStore=(BYTE*)malloc(LevelX*LevelY*2);



	fread(TempStore,LevelX*LevelY,2,DataBitmap);

	fclose(DataBitmap);




	for(i=0;i<LevelX*LevelY*2;i++)
	{
		if(TempStore[i]==255) TempStore[i]=1;
		if(TempStore[i]==0x92) TempStore[i]=2;
	}




	for(i=LevelX*LevelY*2-LevelX;i>=0;i-=LevelX)
	  WriteFile(Level,&TempStore[i],LevelX,&dummy,NULL);

	//fwrite(TempStore,LevelX*LevelY,2,Level);
	//WriteFile(Level,TempStore,LevelX*LevelY*2,&dummy,NULL);


	fgets(buffer,20,BaseframesFile);
	NumBaseframes=atoi(buffer);
	WriteFile(Level,&NumBaseframes,sizeof(NumBaseframes),&dummy,NULL);

	for(i=0;i<NumBaseframes;i++)
	{
		fgets(buffer,20,BaseframesFile);
		Baseframe=atoi(buffer);
		WriteFile(Level,&Baseframe,sizeof(Baseframe),&dummy,NULL);
	}

	if(LevelHeader.numsprites!=0)
	for(i=0;i<LevelHeader.numsprites;i++)
		{
			fgets(buffer,20,SpriteFile);
			SpriteInfo.type=atoi(buffer);
			fgets(buffer,20,SpriteFile);
			SpriteInfo.x=atoi(buffer);
			fgets(buffer,20,SpriteFile);
			SpriteInfo.y=atoi(buffer);
			//fwrite(&SpriteInfo,sizeof(SFSpriteInfo),1,Level);
			WriteFile(Level,&SpriteInfo,sizeof(SFSpriteInfo),&dummy,NULL);
			printf("Sprite %i: Type %i, at %ix%i.\n",i,SpriteInfo.type,SpriteInfo.x,SpriteInfo.y);
		}

	//fclose(Level);
	CloseHandle(Level);
	fclose(SpriteFile);
	SpritesIn=fopen("spritebounds.txt","r");
	Sprites2=CreateFile("c:\\lcc\\Projects\\Scuzzy\\Game\\lcc\\spritebounds.dat",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
	fgets(buffer,20,SpritesIn);
	NumSprites=atoi(buffer);
	//fgets(buffer,20,SpritesIn);
	//cx=atoi(buffer);
	//fgets(buffer,20,SpritesIn);
	//cy=atoi(buffer);

	WriteFile(Sprites2,&NumSprites,sizeof(int),&dummy,NULL);
	fgets(buffer,20,SpritesIn);
	for(i=0;i<NumSprites;i++)
		{
			fgets(buffer,20,SpritesIn);
			TempDef.x=atoi(buffer);
			fgets(buffer,20,SpritesIn);
			TempDef.y=atoi(buffer);
			fgets(buffer,20,SpritesIn);
			TempDef.cx=atoi(buffer);
			fgets(buffer,20,SpritesIn);
			TempDef.cy=atoi(buffer);

			WriteFile(Sprites2,&TempDef,sizeof(TempDef),&dummy,NULL);
			fgets(buffer,20,SpritesIn);
		}
	fclose(SpritesIn);
	CloseHandle(Sprites2);
}
