#include <windows.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR CmdLine, int iCmdShow)
{
	HANDLE InFile;
	HANDLE OutFile;

	int x,y;
	DWORD dummy;
	UCHAR tempdata[4];

	InFile=CreateFile("d:\\lcc\\Projects\\Scuzzy32x\\Game\\lcc\\blocks.raw",GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
	OutFile=CreateFile("d:\\lcc\\Projects\\Scuzzy32x\\Game\\lcc\\blocks.dat",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);

	for(y=0;y<480;y++)
		for(x=0;x<640;x++)
			{
					ReadFile(InFile,tempdata,3,&dummy,NULL);
					*(tempdata+3)=0;
					WriteFile(OutFile,tempdata,4,&dummy,NULL);


			}

	CloseHandle(InFile);
	CloseHandle(OutFile);

	InFile=CreateFile("d:\\lcc\\Projects\\Scuzzy32x\\Game\\lcc\\sprites.raw",GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
	OutFile=CreateFile("d:\\lcc\\Projects\\Scuzzy32x\\Game\\lcc\\sprites.dat",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);

	for(y=0;y<480;y++)
		for(x=0;x<640;x++)
			{
					ReadFile(InFile,tempdata,3,&dummy,NULL);
					*(tempdata+3)=0;
					WriteFile(OutFile,tempdata,4,&dummy,NULL);


			}

	CloseHandle(InFile);
	CloseHandle(OutFile);

	InFile=CreateFile("d:\\lcc\\Projects\\Scuzzy32x\\Game\\lcc\\system.raw",GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
	OutFile=CreateFile("d:\\lcc\\Projects\\Scuzzy32x\\Game\\lcc\\system.dat",GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);

	for(y=0;y<480;y++)
		for(x=0;x<640;x++)
			{
					ReadFile(InFile,tempdata,3,&dummy,NULL);
					*(tempdata+3)=0;
					WriteFile(OutFile,tempdata,4,&dummy,NULL);


			}

	CloseHandle(InFile);
	CloseHandle(OutFile);
	MessageBox(NULL,"Done","Done",MB_OK);

}

