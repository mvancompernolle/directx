// include the basic windows header file
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

ID3D11Device *dev;
ID3D11DeviceContext *devcon;
IDXGISwapChain *swapchain;

void initD3D( HWND hWnd );
void cleanD3D();

// the WindowProc function prototype
LRESULT CALLBACK WindowProc( HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam );

// the entry point for any Windows program
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	// the handle for the window, filled by a function
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory( &wc, sizeof( WNDCLASSEX ) );

	// fill in the struct with the needed information
	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass1";

	RECT wr = { 0, 0, 500, 400 };
	AdjustWindowRect( &wr, WS_OVERLAPPED, FALSE );

	// register the window class
	RegisterClassEx( &wc );

	// create the window and use the result as the handle
	hWnd = CreateWindowEx( NULL,
		"WindowClass1",    // name of the window class
		"Our First Windowed Program",   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		300,    // x-position of the window
		300,    // y-position of the window
		wr.right - wr.left,    // width of the window
		wr.bottom - wr.top,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL );    // used with multiple windows, NULL

				   // display the window on the screen
	ShowWindow( hWnd, nCmdShow );

	initD3D( hWnd );

	// enter the main loop:

	// this struct holds Windows event messages
	MSG msg = {0};

	while ( TRUE ) {
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {
			// translate keystroke messages into the right format
			TranslateMessage( &msg );

			// send the message to the WindowProc function
			DispatchMessage( &msg );

			// check to see if it's time to quit
			if ( msg.message == WM_QUIT ) {
				break;
			}
		} else {

		}
	}

	cleanD3D();

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {
	// sort through and find what code to run for the message given
	switch ( message ) {
		// this message is read when the window is closed
		case WM_DESTROY:
		{
			// close the application entirely
			PostQuitMessage( 0 );
			return 0;
		} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc( hWnd, message, wParam, lParam );
}

void initD3D( HWND hWnd ) {
	// create a struct to hold info about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory( &scd, sizeof( DXGI_SWAP_CHAIN_DESC ) );

	// fill the swap chain description struct
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 4;
	scd.Windowed = TRUE;

	// create a device, device context and swap chain using the info in the scd struct
	D3D11CreateDeviceAndSwapChain( NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon );
}

void cleanD3D( ) {
	swapchain->Release();
	dev->Release();
	devcon->Release();
}