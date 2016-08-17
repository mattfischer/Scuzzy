#include "input.h"

/*
void ProcessInput()
{
	if(KEY_DOWN(VK_ESCAPE)) PostQuitMessage(0);
	if(Player.status==DYING) return;
	Player.xv=0;

	/*if(KEY_DOWN(VK_1)) Player.bullettype=0;
	if(KEY_DOWN(VK_2)) Player.bullettype=1;
	if(KEY_DOWN(VK_SPACE))
		{
			if(!SpaceFlag)
				{
					SpaceFlag=1;
					FireBullet();


				}
		}
	if(KEY_UP(VK_SPACE)) SpaceFlag=0;


	if(KEY_DOWN(VK_RIGHT))
		{
			if(CameraX<LevelX*32-650) CameraX+=10;
		}
	if(KEY_DOWN(VK_LEFT))
		{

			if(CameraX>10) CameraX-=10;
		}
	/*if(KEY_DOWN(VK_CONTROL))
	   {

		  if(!ControlFlag)
			  {
				if(!CanRectMove(Player.x,Player.y,(spritedefs+Player.frame)->cx,(spritedefs+Player.frame)->cy,0,1))
					{


						Player.yv=-30;
						ControlFlag=1;
						Player.status=STARTJUMP;
					}
				}
		}

	if(KEY_UP(VK_CONTROL)) ControlFlag=0;


	if(KEY_DOWN(VK_DOWN))
		{
			if(CameraY<LevelY*32-490+68) CameraY+=10;
		}
	if(KEY_DOWN(VK_UP))
		{
			if(CameraY>10) CameraY-=10;
		}
	/*if(KEY_UP(VK_UP) && KEY_UP(VK_DOWN))
		{
			//if(!CanRectMove(Player.x,Player.y,(spritedefs+Player.frame)->cx,(spritedefs+Player.frame)->cy,0,1))
			//	{
					Player.looking=0;
					if(abs(CameraYOffset)<15) CameraYOffset=0;
					if(CameraYOffset>0) CameraYOffset-=15;
					else if(CameraYOffset<0) CameraYOffset+=15;
			//	}
			//else CameraYOffset=0;
		}

	*/

//}


void ProcessInput()
{
	char buffer[200];

	if(KEY_DOWN(VK_ESCAPE)) PostQuitMessage(0);
	if(Player.status==DYING) return;


	if(KEY_DOWN('1')) Player.bullettype=0;
	if(KEY_DOWN('2')) Player.bullettype=1;

	if(Player.specialstatus!=PIPE)
		{
	if(KEY_DOWN(VK_SPACE))
		{
			if(!SpaceFlag)
				{
					SpaceFlag=1;
					FireBullet();


				}
		}
	if(KEY_UP(VK_SPACE)) SpaceFlag=0;

	if(Player.landwater==LAND)
		{

			//Player.xv=0;
			//Player.xa=0;

			//wsprintf(buffer,"Before: xa=%i, xv=%i  ",(int)Player.xa,(int)Player.xv);
			//DebugString(buffer);
			if(Player.xv>0 && Player.xv<=1 && Player.xa<=0)
				{
					Player.xv=0;
					Player.xa=0;
				}
			if(Player.xv<0 && Player.xv>=-1 && Player.xa>=0)
				{
					Player.xv=0;
					Player.xa=0;
				}
			if(KEY_UP(VK_RIGHT) && KEY_UP(VK_LEFT))
				{
				if(Player.xv>0) Player.xa=-1;
				if(Player.xv<0) Player.xa=1;
				if(Player.xv==0) Player.xa=0;
				}


			if(KEY_DOWN(VK_RIGHT))
				{

					Player.direction=1;
					//Player.xv=5;
					Player.xa=1;
				}
			if(KEY_DOWN(VK_LEFT))
				{

					Player.direction=-1;
					//Player.xv=-5;
					Player.xa=-1;
				}
			//wsprintf(buffer,"After: xa=%i, xv=%i\n",(int)Player.xa,(int)Player.xv);
			//DebugString(buffer);



	if(KEY_DOWN(VK_CONTROL))
	   {

		  if(!ControlFlag)
			  {
				if(!CanRectMove(Player.x,Player.y,Player.cx,Player.cy,0,1) || Player.specialstatus)
					{
						if(KEY_DOWN(VK_DOWN) && Player.specialstatus)
							{
								Player.yv=20;
								Player.fall=1;
								Player.specialstatus=NORMAL;
								Player.status=JUMPING;
							}
						else
			   				{	Player.yv=-10;
								Player.status=STARTJUMP;
							}
						ControlTimer=GetTickCount();
						ControlFlag=1;
					}
				}
		}
	if(KEY_UP(VK_CONTROL)) {

		ControlFlag=0;
		ControlTimer=-1;
	}
	if(KEY_DOWN(VK_DOWN))
		{
			Player.looking=1;
			if(VertOffsetTimer<0) VertOffsetTimer=GetTickCount();
			if(GetTickCount()-VertOffsetTimer>150)
				{

					if(CameraYOffset>-100 && CameraY-CameraYOffset<LevelY*64-422 && (!CanRectMove(Player.x,Player.y,Player.cx,Player.cy,0,1) || Player.specialstatus) && Player.xv==0) CameraYOffset-=4;
					if(Player.fall && CameraYOffset!=0) CameraYOffset-=(abs(CameraYOffset)/CameraYOffset)*6;
				}
		}
	if(KEY_DOWN(VK_UP))
		{

			if(!HitSwitch())
				{
							Player.looking=-1;
					if(VertOffsetTimer<0) VertOffsetTimer=GetTickCount();
						if(GetTickCount()-VertOffsetTimer>150)
							{

							if(CameraYOffset<100 && CameraY-CameraYOffset>5 && (!CanRectMove(Player.x,Player.y,Player.cx,Player.cy,0,1) || Player.specialstatus) && Player.xv==0) CameraYOffset+=4;
							}
						}
			UpFlag=1;
		}
	if(KEY_UP(VK_UP)) UpFlag=0;
	if(KEY_UP(VK_UP) && KEY_UP(VK_DOWN))
		{
			//if(!CanRectMove(Player.x,Player.y,(spritedefs+Player.frame)->cx,(spritedefs+Player.frame)->cy,0,1))
			//	{
					Player.looking=0;
					VertOffsetTimer=-1;
					/*if(Player.status==JUMPING)
						{
							if(abs(CameraYOffset)<6) CameraYOffset=0;
							if(CameraYOffset>0) CameraYOffset-=6;
							else if(CameraYOffset<0) CameraYOffset+=6;
						}
					else
					*/
						if(Player.status!=JUMPING)
						{

							if(abs(CameraYOffset)<10) CameraYOffset=0;
							if(CameraYOffset>0) CameraYOffset-=10;
							else if(CameraYOffset<0) CameraYOffset+=10;
						}

			//	}
			//else CameraYOffset=0;
		}
	}
}

if(Player.landwater==WATER)
	{
		//Player.xa=0;
		//Player.ya=0;

		Player.status=STANDING;

		if(KEY_DOWN(VK_UP))
			{
				Player.ya=-.5;
				Player.status=SWIMMING;
			}
		if(KEY_DOWN(VK_DOWN))
			{
				Player.ya=.5;
				Player.status=SWIMMING;
			}
		if(KEY_UP(VK_UP)&& KEY_UP(VK_DOWN))
			{
				Player.ya=0;
			}

		if(KEY_DOWN(VK_LEFT))
			{
				Player.xa=-.5;
				Player.status=SWIMMING;
			}
		if(KEY_DOWN(VK_RIGHT))
			{
				Player.xa=.5;
				Player.status=SWIMMING;

			}

		if(KEY_UP(VK_RIGHT)&& KEY_UP(VK_LEFT))
			{
				Player.xa=0;
			}

	}
}

