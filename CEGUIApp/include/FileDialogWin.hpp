#pragma once

#include <windows.h>
#include <string>
#include <winstring.h>

void FileOpenDialog()
{	
    OPENFILENAME ofn{};
    TCHAR szFile[260]{};       //文件名缓冲区
    
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL; //设置对话框拥有者句柄
    ofn.lpstrFile = szFile; //设置文件名缓冲区
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile); //设置所选文件路径缓冲区最大长度
    ofn.lpstrFilter = TEXT("Obj Files(*OBJ)\0*.obj\0");
    ofn.nFilterIndex = 1;  //文件类型选中的索引 从1开始
    ofn.lpstrFileTitle = NULL;  //选中的文件名（不包含路径，包含扩展名）
    ofn.nMaxFileTitle = 0;  //选中的文件名缓冲区最大长度
    ofn.lpstrInitialDir = NULL;  //初始路径
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; //用于初始化对话框的标志位 
    
    
    if (GetOpenFileNameA(&ofn) == TRUE)
        printf("%s  xxxxx", ofn.lpstrFile);

}
