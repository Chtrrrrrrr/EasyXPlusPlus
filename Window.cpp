#include "Window.h"

void SetWindowBackgroundColor(int Color)
{
	setbkcolor(Color);
	clearcliprgn();
}
void SetWindowTitle(std::wstring Title)
{
	SetWindowTextW(GetHWnd(), Title.c_str());
	SetConsoleTitle(Title.c_str());
}
void SetWindowIcon(int Icon)
{
	::LoadIcon(NULL, (LPCWSTR)Icon);
}
void SetWindowCursor(HCURSOR Cursor)
{
	SetWindowPos(GetHWnd(), HWND_TOP, 500, 300, 0, 0, SWP_NOSIZE);//加载
	::SetClassLong(GetHWnd(), GCLP_HCURSOR, (LONG)Cursor);           //设置
}
void Blur()
{
	DWORD* pMem = GetImageBuffer();	// 获取显示缓冲区地址
	for (int i = getwidth(); i < (getwidth() * (getheight() - 1)); ++i)
	{
		pMem[i] = RGB(
			(GetRValue(pMem[i]) + GetRValue(pMem[i - getwidth()]) + GetRValue(pMem[i - 1]) + GetRValue(pMem[i + 1]) + GetRValue(pMem[i + getwidth()])) / 5,
			(GetGValue(pMem[i]) + GetGValue(pMem[i - getwidth()]) + GetGValue(pMem[i - 1]) + GetGValue(pMem[i + 1]) + GetGValue(pMem[i + getwidth()])) / 5,
			(GetBValue(pMem[i]) + GetBValue(pMem[i - getwidth()]) + GetBValue(pMem[i - 1]) + GetBValue(pMem[i + 1]) + GetBValue(pMem[i + getwidth()])) / 5);
	}
}
int GetFPS()
{
	static int fps = 0;
	static int lastTime = GetCurrentTime(); //ms
	static int frameCount = 0;

	++frameCount;

	register int curTime = GetCurrentTime();
	if (curTime - lastTime > 1000) //1s
	{
		fps = frameCount;
		frameCount = 0;
		lastTime = curTime;
	}
	return fps;
}
void SetTextSize(double Size)
{
	LOGFONT NowSize;
	gettextstyle(&NowSize);
	NowSize.lfHeight = double(NowSize.lfHeight) * Size;
	NowSize.lfWeight = 0;
	settextstyle(&NowSize);
}
void OpentTextAntiAliasing()
{
	LOGFONT NowStyle;
	gettextstyle(&NowStyle);
	NowStyle.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&NowStyle);
}
void CloseTextAntiAliasing()
{
	LOGFONT NowStyle;
	gettextstyle(&NowStyle);
	NowStyle.lfQuality = NONANTIALIASED_QUALITY;
	settextstyle(&NowStyle);
}
void LoadFontPath(LPTSTR Path)
{
	AddFontResourceEx(Path, FR_PRIVATE, NULL);
}
void CloseFontPath(LPTSTR Path)
{
	RemoveFontResourceEx(Path, FR_PRIVATE, NULL);
}
void TopWindow()
{
	::SetWindowPos(GetHWnd(), HWND_TOPMOST, 0, 0, 100, 100, SWP_NOMOVE | SWP_NOSIZE);
}
void BottomWindow()
{
	::SetWindowPos(GetHWnd(), HWND_BOTTOM, 0, 0, 100, 100, SWP_NOMOVE | SWP_NOSIZE);
}
void HideWindow()
{
	::SetWindowPos(GetHWnd(), HWND_BOTTOM, 0, 0, 100, 100, SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW);
}
void ShowWindow()
{
	::SetWindowPos(GetHWnd(), HWND_NOTOPMOST, 0, 0, 100, 100, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}