#include "root.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{



	switch(iMsg)
	{

		case WM_DESTROY:

		PostQuitMessage(0);
		return 0;

	}

	return DefWindowProc(hWnd,iMsg,wParam,lParam);

}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szCmdLine, int iCmdShow)
{



	WNDCLASSEX WndClass;
	MSG Msg;
	char* szAppName="Scuzzy the Frog";
	int rungame=1;
	HINSTANCE hInstance;

	hInstance=hInst;




	WndClass.cbSize=sizeof(WNDCLASSEX);

	WndClass.style=(UINT)NULL;
	WndClass.lpfnWndProc=WndProc;
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hInstance=hInstance;
	WndClass.hIcon=LoadIcon(0,IDI_APPLICATION);
	WndClass.hCursor=NULL;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(NULL_BRUSH);
	WndClass.lpszMenuName=(HMENU)NULL;
	WndClass.lpszClassName=szAppName;
	WndClass.hIconSm=NULL;

	RegisterClassEx(&WndClass);

	hMainWindow=CreateWindowEx(
		(DWORD)NULL,
		szAppName,
		"Scuzzy the Frog",
		WS_VISIBLE | WS_POPUP,
	    0,
	    0,
		640,
		480,
		(HWND)NULL,
		(HMENU)NULL,
		hInstance,
		0
	);

	ShowWindow(hMainWindow, iCmdShow);


	UpdateWindow(hMainWindow);



	ShowCursor(FALSE);

	if(Game_Init()) rungame=0;


	while(1)
		{
			if(PeekMessage(&Msg,NULL,0,0,PM_REMOVE))
				{
					TranslateMessage(&Msg);
					DispatchMessage(&Msg);
				}
			if(Msg.message==WM_QUIT) break;
			if(rungame) Game_Main();
		}


	Game_Shutdown();
	ShowCursor(TRUE);

	return (Msg.wParam);



}



