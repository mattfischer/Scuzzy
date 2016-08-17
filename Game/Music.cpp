#include <windows.h>
#include <dmusici.h>
#include <dmusicc.h>
#include <dmerror.h>
#include <direct.h>

IDirectMusicPerformance *perf;
IDirectMusicLoader *loader;
IDirectMusicSegment *segment;
IDirectMusicSegmentState *segstate;
DMUS_OBJECTDESC desc;
char szDir[_MAX_PATH];
WCHAR wszDir[_MAX_PATH];
WCHAR wszFileName[60];

extern void DebugString(char*);

void StartMusic()
{
	HRESULT dummy;

	CoInitialize(NULL);


	CoCreateInstance(CLSID_DirectMusicPerformance,NULL,CLSCTX_INPROC,IID_IDirectMusicPerformance,(void**)&perf);
	perf->Init(NULL,NULL,NULL);
	perf->AddPort(NULL);
	CoCreateInstance(CLSID_DirectMusicLoader,NULL,CLSCTX_INPROC,IID_IDirectMusicLoader,(void**)&loader);
	_getcwd(szDir, _MAX_PATH);

#define MULTI_TO_WIDE( x,y )  MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, y, -1, x, _MAX_PATH )


    MULTI_TO_WIDE(wszDir, szDir);
    DebugString("Set Search Directory...\n");

	dummy=loader->SetSearchDirectory(GUID_DirectMusicAllTypes, wszDir, FALSE);

	desc.dwSize = sizeof(DMUS_OBJECTDESC);
	desc.guidClass = CLSID_DirectMusicSegment;
    MULTI_TO_WIDE(wszFileName,"song 1.mid");
	wcscpy( desc.wszFileName, wszFileName);
    desc.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME;


 	loader->GetObject(&desc,IID_IDirectMusicSegment, (void**)&segment);

	segment->SetParam(GUID_StandardMIDIFile, -1, 0, 0, (void*)perf);

	segment->SetParam(GUID_Download, -1, 0, 0, (void*)perf);

	segment->SetRepeats(10000);
	perf->PlaySegment(segment, 0, 0, &segstate);

}

void CleanupDirectMusic()
{
	perf->Stop( NULL, NULL, 0, 0 );

    segment->SetParam(GUID_Unload, -1, 0, 0, (void*)perf);


    segment->Release();


    perf->CloseDown();
    perf->Release();


    loader->Release();


    CoUninitialize();

}

