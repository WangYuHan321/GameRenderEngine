#pragma once

#include <string>
#include "../../Util/Singleton.h"

enum class EFileType
{
    NONE,
    MODEL,
    TEXTURE,
    SHADER,
    MATERIAL,
    SOUND,
    SCENE,
    SCRIPT,
    FONT
};

class PathParser : public CSingleton<PathParser>
{
public:

    std::string GetFileNameByPath(std::string path);
    std::string GetExtension(const std::string p_path);

    EFileType GetFileType(const std::string p_path);
    std::string GetFileTypeToString(EFileType type);
};

