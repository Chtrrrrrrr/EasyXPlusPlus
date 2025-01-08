/*
2023/2/12
杂项
*/
#pragma once
#include "Header.h"

//快速随机
//返回随机结果 A<B
int Random(int A, int B);
//精准延迟函数 https://codebus.cn/yangw/accurate-delayc
//单位毫秒
void HpSleep(int);
//向剪贴板存入字符串 https://blog.csdn.net/airen3339/article/details/122716734
void ClipboardString(std::string);
//从剪贴板读取字符串 https://blog.csdn.net/airen3339/article/details/122716734
std::string GetClipboardString();

//string转wstring https://blog.csdn.net/c914620529/article/details/73503708
std::wstring StringToWString(const std::string&);
//wstring转string https://blog.csdn.net/c914620529/article/details/73503708
std::string WStringToString(const std::wstring&);
//从Http链接下载内容 https://blog.csdn.net/shuilongyin_00/article/details/123790576
//Url：Http链接 FileName：保存的路径
int DownloadFromHttp(std::string Url, std::string FileName);
//重载函数，用于设置下载时对于下载进度的响应函数
//响应函数：返回值void，参数列表int
int DownloadFromHttp(std::string Url, std::string FileName, void (*Function)(double));

//播放音频
//如果mp3文件无法播放，可能是因为封面过大，去除或减小即可
class Audio
{
public:
	Audio() {};
	Audio(std::wstring Path);
	~Audio();
	//设置路径
	void SetAudioPath(std::wstring); 
	//播放
	void Play(); 
	//播放并循环
	void PlayRepeat(); 
	//播放并等待结束
	void PlayWait(); 
	//停止
	void Stop(); 
	//暂停
	void Pause(); 
	//继续
	void Resume(); 
	//关闭
	void Close(); 
	//★尚有bug，不推荐使用★ 设置播放位置：具体位置（单位：毫秒）/start（开头）/end（结尾）
	void Seek(std::wstring); 
	//设置音量 范围：0-1000
	void SetVolume(std::wstring); 
	//获取进度 返回：进度 范围：0-1
	double GetProgress(); 
private:
	std::wstring AudioPath;
};
