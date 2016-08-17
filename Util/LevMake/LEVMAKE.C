#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <stdlib.h>

#include "d:\lcc\Projects\Scuzzy32x\Game\level.h"
#include "global.h"


void main()
{
	int LevelX;
	int LevelY;
	int cx,cy;
	int *points;
	int bytes;
	BITMAPFILEHEADER bmFileHeader;
	BITMAPINFOHEADER bmInfoHeader;
	BITMAP			 TheBitmap;
	RGBQUAD          colors[256];
	struct Sprite_Def TempDef;
	struct Chain_Def TempChain;
	struct Platform_Def TempPlat;
	struct Switch_Def TempSwitch;
	struct Animset Sets;
	struct Pipe TempPipe;
	int NumSprites;
	int NumBaseframes;
	int Baseframe;
	int NumChains;
	int NumSets;
	int NumPlatforms;
	int NumSwitches;
	int NumPipes;
	int Set;
	int c;
	HANDLE Level;
	HANDLE Sprites2;
	FILE *SpritesIn;
	DWORD dummy;
	HANDLE DataBitmap;
	FILE *SpriteFile;
	FILE *BaseframesFile;
	FILE *ChainsFile;
	FILE *SetsFile;
	FILE *PlatformsFile;
	FILE *SwitchesFile;
	FILE *PipesFile;

	BYTE *TempStore;

	SFFileHeader FileHeader;
	SFLevelHeader LevelHeader;
	SFSpriteInfo	SpriteInfo;
	char 			buffer[20];
	int i;
	int blank;
	FileHeader.id[0]='S';
	FileHeader.id[1]='F';
	FileHeader.id[2]='L';

	FileHeader.numlevels=1;

	DataBitmap=CreateFile("Data.bmp",GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
	if(DataBitmap==INVALID_HANDLE_VALUE) printf("Error opening Data.bmp\n");


	SpriteFile=fopen("sprites.txt","r");




	fgets(buffer,20,SpriteFile);
	LevelHeader.PlayerX=atoi(buffer);
	fgets(buffer,20,SpriteFile);
	LevelHeader.PlayerY=atoi(buffer);

	fgets(buffer,20,SpriteFile);
	LevelHeader.numsprites=atoi(buffer);

	//fread(&TheBitmap,sizeof(TheBitmap),1,DataBitmap);
	ReadFile(DataBitmap,&bmFileHeader,sizeof(bmFileHeader),&dummy,NULL);
	ReadFile(DataBitmap,&bmInfoHeader,sizeof(bmInfoHeader),&dummy,NULL);
	ReadFile(DataBitmap,colors,sizeof(RGBQUAD)*256,&dummy,NULL);

	LevelX=bmInfoHeader.biWidth;
	LevelY=bmInfoHeader.biHeight/2;



	LevelHeader.id[0]='L';
	LevelHeader.id[1]='E';
	LevelHeader.id[2]='V';

	LevelHeader.x=LevelX;
	LevelHeader.y=LevelY;

	//Level=fopen("c:\\lcc\\Projects\\Scuzzy\\Game\\lcc\\level.dat","w");
	Level=CreateFile("d:\\lcc\\Projects\\Scuzzy32x\\Game\\lcc\\level.dat",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
	if(Level==INVALID_HANDLE_VALUE)
		{
			printf("Invalid Handle Value\n");
		}
	//fwrite(&FileHeader,sizeof(SFFileHeader),1,Level);
	WriteFile(Level,&FileHeader,sizeof(SFFileHeader),&dummy,NULL);

	//fwrite(&LevelHeader,sizeof(SFLevelHeader),1,Level);
	WriteFile(Level,&LevelHeader,sizeof(SFLevelHeader),&dummy,NULL);
	TempStore=(BYTE*)malloc(LevelX*LevelY*2);

	if(TempStore==NULL) printf("Invalid pointer value\n");

	ReadFile(DataBitmap,TempStore,LevelX*LevelY*2,&dummy,NULL);
	printf("%i\n",GetLastError());
	if(dummy!=LevelX*LevelY*2) printf("Error loading level bitmap, %i bytes required, %i read\n",LevelX*LevelY*2,dummy);
	for(i=LevelX*LevelY*2-LevelX;i>=0;i-=LevelX)
		{
			WriteFile(Level,TempStore+i,LevelX,&dummy,NULL);

		}

	  CloseHandle(DataBitmap);
	//fwrite(TempStore,LevelX*LevelY,2,Level);
	//WriteFile(Level,TempStore,LevelX*LevelY*2,&dummy,NULL);

	BaseframesFile=fopen("baseframes.txt","r");
	fgets(buffer,20,BaseframesFile);
	NumBaseframes=atoi(buffer);
	WriteFile(Level,&NumBaseframes,sizeof(NumBaseframes),&dummy,NULL);

	for(i=0;i<NumBaseframes;i++)
	{
		fgets(buffer,20,BaseframesFile);
		Baseframe=atoi(buffer);
		WriteFile(Level,&Baseframe,sizeof(Baseframe),&dummy,NULL);
	}
	fclose(BaseframesFile);

	SetsFile=fopen("sets.txt","r");
	fgets(buffer,20,SetsFile);
	NumSets=atoi(buffer);
	WriteFile(Level,&NumSets,sizeof(NumSets),&dummy,NULL);

	for(i=0;i<NumSets;i++)
	{
		fgets(buffer,20,SetsFile);
		Sets.frameoffset=atoi(buffer);
		fgets(buffer,20,SetsFile);
		Sets.x=atoi(buffer);
		fgets(buffer,20,SetsFile);
		Sets.y=atoi(buffer);
		fgets(buffer,20,SetsFile);
		Sets.cx=atoi(buffer);
		fgets(buffer,20,SetsFile);
		Sets.cy=atoi(buffer);
		WriteFile(Level,&Sets,sizeof(struct Animset),&dummy,NULL);
		//printf("Set %i:Frameoffset %i, %ix%i, %ix%i\n",i,Sets.frameoffset,Sets.x,Sets.y,Sets.cx,Sets.cy);
		fgets(buffer,20,SetsFile);
	}
	fclose(SetsFile);

	printf("Writing sprites...\n");
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
	fclose(SpriteFile);
	ChainsFile=fopen("chains.txt","r");
	printf("Writing Chains...\n");
	fgets(buffer,20,ChainsFile);

	NumChains=atoi(buffer);

	WriteFile(Level,&NumChains,sizeof(NumChains),&dummy,NULL);
	printf("NumChains=%i\n",NumChains);
	if(NumChains!=0)
		for(i=0;i<NumChains;i++)
			{
				printf("In Chain loop\n");
				fgets(buffer,20,ChainsFile);
				TempChain.x=atoi(buffer);
				fgets(buffer,20,ChainsFile);
				TempChain.y=atoi(buffer);
				fgets(buffer,20,ChainsFile);
				TempChain.cx=atoi(buffer);
				fgets(buffer,20,ChainsFile);
				TempChain.type=atoi(buffer);
				WriteFile(Level,&TempChain,sizeof(struct Chain_Def),&dummy,NULL);
				printf("Chain %i: Type %i, at %ix%i, %i blocks long\n",i,TempChain.type,TempChain.x,TempChain.y,TempChain.cx);
			}
	fclose(ChainsFile);

	PlatformsFile=fopen("platforms.txt","r");
	fgets(buffer,20,PlatformsFile);
	NumPlatforms=atoi(buffer);
	printf("%i Platforms\n",NumPlatforms);
	WriteFile(Level,&NumPlatforms,sizeof(NumPlatforms),&dummy,NULL);
	if(NumPlatforms!=0)
		for(i=0;i<NumPlatforms;i++)
			{
				fgets(buffer,20,PlatformsFile);
				TempPlat.cx=atoi(buffer);
				fgets(buffer,20,PlatformsFile);
				TempPlat.type=atoi(buffer);
				fgets(buffer,20,PlatformsFile);
				TempPlat.sprite=atoi(buffer);
				fgets(buffer,20,PlatformsFile);
				TempPlat.speed=atoi(buffer);


				fgets(buffer,20,PlatformsFile);
				TempPlat.numpoints=atoi(buffer);

				points=(int*)malloc(sizeof(int)*TempPlat.numpoints*2);
				for(c=0;c<TempPlat.numpoints;c++)
				{
					fgets(buffer,20,PlatformsFile);
					*(points+c*2)=atoi(buffer);
					fgets(buffer,20,PlatformsFile);
					*(points+c*2+1)=atoi(buffer);
				}
				WriteFile(Level,&TempPlat,sizeof(struct Platform_Def),&dummy,NULL);
				WriteFile(Level,points,sizeof(int)*TempPlat.numpoints*2,&dummy,NULL);
				printf("Platform %i: Type: %i, %i pixels long, %i points:\n",i,TempPlat.type,TempPlat.cx,TempPlat.numpoints);
				for(c=0;c<TempPlat.numpoints;c++) printf("Point %i: %ix%i\n",c,*(points+c*2),*(points+c*2+1));

				free(points);
			}

	fclose(PlatformsFile);
	SwitchesFile=fopen("switches.txt","r");
	fgets(buffer,20,SwitchesFile);
	NumSwitches=atoi(buffer);
	printf("%i switches\n",NumSwitches);
	WriteFile(Level,&NumSwitches,sizeof(NumSwitches),&dummy,NULL);
	printf("%i bytes written\n",dummy);
	if(NumSwitches!=0)
		for(i=0;i<NumSwitches;i++)
			{
				fgets(buffer,20,SwitchesFile);
				TempSwitch.x=atoi(buffer);
				fgets(buffer,20,SwitchesFile);
				TempSwitch.y=atoi(buffer);
				fgets(buffer,20,SwitchesFile);
				TempSwitch.sprite=atoi(buffer);
				fgets(buffer,20,SwitchesFile);
				TempSwitch.type=atoi(buffer);
				fgets(buffer,20,SwitchesFile);
				TempSwitch.target=atoi(buffer);
				WriteFile(Level,&TempSwitch,sizeof(struct Switch_Def),&dummy,NULL);
				printf("Switch %i: Sprite %i, at %ix%i type %i\n",i,TempSwitch.sprite,TempSwitch.x,TempSwitch.y,TempSwitch.type);
			}

	fclose(SwitchesFile);
	//fclose(Level);

	PipesFile=fopen("pipes.txt","r");
	printf("Writing Pipes...\n");
	fgets(buffer,20,PipesFile);

	NumPipes=atoi(buffer);

	WriteFile(Level,&NumPipes,sizeof(NumPipes),&dummy,NULL);
	printf("NumPipes=%i\n",NumPipes);
	if(NumPipes!=0)
		for(i=0;i<NumPipes;i++)
			{

				fgets(buffer,20,PipesFile);
				TempPipe.x=atoi(buffer);
				fgets(buffer,20,PipesFile);
				TempPipe.y=atoi(buffer);
				fgets(buffer,20,PipesFile);
				TempPipe.xlength=atoi(buffer);
				fgets(buffer,20,PipesFile);
				TempPipe.ylength=atoi(buffer);
				fgets(buffer,20,PipesFile);
				TempPipe.direction=atoi(buffer);
				WriteFile(Level,&TempPipe,sizeof(struct Pipe),&dummy,NULL);
				printf("Pipe %i: At %ix%i, %ix%i long, direction: %i\n",i,TempPipe.x,TempPipe.y,TempPipe.xlength,TempPipe.ylength,TempPipe.direction);
			}
	fclose(PipesFile);


	CloseHandle(Level);






	SpritesIn=fopen("spritebounds.txt","r");
	Sprites2=CreateFile("d:\\lcc\\Projects\\Scuzzy32x\\Game\\lcc\\spritebounds.dat",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
	if(Sprites2==INVALID_HANDLE_VALUE) printf("Error creating Spritedef file (%x%x)\n",GetLastError()>>16,GetLastError()&0xFFFF);
	fgets(buffer,20,SpritesIn);
	NumSprites=atoi(buffer);
	printf("%i spritedefs\n",NumSprites);
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
