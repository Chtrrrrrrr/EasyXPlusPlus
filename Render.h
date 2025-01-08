/*
2023/1/30
绘制有关的内容

如果有error C4716，请在“属性——C/C++——高级——禁用特定警告”中添加“4716”
*/
#pragma once
#include "Header.h"

//图片
//透明绘图 https://codebus.cn/lingyin/improve-transparent-putimage
//srcimg：源图 dstimg：目标图 
void PutTransparentImage(IMAGE* srcimg, int, int, IMAGE*);
//附加透明值 https://codebus.cn/lingyin/improve-transparent-putimage
//srcimg：源图 saadd：叠加透明度 dstimg：目标图 
void PutTransparentImage(IMAGE* srcimg, int x, int y, UINT saadd, IMAGE* dstimg = NULL);
//旋转图片，指定背景填充色，自适应大小 https://codebus.cn/huidong/hieasyx
//返回目标图 pImg：源图 randian：角度 bkcolor：背景填充颜色
IMAGE RotateImage(IMAGE* pImg, double radian, COLORREF bkcolor = BLACK);
//缩放图片 https://codebus.cn/huidong/hieasyx
//返回目标图 srcimg：源图 
IMAGE ZoomImage(IMAGE* srcimg, int width, int height);
//高质量缩放图片 https://codebus.cn/margoo/anti-aliasing
//TargetImage：目标图 SourceImage：源图 TargetWidth：目标宽度 TargetHeight：目标高度
void ZoomImage(IMAGE* TargetImage, IMAGE* SourceImage, int TargetWidth, int TargetHeight);

//画图
//快速画点函数 https://codebus.cn/yangw/fast-putpixel
void PutPixel(int x, int y, COLORREF c);
//返回内容 快速读点函数 https://codebus.cn/yangw/fast-putpixel
COLORREF GetPixel(int x, int y);
