#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
#include "c:\lcc\Projects\Scuzzy\Game\level.h"

void main()
{
	HANDLE thefile;
	SFFileHeader sffh;
	SFLevelHeader sflh;
	SFSpriteInfo  sfsi;
    BYTE			  *leveldata;
	DWORD 		dummy;
	int 		 i;

	//thefile=fopen("c:\\lcc\\Projects\\Scuzzy\\Game\\lcc\\level.dat","r");
	thefile=CreateFile("c:\\lcc\\Projects\\Scuzzy\\Game\\lcc\\level.dat",GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);

	//fread(&sffh,sizeof(sffh),1,thefile);
	ReadFile(thefile,&sffh,sizeof(sffh),&dummy,NULL);
	printf("Signature %c%c%c, NumLevels=%i\n",sffh.id[0],sffh.id[1],sffh.id[2],sffh.numlevels);

	//fread(&sflh,sizeof(sflh),1,thefile);
	ReadFile(thefile,&sflh,sizeof(sflh),&dummy,NULL);

	printf("Signature %c%c%c, %ix%i, %i sprites\n",sflh.id[0],sflh.id[1],sflh.id[2],sflh.x,sflh.y,sflh.numsprites);
	printf("Player Location: %ix%i\n",sflh.PlayerX,sflh.PlayerY);

	leveldata=(BYTE*)malloc(sflh.x*sflh.y*2);
	//fread(leveldata,sflh.x*sflh.y*2,1,thefile);
	ReadFile(thefile,leveldata,sflh.x*sflh.y*2,&dummy,NULL);
	if(sflh.numsprites!=0)
	for(i=0;i<sflh.numsprites;i++)
		{
			//fread(&sfsi,sizeof(sfsi),1,thefile);
			ReadFile(thefile,&sfsi,sizeof(sfsi),&dummy,NULL);
			printf("Sprite %i: Type %i, at %ix%i.\n",i,sfsi.type,sfsi.x,sfsi.y);
		}

	//fclose(thefile);
	CloseHandle(thefile);
}

