#include "UI.h"

inline void UIAnimation(int Color, int* NowColor)
{
	int r = GetRValue(*NowColor), g = GetGValue(*NowColor), b = GetBValue(*NowColor);
	if (std::abs(GetRValue(Color) - r) > ANIMATION) r += (GetRValue(Color) - r) < 0 ? -ANIMATION : ANIMATION;
	else if (r != GetRValue(Color))	r = GetRValue(Color);
	if (std::abs(GetGValue(Color) - g) > ANIMATION) g += (GetGValue(Color) - g) < 0 ? -ANIMATION : ANIMATION;
	else if (g != GetGValue(Color)) g = GetGValue(Color);
	if (std::abs(GetBValue(Color) - b) > ANIMATION) b += (GetBValue(Color) - b) < 0 ? -ANIMATION : ANIMATION;
	else if (b != GetBValue(Color)) b = GetBValue(Color);
	*NowColor = RGB(r, g, b);
}

Button::Button(int x, int y, int width, int height, std::wstring text)
{
	Button::X = x; Button::Y = y; Button::Width = width; Button::Height = height;
	Button::Text = text;
	Button::TextRectangle = { x,y,x + width,y + height };
}
Button::Button(int x, int y, int width, int height, std::wstring text, ButtonStyle style)
{
	Button::X = x; Button::Y = y; Button::Width = width; Button::Height = height;
	Button::Text = text;
	Button::Style = style;
	Button::TextRectangle = { x,y,x + width,y + height };
}
void Button::Reset(int x, int y, int width, int height)
{
	Button::X = x; Button::Y = y; Button::Width = width; Button::Height = height;
	Button::TextRectangle = { x,y,x + width,y + height };
}
void Button::SetStyle(ButtonStyle style)
{
	Button::Style = style;
}
void Button::RedirectRenderFunction(void (*Function)(int))
{
	Button::RedirectRender = Function;
}
void Button::SetUIMsgProc(void (*UIMsgProc)(int))
{
	Button::MsgProc = UIMsgProc;
}
void Button::SetText(std::wstring text)
{
	Button::Text = text;
}
void Button::SetTextRender(UINT type)
{
	Button::TextRenderType = type;
}
void Button::Render(int style)
{
	UIAnimation(Button::Style.EdgeColor[style], &(Button::Edge));
	UIAnimation(Button::Style.BackgroundColor[style], &(Button::Background));
	UIAnimation(Button::Style.TextColor[style], &(Button::text));
	setfillcolor(Button::Background);
	setlinecolor(Button::Edge);
	fillroundrect(Button::X, Button::Y, Button::X + Button::Width, Button::Y + Button::Height, 5, 5);
	settextcolor(Button::text);
	drawtext(Button::Text.c_str(), &(Button::TextRectangle), Button::TextRenderType);
}
int Button::Flush(ExMessage mmsg)
{
	int NowStyle = UI_NORMAL;
	if (mmsg.x > Button::X && mmsg.x<(Button::X + Button::Width) && mmsg.y>Button::Y && mmsg.y < (Button::Y + Button::Height))
	{
		NowStyle = UI_ONPASS;
		if (mmsg.lbutton == true) NowStyle = UI_ONCLICK;
	}
	if (Button::RedirectRender == NULL) Button::Render(NowStyle);
	else Button::RedirectRender(NowStyle);
	if (Button::MsgProc != NULL) Button::MsgProc(NowStyle);
	return NowStyle;
}