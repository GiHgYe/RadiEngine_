#pragma once

#include <iostream>
#include <unordered_map>
#include "freetype/ftglyph.h"


class Texture2D;
class Font
{
public:
    Texture2D* font_texture() { return font_texture_; }

    /// freetypeΪ�ַ�����bitmap
    /// \param c
    void LoadCharacter(char ch);

    /// ��¼�����ַ���ͼ���ϵ����ꡢ���ߣ���������ͬ�ߴ�Ķ������ݣ�1��1��Ⱦ��
    struct Character {
        float left_top_x_;
        float left_top_y_;
        float right_bottom_x_;
        float right_bottom_y_;
        Character(float left_top_x, float left_top_y, float right_bottom_x, float right_bottom_y) {
            left_top_x_ = left_top_x;
            left_top_y_ = left_top_y;
            right_bottom_x_ = right_bottom_x;
            right_bottom_y_ = right_bottom_y;
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
    Texture2D* font_texture_;
    unsigned short font_texture_size_ = 1024;
    unsigned short font_texture_fill_x = 0;//��ǰ�е���ʼ��
    unsigned short font_texture_fill_y = 0;//�µ�һ�е�������ʼ��
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