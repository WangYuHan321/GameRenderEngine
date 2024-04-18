#pragma once

#include <ft2build.h> 
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include "../../Util/common.h"

class Texture;
class Font {
public:
    Texture* font_texture() { return font_texture_; }

    /// freetypeΪ�ַ�����bitmap
    /// \param c
    void LoadCharacter(char ch);

    /// ��¼�����ַ���ͼ���ϵ����ꡢ��ߣ���������ͬ�ߴ�Ķ������ݣ�1��1��Ⱦ��
    struct Character {
        float left_top_x_;
        float left_top_y_;
        float right_bottom_x_;
        float right_bottom_y_;
        char ch_font_;
        Character(float left_top_x, float left_top_y, float right_bottom_x, float right_bottom_y, char ch) {
            left_top_x_ = left_top_x;
            left_top_y_ = left_top_y;
            right_bottom_x_ = right_bottom_x;
            right_bottom_y_ = right_bottom_y;
            ch_font_ = ch;
        }
    };

    /// Ϊ�ַ�������bitmap�������ַ���ÿ���ַ���Character���ݡ�
    /// \param str
    /// \return
    std::vector<Character*> LoadStr(std::string str);

private:
    unsigned short font_size_ = 20;//Ĭ�������С
    char* font_file_buffer_ = nullptr;//ttf�����ļ����ص��ڴ�
    FT_Library ft_library_;
    FT_Face ft_face_;
    Texture* font_texture_;
    unsigned short font_texture_size_ = 1024;
    unsigned short font_texture_fill_x = 0;//
    unsigned short font_texture_fill_y = 0;
    std::unordered_map<char, Character*> character_map_;//�Ѿ�����bitmap���ַ�

public:
    /// ����һ�������ļ�������
    /// \param image_file_path ttf�����ļ�·��
    /// \param font_size Ĭ�����ֳߴ�
    /// \return
    static Font* LoadFromFile(std::string font_file_path, unsigned short font_size);

    /// ��ȡFontʵ��
    /// \param font_file_path ttf·��
    /// \return
    static Font* GetFont(std::string font_file_path);
private:
    static std::unordered_map<std::string, Font*> font_map_;//�洢���ص����� key��ttf·�� value��Fontʵ��
};

