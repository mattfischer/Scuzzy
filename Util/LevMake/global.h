#define BULLET 62
struct Animset {
	int frameoffset;
	int x;
	int y;
	int cx;
	int cy;
};

struct Player_Info {

	int x;
	int y;
	float xv;
	float yv;
	float xa;
	float ya;
	int cx;
	int cy;
	float compositexv;
	float compositeyv;
	int frame;
	int direction;
	unsigned long frametimer;
	int status;
	int health;
	int invul;
	unsigned long invultimer;
	int flashstate;
	unsigned long flashtimer;
	int ammo[2];
	int bullettype;
	int looking;
	int onchain;
	int onplatform;
	int fall;
	int animset;
	struct Animset *setlist;
	int platformnum;
	int specialstatus;
	int YOffset;
	int XOffset;
	int landwater;
	int pipenum;

};

struct Sprite_Info {

	int x;
	int y;
	int xv;
	int yv;
	int xa;
	int ya;
	int cx;
	int cy;
	int frame;
	int baseframe;
	int direction;
	unsigned long frametimer;
	int type;
	int status;
	int animset;
	int isstatic;
	struct Animset *setlist;
	struct Sprite_Info *next;
	struct Sprite_Info *prev;

};

struct Sprite_Def {
	int x;
	int y;
	int cx;
	int cy;

};

struct Bullet {


	int x;
	int y;
	int cx;
	int cy;
	int direction;
	int xv;
	int yv;
	int ya;
	int type;
	int frame;
	long frametimer;
	int status;
	int baseframe;
	long bullettimer;
	int animset;
	struct Animset *setlist;
	struct Bullet *next;
	struct Bullet *prev;


};


struct Chain_Def {
	int x;
	int y;
	int cx;
	int type;
};

struct Chain {

	int x;
	int y;
	int cx;
	int type;

	struct Chain *next;
	struct Chain *prev;

};


struct Platform_Def {
	int cx;
	int numpoints;
	int type;
	int sprite;
	int speed;
};

struct Platform {

	double x;
	double y;
	int cx;
	double dx;
	double dy;
	double linelength;
	int numpoints;
	int type;
	int sprite;
	int *points;
	int status;
	int movepoint;
	int lastpoint;
	int speed;
	int number;

	struct Platform *next;
	struct Platform *prev;

};

struct Switch_Def {
	int x;
	int y;
	int sprite;
	int type;
	int target;
};


struct Switch {

	int x;
	int y;
	int cx;
	int cy;
	int sprite;
	int state;
	int type;
	int frametimer;
	int target;

};

struct Pipe {
	int x;
	int y;
	int xlength;
	int ylength;
	int direction;
};

#define SLEEPING  -1
#define STANDING  0
#define WALKING   1
#define STARTJUMP 2
#define JUMPING	 3
#define DYING     4
#define FLIPSWITCH 5
#define SWIMMING 1

#define BULLET_NORMAL 0
#define BULLET_BLOWUP 1

#define BASEFRAME_PLAYER 0
#define BASEFRAME_SPRITE 1

#define BASEFRAME_POW_100 3
#define BASEFRAME_POW_200 4
#define BASEFRAME_POW_500 5
#define BASEFRAME_POW_1000 6
#define BASEFRAME_POW_5000 7
#define BASEFRAME_POW_AMMO   8
#define BASEFRAME_POW_HEALTH 9

#define BASEFRAME_BULLET 10

#define BASEFRAME_CHAIN  12

#define BASEFRAME_PLATFORM 13

#define BASEFRAME_SWITCH 15
#define BASEFRAME_STATIC 16

#define SET_PLAYER 0
#define SET_SPRITE1 4
#define SET_SPRITE2 6

#define SET_AMMO   8
#define SET_HEALTH 9

#define SET_BULLET1 10
#define SET_BULLET2 14

#define PLATFORM_STOPPED 0
#define PLATFORM_MOVING  1

#define PLATFORMTYPE_STATIONARY 0
#define PLATFORMTYPE_MOVEALWAYS 1
#define PLATFORMTYPE_MOVEONCE	2
#define PLATFORMTYPE_DOOR		3

#define SWITCH_TOGGLE 0
#define SWITCH_RETURN 1

#define NORMAL 0
#define PLATFORM 1
#define CHAIN 2
#define PIPE 3

#define LAND 0
#define WATER 1
