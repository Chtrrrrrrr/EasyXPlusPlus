/*
2023/2/13
文件有关的内容

//如果出现有关_CRT_SECURE_NO_WARNINGS的报错，请在“属性——C/C++——预处理器——预处理器定义——编辑”中添加“_CRT_SECURE_NO_WARNINGS”
*/
#pragma once
#include "Header.h"

//获取文件行数
//返回行数 filename：文件名
int GetFileLine(const char* filename);
//读取文件某行内容
//返回内容 filename：文件名 line：行数
std::string ReadFileLineContent(char* filename, int line);
//更改文件某行内容
//fileName：文件名 lineNum：行数 lineDate：新的内容
void ChangeFileLineContent(char* fileName, int lineNum, const char* lineData);

//创建一个选择文件对话框
//返回文件位置 FileType：选择文件的名称限制（可使用通配符），用\0分割，依次为显示的选项名称和文件名 Title：对话框的标题
//如："All\0*.*\0Cpp\0*.cpp\0README\0README.MD\0"
std::wstring GetFilePath(std::wstring FileType, std::wstring Title);
//创建一个获取保存位置对话框
//返回文件位置（包含文件名） FileType：保存文件的名称（可使用通配符），用\0分割，依次为显示的选项名称和文件名 Title：对话框的标题
//如："All\0*.*\0Cpp\0*.cpp\0README\0README.MD\0"
std::wstring GetSavePath(std::wstring FileType, std::wstring Title);
