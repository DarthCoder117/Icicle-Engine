#ifdef ICE_WINDOWS

#include "system/Win32Window.h"
#include <core/Debug.h>

using namespace ice;
using namespace system;


struct WindowInstanceData
{
	WindowInstanceData()
		:m_window(NULL),
		m_windowProc(NULL)
	{

	}

	Win32Window* m_window;
	WNDPROC m_windowProc;
};

Map<HWND, WindowInstanceData> g_windowInstances;//TODO: Replace with lookup table

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WindowInstanceData& inst = g_windowInstances[hWnd];

	inst.m_window->windowProc(hWnd, message, wParam, lParam);

	if (!inst.m_windowProc)
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	else
	{
		return inst.m_windowProc(hWnd, message, wParam, lParam);
	}
}

void Win32Window::windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CLOSE)
	{
		WindowEvent evt;
		evt.window = this;
		evt.type = WindowEvent::CLOSED;

		transmitWindowEvent(evt);
	}
	else if (message == WM_DESTROY)
	{
		//PostQuitMessage(0);
	}
	else if (message == WM_SIZE)
	{
		WindowEvent evt;
		evt.window = this;
		evt.type = WindowEvent::RESIZED;

		evt.size.x = LOWORD(lParam);
		evt.size.y = HIWORD(lParam);

		transmitWindowEvent(evt);
	}
}

Win32Window::Win32Window(const Vec2u& size, const String& windowTitle, HWND existingWindow)
	:m_window(existingWindow)
{
	//If an existing window was supplied then we only have to attach the new window procedure to it
	if (m_window)
	{
		//Update global instance data
		WindowInstanceData& inst = g_windowInstances[m_window];
		inst.m_window = this;
		inst.m_windowProc = (WNDPROC)GetWindowLong(m_window, GWL_WNDPROC);

		//Set new window procedure
		SetWindowLong(m_window, GWL_WNDPROC, (long)WndProc);
	}
	else
	{
		//Create new win32 window
		HINSTANCE hInstance = GetModuleHandle(0);

		LPCSTR ClassName = __TEXT("IcicleEngineWindowClass");

		// Register Class
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = 0;
		wcex.lpszClassName = ClassName;
		wcex.hIconSm = 0;

		wcex.hIcon = (HICON)LoadImage(hInstance, __TEXT("icicle-engine.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

		ATOM ret = RegisterClassEx(&wcex);
		DWORD error = GetLastError();
		printf("");

		//Create window
		m_window = CreateWindow(ClassName,
			windowTitle.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			size.x, size.y,
			NULL,
			NULL,
			hInstance,
			NULL);

		error = GetLastError();

		if (!m_window)
		{
			core::Debug::error("Could not create win32 window. Error code: "+error);
			return;
		}

		//Update global instance data
		WindowInstanceData& inst = g_windowInstances[m_window];
		inst.m_window = this;
	}

	//Show window
	ShowWindow(m_window, SW_SHOWDEFAULT);
	UpdateWindow(m_window);
}

bool Win32Window::run()
{
	if (!m_window)
	{
		return false;
	}

	MSG msg;

	if (PeekMessage(&msg, m_window, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

void Win32Window::close()
{
	DestroyWindow(m_window);
	m_window = NULL;
}

void Win32Window::setWindowTitle(const String& title)
{
	SetWindowText(m_window, title.c_str());
}

Vec2u Win32Window::getWindowSize()
{
	RECT rect;
	GetClientRect(m_window, &rect);

	return Vec2u(rect.right, rect.bottom);
}

WindowHandle Win32Window::getSystemHandle()
{
	return m_window;
}
#endif //ICE_WINDOWS