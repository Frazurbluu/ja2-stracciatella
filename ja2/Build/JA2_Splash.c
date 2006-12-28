#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
#else
	#include "Types.h"
	#include "VSurface.h"
	#include "Timer_Control.h"
	#include <stdio.h>
	#include "TopicIDs.h"
	#include "LibraryDataBase.h"
	#include "TopicOps.h"
	#include "Debug.h"
	#include "MainMenuScreen.h"
	#include "Video.h"
#endif

#ifndef ENGLISH
#	include "Multi_Language_Graphic_Utils.h"
#endif


UINT32 guiSplashFrameFade = 10;
UINT32 guiSplashStartTime = 0;
extern HVSURFACE ghFrameBuffer;

//Simply create videosurface, load image, and draw it to the screen.
void InitJA2SplashScreen()
{
	UINT32 uiLogoID = 0;
	STRING512			CurrentDir;
	STRING512			DataDir;
	HVSURFACE hVSurface;
	INT32 i = 0;

	InitializeJA2Clock();
	// Get Executable Directory
	GetExecutableDirectory( CurrentDir );

	// Adjust Current Dir
	sprintf( DataDir, "%s\\Data", CurrentDir );
	if ( !SetFileManCurrentDirectory( DataDir ) )
	{
		DebugMsg( TOPIC_JA2, DBG_LEVEL_3, "Could not find data directory, shutting down");
		return;
	}

	//Initialize the file database
	InitializeFileDatabase( gGameLibaries, NUMBER_OF_LIBRARIES );

#if !defined( ENGLISH ) && defined( JA2TESTVERSION )
	if (!AddVideoSurfaceFromFile("LOADSCREENS\\Notification.sti", &uiLogoID))
	{
		AssertMsg( 0, String( "Failed to load %s", VSurfaceDesc.ImageFile ) );
		return;
	}
	hVSurface = GetVideoSurface(uiLogoID);
	BltVideoSurfaceToVideoSurface(ghFrameBuffer, hVSurface, 0, 0, NULL);
	DeleteVideoSurfaceFromIndex( uiLogoID );


	InvalidateScreen();
	RefreshScreen();

	guiSplashStartTime = GetJA2Clock();
	while( i < 60 * 15 )//guiSplashStartTime + 15000 > GetJA2Clock() )
	{
		//Allow the user to pick his bum.
		InvalidateScreen();
		RefreshScreen();
		i++;
	}
#endif

	#ifdef ENGLISH
		ClearMainMenu();
	#else
		{
			SGPFILENAME ImageFile;
			GetMLGFilename(ImageFile, MLG_SPLASH);
			if (!AddVideoSurfaceFromFile(ImageFile, &uiLogoID))
			{
				AssertMsg(0, String("Failed to load %s", ImageFile));
				return;
			}

			hVSurface = GetVideoSurface(uiLogoID);
			BltVideoSurfaceToVideoSurface(ghFrameBuffer, hVSurface, 0, 0, NULL);
			DeleteVideoSurfaceFromIndex( uiLogoID );
		}
	#endif


	InvalidateScreen();
	RefreshScreen();

	guiSplashStartTime = GetJA2Clock();
}
