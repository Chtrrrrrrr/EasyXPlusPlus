#pragma once
#include "Header.h"

//平时
const int UI_NORMAL = 0;
//鼠标悬停
const int UI_ONPASS = 1;
//按下
const int UI_ONCLICK = 2;

//动画的快慢
const int ANIMATION = 7;

//按钮的外观结构体
struct ButtonStyle
{
	/* 0：平时，1：鼠标悬停，2：点击 */
	//边框颜色
	int EdgeColor[3] = { RGB(208, 208, 208) ,RGB(0, 120, 212) ,RGB(0, 120, 212) };
	//背景颜色
	int BackgroundColor[3] = { RGB(253, 253, 253) ,RGB(224, 238, 249) ,RGB(204, 228, 247) };
	//文字颜色
	int TextColor[3] = { RGB(0, 0, 0) , RGB(0, 0, 0) , RGB(94, 94, 94) };
};
//按钮
class Button
{
public:
	Button() {};
	//左上角X坐标，左上角Y坐标，宽度，高度，显示内容
	Button(int, int, int, int, std::wstring);
	//左上角X坐标，左上角Y坐标，宽度，高度，显示内容，外观结构体
	Button(int, int, int, int, std::wstring, ButtonStyle);
	//设置按钮外观结构体
	void SetStyle(ButtonStyle);
	//刷新按钮并渲染
	//返回当前状态
	int Flush(ExMessage);
	//重定向按钮的渲染函数，如果为NULL则使用默认
	//函数返回值void，参数int，内容为当前状态
	void RedirectRenderFunction(void (*)(int));
	//设置按钮的消息处理函数，如果为NULL则不使用
	// 函数返回值void，参数int，内容为当前状态
	void SetUIMsgProc(void (*)(int));
	//设置内容
	void SetText(std::wstring);
	//重新设置按钮位置和内容
	//左上角X坐标，左上角Y坐标，宽度，高度
	void Reset(int, int, int, int);
	//设置超出按钮的文本显示方法
	//详见 https://docs.easyx.cn/zh-cn/drawtext
	//DT_WORDBREAK：超出部分自动换行，DT_WORD_ELLIPSIS：超出部分截断并用...代替
	void SetTextRender(UINT);
private:
	int X, Y, Width, Height; //大小
	int Edge = RGB(0, 120, 212), Background = RGB(253, 253, 253), text = RGB(0, 0, 0); //当前颜色
	UINT TextRenderType = DT_WORD_ELLIPSIS | DT_CENTER | DT_VCENTER | DT_SINGLELINE; //内容渲染模式
	std::wstring Text; //内容
	ButtonStyle Style; //外观结构体
	RECT TextRectangle; //内容输出的矩形范围
	void (*RedirectRender) (int) = NULL, (*MsgProc) (int) = NULL; //自定义渲染函数，消息处理函数

	void Render(int); //渲染函数
};

//拖拽条的外观结构体
struct SeekBarStyle
{
	/* 0：平时，1：鼠标悬停，2：点击 */
	//左侧/下方 颜色
	int LeftLineColor[3] = { RGB(0, 103, 192) ,RGB(0, 103, 192) ,RGB(0, 103, 192) };
	//右侧/上方 颜色
	int RightLineColor[3] = { RGB(127, 127, 127) ,RGB(127, 127, 127) ,RGB(127, 127, 127) };
	//中间按钮边框颜色
	int ButtonEdgeColor[3] = { RGB(254, 254, 255) , RGB(254, 254, 255) , RGB(254, 254, 255) };
	//中间按钮颜色
	int ButtonColor[3] = { RGB(0, 103, 192) , RGB(0, 103, 192) , RGB(51, 133, 204) };
};
//拖拽条
class SeekBar
{
public:
	SeekBar() {};
	//[=======(O)------]
	//左上角X坐标，左上角Y坐标，宽度，高度，圆形按钮的总体半径，中间部分和外框的距离
	SeekBar(int, int, int, int, int, int);
	//左上角X坐标，左上角Y坐标，宽度，高度，圆形按钮的总体半径，中间部分和外框的距离，外观结构体
	SeekBar(int, int, int, int, int, int, SeekBarStyle);
	//设置拖拽条外观结构体
	void SetStyle(ButtonStyle);
	//刷新拖拽条并渲染
	//返回当前状态
	int Flush(ExMessage);
	//重定向按钮的渲染函数，如果为NULL则使用默认
	//函数返回值void，参数int，内容为当前状态和当前拖拽长度（左侧/下方）
	void RedirectRenderFunction(void (*)(int, int));
	//设置的拖拽条处理函数，如果为NULL则不使用
	// 函数返回值void，参数int，内容为当前状态和当前拖拽长度（左侧/下方）
	void SetUIMsgProc(void (*)(int, int));
	//设置当前拖拽长度（左侧/下方）
	void SetLength(std::wstring);
	//重新设置拖拽条位置
	void Reset(int, int, int, int, int, int);
private:
	int X, Y, Width, Height, Radius, EdgeWidth; //大小
	int LeftLine = RGB(0, 103, 192), RightLine = RGB(127, 127, 127), ButtonEdgeColor = RGB(254, 254, 255), ButtonColor = RGB(0, 103, 192); //当前颜色
	SeekBarStyle Style; //外观结构体
	void (*RedirectRender) (int, int) = NULL, (*MsgProc) (int, int) = NULL; //自定义渲染函数，消息处理函数
	bool IsOnClick = false; //是否正在被拖动

	void Render(int);
};
