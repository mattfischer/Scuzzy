#include "sprites.h"

Bullet *Bullet::Update()
{

	if(type==0)
		{
			if(!CanRectMove(x,y,cx,cy,xv,yv) && status==BULLET_NORMAL)
				{
					MoveRect(&x,&y,cx,cy,xv,yv,0);
					status=BULLET_BLOWUP;
					frame=1;
					cx=(spritedefs+baseframe+(setlist+animset)->frameoffset+frame)->cx;
					cy=(spritedefs+baseframe+(setlist+animset)->frameoffset+frame)->cy;

					frametimer=GetTickCount();
				}

			if(status==BULLET_NORMAL)
				{

					x+=xv;
					y+=yv;
				}
		}
		if(type==1)
			{

			if(GetTickCount()>bullettimer+5000) status=BULLET_BLOWUP;
			if(status==BULLET_NORMAL)
				{
					yv+=ya;
					MoveRect(&x,&y,cx,cy,xv,yv,0);

					if(!CanRectMove(x,y,cx,cy,xv,0)) xv*=-1;
					if(!CanRectMove(x,y,cx,cy,0,yv)) yv*=-1.25;
					if(yv>15) yv=15;
					if(yv<-15) yv=-15;
					if(xv>15) xv=15;
					if(xv<-15) xv=-15;

					if(yv==0) yv=-7;
				}
		}
			if(status==BULLET_BLOWUP)
				{

					if(GetTickCount()>frametimer+20)
						{
							frame++;
							frametimer=GetTickCount();
						}

				}

			temp=next;
			if(temp==bullets) temp=NULL;

			if(x>CameraX+1140 || x<CameraX-cx-500 || y>CameraY+980 || y<CameraY-cy-500 || (status==BULLET_BLOWUP && frame==5))
			{
			DeleteBullet(this);
			}
	return temp;
}


void UpdateBullets()
{
	struct Bullet *tempbullet;
	struct Bullet *todelete;
	char buffer[100];
	if(bullets==NULL) return;
	tempbullet=bullets;
	while(tempbullet!=NULL)
		{
			tempbullet=tempbullet->Update();
		}

}


void LoadSpriteDefs()
{
	HANDLE SpriteInfo;
	DWORD dummy;
	int i;
	char buffer[100];

	SpriteInfo=CreateFile("spritebounds.dat",GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
	ReadFile(SpriteInfo,&NumSpriteDefs,sizeof(NumSpriteDefs),&dummy,NULL);

	spritedefs=(struct Sprite_Def*)malloc(NumSpriteDefs * sizeof(struct Sprite_Def));

	ReadFile(SpriteInfo,spritedefs,NumSpriteDefs*sizeof(struct Sprite_Def),&dummy,NULL);
	CloseHandle(SpriteInfo);
	for(i=0;i<NumSpriteDefs;i++)
		{
			wsprintf(buffer,"Spritedef %i: %ix%i, %ix%i\n",i,(spritedefs+i)->x,(spritedefs+i)->y,(spritedefs+i)->cx,(spritedefs+i)->cy);
			DebugString(buffer);
		}
}

void Sprite_Info::Update()
{
	if(type==1)
		{


			if(direction==-1 && !CanRectMove(x,y,cx,cy,-1,0)) direction=1;
			else if(direction==1 && !CanRectMove(x,y,cx,cy,1,0)) direction=-1;


		}

	if(type==2)
		{



			if(abs(x-Player.x)<1000 && abs(y-Player.y)<1000)
				{
			if(rand()%20==1)
				{
			if(x-Player.x>0) direction=-1;
			if(x-Player.x<0) direction=1;
				}
			if(rand()%100==1)
				{
			if(x-Player.x>0) direction=1;
			if(x-Player.x<0) direction=-1;
				}
			if(!CanRectMove(x,y,cx,cy,direction,0) && rand()%5==1 && !CanRectMove(x,y,cx,cy,0,1))
			{
				yv=-15;
				status=STARTJUMP;
			}

			if(abs(Player.y-y)>128 && abs(Player.x-x)<256 && rand()%100==1 && !CanRectMove(x,y,cx,cy,0,1))
				{
				yv=-15;
				status=STARTJUMP;
			}
		}


		}

	if(floating==1)
	   if(GetTickCount()>frametimer+2000 || y+cy<CameraY+CameraYOffset || y>CameraY+CameraYOffset+480 || x+cx<CameraX || x>CameraX+640){ DeleteSprite(this); return;}
   	if(type!=1 && type!=2)
		{
			x+=xv;
			y+=yv;
			return;
		}
	if(isstatic) return;

	if(status==DYING)
		{
			if(GetTickCount()>frametimer+50)
				{
					frametimer=GetTickCount();
					frame++;
					if(frame>10)
						{


							DeleteSprite(this);
						}

					}

		return;
		}

	if(status==SLEEPING)
		{
			if(x<CameraX+740 && x>CameraX-cx-100 && y<CameraY+580 && y>CameraY-cy-100) status=STANDING;
			return;
		}
	if(!CanRectMove(x,y,cx,cy,0,1))
		{
		if(status==JUMPING)
			{

				frame=0;

				if(xv==0) status=STANDING;
				else	  status=WALKING;
			}
		if(status==WALKING || status==STANDING)
			{
		if(xv!=0)
		{
			status=WALKING;
			if(GetTickCount()> frametimer+70)
				{
					frametimer=GetTickCount();
					if(frame>=4) frame=0;

					frame=frame+1;

					if(frame>=4) frame=0;


				}
		}

	else
		{
		frame=0;

		status=STANDING;
		}
	}
}

if(CanRectMove(x,y,cx,cy,0,1) && status!=STARTJUMP && status!=JUMPING) status=JUMPING;

	if(status==STARTJUMP)
				{

					frame=4;

					status=JUMPING;
				}
	else if(status==JUMPING)
				{

					if(yv<0) frame=5;
					else frame=6;

			}

	if(CanRectMove(x,y,cx,cy,0,1)) ya=2;
	else				ya=0;

	if(yv<0 && !CanRectMove(x,y,cx,cy,0,-1)) yv=0;

	if(direction==-1) xa=-1;
	if(direction==1) xa=1;

	xv+=xa;
	yv+=ya;

	if(yv>25) yv=15;
	if(xv>3) xv=3;
	if(xv<-3) xv=-3;

	MoveRect(&x,&y,cx,cy,xv,yv,0);

	if(direction==1) animset=0;
	if(direction==-1)animset=1;
}

void UpdateSprites()
{

	int i;
	struct Sprite_Info *temp;
	char buffer[50];
	if(Sprites==NULL) return;
	temp=Sprites;
	while(1)
		{
			temp->Update();
			if(Sprites==NULL) break;
			temp=temp->next;
			if(temp==Sprites) break;
		}


}


void CreateBullet(int x,int y,int type,int xv,int yv)
{
struct Bullet *temp;

if(bullets==NULL)
{
bullets=(struct Bullet*)malloc(sizeof(struct Bullet));
temp=bullets;
bullets->next=bullets;
bullets->prev=bullets;
}
else
{
temp=(struct Bullet*)malloc(sizeof(struct Bullet));
bullets->prev->next=temp;
bullets->prev->next->prev=bullets->prev;
bullets->prev=temp;
bullets->prev->next=bullets;
}
temp->x=x;
temp->y=y;
temp->type=type;
temp->xv=xv;
temp->yv=yv;
temp->frame=0;

if(temp->xv>0) temp->direction=1;
else if(temp->xv<0) temp->direction=3;
else if(temp->yv<0) temp->direction=0;
else if(temp->prev->yv>0) temp->direction=2;

temp->animset=temp->direction;
if(type==0)temp->setlist=Sets+SET_BULLET1;
if(type==1)
	{
		temp->setlist=Sets+SET_BULLET2;
		temp->animset=0;
	}

temp->status=BULLET_NORMAL;

temp->baseframe=*(Baseframes+BASEFRAME_BULLET+type);
temp->cx=(spritedefs+temp->baseframe+(temp->setlist+temp->animset)->frameoffset)->cx;
temp->cy=(spritedefs+temp->baseframe+(temp->setlist+temp->animset)->frameoffset)->cy;
if(type==1)	temp->ya=2;
/*if(physics[temp->y*LevelX/32+temp->x/32]!=0)
	{
		temp->x=Player.x+Player.cx/2-temp->cx/2;
		temp->y=Player.y+Player.cy/2-temp->cy/2;
	}
*/
NumBullets++;

temp->bullettimer=GetTickCount();

}

void DeleteBullet(struct Bullet *bullet)
{
	if(bullet==bullets)
		{
			if(bullet->next==bullets && bullet->prev==bullets)
				{

					free(bullets);
					bullets=NULL;
				}
			else
				{
					bullet->prev->next=bullet->next;
					bullet->next->prev=bullet->prev;
					bullets=bullet->next;
					free(bullet);
				}
		}
	else
		{
			bullet->prev->next=bullet->next;
			bullet->next->prev=bullet->prev;
			free(bullet);
		}

NumBullets--;
}

void CheckBulletCollisions()
{
	int i,c;
	struct Sprite_Info *tempsprite;
	struct Bullet *tempbullet;
	int indexnumber;
	char buffer[100];
	for(i=0;i<NumSprites;i++)
	{
		tempsprite=GetSprite(i);
		if(tempsprite->type!=1 && tempsprite->type!=2) continue;
		indexnumber=tempsprite->frame+tempsprite->baseframe;

		for(c=0;c<NumBullets;c++)
			{
				tempbullet=GetBullet(c);
				if(RectsOverlap(tempsprite->x,tempsprite->y,tempsprite->cx,tempsprite->cy,tempbullet->x,tempbullet->y,tempbullet->cx,tempbullet->cy) && tempsprite->status!=DYING)
					{
						DebugString("Bullet Collision\n");
						DeleteBullet(tempbullet);
						tempsprite->status=DYING;
						tempsprite->frametimer=GetTickCount();
						tempsprite->frame=7;

						c--;
						break;
					}
			}
	}
}
struct Sprite_Info *GetSprite(int i)
{
	int c;

	struct Sprite_Info *temp;
	temp=Sprites;
	if(i==0) return temp;

	for(c=0;c<i;c++) temp=temp->next;

	return temp;
}

void DeleteSprite(struct Sprite_Info *sprite)
{




	if(sprite->next==sprite && sprite->prev==sprite)
		{
			free(sprite);
			Sprites=NULL;
			NumSprites=0;
		}
	else
		{

			sprite->prev->next=sprite->next;
			sprite->next->prev=sprite->prev;
			if(sprite==Sprites) Sprites=sprite->next;
			free(sprite);
			NumSprites--;
		}
}

struct Bullet *GetBullet(int i)
{
	int c;

	struct Bullet *temp;
	temp=bullets;
	if(i==0) return temp;

	for(c=0;c<i;c++) temp=temp->next;

	return temp;
}

void Platform::Update()
{
	int x1,y1,x2,y2;

	if(type==PLATFORMTYPE_STATIONARY) return;
	if(status==PLATFORM_STOPPED) return;
	status=PLATFORM_MOVING;


	x1=x;
	y1=y;
	x+=dx;
	y+=dy;
	x2=x;
	y2=y;

	if(Player.platformnum==number)
		{
			Player.x+=(x2-x1);
			Player.y+=(y2-y1);
			Player.compositexv+=(x2-x1);
			Player.compositeyv+=(y2-y1);
		}
	if(abs(x-*(points+movepoint*2))<=abs(dx) && abs(y-*(points+movepoint*2+1))<=abs(dy))
		{
		if(Player.platformnum==number)
			{
				Player.x+=*(points+movepoint*2)-x;
				Player.y+=*(points+movepoint*2+1)-y;
			}
		x=*(points+movepoint*2);
		y=*(points+movepoint*2+1);
		movepoint++;

		if(movepoint==numpoints) movepoint=0;


		if(movepoint!=0) lastpoint=movepoint-1;
		else			 lastpoint=numpoints-1;

		dx=*(points+movepoint*2)-*(points+lastpoint*2);
		dy=*(points+movepoint*2+1)-*(points+lastpoint*2+1);
		linelength=sqrt(dx*dx+dy*dy);
		linelength/=(double)speed;
		dx/=(double)linelength;
		dy/=(double)linelength;

		if(type==PLATFORMTYPE_MOVEONCE || type==PLATFORMTYPE_DOOR) status=PLATFORM_STOPPED;
	}
}
void UpdatePlatforms()
{
	int i;
	double dx,dy;
	int movepoint;
	int lastpoint;
	int x1,y1,x2,y2;
	double linelength;
	char buffer[100];
	Platform *tempplat;
	if(Platforms==NULL) return;

	tempplat=Platforms;
	while(1)
		{
			tempplat->Update();
			tempplat=tempplat->next;
			if(tempplat==Platforms) break;
		}
}

void Switch::Update()
{
	if((Platforms+target)->status==PLATFORM_STOPPED) state=0;
	if((Platforms+target)->status==PLATFORM_MOVING)  state=1;
}


void UpdateSwitches()
{
	int i;

	for(i=0;i<NumSwitches;i++)
		{
			(Switches+i)->Update();
		}

}


int HitSwitch()
{
	int i;
	int x1,y1,cx1,cy1;
	int x2,y2,cx2,cy2;

	if(KEY_DOWN(VK_LEFT) || KEY_DOWN(VK_RIGHT)) return 0;

	x2=Player.x;
	y2=Player.y;

	cx2=Player.cx;
	cy2=Player.cy;
	for(i=0;i<NumSwitches;i++)
		{

			x1=(Switches+i)->x;
			y1=(Switches+i)->y;
			cx1=(Switches+i)->cx;
			cy1=(Switches+i)->cy;

			if(RectsOverlap(x1,y1,cx1,cy1,x2,y2,cx2,cy2))
				{
				if(UpFlag==0)
				{
					if((Switches+i)->state==1 && (Switches+i)->type==SWITCH_RETURN) return 1;
					Player.status=FLIPSWITCH;
					Player.frametimer=GetTickCount();
					if((Switches+i)->type==SWITCH_TOGGLE)
						{
							if((Switches+i)->state==0)
								{
									(Platforms+(Switches+i)->target)->status=PLATFORM_MOVING;
									(Switches+i)->state=1;
								}
							else
								{
		 					   		(Switches+i)->state=0;
									(Platforms+(Switches+i)->target)->status=PLATFORM_STOPPED;
								}
						}
					if((Switches+i)->type==SWITCH_RETURN)
						{
							(Switches+i)->state=1;
							(Platforms+(Switches+i)->target)->status=PLATFORM_MOVING;
						}

				}
					return 1;
			}
		}
	return 0;
}

void Chain::Update()
{
	return;
}

