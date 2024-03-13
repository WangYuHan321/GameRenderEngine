#include "PathParser.h"
#include <algorithm>

std::string PathParser::GetFileNameByPath(std::string path)
{
    std::string result;

    if (!path.empty() && path.back() == '\\')
        path.pop_back();

    for (auto it = path.rbegin(); it != path.rend() && *it != '\\' && *it != '/'; ++it)
        result += *it;

    std::reverse(result.begin(), result.end());

    return result;
}

std::string PathParser::GetExtension(const std::string p_path)
{
    std::string result;

    for (auto it = p_path.rbegin(); it != p_path.rend() && *it != '.'; ++it)
        result += *it;

    std::reverse(result.begin(), result.end());

    return result;
}

EFileType PathParser::GetFileType(const std::string p_path)
{
    std::string ext = GetExtension(p_path);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    if (ext == "fbx" || ext == "obj")											return EFileType::MODEL;
    else if (ext == "png" || ext == "jpeg" || ext == "jpg" || ext == "tga")		return EFileType::TEXTURE;
    else if (ext == "glsl")														return EFileType::SHADER;
    else if (ext == "opmat")													return EFileType::MATERIAL;
    else if (ext == "wav" || ext == "mp3" || ext == "ogg")						return EFileType::SOUND;
    else if (ext == "opscene")													return EFileType::SCENE;
    else if (ext == "lua")														return EFileType::SCRIPT;
    else if (ext == "ttf")														return EFileType::FONT;

    return EFileType::NONE;
}

std::string PathParser::GetFileTypeToString(EFileType type)
{
    switch (type)
    {
    case EFileType::FONT:
        return "Font";
    case EFileType::MATERIAL:
        return "Material";
    case EFileType::MODEL:
        return "Model";
    case EFileType::SCENE:
        return "Scene";
    case EFileType::SCRIPT:
        return "Script";
    case EFileType::SHADER:
        return "Shader";
    case EFileType::SOUND:
        return "Sound";
    case EFileType::TEXTURE:
        return "Texture";
    default:
        return "NONE";
    }
}