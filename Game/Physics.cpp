#include "physics.h"

void MoveRect(int *ax,int *ay,int cx,int cy,int dx,int dy,int isplayer)
{
	int x1,y1;
	int xa,ya;
	int xb,yb;
	int x,y;
	int dx1,dy1;
	int ResultX,ResultY;
	int SizeX,SizeY;
	int xc,yc;

	int firsttile,secondtile,thirdtile;
	x=*ax;
	y=*ay;


	x1=x+dx;
	y1=y+dy;

	if(isplayer && Player.specialstatus==PIPE)
		{
			*ax=x1;
			*ay=y1;
			return;
		}
	SizeX=cx;
	SizeY=cy;

	if(dx!=0)
		{
	if(dx>0)
		{
			xa=x1+SizeX-1;
			ya=y;

			xb=x1+SizeX-1;
			yb=y+SizeY-1;

			xc=x1+SizeX-1;
			yc=y+SizeY/2-1;

			dx1=xa%32+1;


			firsttile=xa/32+LevelX*(ya/32);
			secondtile=xb/32+LevelX*(yb/32);
			thirdtile=xc/32+LevelX*(yc/32);

			if(*(physics+firsttile)==1 || *(physics+secondtile)==1 || *(physics+thirdtile)==1)
				ResultX=x1-dx1;
			else
				ResultX=x1;

			}
	if(dx<0)
		{
			xa=x1;
			ya=y;

			xb=x1;
			yb=y+SizeY-1;

			xc=x1;
			yc=y+SizeY/2-1;
			dx1=x%32;

			firsttile=xa/32+LevelX*(ya/32);
			secondtile=xb/32+LevelX*(yb/32);
			thirdtile=xc/32+LevelX*(yc/32);


			if(*(physics+firsttile)==1 || *(physics+secondtile)==1 || *(physics+thirdtile)==1)
				ResultX=x-dx1;
			else
				ResultX=x1;

		}


}
	else ResultX=x;
	if(ResultX<0) ResultX=0;
	if(ResultX>LevelX*32-SizeX) ResultX=LevelX*32-SizeX;
	x=ResultX;
if(dy!=0)
	{
	if(dy>0)
		{
			xa=x;
			ya=y1+SizeY-1;

			xb=x+SizeX-1;
			yb=y1+SizeY-1;

			dy1=ya%32+1;

			firsttile=xa/32+LevelX*(ya/32);
			secondtile=xb/32+LevelX*(yb/32);


			if(*(physics+firsttile)==1 || *(physics+secondtile)==1)
				ResultY=y1-dy1;
			else
				ResultY=y1;

			}
	if(dy<0)
		{
			xa=x;
			ya=y1;

			xb=x+SizeX-1;
			yb=y1;

			dy1=y%32;

			firsttile=xa/32+LevelX*(ya/32);
			secondtile=xb/32+LevelX*(yb/32);


			if(*(physics+firsttile)==1 || *(physics+secondtile)==1)
				ResultY=y-dy1;
			else
				ResultY=y1;

		}

}
else ResultY=y;


	if(ResultY<0) ResultY=0;

	if(ResultY>LevelY*32-SizeY) ResultY=LevelY*32-SizeY;

	*ax=ResultX;
	*ay=ResultY;

}

int CanRectMove(int ax,int ay,int cx,int cy,int dx,int dy)
{
	int x1,y1;
	int xa,ya;
	int xb,yb;
	int x,y;
	int dx1,dy1;
	int ResultX,ResultY;
	int SizeX,SizeY;
	int xc,yc;
	int firsttile,secondtile,thirdtile;
	x=ax;
	y=ay;


	x1=x+dx;
	y1=y+dy;

	SizeX=cx;
	SizeY=cy;

	if(dx!=0)
		{
	if(dx>0)
		{
			xa=x1+SizeX-1;
			ya=y;

			xb=x1+SizeX-1;
			yb=y+SizeY-1;

			xc=x1+SizeX-1;
			yc=y+SizeY/2-1;

			dx1=xa%32+1;

			firsttile=xa/32+LevelX*(ya/32);
			secondtile=xb/32+LevelX*(yb/32);
			thirdtile=xc/32+LevelX*(yc/32);

			if(*(physics+firsttile)==1 || *(physics+secondtile)==1 || *(physics+thirdtile)==1)
				ResultX=x1-dx1;
			else
				ResultX=x1;

			}
	if(dx<0)
		{
			xa=x1;
			ya=y;

			xb=x1;
			yb=y+SizeY-1;

			xc=x1;
			yc=y+SizeY/2-1;

			dx1=x%32;

			firsttile=xa/32+LevelX*(ya/32);
			secondtile=xb/32+LevelX*(yb/32);
			thirdtile=xc/32+LevelX*(yc/32);

			if(*(physics+firsttile)==1 || *(physics+secondtile)==1 || *(physics+thirdtile)==1)
				ResultX=x-dx1;
			else
				ResultX=x1;

		}


}
	else ResultX=x;

	x=ResultX;
if(dy!=0)
	{
	if(dy>0)
		{
			xa=x;
			ya=y1+SizeY-1;

			xb=x+SizeX-1;
			yb=y1+SizeY-1;

			dy1=ya%32+1;

			firsttile=xa/32+LevelX*(ya/32);
			secondtile=xb/32+LevelX*(yb/32);


			if(*(physics+firsttile)==1 || *(physics+secondtile)==1)
				ResultY=y1-dy1;
			else
				ResultY=y1;

			}
	if(dy<0)
		{
			xa=x;
			ya=y1;

			xb=x+SizeX-1;
			yb=y1;

			dy1=y%32;

			firsttile=xa/32+LevelX*(ya/32);
			secondtile=xb/32+LevelX*(yb/32);

			if(*(physics+firsttile)==1 || *(physics+secondtile)==1)
				ResultY=y-dy1;
			else
				ResultY=y1;

		}

}
else ResultY=y;

	if(ResultX<0) ResultX=0;
	if(ResultY<0) ResultY=0;
	if(ResultX>LevelX*32-SizeX) ResultX=LevelX*32-SizeX;
	if(ResultY>LevelY*32-SizeY) ResultY=LevelY*32-SizeY;

	if(ResultX==x1 && ResultY==y1) return 1; else return 0;
}



int RectsOverlap(int x1,int y1,int cx1,int cy1,int x2,int y2,int cx2,int cy2)
{
	if((x1>=x2 && x1<=x2+cx2 && y1>=y2 && y1<=y2+cy2) ||
	   (x1+cx1>=x2 && x1+cx1<=x2+cx2 && y1+cy1>=y2 && y1+cy1<=y2+cy2) ||
       (x2+cx2>=x1 && x2+cx2<=x1+cx1 && y2>=y1 && y2<=y1+cy1) ||
	   (x2>=x1 && x2<=x1+cx1 && y2+cy2>=y1 && y2+cy2<=y1+cy1)) return 1;
	else if((x1<x2 && x1+cx1>x2+cx2 && y1>y2 && y1+cy1<y2+cy2) ||
			(x1>x2 && x1+cx1<x2+cx2 && y1<y2 && y1+cy1>y2+cy2)) return 1;
	return 0;
}
