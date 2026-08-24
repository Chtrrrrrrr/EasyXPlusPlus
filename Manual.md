# EasyX++ 开发手册

> **版本**：v1.0（对应 EasyX++ 2023.2 源码）
> **适用环境**：Visual Studio 2017+ / EasyX 图形库

---

## 目录
- [环境配置](#环境配置)
- [一、窗口模块 (Window.h)](#一窗口模块-windowh)
- [二、渲染模块 (Render.h)](#二渲染模块-renderh)
- [三、UI 模块 (UI.h)](#三ui-模块-uih)
- [四、文件模块 (File.h)](#四文件模块-fileh)
- [五、杂项工具 (Other.h)](#五杂项工具-otherh)
- [六、完整示例](#六完整示例)
- [七、常见问题](#七常见问题)

---

## 环境配置

### 编译环境
- 需安装 [EasyX](https://easyx.cn/) 图形库
- 建议使用 Visual Studio（2017 及以上版本）

### 项目设置
1. **预处理器定义**：添加 `_CRT_SECURE_NO_WARNINGS`
2. **禁用特定警告**：添加 `4716`
3. **字符集**：设置为 **使用 Unicode 字符集**

---

## 一、窗口模块 (Window.h)

### 1.1 窗口基本操作

| 函数 | 说明 | 示例 |
|------|------|------|
| `void SetWindowBackgroundColor(int Color)` | 设置窗口背景色并清屏 | `SetWindowBackgroundColor(WHITE);` |
| `void SetWindowTitle(std::wstring Title)` | 设置窗口及控制台标题 | `SetWindowTitle(_T("我的程序"));` |
| `void SetWindowIcon(int Icon)` | 设置窗口图标（资源 ID） | `SetWindowIcon(IDI_ICON1);` |
| `void SetWindowCursor(HCURSOR Cursor)` | 设置鼠标光标样式 | `SetWindowCursor(LoadCursor(NULL, IDC_HAND));` |

### 1.2 特效与性能

| 函数 | 说明 | 注意事项 |
|------|------|----------|
| `void Blur()` | 对当前画布进行全局模糊 | 速度较慢，建议静态场景使用；暂不支持边缘像素。 |
| `int GetFPS()` | 获取实时帧率（1 秒更新） | 需在消息循环中调用。 |

### 1.3 字体控制

| 函数 | 说明 |
|------|------|
| `void SetTextSize(double Size)` | 按比例缩放当前字体大小（非绝对值） |
| `void OpentTextAntiAliasing()` | 开启字体抗锯齿 |
| `void CloseTextAntiAliasing()` | 关闭字体抗锯齿 |
| `void LoadFontPath(LPTSTR Path)` | 加载外部字体文件（如 `.ttf`） |
| `void CloseFontPath(LPTSTR Path)` | 卸载外部字体文件 |

### 1.4 窗口层级

| 函数 | 说明 |
|------|------|
| `void TopWindow()` | 窗口置顶 |
| `void BottomWindow()` | 窗口置底 |
| `void HideWindow()` | 隐藏窗口 |
| `void ShowWindow()` | 显示窗口 |

---

## 二、渲染模块 (Render.h)

### 2.1 透明贴图

#### 基础版
```cpp
void PutTransparentImage(IMAGE* srcimg, int x, int y, IMAGE* dstimg = NULL);
```
- **参数**：
  - `srcimg`：源图（需包含 Alpha 通道）
  - `x, y`：目标绘制坐标
  - `dstimg`：目标画布（默认当前窗口）
- **说明**：基于像素 Alpha 混合，支持任意透明度。

#### 附加透明值版
```cpp
void PutTransparentImage(IMAGE* srcimg, int x, int y, UINT saadd, IMAGE* dstimg = NULL);
```
- 额外叠加透明度（0~255），适合制作淡入淡出效果。

### 2.2 旋转图片

```cpp
IMAGE RotateImage(IMAGE* pImg, double radian, COLORREF bkcolor = BLACK);
```
- **参数**：
  - `pImg`：源图片
  - `radian`：旋转角度（弧度制，正值为逆时针）
  - `bkcolor`：背景填充色（默认黑色）
- **返回**：旋转后的新 `IMAGE` 对象（自适应大小）。

### 2.3 缩放图片

#### 快速缩放（最近邻插值）
```cpp
IMAGE ZoomImage(IMAGE* srcimg, int width, int height);
```
- 速度快，边缘有锯齿，适合位图精灵。

#### 高质量缩放（StretchBlt + HALFTONE）
```cpp
void ZoomImage(IMAGE* TargetImage, IMAGE* SourceImage, int TargetWidth, int TargetHeight);
```
- 效果平滑，适合照片或需要清晰展示的场景。

### 2.4 快速像素读写

```cpp
void PutPixel(int x, int y, COLORREF c);
COLORREF GetPixel(int x, int y);
```
- 比 EasyX 原生 `putpixel/getpixel` 快得多，适合粒子、模糊等高频操作。

---

## 三、UI 模块 (UI.h)

### 3.1 状态常量

| 常量 | 值 | 说明 |
|------|-----|------|
| `UI_NORMAL` | 0 | 平时状态 |
| `UI_ONPASS` | 1 | 鼠标悬停 |
| `UI_ONCLICK` | 2 | 鼠标按下 |

### 3.2 按钮 (Button)

#### 构造函数
```cpp
Button(int x, int y, int width, int height, std::wstring text);
Button(int x, int y, int width, int height, std::wstring text, ButtonStyle style);
```

#### 主要方法

| 方法 | 说明 |
|------|------|
| `void Reset(int x, int y, int w, int h)` | 重新设置位置和尺寸 |
| `void SetStyle(ButtonStyle style)` | 自定义外观 |
| `void SetText(std::wstring text)` | 修改按钮文字 |
| `void SetTextRender(UINT type)` | 设置文字对齐（如 `DT_CENTER`） |
| `void RedirectRenderFunction(void (*)(int))` | 重定向渲染函数（需自行调用绘图 API） |
| `void SetUIMsgProc(void (*)(int))` | 状态回调（参数为当前状态） |
| `int Flush(ExMessage msg)` | 处理事件并渲染，返回当前状态 |

#### 自定义 ButtonStyle
```cpp
struct ButtonStyle {
    int EdgeColor[3];         // 边框颜色（索引 0/1/2 对应状态）
    int BackgroundColor[3];   // 背景颜色
    int TextColor[3];         // 文字颜色
};
```

### 3.3 拖拽条 (SeekBar)

#### 构造函数
```cpp
SeekBar(int x, int y, int width, int height, int radius, int edge_width);
SeekBar(int x, int y, int width, int height, int radius, int edge_width, SeekBarStyle style);
```

#### 主要方法

| 方法 | 说明 |
|------|------|
| `void SetStyle(SeekBarStyle style)` | 自定义外观 |
| `void SetLength(std::wstring)` | 设置当前拖拽长度 |
| `void Reset(int, int, int, int, int, int)` | 重置位置和尺寸 |
| `void RedirectRenderFunction(void (*)(int, int))` | 自定义渲染（参数：状态, 拖拽长度） |
| `void SetUIMsgProc(void (*)(int, int))` | 回调（参数：状态, 拖拽长度） |
| `int Flush(ExMessage msg)` | 处理拖动事件并渲染 |

---

## 四、文件模块 (File.h)

### 4.1 文本文件操作

| 函数 | 说明 |
|------|------|
| `int GetFileLine(const char* filename)` | 获取文件总行数 |
| `std::string ReadFileLineContent(char* filename, int line)` | 读取第 N 行内容（自动 UTF-8 → GBK） |
| `void ChangeFileLineContent(char* fileName, int lineNum, const char* lineData)` | 修改第 N 行内容 |

### 4.2 文件对话框

```cpp
std::wstring GetFilePath(std::wstring FileType, std::wstring Title);
std::wstring GetSavePath(std::wstring FileType, std::wstring Title);
```

**FileType 格式示例**
```cpp
std::wstring filters = _T("所有文件\0*.*\0文本文件\0*.txt\0C++文件\0*.cpp\0");
std::wstring path = GetFilePath(filters, _T("请选择一个文件"));
```

---

## 五、杂项工具 (Other.h)

### 5.1 基础工具

| 函数 | 说明 |
|------|------|
| `int Random(int A, int B)` | 生成 `[A, B]` 随机整数 |
| `void HpSleep(int ms)` | 高精度延时（不占用过高 CPU） |
| `void ClipboardString(std::string str)` | 写入剪贴板 |
| `std::string GetClipboardString()` | 读取剪贴板文本 |

### 5.2 字符编码转换

```cpp
std::wstring StringToWString(const std::string& str);    // ANSI → Unicode
std::string WStringToString(const std::wstring& wstr);   // Unicode → ANSI
std::wstring u8StringTouWString(const std::string& str); // UTF-8 → Unicode
std::string uWStringTou8String(const std::wstring& wstr);// Unicode → UTF-8
```

### 5.3 URL 编解码

```cpp
std::string urlencode(std::string& str);
std::string urldecode(std::string& str);
```

### 5.4 网络下载

```cpp
// 基础下载（无进度回调）
int DownloadFromHttp(std::string Url, std::string FileName);

// 带进度回调（参数为 0~100 百分比）
int DownloadFromHttp(std::string Url, std::string FileName, void (*Function)(double));
```

### 5.5 音频播放 (Audio 类)

#### 构造函数 / 析构函数
```cpp
Audio(std::wstring Path);  // 加载音频文件
~Audio();                  // 释放资源
```

#### 方法

| 方法 | 说明 |
|------|------|
| `void SetAudioPath(std::wstring)` | 切换音频文件 |
| `void Play()` | 播放一次 |
| `void PlayRepeat()` | 循环播放 |
| `void PlayWait()` | 播放并等待结束（阻塞） |
| `void Stop()` | 停止播放 |
| `void Pause()` | 暂停 |
| `void Resume()` | 继续播放 |
| `void Close()` | 关闭音频设备 |
| `void Seek(std::wstring)` | 跳转位置（毫秒，或 `"start"`/`"end"`） |
| `void SetVolume(std::wstring)` | 设置音量（0~1000） |
| `double GetProgress()` | 获取播放进度（0~1） |

---

## 六、完整示例

```cpp
#include "EasyX++.h"

int main()
{
    // 创建窗口
    initgraph(600, 500, 1);
    SetWindowTitle(_T("EasyX++ 演示程序"));
    SetWindowBackgroundColor(WHITE);
    OpentTextAntiAliasing();

    // 创建按钮
    Button myBtn(100, 100, 200, 60, _T("点击我"));

    // 自定义按钮外观
    ButtonStyle style;
    style.BackgroundColor[UI_NORMAL]  = RGB(220, 220, 220);
    style.BackgroundColor[UI_ONPASS]  = RGB(180, 220, 255);
    style.BackgroundColor[UI_ONCLICK] = RGB(150, 200, 255);
    myBtn.SetStyle(style);

    // 按钮事件回调
    myBtn.SetUIMsgProc([](int state) {
        if (state == UI_ONCLICK) {
            OutputDebugString(_T("按钮被点击了！\n"));
        }
    });

    // 音频播放
    Audio bgm(_T("C:\\music\\bgm.mp3"));
    bgm.PlayRepeat();

    ExMessage msg;
    while (true)
    {
        peekmessage(&msg);
        BeginBatchDraw();
        myBtn.Flush(msg);          // 处理 UI 状态与渲染
        FlushBatchDraw();
        HpSleep(1000 / 60);        // 精准控制 60 FPS
        std::cout << "FPS: " << GetFPS() << std::endl;
    }

    closegraph();
    return 0;
}
```

---

## 七、常见问题

| 问题 | 解决方案 |
|------|----------|
| 编译报错 `error C4716` | 在 属性 → C/C++ → 高级 → 禁用特定警告 中添加 `4716` |
| 出现 `_CRT_SECURE_NO_WARNINGS` 报错 | 在 属性 → C/C++ → 预处理器 → 预处理器定义 中添加 `_CRT_SECURE_NO_WARNINGS` |
| 中文乱码 | 库内部已处理 UTF-8 → GBK，文件保存时建议统一 UTF-8 编码 |
| 音频无法播放 | MP3 封面过大可能导致问题，尝试去除封面 |
| 下载失败 | 检查 URL 可访问性及网络权限（防火墙/代理） |

---

*文档生成时间：2026-08-24*
