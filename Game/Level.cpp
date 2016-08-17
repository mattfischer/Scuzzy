#include "level_cpp.h"

int LoadLevel()
{
	DWORD dummy;
	SFFileHeader sffh;
	SFLevelHeader sflh;
	SFSpriteInfo SpriteDummy;
	struct Sprite_Info *temp;
	struct Sprite_Info *temp2;
	Chain *tempchain;
	Chain_Def chaindef;
	Platform *tempplatform;
	struct Platform_Def plattemp;
	struct Switch_Def switchtemp;
	struct Pipe pipetemp;
	int i;
	char buffer[100];
	int c;
	HANDLE hLevelFile;
	SFSpriteInfo tempsprites;
	hLevelFile=CreateFile("level.dat",GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);

	if(hLevelFile==INVALID_HANDLE_VALUE)
		{
			DebugString("Error\n");
			wsprintf(buffer,"Error %i\n",GetLastError());
			DebugString(buffer);
			return 1;
		}
	if(!ReadFile(hLevelFile,&sffh,sizeof(SFFileHeader),&dummy,NULL))
		{
			DebugString("Error 1:\n");
			wsprintf(buffer,"Error %i\n",GetLastError());
			DebugString(buffer);
			return 1;
		}

	if(!ReadFile(hLevelFile,&sflh,sizeof(SFLevelHeader),&dummy,NULL))
		{
			DebugString("Error 2:\n");
			wsprintf(buffer,"Error %i\n",GetLastError());
			DebugString(buffer);
			return 1;
		}

	wsprintf(buffer,"Header size=%i bytes\n",sizeof(sffh));
	DebugString(buffer);
	wsprintf(buffer,"NumLevels=%i\n",sffh.numlevels);
	DebugString(buffer);
	wsprintf(buffer,"Header: %c%c%c\n",sffh.id[0],sffh.id[1],sffh.id[2]);
	DebugString(buffer);
	wsprintf(buffer,"Header: %c%c%c\n",sflh.id[0],sflh.id[1],sflh.id[2]);
	DebugString(buffer);

	if(sflh.x>100 || sflh.y>100)
		{
			DebugString("Error: Level Dimensions too large\n");
			return 1;
		}
	level=(UCHAR*)malloc(sflh.x*sflh.y);
	physics=(UCHAR*)malloc(sflh.x*sflh.y);

	LevelX=sflh.x;
	LevelY=sflh.y;

	wsprintf(buffer,"Level: %ix%i\n",LevelX,LevelY);
	DebugString(buffer);

	ReadFile(hLevelFile,level,sflh.x*sflh.y,&dummy,NULL);
	ReadFile(hLevelFile,physics,sflh.x*sflh.y,&dummy,NULL);


	NumSprites=sflh.numsprites;



	ReadFile(hLevelFile,&NumBaseframes,sizeof(NumBaseframes),&dummy,NULL);
	wsprintf(buffer,"NumBaseframes=%i\n",NumBaseframes);
	DebugString(buffer);


	Baseframes=(int*)malloc(sizeof(int)*NumBaseframes);
	ReadFile(hLevelFile,Baseframes,sizeof(int)*NumBaseframes,&dummy,NULL);


	ReadFile(hLevelFile,&NumSets,sizeof(NumSets),&dummy,NULL);

	Sets=(struct Animset*)malloc(sizeof(struct Animset)*NumSets);
	ReadFile(hLevelFile,Sets,sizeof(struct Animset)*NumSets,&dummy,NULL);
	wsprintf(buffer,"NumSets=%i\n",NumSets);
	DebugString(buffer);
	for(i=0;i<NumSets;i++)
		{
			wsprintf(buffer,"Set %i: frameoffset %i, %ix%i, %ix%i\n",i,(Sets+i)->frameoffset,(Sets+i)->x,(Sets+i)->y,(Sets+i)->cx,(Sets+i)->cy);
			DebugString(buffer);
		}


	Sprites=NULL;
	if(NumSprites!=0)
		{
	Sprites=(struct Sprite_Info*)malloc(sizeof(struct Sprite_Info));

	Sprites->next=Sprites;
	Sprites->prev=Sprites;
	temp=Sprites;


	for(i=0;i<NumSprites;i++)
	{
		 ReadFile(hLevelFile,&SpriteDummy,sizeof(SFSpriteInfo),&dummy,NULL);
		 temp->x=SpriteDummy.x;
		 temp->y=SpriteDummy.y;
		 temp->type=SpriteDummy.type;
		 temp->xv=0;
		 temp->yv=0;
		 temp->xa=0;
		 temp->ya=0;
		 temp->frame=0;
		 temp->floating=0;
		 if(SpriteDummy.type>=BASEFRAME_STATIC) temp->isstatic=1; else temp->isstatic=0;
		 if(temp->isstatic==0) temp->baseframe=*(Baseframes+BASEFRAME_SPRITE+temp->type-1);
		 wsprintf(buffer,"Sprite %i: Type %i, baseframe set to %i\n",i,temp->type,temp->baseframe);
		 DebugString(buffer);
		 if(temp->isstatic==1)
			{
		    temp->type-=BASEFRAME_STATIC;
		 	temp->baseframe=*(Baseframes+BASEFRAME_STATIC+temp->type);
			}
		 temp->cx=(spritedefs+temp->baseframe)->cx;
		 temp->cy=(spritedefs+temp->baseframe)->cy;
		 temp->frametimer=GetTickCount();
		 temp->direction=-1;
		 temp->status=SLEEPING;
		 temp->animset=0;

		 //temp->setlist=Sets+SetStart[temp->type];
		 temp->setlist=&EmptySet;
		 if(temp->type==1)temp->setlist=Sets+SET_SPRITE1;
		 if(temp->type==2)temp->setlist=Sets+SET_SPRITE2;

		 if(temp->isstatic==1) {
			 temp->setlist=&EmptySet;
			 wsprintf(buffer,"Static type %i, baseframe %i,\n",temp->type,temp->baseframe);
			 DebugString(buffer);
			}
//		 ReadFile(hLevelFile,&tempsprites,sizeof(SFSpriteInfo),&dummy,NULL);
//       wsprintf(buffer,"Sprite %i: Type %i, at %ix%i.\n",i,tempsprites.type,tempsprites.x,tempsprites.y);

		if(i!=NumSprites-1)
			{
				temp2=(struct Sprite_Info*)malloc(sizeof(struct Sprite_Info));
				temp->next=temp2;
				temp2->prev=temp;
				temp2->next=Sprites;
				Sprites->prev=temp2;
				temp=temp2;
				}
		}
}

	ReadFile(hLevelFile,&NumChains,sizeof(NumChains),&dummy,NULL);


	if(NumChains!=0)
	for(i=0;i<NumChains;i++)
	{
		ReadFile(hLevelFile,&chaindef,sizeof(Chain_Def),&dummy,NULL);
		tempchain=(struct Chain*)malloc(sizeof(struct Chain));
		tempchain->x=chaindef.x;
		tempchain->y=chaindef.y;
		tempchain->cx=chaindef.cx;
		tempchain->type=chaindef.type;

		if(Chains==NULL)
		   {
		    	Chains=tempchain;
				Chains->next=Chains;
				Chains->prev=Chains;
			}
		else
			{
				tempchain->next=Chains;
				tempchain->prev=Chains->prev;
				Chains->prev->next=tempchain;
				Chains->prev=tempchain;
			}
	}



	wsprintf(buffer,"NumChains=%i\n",NumChains);
	DebugString(buffer);

	tempchain=Chains;
	if(NumChains!=0)
	for(i=0;i<NumChains;i++)
		{
			wsprintf(buffer,"Chain %i: Location %ix%i, Length %i, type %i\n",i,tempchain->x,tempchain->y,tempchain->cx,tempchain->type);
			DebugString(buffer);
			tempchain=tempchain->next;
		}


	ReadFile(hLevelFile,&NumPlatforms,sizeof(NumPlatforms),&dummy,NULL);

	wsprintf(buffer,"%i Platforms\n",NumPlatforms);
	DebugString(buffer);

	Platforms=NULL;
	if(NumPlatforms!=0)
	for(i=0;i<NumPlatforms;i++)
	{
		ReadFile(hLevelFile,&plattemp,sizeof(Platform_Def),&dummy,NULL);
		tempplatform=(struct Platform*)malloc(sizeof(struct Platform));
		tempplatform->cx=plattemp.cx;
		tempplatform->numpoints=plattemp.numpoints;
		tempplatform->type=plattemp.type;
		tempplatform->sprite=plattemp.sprite;
		tempplatform->speed=plattemp.speed;

		tempplatform->points=(int*)malloc(sizeof(int)*plattemp.numpoints*2);
		ReadFile(hLevelFile,tempplatform->points,sizeof(int)*plattemp.numpoints*2,&dummy,NULL);
		tempplatform->x=*(tempplatform->points);
		tempplatform->y=*(tempplatform->points+1);
		tempplatform->speed=plattemp.speed;
		tempplatform->number=i;


		for(c=0;c<plattemp.numpoints;c++)
			{
				wsprintf(buffer,"Point %i: %ix%i\n",c,*((Platforms+i)->points+c*2),*((Platforms+i)->points+c*2+1));
				DebugString(buffer);
			}
		if(tempplatform->type==PLATFORMTYPE_STATIONARY)
			{
				tempplatform->movepoint=-1;
				tempplatform->status=PLATFORM_STOPPED;
			}
		if(tempplatform->type==PLATFORMTYPE_MOVEALWAYS || tempplatform->type==PLATFORMTYPE_MOVEONCE)
			{
				tempplatform->status=PLATFORM_MOVING;
				tempplatform->movepoint=1;
				tempplatform->lastpoint=0;
			}
		if(tempplatform->type==PLATFORMTYPE_DOOR)
			{
				tempplatform->status=PLATFORM_STOPPED;
				tempplatform->movepoint=1;
				tempplatform->lastpoint=0;
			}

		tempplatform->dx=*(tempplatform->points+2)-*(tempplatform->points);
		tempplatform->dy=*(tempplatform->points+3)-*(tempplatform->points+1);
		tempplatform->linelength=sqrt(tempplatform->dx*tempplatform->dx+tempplatform->dy*tempplatform->dy);
		tempplatform->linelength/=(double)tempplatform->speed;
		tempplatform->dx/=(double)tempplatform->linelength;
		tempplatform->dy/=(double)tempplatform->linelength;

		if(Platforms==NULL)
		   {
		    	Platforms=tempplatform;
				Platforms->next=Platforms;
				Platforms->prev=Platforms;
			}
		else
			{
				tempplatform->next=Platforms;
				tempplatform->prev=Platforms->prev;
				Platforms->prev->next=tempplatform;
				Platforms->prev=tempplatform;
			}

		wsprintf(buffer,"Platform %i: Location %ix%i, Length %i, %i Points:\n",i,(int)tempplatform->x,(int)tempplatform->y,tempplatform->cx,tempplatform->numpoints);
		DebugString(buffer);

	}





	ReadFile(hLevelFile,&NumSwitches,sizeof(NumSwitches),&dummy,NULL);
	wsprintf(buffer,"%i Switches\n",NumSwitches);
	DebugString(buffer);
	/*
	Switches=(struct Switch*)malloc(sizeof(struct Switch)*NumSwitches);
	if(NumSwitches)
	for(i=0;i<NumSwitches;i++)
		{

			ReadFile(hLevelFile,&switchtemp,sizeof(struct Switch_Def),&dummy,NULL);
			(Switches+i)->x=switchtemp.x;
			(Switches+i)->y=switchtemp.y;
			(Switches+i)->sprite=switchtemp.sprite;
			(Switches+i)->state=0;
			(Switches+i)->type=switchtemp.type;
			(Switches+i)->target=switchtemp.target;
			(Switches+i)->cx=(spritedefs+*(Baseframes+BASEFRAME_SWITCH+switchtemp.sprite))->cx;
			(Switches+i)->cy=(spritedefs+*(Baseframes+BASEFRAME_SWITCH+switchtemp.sprite))->cy;

			wsprintf(buffer,"Switch %i: At %ix%i, sprite %i type %i \n",i,switchtemp.x,switchtemp.y,switchtemp.sprite,switchtemp.type);
			DebugString(buffer);
		}
	*/

	ReadFile(hLevelFile,&NumPipes,sizeof(NumPipes),&dummy,NULL);
	Pipes=(struct Pipe*)malloc(sizeof(struct Pipe)*NumPipes);
	wsprintf(buffer,"%i Pipes\n",NumPipes);
	DebugString(buffer);

	for(i=0;i<NumPipes;i++)
		{

			ReadFile(hLevelFile,&pipetemp,sizeof(struct Pipe),&dummy,NULL);
			(Pipes+i)->x=pipetemp.x;
			(Pipes+i)->y=pipetemp.y;
			(Pipes+i)->xlength=pipetemp.xlength;
			(Pipes+i)->ylength=pipetemp.ylength;
			(Pipes+i)->direction=pipetemp.direction;
			wsprintf(buffer,"Pipe %i: At %ix%i, %ix%i long, direction: %i \n",i,pipetemp.x,pipetemp.y,pipetemp.xlength,pipetemp.ylength,pipetemp.direction);
			DebugString(buffer);
		}


	CloseHandle(hLevelFile);
	CameraX=0;
	CameraY=0;
	OldCameraY=0;
	OldCameraX=0;
	NumBullets=0;
	Player.InitPlayer(sflh.PlayerX,sflh.PlayerY,Sets);
	return 0;
}


