// AvantExecutable.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "AvantExecutable.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

bool exiting = false;
long windowWidth = 1024;
long windowHeight = 768;
long windowBits = 32;
bool fullscreen = false;
HDC hDC;
int height, width;
float fps;

Avant::OpenGLRenderer *g_glRender = NULL;
Resource::CHiResTimer *g_hiResTimer = NULL;
Avant::Input *input;
Avant::GameEngine * g_engine = NULL;



void SetupPixelFormat(HDC hDC)
{
    int pixelFormat;

    PIXELFORMATDESCRIPTOR pfd =
    {   
        sizeof(PIXELFORMATDESCRIPTOR),  // size
            1,                          // version
            PFD_SUPPORT_OPENGL |        // OpenGL window
            PFD_DRAW_TO_WINDOW |        // render to window
            PFD_DOUBLEBUFFER,           // support double-buffering
            PFD_TYPE_RGBA,              // color type
            32,                         // prefered color depth
            0, 0, 0, 0, 0, 0,           // color bits (ignored)
            0,                          // no alpha buffer
            0,                          // alpha bits (ignored)
            0,                          // no accumulation buffer
            0, 0, 0, 0,                 // accum bits (ignored)
            16,                         // depth buffer
            0,                          // no stencil buffer
            0,                          // no auxiliary buffers
            PFD_MAIN_PLANE,             // main layer
            0,                          // reserved
            0, 0, 0,                    // no layer, visible, damage masks
    };

    pixelFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, pixelFormat, &pfd);
}

void DisplayTitle(HWND hwnd, float fps)
{
  static char title[255];
  sprintf(title, "Operator No. 2 - FPS: %.0f", fps);
  SetWindowText(hwnd, title);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASSEX windowClass;     // window class
    HWND       hwnd;            // window handle
    MSG        msg;             // message
    DWORD      dwExStyle;       // Window Extended Style
    DWORD      dwStyle;         // Window Style
    RECT       windowRect;

////////////////////////////////////////////////////////////////////////////////////////////////////////
//         Creation                                                                                   //
////////////////////////////////////////////////////////////////////////////////////////////////////////
    
	g_glRender = new Avant::OpenGLRenderer;
	g_hiResTimer = new Resource::CHiResTimer;
	/*input = (Avant::Input *) malloc(sizeof(Avant::Input)); dunno why i thought new didnt work*/ 
	
	input = new Avant::Input;
	input->downkey = false;
	input->upkey = false;
	input->rightkey = false;
	input->leftkey = false;
	input->usekey = false;
	input->weaponkey = false;
	input->mouse = false;
	input->mousex = 0;
	input->mousey = 0;
	

	g_engine = new Avant::GameEngine;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////
//			Windows Stuff                                                                             //
////////////////////////////////////////////////////////////////////////////////////////////////////////

    windowRect.left=(long)0;                        // Set Left Value To 0
    windowRect.right=(long)windowWidth; // Set Right Value To Requested Width
    windowRect.top=(long)0;                         // Set Top Value To 0
    windowRect.bottom=(long)windowHeight;   // Set Bottom Value To Requested Height

    // fill out the window class structure
    windowClass.cbSize          = sizeof(WNDCLASSEX);
    windowClass.style           = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc     = WndProc;
    windowClass.cbClsExtra      = 0;
    windowClass.cbWndExtra      = 0;
    windowClass.hInstance       = hInstance;
    windowClass.hIcon           = LoadIcon(NULL, IDI_APPLICATION);  // default icon
    windowClass.hCursor         = LoadCursor(NULL, IDC_ARROW);      // default arrow
    windowClass.hbrBackground   = NULL;                             // don't need background
    windowClass.lpszMenuName    = NULL;                             // no menu
    windowClass.lpszClassName   = "GLClass";
    windowClass.hIconSm         = LoadIcon(NULL, IDI_WINLOGO);      // windows logo small icon

    // register the windows class
    if (!RegisterClassEx(&windowClass))
        return 0;
	int x = MessageBox(NULL, "Display in fullscreen?" , "Display Mode", MB_YESNOCANCEL);
	if(x == IDNO)
	{
		fullscreen = false;
	}
	else if(x == IDYES)
	{
		height = (int) windowHeight;
		width = (int) windowWidth;
		fullscreen = true;
	}
	else
		PostQuitMessage(0);
    
	if (fullscreen)                             // fullscreen?
    {
        DEVMODE dmScreenSettings;                   // device mode
        memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings); 
        dmScreenSettings.dmPelsWidth = windowWidth;         // screen width
        dmScreenSettings.dmPelsHeight = windowHeight;           // screen height
        dmScreenSettings.dmBitsPerPel = windowBits;             // bits per pixel
        dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

        // 
        if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            // setting display mode failed, switch to windowed
            MessageBox(NULL, "Display mode failed", NULL, MB_OK);
            fullscreen = FALSE; 
        }
    }

    if (fullscreen)                             // Are We Still In Fullscreen Mode?
    {
        dwExStyle=WS_EX_APPWINDOW;                  // Window Extended Style
        dwStyle=WS_POPUP;                       // Windows Style
        ShowCursor(FALSE);                      // Hide Mouse Pointer
    }
    else
    {
        dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // Window Extended Style
        dwStyle=WS_OVERLAPPEDWINDOW;                    // Windows Style
    }

    AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);     // Adjust Window To True Requested Size

    // class registered, so now create our window
    hwnd = CreateWindowEx(NULL,                                 // extended style
        "GLClass",                          // class name
        "Operator No. 2",      // app name
        dwStyle | WS_CLIPCHILDREN |
        WS_CLIPSIBLINGS,
        0, 0,                               // x,y coordinate
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top, // width, height
        NULL,                               // handle to parent
        NULL,                               // handle to menu
        hInstance,                          // application instance
        NULL);                              // no extra params

    hDC = GetDC(hwnd);

    // check if window creation failed (hwnd would equal NULL)
    if (!hwnd)
        return 0;

    ShowWindow(hwnd, SW_SHOW);          // display the window
    UpdateWindow(hwnd);                 // update the window
////////////////////////////////////////////////////////////////////////////////////////////////////////
//         Init                                                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////////

	g_glRender->AttachToGame(g_engine); 
	g_hiResTimer->Init();
	
	bool result = g_glRender->Init();
	if(!result)
	{
		MessageBox(NULL, "Game Initialization failed" , "Failed" , MB_OK);
		PostQuitMessage(0);
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//			Font                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////////

	HFONT hFont = CreateFont(14,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,
							ANTIALIASED_QUALITY,FF_DONTCARE | DEFAULT_PITCH, "Courier");

	if(!hFont)
	{
		MessageBox(NULL, "Font could not be created" , "Failed" , MB_OK);
	}

	SelectObject(hDC, hFont);
	
	wglUseFontBitmaps(hDC, 32, 96, (DWORD) g_glRender->getFontBase());


////////////////////////////////////////////////////////////////////////////////////////////////////////
//			Main App Loop                                                                             //
////////////////////////////////////////////////////////////////////////////////////////////////////////

    while (!exiting) 
    {
		
		g_engine->state = Avant::GameEngine::GAMESTATE_MENU;
		/*choice = g_engine->getMenuChoice(); or something
		switch(choice)
		{
		case: newGame
			  {
				  g_engine->state = Avant::GameEngine::GAMESTATE_LOADING;
				  g_engine->loadCampaign(); or something
				  g_engine->state = Avant::GameEngine::GAMESTATE_RUNNING;
				  break;
			  }

		case: loadGame
			  {
				  g_engine->state = Avant::GameEngine::GAMESTATE_LOADING;
				  g_engine->loadLevel(LevelTheyAreOn); 
				  g_engine->state = Avant::GameEngine::GAMESTATE_RUNNING;
				  break;
			  }

		case: options
			  {
				  g_engine->state = Avant::GameEngine::GAMESTATE_OPTIONS;
				  if(options are changed)
				  {
					  Writer.writeToConfigFile();
				  }
				  own menu code too like back button
				  break;
			  }

		case: quit
			  {
				  g_engine->state = Avant::GameEngine::GAMESTATE_EXITING;
				  exiting = true;
				  break;
			  }
		*/

        g_glRender->Prepare(g_hiResTimer->GetElapsedSeconds(1), input);
		//fps = g_hiResTimer->LockFPS(150);
        fps = g_hiResTimer->GetFPS();
		DisplayTitle(hwnd, fps);
		g_glRender->Render();
		SwapBuffers(hDC);

        while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            if (!GetMessage (&msg, NULL, 0, 0))
            {
                exiting = true;
                break;
            }

            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////
//			Exiting                                                                                   //
////////////////////////////////////////////////////////////////////////////////////////////////////////
    
	g_glRender->Shutdown();
	delete g_glRender;
	delete input;
	delete g_engine;
	delete g_hiResTimer;

    if (fullscreen)
    {
        ChangeDisplaySettings(NULL,0);          // If So Switch Back To The Desktop
        ShowCursor(TRUE);                       // Show Mouse Pointer
    }

    return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_AVANTEXECUTABLE);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_AVANTEXECUTABLE;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	static HDC hdc;
	static HGLRC hRC;

	switch (message) 
	{
	
	case WM_CREATE:         // window creation
        hDC = GetDC(hWnd);
        SetupPixelFormat(hDC);
        //SetupPalette();
        hRC = wglCreateContext(hDC);
        wglMakeCurrent(hDC, hRC);
        break;

	case WM_SIZE:
        height = HIWORD(lParam);        // retrieve width and height
        width = LOWORD(lParam);

        g_glRender->SetupProjection(width, height);

        break;

    case WM_ACTIVATEAPP:        // activate app
        break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	
	case WM_KEYDOWN:
        int fwKeys;
        LPARAM keyData;
        fwKeys = (int)wParam;    // virtual-key code 
        keyData = lParam;          // key data 

        switch(fwKeys)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;

		case 65:      //A
			input->leftkey = true;
			break;
		case 87:      //W
			input->upkey = true;
			break;
		case 83:      //S
			input->downkey = true;
			break;
		case 68:      //D
			input->rightkey = true;
			break;
		case 81:      //Q
			input->weaponkey = true;
			break;
		case 69:      //E
			input->usekey = true;
			break;
		
        default:
            break;
        }

        break;
	
	

	case WM_KEYUP:
		switch((int)wParam)
		{
		case 65:      //A
			input->leftkey = false;
			break;
		case 87:      //W
			input->upkey = false;
			break;
		case 83:      //S
			input->downkey = false;
			break;
		case 68:      //D
			input->rightkey = false;
			break;
		case 81:      //Q
			input->weaponkey = false;
			break;
		case 69:      //E
			input->usekey = false;
			break;
		}
		
		break;

	case WM_MOUSEMOVE:
		input->mousex = LOWORD(lParam);
		input->mousey = HIWORD(lParam);
		break;

	case WM_LBUTTONDOWN:
		input->mouse = true;
		break;
	case WM_LBUTTONUP:
		input->mouse = false;
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	
	case WM_DESTROY:
	case WM_QUIT:
    case WM_CLOSE:    
		wglMakeCurrent(hDC, NULL);
        wglDeleteContext(hRC);
		PostQuitMessage(0);
		break;
	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
