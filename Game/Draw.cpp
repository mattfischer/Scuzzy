#include "draw.h"

Bullet *Bullet::temp=0;

void PreComputeBlocks()
{
	int i;
	int x,y;

	for(i=0;i<255;i++)
		{
			x=i%9;
			y=(i-x)/9;
			PreComp[i].left=1+x*33;
			PreComp[i].right=PreComp[i].left+32;
			PreComp[i].top=1+y*33;
			PreComp[i].bottom=PreComp[i].top+32;
		}
}

void BlitBlock(int num,int x1,int y1)
{

}

void BlitSprite(int num,int x1,int y1)
{
	int x;
	int y;
	int cx;
	int cy;
	RECT Dest;
	RECT Source;
	char buffer[100];

	x=(spritedefs+num)->x;
	y=(spritedefs+num)->y;
	cx=(spritedefs+num)->cx;
	cy=(spritedefs+num)->cy;



	Dest.top=y1;
	Dest.bottom=y1+cy;
	Dest.left=x1;
	Dest.right=x1+cx;

	Source.left=x;
	//Source.left=1;
	Source.right=Source.left+cx;
	Source.top=y;
	//Source.top=1;
	Source.bottom=Source.top+cy;

	lpDDSBack->Blt(&Dest,lpDDSSprites,&Source,DDBLT_KEYSRC,NULL);

}

void DrawParallaxBackground()
{
	RECT Dest;
	RECT Source;



	Dest.top=0;
	Dest.bottom=480;
	Dest.left=0;
	Dest.right=640;

	Source.left=0;
	//Source.left=1;
	Source.right=640;
	Source.top=0;
	//Source.top=1;
	Source.bottom=480;

	lpDDSBack->Blt(&Dest,lpDDSBackground,&Source,DDBLT_WAIT,NULL);
	}


void BlitBackground()
{
	RECT Dest;
	RECT Source;



	Dest.top=0;
	Dest.bottom=480;
	Dest.left=0;
	Dest.right=640;

	Source.left=0;
	//Source.left=1;
	Source.right=640;
	Source.top=0;
	//Source.top=1;
	Source.bottom=480;

	lpDDSBack->Blt(&Dest,lpDDSBack2,&Source,DDBLT_WAIT,NULL);
}


/*void DrawBackground()
{
	int x1;
	int y1;
	int newy;
	int x;
	int y;
	int x2,y2;
	int cx,cy;
	int index;
	int tile;
	int inc;
	int i,c;
	char buffer[100];
	unsigned long spointer,dpointer;
	RECT Dest;
	RECT Source;
	int ddrval;

	UCHAR *ssurface,*dsurface;
	LONG spitch,dpitch;
	DDSURFACEDESC sddsurfdesc,dddsurfdesc;

	newy=CameraY-CameraYOffset;
	x1=CameraX/32;
	y1=newy/32;

	cx=CameraX%32;
	cy=newy%32;

	ClearSurface(lpDDSBack);
DrawParallaxBackground();
	inc=LevelX-20;

	Dest.top=-cy;
	Dest.bottom=-cy+32;
	Dest.left=-cx;
	Dest.right=-cx+32;

	ZeroMemory(&dddsurfdesc,sizeof(dddsurfdesc));
	dddsurfdesc.dwSize=sizeof(dddsurfdesc);

	ZeroMemory(&sddsurfdesc,sizeof(sddsurfdesc));
	sddsurfdesc.dwSize=sizeof(sddsurfdesc);

	ddrval=IDirectDrawSurface_Lock(lpDDSBack,NULL,&dddsurfdesc,DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,NULL);
	if(ddrval!=DD_OK) HandleBadResult(ddrval,21);

	ddrval=IDirectDrawSurface_Lock(lpDDSBlocks,NULL,&sddsurfdesc,DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,NULL);
	if(ddrval!=DD_OK) HandleBadResult(ddrval,22);
	dsurface=(UCHAR*)dddsurfdesc.lpSurface;
	dpitch=dddsurfdesc.lPitch;

	ssurface=(UCHAR*)sddsurfdesc.lpSurface;
	spitch=sddsurfdesc.lPitch;
	index=y1*LevelX+x1;
	for(y=0;y<15;y++)
		{
 		for(x=0;x<20;x++)
		{

			tile=level[index];
			Source=PreComp[tile];

			if(tile!=0)
				{
					spointer=(Source.top)*spitch+Source.left;
					dpointer=(y*32)*dpitch+x*32;
					for(i=0;i<32;i++)
					{
						for(c=0;c<32;c++)
							{

								*(dsurface+dpointer++)=*(ssurface+spointer++);
							}

						spointer+=spitch-32;
						dpointer+=dpitch-32;
					}

					//ddrval=IDirectDrawSurface_Blt(lpDDSBack,&Dest,lpDDSBlocks,&Source,DDBLT_WAIT,NULL);

				}

			index++;
			Dest.right+=32;
			Dest.left+=32;

		}

		index+=inc;
		Dest.left=-cx;
		Dest.right=-cx+32;
		Dest.top+=32;
		Dest.bottom+=32;
	}
IDirectDrawSurface_Unlock(lpDDSBlocks,NULL);
IDirectDrawSurface_Unlock(lpDDSBack,NULL);
}
*/
void Sprite_Info::Draw()
{
	int l_x,l_y;
	int temp;
	char buffer[100];
	l_x=x-CameraX;
	l_y=y-CameraY+CameraYOffset;
	temp=frame+baseframe+(setlist+animset)->frameoffset;
	wsprintf(buffer,"Blitting sprite with baseframe %i\n",temp);
	DebugString(buffer);

	if(l_x>640 || l_y>480 || l_x+cx<0 || l_y+cy<0) return;
		  BlitSprite(temp,l_x,l_y);
}

void DrawSprites()
{
	int i;
	struct Sprite_Info *tempsprite;
	char buffer[100];
	int x,y;
	for(i=0;i<NumSprites;i++)
	   {

		  tempsprite=GetSprite(i);
		  if(tempsprite==NULL) break;
		  wsprintf(buffer,"Drawing sprite %i\n",i);
		  DebugString(buffer);
		  tempsprite->Draw();
		  wsprintf(buffer,"Drew sprite %i\n",i);
		  DebugString(buffer);

		}
}

void Chain::Draw()
{

	int c;
	for(c=0;c<cx;c++)
		BlitSprite(*(Baseframes+BASEFRAME_CHAIN+type),x+c*32-CameraX,y-CameraY+CameraYOffset);
}

void DrawChains()
{
	int i;
	Chain *tempchain;
	tempchain=Chains;
	if(tempchain==NULL) return;
	while(1)
		{
			tempchain->Draw();
			tempchain=tempchain->next;
			if(tempchain==Chains) break;
		}
}

void Platform::Draw()
{
		BlitSprite(*(Baseframes+BASEFRAME_PLATFORM+sprite),x-CameraX,y-CameraY+CameraYOffset);
}
void DrawPlatforms()
{
	int i;
	int c;
	Platform *tempplat;
	if(Platforms==NULL) return;
	tempplat=Platforms;
	while(1)
	{
		tempplat->Draw();
		tempplat=tempplat->next;
		if(tempplat==Platforms) break;
	}

}

void Switch::Draw()
{
	BlitSprite(*(Baseframes+BASEFRAME_SWITCH+sprite)+state,x-CameraX,y-CameraY+CameraYOffset);
}

void DrawSwitches()
{
	int i;

	for(i=0;i<NumSwitches;i++)
		(Switches+i)->Draw();

}

void UpdateCameraPosition()
{
	if(Player.status==DYING) return;
	if(Player.x-CameraX<248)//248  //320
		if(Player.x-248>0) CameraX=Player.x-248;
		else				 CameraX=0;
	if(Player.x-CameraX>328)//328  //276
		if(Player.x-328<LevelX*32-641) CameraX=Player.x-328;
	    else				 CameraX=LevelX*32-641;
    if(Player.y-CameraY<178)//178  //202
		if(Player.y-178>0) CameraY=Player.y-178;
		else				 CameraY=0;
	if(Player.y-CameraY>238)//238  //176
		if(Player.y-238<LevelY*32-418) CameraY=Player.y-238;
	    else				 CameraY=LevelY*32-418;

	if(CameraY-CameraYOffset+417>LevelY*32) CameraYOffset=(CameraY-(LevelY*32-417));
	if(CameraY-CameraYOffset<0) CameraYOffset=CameraY;
	//CameraX=CameraX-CameraX%32;
	//CameraY=CameraY-CameraY%32;
	//CameraY=(CameraY-CameraYOffset)-(CameraY-CameraYOffset)%32+CameraYOffset;

}


void RedrawFrontBlocks()
{
	int x1;
	int y1;
	int newy;
	int x;
	int y;
	int x2,y2;
	int cx,cy;
	int index;
	int tile;
	int inc;
	RECT Dest;
	RECT Source;

	newy=CameraY-CameraYOffset;
	x1=(CameraX-CameraX%32)/32;
	y1=(newy-newy%32)/32;

	cx=CameraX%32;
	cy=newy%32;


	inc=LevelX-21;
	index=y1*LevelX+x1;
	Dest.top=-cy;
	Dest.bottom=-cy+32;
	Dest.left=-cx;
	Dest.right=-cx+32;

	for(y=0;y<15;y++)
		{
 		for(x=0;x<21;x++)
		{
			tile=level[index];
			Source=PreComp[tile];
			if(physics[index]==2) lpDDSBack->Blt(&Dest,lpDDSBlocks,&Source,DDBLT_WAIT,NULL);
			index++;
			Dest.right+=32;
			Dest.left+=32;
		}
		index+=inc;
		Dest.left=-cx;
		Dest.right=-cx+32;
		Dest.top+=32;
		Dest.bottom+=32;
	}
}


void DrawEntireBackground()
{
	int x1;
	int y1;
	int newy;
	int x;
	int y;
	int x2,y2;
	int cx,cy;
	int index;
	int tile;
	int inc;
	RECT Dest;
	RECT Source;

	newy=CameraY-CameraYOffset;
	x1=(CameraX-CameraX%32)/32;
	y1=(newy-newy%32)/32;

	cx=CameraX%32;
	cy=newy%32;


	inc=LevelX-21;
	index=y1*LevelX+x1;
	Dest.top=-cy;
	Dest.bottom=-cy+32;
	Dest.left=-cx;
	Dest.right=-cx+32;

	for(y=0;y<15;y++)
		{
 		for(x=0;x<21;x++)
		{
			tile=level[index];
			Source=PreComp[tile];
			lpDDSBack2->Blt(&Dest,lpDDSBlocks,&Source,DDBLT_WAIT,NULL);
			index++;
			Dest.right+=32;
			Dest.left+=32;
		}
		index+=inc;
		Dest.left=-cx;
		Dest.right=-cx+32;
		Dest.top+=32;
		Dest.bottom+=32;
	}
}


void DrawStatusBar()
{
	RECT Dest;
	RECT Source;



	Dest.top=416;
	Dest.bottom=480;
	Dest.left=0;
	Dest.right=640;

	Source.left=0;
	//Source.left=1;
	Source.right=640;
	Source.top=416;
	//Source.top=1;
	Source.bottom=480;


	lpDDSBack->Blt(&Dest,lpDDSSystem,&Source,DDBLT_WAIT,NULL);

	DrawHealthBar();
	DrawScore();
	DrawAmmo();
}

void DrawHealthBar()
{
	RECT Dest;
	RECT Source;



	Source.top=406;
	Source.bottom=415;
	Source.left=0;
	Source.right=Player.health*10;

	Dest.left=203;
	Dest.right=203+Player.health*10;
	Dest.top=460;
	Dest.bottom=470;


	lpDDSBack->Blt(&Dest,lpDDSSystem,&Source,DDBLT_WAIT,NULL);

}
void DrawCharacter(int type,int x,int y,char c)
{

	int x1,y1;
	RECT Source, Dest;

	if(type==1)
		{
			if(c>96 && c<123) c-=32;
			c-=32;
			if(c<37) y1=1; else y1=18;
			if(c<37) x1=c*17+1; else x1=(c-37)*17+1;
			Source.top=y1;
			Source.bottom=y1+15;
			Source.left=x1;
			Source.right=x1+15;
			Dest.left=x;
			Dest.top=y;
			Dest.right=x+15;
			Dest.bottom=y+15;

			lpDDSBack->Blt(&Dest,lpDDSSystem,&Source,DDBLT_WAIT | DDBLT_KEYSRC,NULL);
		}
}

void DrawString(int type,int x,int y,char *c)
{
	int x1;

	if(type==1)	for(x1=x;*c!='\0';x1+=10,c++) DrawCharacter(type,x1,y,*c);
}


void DrawScore()
{
	char scorec[7];
	int temp;
	int i;
	int div;
	static int scoreinc=0;

	if(Realscore!=Score && scoreinc==0)
		{
			scoreinc=(Score-Realscore)/50;
		}
	if(abs(Realscore-Score)<abs(scoreinc))Realscore=Score;
		else Realscore+=scoreinc;
	if(Realscore==Score) scoreinc=0;
/*	div=100000;

	for(i=0;i<6;i++)
		{
			temp=localscore/div;
			scorec[i]=temp+48;
			localscore-=temp*div;
			div/=10;

		}
	scorec[6]='\0';
*/
	wsprintf(scorec,"%06i",Realscore);
	DrawString(1,45,455,scorec);
}

void Bullet::Draw()
{
	RECT Source,Dest;
	int l_frame;
	l_frame=baseframe+frame+(setlist+animset)->frameoffset;
	Source.left=(spritedefs+l_frame)->x;
	Source.right=(spritedefs+l_frame)->x+(spritedefs+l_frame)->cx;
	Source.top=(spritedefs+l_frame)->y;
	Source.bottom=(spritedefs+l_frame)->y+(spritedefs+l_frame)->cy;

	Dest.left=x-CameraX;
	Dest.right=x+cx-CameraX;
	Dest.top=y-CameraY+CameraYOffset;
	Dest.bottom=y+cy-CameraY+CameraYOffset;

	lpDDSBack->Blt(&Dest,lpDDSSprites,&Source,DDBLT_WAIT | DDBLT_KEYSRC,NULL);
}


void DrawBullets()
{
	RECT Source,Dest;
	struct Bullet *tempbullet;
	int frame;
	if(bullets==NULL) return;
	tempbullet=bullets;
	while(1)
		{
			tempbullet->Draw();
			tempbullet=tempbullet->next;
			if(tempbullet==bullets) break;
		}
}


void DrawAmmo()
{
	char ammoc[7];
	int temp;
	int i;
	int div;
	int localammo=Player.ammo[Player.bullettype];

	div=100000;

	for(i=0;i<6;i++)
		{
			temp=localammo/div;
			ammoc[i]=temp+48;
			localammo-=temp*div;
			div/=10;

		}
	ammoc[6]='\0';
	if(Player.bullettype==0) strcpy(ammoc,"------");
	DrawString(1,362,455,ammoc);
	DrawBulletType();

}


void DrawBulletType()
{
	RECT Source,Dest;
	int baseframe;


	baseframe=*(Baseframes+BASEFRAME_BULLET+Player.bullettype);


			Source.left=(spritedefs+baseframe)->x;
			Source.right=(spritedefs+baseframe)->x+(spritedefs+baseframe)->cx;
			Source.top=(spritedefs+baseframe)->y;
			Source.bottom=(spritedefs+baseframe)->y+(spritedefs+baseframe)->cy;

			Dest.left=333;
			Dest.right=349;
			Dest.top=455;
			Dest.bottom=471;

			lpDDSBack->Blt(&Dest,lpDDSSprites,&Source,DDBLT_WAIT | DDBLT_KEYSRC,NULL);

}

void DrawBackground()
{
	int x,y;
	int x1,y1;
	RECT Source,Dest;
	char buffer[200];
	long dx,dy;
	int ddrval;
	int index,tile;
	int StartX,StartY,EndX,EndY;

	dx=CameraX-OldCameraX;
	dy=CameraY-CameraYOffset-OldCameraY;
	OldCameraX=CameraX;
	OldCameraY=CameraY-CameraYOffset;

	//DrawEntireBackground();
	//BlitBackground();
	//return;
	Source.left=Source.top=0;
	Source.right=640;
	Source.bottom=480;
	if(dx>0) Source.left=dx;
	if(dx<0) Source.right+=dx;
	if(dy>0) Source.top=dy;
	if(dy<0) Source.bottom+=dy;

	Dest.left=Dest.top=0;
	Dest.right=640;
	Dest.bottom=480;
	if(dx>0) Dest.right-=dx;
	if(dx<0) Dest.left=-dx;
	if(dy>0) Dest.bottom-=dy;
	if(dy<0) Dest.top=-dy;
	ddrval=lpDDSBack->Blt(&Dest,lpDDSBack2,&Source,DDBLT_WAIT,NULL);
	if(ddrval!=DD_OK)
		{
			HandleBadResult(ddrval,20);

		}

	if(dx>0)
		{
			StartX=(CameraX-1)/32+19-dx/32;
			EndX=StartX+2+dx/32;
			StartY=(CameraY-CameraYOffset)/32;
			EndY=StartY+15;
			for(x=StartX,x1=0;x<EndX;x++,x1++)
				{
					for(y=StartY,y1=0;y<EndY;y++,y1++)
						{
							index=y*LevelX+x;
							tile=level[index];
							Source=PreComp[tile];
							Dest.left=(x-CameraX/32)*32-(CameraX%32);
							Dest.top=(y-(CameraY-CameraYOffset)/32)*32-((CameraY-CameraYOffset)%32);
							Dest.right=Dest.left+32;
							Dest.bottom=Dest.top+32;
							ddrval=lpDDSBack->Blt(&Dest,lpDDSBlocks,&Source,DDBLT_WAIT,NULL);

						}
				}
		}

	if(dx<0)
		{
			StartX=(CameraX-1)/32;
			EndX=StartX+2-dx/32;
			StartY=(CameraY-CameraYOffset)/32;
			EndY=StartY+15;
			for(x=StartX,x1=0;x<EndX;x++,x1++)
				{
					for(y=StartY,y1=0;y<EndY;y++,y1++)
						{
							index=y*LevelX+x;
							tile=level[index];
							Source=PreComp[tile];
							Dest.left=(x-CameraX/32)*32-(CameraX%32);
							Dest.top=(y-(CameraY-CameraYOffset)/32)*32-((CameraY-CameraYOffset)%32);
							Dest.right=Dest.left+32;
							Dest.bottom=Dest.top+32;
							ddrval=lpDDSBack->Blt(&Dest,lpDDSBlocks,&Source,DDBLT_WAIT,NULL);

						}
				}
		}

	if(dy>0)
		{
			StartY=(CameraY-CameraYOffset-1)/32+14-dy/32;
			EndY=StartY+2+dy/32;
			StartX=CameraX/32;
			EndX=StartX+21;
			for(x=StartX,x1=0;x<EndX;x++,x1++)
				{
					for(y=StartY,y1=0;y<EndY;y++,y1++)
						{
							index=y*LevelX+x;
							tile=level[index];
							Source=PreComp[tile];
							Dest.left=(x-CameraX/32)*32-(CameraX%32);
							Dest.top=(y-(CameraY-CameraYOffset)/32)*32-((CameraY-CameraYOffset)%32);
							Dest.right=Dest.left+32;
							Dest.bottom=Dest.top+32;
							ddrval=lpDDSBack->Blt(&Dest,lpDDSBlocks,&Source,DDBLT_WAIT,NULL);

						}
				}
		}

	if(dy<0)
		{
			StartY=(CameraY-CameraYOffset-1)/32;
			EndY=StartY+2-dy/32;
			StartX=CameraX/32;
			EndX=StartX+21;


			for(x=StartX,x1=0;x<EndX;x++,x1++)
				{
					for(y=StartY,y1=0;y<EndY;y++,y1++)
						{
							index=y*LevelX+x;
							tile=level[index];
							Source=PreComp[tile];
							Dest.left=(x-CameraX/32)*32-(CameraX%32);
							Dest.top=(y-(CameraY-CameraYOffset)/32)*32-((CameraY-CameraYOffset)%32);
							Dest.right=Dest.left+32;
							Dest.bottom=Dest.top+32;
							ddrval=lpDDSBack->Blt(&Dest,lpDDSBlocks,&Source,DDBLT_WAIT,NULL);

						}
				}
		}


	Source.left=Source.top=0;
	Source.right=640;
	Source.bottom=480;
	Dest.left=Dest.top=0;
	Dest.right=640;
	Dest.bottom=480;

	ddrval=lpDDSBack2->Blt(&Dest,lpDDSBack,&Source,DDBLT_WAIT,NULL);
	if(ddrval!=DD_OK)
		{
			HandleBadResult(ddrval,22);

		}

}
