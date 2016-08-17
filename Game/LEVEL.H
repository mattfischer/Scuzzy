typedef struct tag_SFFileHeader
{
	char id[3]; //"SFL"
	int numlevels;
} SFFileHeader;

typedef struct tag_SFLevelHeader
{
	char id[3]; //"LEV"
	int x;
	int y;
	int numsprites;
	int PlayerX;
	int PlayerY;
} SFLevelHeader;

typedef struct tag_SFSpriteInfo
{
	int type;
	int x;
	int y;
} SFSpriteInfo;

