#include "EasyX++.h"

int main()
{
	/*initgraph(600, 500, 1);
	SetWindowTitle(_T("≤‚ ‘ Window For EasyX++"));
	Audio Mood(_T("C:\\Users\\chuqw\\Downloads\\Music\\Mood.mp3")), Mask(_T(".\\Mask.wma"));
	Mask.Play();
	Mood.Play();
	_getch();
	closegraph();*/
	initgraph(600, 500, 1);
	setbkmode(TRANSPARENT);
	OpentTextAntiAliasing();
	SetWindowBackgroundColor(WHITE);
	std::wstring ws = StringToWString(GetClipboardString());
	Button b(5, 5, 300, 300, ws.c_str());
	Button c(180, 200, 140, 134, _T("Œ“≤‚ƒ„√«¬Ì"));
	Button a(100, 300, 100, 20, _T("wdnmd"));
	ExMessage mmsg;
	for (;;)
	{
		peekmessage(&mmsg);
		BeginBatchDraw();
		b.Flush(mmsg);
		c.Flush(mmsg);
		a.Flush(mmsg);
		FlushBatchDraw();
		HpSleep(1000/60);
		std::cout << GetFPS() << std::endl;
	}
	closegraph();
	return 0;
}