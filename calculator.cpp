#include <windows.h>
#include <string>
#include <cstdio>
using namespace std;

HWND hEdit1, hEdit2;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message) {
    case WM_CREATE: {

        // ช่อง Please input two numbers
        CreateWindow("STATIC", " Please input two numbers", WS_VISIBLE | WS_CHILD ,
            25, 20, 200, 25, hwnd, NULL, NULL, NULL);

        // ช่องกรอกตัวเลขช่อง 1 
        hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
            50, 55, 150, 25, hwnd, (HMENU)1, NULL, NULL);

        // ช่องกรอกตัวเลขช่อง 2
        hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
            50, 90, 150, 25, hwnd, (HMENU)2, NULL, NULL);

        // ปุ่ม +, -, *, /
        CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 60, 130, 30, 30, hwnd, (HMENU)10, NULL, NULL);
        CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 95, 130, 30, 30, hwnd, (HMENU)11, NULL, NULL);
        CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 130, 130, 30, 30, hwnd, (HMENU)12, NULL, NULL);
        CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 165, 130, 30, 30, hwnd, (HMENU)13, NULL, NULL);
        break;
    }
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (wmId >= 10 && wmId <= 13) {

            char b1[32], b2[32];
            GetWindowText(hEdit1, b1, 32);
            GetWindowText(hEdit2, b2, 32);
            double n1 = atof(b1), n2 = atof(b2), res = 0;

            if (wmId == 10) res = n1 + n2;
            else if (wmId == 11) res = n1 - n2;
            else if (wmId == 12) res = n1 * n2;
            else if (wmId == 13) res = (n2 != 0) ? n1 / n2 : 0;

            char out[64];
            sprintf(out, "%f", res); 

            string s = out;
            MessageBox(hwnd, s.c_str(), "Result", MB_OK);
        }
    break;
    }   
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(0, 8, 245));
	wc.lpszClassName = "MyCalcClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"MyCalcClass","My Calculator",WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT, /* x */
        CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

    while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
    return 0;
} // g++ main.cpp -o MyCalculator.exe -mwindows
