#include "player.h"

Player_Info::Player_Info()
{
	frametimer=GetTickCount();
	health=5;
	direction=1;

	xv=0;
	yv=0;
	xa=0;
	ya=0;
	invul=0;
	flashstate=0;
	ammo[0]=0;
	ammo[1]=10;
	bullettype=0;

	looking=0;

	fall=0;
	animset=0;

	platformnum=-1;
	//Player.cx=(spritedefs+*(Baseframes+BASEFRAME_PLAYER))->cx;
	//Player.cy=(spritedefs+*(Baseframes+BASEFRAME_PLAYER))->cy;
	specialstatus=NORMAL;
	landwater=LAND;
	pipenum=-1;
}

void Player_Info::InitPlayer(int PlayerX,int PlayerY,struct Animset *PlayerSetList)
{
	x=PlayerX;
	y=PlayerY;
	setlist=PlayerSetList+SET_PLAYER;
	cx=(setlist+animset)->cx;
	cy=(setlist+animset)->cy;
	XOffset=(setlist+animset)->x;
	YOffset=(setlist+animset)->y;
	wsprintf(buffer,"Player is %ix%i, offset %ix%i\n",cx,cy,XOffset,YOffset);
	DebugString(buffer);
}

void Player_Info::Draw()
{
	int l_frame;
	if(flashstate==1) return;
	l_frame=frame+(setlist+animset)->frameoffset;


	if(specialstatus!=PIPE) BlitSprite(l_frame,x-CameraX-XOffset,y-CameraY+CameraYOffset-YOffset);
}


void Player_Info::Update()
{

	if(invul==1) if(GetTickCount()>invultimer+3000) invul=0;
	if(invul==1)
		{
	if(GetTickCount()>flashtimer+100)
		{
			if(flashstate==1) flashstate=0;
			else Player.flashstate=1;
			flashtimer=GetTickCount();
		}
}
	else flashstate=0;

	if(status==DYING)
		{
			frame=0;
			xv=5*Player.direction;
			ya=5;
			yv+=ya;
			x+=xv;
			y+=yv;
			if(yv>25) yv=15;
			if(y>CameraY+480) PostQuitMessage(0);
			if(direction==1) animset=0;
			if(direction==-1) animset=1;
			return;

		}

if(landwater==LAND)
{
	if(status==FLIPSWITCH)
		{
			if(GetTickCount()<frametimer+250)
				{
					frame=10;
					if(direction==1) animset=0;
					if(direction==-1) animset=1;
					if(specialstatus==CHAIN) animset+=2;
					return;
				}
			else status=STANDING;
		}

	if(!CanRectMove(x,y,cx,cy,0,1) || specialstatus)
		{

		if(status==JUMPING)
			{
				//CameraYOffset=0;
				frame=0;
				if(xv==0) status=STANDING;
				else			 status=WALKING;
			}
		if(status==WALKING || status==STANDING)
			{
		if(xv!=0)
		{
			status=WALKING;
			if(GetTickCount()>frametimer+70)
				{
					frametimer=GetTickCount();
					frame++;
					if(frame>=5) frame=1;
				}
		}

	else
	{
		frame=0;
		status=STANDING;
	}
	}

}

if(CanRectMove(x,y,cx,cy,0,1) && status!=STARTJUMP && status!=JUMPING && !specialstatus) status=JUMPING;

	if(status==STARTJUMP)
				{
					frame=5;
					status=JUMPING;
				}
	else if(status==JUMPING)
				{
					if(yv<0) frame=6;
					else frame=7;
				}

	if(CanRectMove(x,y,cx,cy,0,1))
		{
			ya=.8;
			if(ControlTimer>0 && GetTickCount()-ControlTimer<200) yv-=.75;

		}

	else				ya=0;


	if(specialstatus!=PIPE) if(yv<0 && !CanRectMove(x,y,cx,cy,0,-1)) yv=0;
	if(specialstatus==CHAIN || specialstatus==PIPE && yv>=0 && fall==0) ya=0;
	xv+=xa;
	yv+=ya;

	if(specialstatus!=PIPE) if(yv>10) yv=10;
	if(specialstatus!=PIPE) if(xv>5) xv=5;
	if(specialstatus!=PIPE) if(xv<-5) xv=-5;

	if(status==STANDING && looking==-1) frame=8;
	if(status==STANDING && looking==1) frame=9;


	if(direction==1) animset=0;
	if(direction==-1) animset=1;
	if(specialstatus==CHAIN) animset+=2;
	if(specialstatus==PIPE) frame=0;
}

if(landwater==WATER)
	{

		if(status==STANDING) frame=0;
		if(status==SWIMMING)
			if(GetTickCount()>frametimer+70)
				{
					frametimer=GetTickCount();
					frame++;
					if(frame>=4) frame=0;
				}

		if(status==STANDING)
			{
				if(xv>0) xa=-.05;
				if(xv<0) xa=.05;
				if(yv>1) ya=-.05;
				if(yv<1) ya=.05;


			}

		xv+=xa;
		yv+=ya;


		if(ya>0 && yv>0 && yv<1) yv=1;
		if(xv>2) xv=2;
		if(xv<-2) xv=-2;
		if(yv>2) yv=2;
		if(yv<-2) yv=-2;

		if(xv>.5) direction=1;
		if(xv<-.5) direction=-1;
		if(direction==1) animset=0;
	    if(direction==-1) animset=1;
		//if(xv>0 && xv<1) xv=1;
		//if(xv<0 && xv>-1) xv=-1;
	}


	MoveRect(&x,&y,cx,cy,xv,yv,1);
	compositexv=xv;
	compositeyv=yv;

	if(specialstatus==PIPE)
		{
			if(physics[x/32+y*LevelX/32]!=0)
				{
			if((Pipes+pipenum)->direction==0)
				if(y<(Pipes+pipenum)->y) y=(Pipes+pipenum)->y+16;
			if((Pipes+pipenum)->direction==1)
				if(x>(Pipes+pipenum)->x+(Pipes+pipenum)->xlength*32) x=(Pipes+pipenum)->x+(Pipes+pipenum)->xlength*32-16;
			if((Pipes+pipenum)->direction==2)
				if(y>(Pipes+pipenum)->y+(Pipes+pipenum)->ylength*32) y=(Pipes+pipenum)->y+(Pipes+pipenum)->ylength*32-16;
			if((Pipes+pipenum)->direction==3)
				if(x<(Pipes+pipenum)->x) x=(Pipes+pipenum)->x+16;
			}
		}
}

void Player_Info::CheckLandWater()
{
	int firsttile=x/32+LevelX*(y/32);
	int secondtile=x/32+LevelX*((y+cy)/32);


	if(*(physics+firsttile)==3 && *(physics+secondtile)==3)
		{
			if(landwater==LAND)
				{

					yv=5;
					status=STANDING;
				}
			landwater=WATER;

		}

	if(*(physics+firsttile)!=3 && *(physics+secondtile)!=3)
		{
			landwater=LAND;

		}


}
void Player_Info::HandleCollisions()
{

	int i;
	int found;
	struct Sprite_Info *temp;

	if(status==DYING) return;

	if(specialstatus==PIPE) specialstatus=NORMAL;
	for(i=0;i<NumPipes;i++)
		{
			//if(Player.x>=(Pipes+i)->x && Player.x<(Pipes+i)->x+(Pipes+i)->xlength*32 && Player.y>(Pipes+i)->y && Player.y<(Pipes+i)->y+(Pipes+i)->ylength*32)
			if(RectsOverlap(x,y,cx,cy,(Pipes+i)->x,(Pipes+i)->y,(Pipes+i)->xlength*32,(Pipes+i)->ylength*32))
				{

							//wsprintf(buffer,"Potentially in pipe %i\n",i);
							//DebugString(buffer);

							if(i<pipenum)
							   {
							//	wsprintf(buffer,"Pipe %i rejected\n",i);
							//	DebugString(buffer);
								continue;
							}

							pipenum=i;
							//wsprintf(buffer,"In pipe %i\n",i);
							//DebugString(buffer);
							specialstatus=PIPE;
							if((Pipes+i)->direction==0)
								{
									yv=-35;
									xv=0;
									x=(Pipes+i)->x+16;
								}
							if((Pipes+i)->direction==2)
								{
									yv=35;
									xv=0;
									x=(Pipes+i)->x+16;
								}

							if((Pipes+i)->direction==1)
								{
									yv=0;
									xv=35;
									y=(Pipes+i)->y+16;
								}
							if((Pipes+i)->direction==3)
								{
									yv=0;
									xv=-35;
									y=(Pipes+i)->y+16;
								}


							ya=0;
							status=STANDING;

						}


		}


		if(specialstatus!=PIPE){
		    //DebugString("Not in pipe\n");
			pipenum=-1;

		}
		else return;






	if(specialstatus==CHAIN) specialstatus=NORMAL;
	found=0;
	for(i=0;i<NumChains;i++)
		{
			if(x>=(Chains+i)->x && x<(Chains+i)->x+(Chains+i)->cx*32 && y>(Chains+i)->y-SnapResolution && y<(Chains+i)->y+SnapResolution)
				{
					found=1;
					if(yv>=0 && fall==0)
						{


							specialstatus=CHAIN;
							yv=0;
							ya=0;
							y=(Chains+i)->y;
							status=STANDING;
						}

				}
		}



	if(status==PLATFORM) specialstatus=NORMAL;
	platformnum=-1;
	for(i=0;i<NumPlatforms;i++)
		{
			if((Platforms+i)->type!=PLATFORMTYPE_DOOR)
				{

					if(x+cx>=(Platforms+i)->x && x<(Platforms+i)->x+(Platforms+i)->cx && y+cy>(Platforms+i)->y-2 && y+cy<(Platforms+i)->y+SnapResolution)
						{
							found=1;
							if(yv>=0 && fall==0)
								{


									specialstatus=PLATFORM;
									yv=0;
									ya=0;
									y=(Platforms+i)->y-cy;
									status=STANDING;
									platformnum=i;
								}

						}
				}
			else
				{
					if(RectsOverlap(x,y,cx,cy,(Platforms+i)->x,(Platforms+i)->y,8,(Platforms+i)->cx))
						{


							//if(Player.x+Player.cx/2>(Platforms+i)->x)
							if(compositexv<0)
								x=(Platforms+i)->x+8;
							else
								x=(Platforms+i)->x-cx;
						}

				}
		}


	if(found==0) fall=0;


	if(specialstatus==PIPE) return;
	for(i=0;i<NumSprites;i++)
		{
			temp=GetSprite(i);

			if(temp->isstatic) continue;
			//if(RectsOverlap(Player.x,Player.y,(spritedefs+(Player.frame))->cx,(spritedefs+(Player.frame))->cy,temp->x,temp->y,(spritedefs+temp->frame+temp->baseframe)->cx,(spritedefs+temp->frame+temp->baseframe)->cy))
			if(RectsOverlap(x,y,cx,cy,temp->x,temp->y,temp->cx,temp->cy))
				{
					if(temp->type==1 || temp->type==2)
						if(temp->status!=DYING) DoDamage();

					if(temp->type==BASEFRAME_POW_100)
						{
							Score+=100;
							i--;
							CreateFloatingScore(BASEFRAME_FLOAT_100,temp->x,temp->y);
							DeleteSprite(temp);
							continue;
						}

					if(temp->type==BASEFRAME_POW_200)
						{
							Score+=200;
							i--;
							CreateFloatingScore(BASEFRAME_FLOAT_200,temp->x,temp->y);
							DeleteSprite(temp);
							continue;
						}
					if(temp->type==BASEFRAME_POW_500)
						{
							Score+=500;
							i--;
							CreateFloatingScore(BASEFRAME_FLOAT_500,temp->x,temp->y);
							DeleteSprite(temp);
							continue;
						}
					if(temp->type==BASEFRAME_POW_1000)
						{
							Score+=1000;
							i--;
							CreateFloatingScore(BASEFRAME_FLOAT_1000,temp->x,temp->y);
							DeleteSprite(temp);
							continue;
						}
					if(temp->type==BASEFRAME_POW_5000)
						{
							Score+=5000;
							i--;
							CreateFloatingScore(BASEFRAME_FLOAT_5000,temp->x,temp->y);
							DeleteSprite(temp);
							continue;
						}

					if(temp->type==BASEFRAME_POW_AMMO)
						{
							ammo[1]+=5;
							i--;
							DeleteSprite(temp);
							continue;
						}
					if(temp->type==BASEFRAME_POW_HEALTH)
						{
							if(health<5) health++;
							i--;
							DeleteSprite(temp);
							continue;
						}
				}
		}
}

void DoDamage()
{
	if(Player.invul==0)
	{
		MessageBeep(MB_ICONASTERISK);
		if(Player.health>0) Player.health--;
		if(Player.health>0)
			{
				Player.invul=1;
				Player.invultimer=GetTickCount();
				Player.flashtimer=GetTickCount();
			}
		else
			{
				Player.status=DYING;
				Player.yv=-30;
			}
	}
}

void FireBullet()
{
int xv;
int bx,by;
int bcx,bcy;
if(Player.ammo[Player.bullettype]==0 && Player.bullettype!=0) return;
if(Player.bullettype!=0) Player.ammo[Player.bullettype]--;
if(Player.bullettype==0) xv=25;
if(Player.bullettype==1) xv=10;

if(!KEY_DOWN(VK_UP) && !KEY_DOWN(VK_DOWN))
	{

		//if(Player.direction==-1) CreateBullet(Player.x-(spritedefs+*(Baseframes+BASEFRAME_BULLET+Player.bullettype))->cx,Player.y+Player.cy/2-(spritedefs+*(Baseframes+BASEFRAME_BULLET+Player.bullettype))->cy/2,Player.bullettype,-xv,0);
		//if(Player.direction==1)  CreateBullet(Player.x+Player.cx,Player.y+Player.cy/2-(spritedefs+*(Baseframes+BASEFRAME_BULLET+Player.bullettype))->cy/2,Player.bullettype,xv,0);
		bcx=(spritedefs+*(Baseframes+BASEFRAME_BULLET+Player.bullettype))->cx;
		bcy=(spritedefs+*(Baseframes+BASEFRAME_BULLET+Player.bullettype))->cy;
		if(Player.bullettype==0)
			{
				bcx=(spritedefs+*(Baseframes+BASEFRAME_BULLET+(Sets+SET_BULLET1+1)->frameoffset))->cx;
				bcy=(spritedefs+*(Baseframes+BASEFRAME_BULLET+(Sets+SET_BULLET1+1)->frameoffset))->cx;
			}
		if(Player.direction==-1)
			{
				bx=Player.x-bcx;
				by=Player.y+Player.cy/2-bcy/2;
				CreateBullet(bx,by,Player.bullettype,-xv,0);
			}
		if(Player.direction==1)
			{
				bx=Player.x+Player.cx;
				by=Player.y+Player.cy/2-bcy/2;
				CreateBullet(bx,by,Player.bullettype,xv,0);
			}
		wsprintf(buffer,"Firing bullet at %ix%i, size %ix%i, Player at %ix%i, size %ix%i\n",bx,by,bcx,bcy, Player.x,Player.y,Player.cx,Player.cy);
		DebugString(buffer);
		return;
	}
if(KEY_DOWN(VK_UP))
	{
		CreateBullet(Player.x+(spritedefs+Player.frame)->cx/2-(spritedefs+*(Baseframes+BASEFRAME_BULLET+Player.bullettype))->cx/2,Player.y-(spritedefs+*(Baseframes+BASEFRAME_BULLET+Player.bullettype))->cy,Player.bullettype,0,-xv);
		return;
	}
if(KEY_DOWN(VK_DOWN))
	{
		if(!CanRectMove(Player.x,Player.y,Player.cx,Player.cy,0,1))
			{
			if(Player.direction==-1) CreateBullet(Player.x-(spritedefs+*(Baseframes+BASEFRAME_BULLET+Player.bullettype))->cx,Player.y+(spritedefs+Player.frame)->cy/2-(spritedefs+62)->cy/2,Player.bullettype,-xv,0);
			if(Player.direction==1)  CreateBullet(Player.x+(spritedefs+Player.frame)->cx,Player.y+(spritedefs+Player.frame)->cy/2-(spritedefs+*(Baseframes+BASEFRAME_BULLET+Player.bullettype))->cy/2,Player.bullettype,xv,0);
			}
		else CreateBullet(Player.x+Player.cx/2-(spritedefs+*(Baseframes+BASEFRAME_BULLET+Player.bullettype))->cx/2,Player.y+Player.cy,Player.bullettype,0,xv);
		return;
	}

}

void CreateFloatingScore(int baseframe,int x,int y)
{
	Sprite_Info *temp;

	DebugString("Creating Floating Score\n");
	temp=(Sprite_Info*)malloc(sizeof(Sprite_Info));
	temp->x=x;
	temp->y=y;
	temp->frametimer=GetTickCount();
	temp->xv=0;
	temp->yv=-1;
	temp->xa=0;
	temp->ya=0;
	temp->type=baseframe;
	temp->baseframe=*(Baseframes+baseframe);
	temp->cx=(spritedefs+temp->baseframe)->cx;
	temp->cy=(spritedefs+temp->baseframe)->cy;
	temp->isstatic=0;
	temp->setlist=&EmptySet;
	temp->floating=1;
	if(Sprites==NULL)
		{

			Sprites=temp;
			Sprites->next=Sprites;
			Sprites->prev=Sprites;
			NumSprites++;
			return;
		}
	else
		{
			temp->prev=Sprites->prev;
			temp->next=Sprites;
			Sprites->prev->next=temp;
			Sprites->prev=temp;
			NumSprites++;
			return;
		}
}
