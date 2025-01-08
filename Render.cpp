#include "Render.h"

// 绘制透明图片
void PutTransparentImage(IMAGE* src_image, int x, int y, IMAGE* dst_image = NULL) 
{
    // 初始化变量
    const int src_width = src_image->getwidth();
    const int src_height = src_image->getheight();
    const int dst_width = (dst_image == NULL ? getwidth() : dst_image->getwidth());
    const int dst_height = (dst_image == NULL ? getheight() : dst_image->getheight());

    DWORD* dst_buffer = GetImageBuffer(dst_image);
    DWORD* src_buffer = GetImageBuffer(src_image);

    // 处理超出边界的情况
    if (x < 0)
    {
        src_buffer -= x;
        x = 0;
    }
    if (y < 0) 
    {
        src_buffer -= src_width * y;
        y = 0;
    }
    const int max_width = dst_width - x;
    const int max_height = dst_height - y;
    const int iwidth = (src_width > max_width) ? max_width : src_width;
    const int iheight = (src_height > max_height) ? max_height : src_height;

    // 透明度混合计算
    for (int iy = 0; iy < iheight; ++iy) 
    {
        DWORD* dst = dst_buffer + dst_width * (y + iy) + x;
        DWORD* src = src_buffer + src_width * iy;
        for (int ix = 0; ix < iwidth; ++ix) 
        {
            const DWORD src_pixel = *src++;
            const int sa = (src_pixel >> 24) & 0xFF;
            if (sa == 0)
                continue;
            else if (sa == 255) 
            {
                *dst = src_pixel;
            } 
            else 
            {
                const int da = ((*dst >> 24) * (255 - sa) + 128) / 255;
                const int dr = ((*dst >> 16 & 0xFF) * da + 128) / 255 + ((src_pixel >> 16 & 0xFF) * sa + 128) / 255;
                const int dg = ((*dst >> 8 & 0xFF) * da + 128) / 255 + ((src_pixel >> 8 & 0xFF) * sa + 128) / 255;
                const int db = ((*dst & 0xFF) * da + 128) / 255 + ((src_pixel & 0xFF) * sa + 128) / 255;
                *dst = (da << 24) | (dr << 16) | (dg << 8) | db;
            }
            ++dst;
        }
    }
}
void PutTransparentImage(IMAGE* srcimg, int x, int y, UINT saadd, IMAGE* dstimg) 
{
if (saadd < 0) return;
// 变量初始化
DWORD* dst = GetImageBuffer(dstimg);
DWORD* src = GetImageBuffer(srcimg);
int src_width = srcimg->getwidth();
int src_height = srcimg->getheight();
int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());
// 计算贴图的实际长宽
int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width; // 处理超出右边界
int iheight = (y + src_height > dst_height) ? dst_height - y : src_height; // 处理超出下边界
if (x < 0) { src += -x; iwidth -= -x; x = 0; } // 处理超出左边界
if (y < 0) { src += src_width * -y; iheight -= -y; y = 0; } // 处理超出上边界
// 修正贴图起始位置
dst += dst_width * y + x;
// 阿尔法值
int sa;
// 实现透明贴图
for (int iy = 0; iy < iheight; ++iy) {
for (int i = 0; i < iwidth; ++i) {
sa = ((src[i] & 0xff000000) >> 24) + saadd; //获取阿尔法值
if (sa > 0) { //假如是完全透明就不处理
if (sa >= 255) { //假如完全不透明则直接拷贝
dst[i] = src[i];
} else { //真正需要阿尔法混合计算的图像边界才进行混合
int isrc_r = (src[i] & 0xff0000) >> 16;
int idst_r = (dst[i] & 0xff0000) >> 16;
int isrc_g = (src[i] & 0xff00) >> 8;
int idst_g = (dst[i] & 0xff00) >> 8;
int isrc_b = src[i] & 0xff;
int idst_b = dst[i] & 0xff;
int ialpha = 255 - sa;
dst[i] = ((isrc_r * sa + idst_r * ialpha) / 255 << 16) |
((isrc_g * sa + idst_g * ialpha) / 255 << 8) |
((isrc_b * sa + idst_b * ialpha) / 255);
}
}
}
dst += dst_width;
src += src_width;
}
}
IMAGE RotateImage(IMAGE* pImg, double radian, COLORREF bkcolor)
{
	radian = -radian;														// 由于 y 轴翻转，旋转角度需要变负
	double fSin = (double)sin(radian), fCos = (double)cos(radian);				// 存储三角函数值
	double fNSin = (double)sin(-radian), fNCos = (double)cos(-radian);
	int left = 0, top = 0, right = 0, bottom = 0;							// 旋转后图像顶点
	int w = pImg->getwidth(), h = pImg->getheight();
	DWORD* pBuf = GetImageBuffer(pImg);
	POINT points[4] = { { 0, 0 },{ w, 0 },{ 0, h },{ w, h } };				// 存储图像顶点
	for (int j = 0; j < 4; ++j)												// 旋转图像顶点，搜索旋转后的图像边界
	{
		points[j] = {
			(int)(points[j].x * fCos - points[j].y * fSin),
			(int)(points[j].x * fSin + points[j].y * fCos)
		};
		if (points[j].x < points[left].x)	left = j;
		if (points[j].y > points[top].y)	top = j;
		if (points[j].x > points[right].x)	right = j;
		if (points[j].y < points[bottom].y)	bottom = j;
	}

	int nw = points[right].x - points[left].x;								// 旋转后的图像尺寸
	int nh = points[top].y - points[bottom].y;
	int nSize = nw * nh;
	int offset_x = points[left].x < 0 ? points[left].x : 0;					// 旋转后图像超出第一象限的位移（据此调整图像位置）
	int offset_y = points[bottom].y < 0 ? points[bottom].y : 0;

	IMAGE img(nw, nh);
	DWORD* pNewBuf = GetImageBuffer(&img);
	if (bkcolor != BLACK)													// 设置图像背景色
		for (int i = 0; i < nSize; i++)
			pNewBuf[i] = BGR(bkcolor);

	for (int i = offset_x, ni = 0; ni < nw; ++i, ++ni)						// i 用于映射原图像坐标，ni 用于定位旋转后图像坐标
	{
		for (int j = offset_y, nj = 0; nj < nh; ++j, ++nj)
		{
			int nx = (int)(i * fNCos - j * fNSin);							// 从旋转后的图像坐标向原图像坐标映射
			int ny = (int)(i * fNSin + j * fNCos);
			if (nx >= 0 && nx < w && ny >= 0 && ny < h)						// 若目标映射在原图像范围内，则拷贝色值
				pNewBuf[nj * nw + ni] = pBuf[ny * w + nx];
		}
	}

	return img;
}
IMAGE ZoomImage(IMAGE* srcimg, int width, int height)
{
	// 初始化新图
	IMAGE dstImage(width, height);
	IMAGE* dstimg = &dstImage;

	DWORD* dst = GetImageBuffer(dstimg);
	DWORD* src = GetImageBuffer(srcimg);

	int src_width = srcimg->getwidth();
	int src_height = srcimg->getheight();

	int dst_width = (!dstimg ? getwidth() : dstimg->getwidth());

	double w_scale_rate = (double)src_width / width;
	double h_scale_rate = (double)src_height / height;

	DWORD* p = src;
	int psc_width = srcimg->getwidth();

	for (int iy = 0; iy < height; ++iy)
	{
		for (int ix = 0; ix < width; ++ix)
		{
			// 计算原图相应坐标
			int i_scale = (int)(h_scale_rate * iy);
			int j_scale = (int)(w_scale_rate * ix);
			DWORD* pp = p;
			for (int iy = 0; iy < i_scale; ++iy)
			{
				pp += psc_width;
			}
			dst[ix] = pp[j_scale];
		}
		dst += dst_width;
		src += src_width;
	}

	return dstImage;
}
void ZoomImage(IMAGE* TargetImage, IMAGE* SourceImage, int TargetWidth, int TargetHeight)
{
	TargetImage->Resize(TargetWidth, TargetHeight);
	HDC TargetDC = GetImageHDC(TargetImage);
	HDC SourceDC = GetImageHDC(SourceImage);
	int Width = SourceImage->getwidth();
	int Height = SourceImage->getheight();

	SetStretchBltMode(TargetDC, HALFTONE);
	StretchBlt(TargetDC, 0, 0, TargetWidth, TargetHeight, SourceDC, 0, 0, Width, Height, SRCCOPY);
}

//画图
void PutPixel(int x, int y, COLORREF c)
{
	GetImageBuffer()[y * getwidth() + x] = BGR(c);
}
COLORREF GetPixel(int x, int y)
{
	return BGR(GetImageBuffer()[y * getwidth() + x]);
}

