/*
2023/1/30
窗口有关的内容
*/
#pragma once
#include "Header.h"

//设置背景颜色
void SetWindowBackgroundColor(int);
//设置标题
void SetWindowTitle(std::wstring);
//设置图标
void SetWindowIcon(int);
//设置光标
void SetWindowCursor(HCURSOR);
//全局模糊 https://codebus.cn/yangw/free-dots
//不包括上下两行
void Blur();
//获取fps
//返回fps
int GetFPS();

//字体
//设置字体大小（按比例）
//Size:比例
void SetTextSize(double Size);
//开启字体抗锯齿
void OpentTextAntiAliasing();
//关闭字体抗锯齿
void CloseTextAntiAliasing();
//加载指定路径字体 https://codebus.cn/yangw/use-external-font-file
//Path：路径
void LoadFontPath(LPTSTR Path);
//卸载指定路径字体 https://codebus.cn/yangw/use-external-font-file
//Path：路径
void CloseFontPath(LPTSTR Path);

//置顶窗口
void TopWindow();
//取消窗口置顶并退至最底部
void BottomWindow();
//隐藏窗口
void HideWindow();
//显示窗口
void ShowWindow();