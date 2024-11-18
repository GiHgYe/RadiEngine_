#include "renderer/texture2d.h"
#include "utils/debug.h"
#include <fstream>

Texture2D::Texture2D() : mipmap_level_(0), width_(0), height_(0), gl_texture_format_(0), texture_handle_(0)
{

}

Texture2D::~Texture2D() {
    if (texture_handle_ > 0) {
        glDeleteTextures(1, &texture_handle_); __CHECK_GL_ERROR__
        //RenderTaskProducer::ProduceRenderTaskDeleteTextures(1, &texture_handle_);
    }
}

void Texture2D::UpdateSubImage(int x, int y, int width, int height, unsigned int client_format, unsigned int data_type,
    unsigned char* data) {
    if (width <= 0 || height <= 0) {
        return;
    }
    glBindTexture(GL_TEXTURE_2D, texture_handle_); __CHECK_GL_ERROR__
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); __CHECK_GL_ERROR__
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, client_format, data_type, data); __CHECK_GL_ERROR__
    //RenderTaskProducer::ProduceRenderTaskUpdateTextureSubImage2D(texture_handle_, x, y, width, height, client_format, data_type, data, data_size);
}

Texture2D* Texture2D::LoadFromFile(const std::string& image_file_path)
{
    if (image_file_path.empty()) {
        //LOG_ERROR("image_file_path empty");
        return nullptr;
    }

    Texture2D* texture2d = new Texture2D();

    //��ȡ cpt ѹ�������ļ�
    std::ifstream input_file_stream(image_file_path, std::ios::in | std::ios::binary);
    TextureFileHead cpt_file_head;
    input_file_stream.read((char*)&cpt_file_head, sizeof(TextureFileHead));

    unsigned char* data = (unsigned char*)malloc(cpt_file_head.compress_size_);
    input_file_stream.read((char*)data, cpt_file_head.compress_size_);
    input_file_stream.close();

    texture2d->gl_texture_format_ = cpt_file_head.gl_texture_format_;
    texture2d->width_ = cpt_file_head.width_;
    texture2d->height_ = cpt_file_head.height_;


    //1. ֪ͨ�Կ�����������󣬷��ؾ��;
    glGenTextures(1, &(texture2d->texture_handle_)); __CHECK_GL_ERROR__

    //2. ������󶨵��ض�����Ŀ��;
    glBindTexture(GL_TEXTURE_2D, texture2d->texture_handle_); __CHECK_GL_ERROR__

    //3. ��ѹ�����������ϴ���GPU;
    glCompressedTexImage2D(GL_TEXTURE_2D, 0, texture2d->gl_texture_format_, texture2d->width_, texture2d->height_, 0, cpt_file_head.compress_size_, data);
    __CHECK_GL_ERROR__

    //4. ָ���Ŵ���С�˲���ʽ�������˲������Ŵ���С�Ĳ�ֵ��ʽ;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); __CHECK_GL_ERROR__
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); __CHECK_GL_ERROR__

    free (data);

    return texture2d;
}

Texture2D* Texture2D::Create(unsigned short width, unsigned short height, unsigned int server_format, unsigned int client_format,
    unsigned int data_type, unsigned char* data) {
    Texture2D* texture2d = new Texture2D();
    texture2d->gl_texture_format_ = server_format;
    texture2d->width_ = width;
    texture2d->height_ = height;

    glGenTextures(1, &(texture2d->texture_handle_)); __CHECK_GL_ERROR__
    glBindTexture(GL_TEXTURE_2D, texture2d->texture_handle_); __CHECK_GL_ERROR__
    glTexImage2D(GL_TEXTURE_2D, 0, texture2d->gl_texture_format_, texture2d->width_, texture2d->height_, 0, client_format, data_type, data);
    __CHECK_GL_ERROR__

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); __CHECK_GL_ERROR__
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); __CHECK_GL_ERROR__

    //texture2d->texture_handle_ = GPUResourceMapper::GenerateTextureHandle();

    // �������񣺴�������
    //RenderTaskProducer::ProduceRenderTaskCreateTexImage2D(texture2d->texture_handle_, texture2d->width_, texture2d->height_, texture2d->gl_texture_format_, client_format, data_type, data_size, data);

    return texture2d;
}