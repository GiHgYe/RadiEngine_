#include "renderer/animation_clip.h"
#include <fstream>
#include "utils/debug.h"
#include "utils/time.h"
#include <serializer/all_serializer.h>

#define SKELETON_ANIMATION_HEAD "skeleton_anim"
#define SKELETON_ANIMATION_FRAME_RATE 24

AnimationClip::AnimationClip() {

}

AnimationClip::~AnimationClip() {

}

void AnimationClip::LoadFromFile(const char* file_path) {
    //��ȡ�ļ�ͷ
    std::ifstream input_file_stream(file_path, std::ios::in | std::ios::binary);
    if (!input_file_stream.is_open()) {
        LOG_ERROR("AnimationClip::LoadFromFile: open file failed,file_path:{}", file_path);
        return;
    }
    char file_head[14];
    input_file_stream.read(file_head, 13);
    file_head[13] = '\0';
    if (strcmp(file_head, SKELETON_ANIMATION_HEAD) != 0) {
        LOG_ERROR("AnimationClip::LoadFromFile: file head error,file_head:{},the right is:{}", file_head, SKELETON_ANIMATION_HEAD);
        return;
    }

    //��ȡ��������
    unsigned short bone_count = 0;
    input_file_stream.read(reinterpret_cast<char*>(&bone_count), sizeof(unsigned short));
    //��ȡ������������
    for (unsigned short i = 0; i < bone_count; i++) {
        //��ȡ�������ֳ���
        unsigned short bone_name_size = 0;
        input_file_stream.read(reinterpret_cast<char*>(&bone_name_size), sizeof(unsigned short));

        char* bone_name = new char[bone_name_size + 1];
        input_file_stream.read(bone_name, bone_name_size);
        bone_name[bone_name_size] = '\0';
        bone_names_.push_back(bone_name);
        delete[] bone_name;
    }
    //��ȡ�����ӽڵ�
    for (unsigned short bone_index = 0; bone_index < bone_count; bone_index++) {
        //��ȡ�����ӽڵ�����
        unsigned short child_count = 0;
        input_file_stream.read(reinterpret_cast<char*>(&child_count), sizeof(unsigned short));
        //��ȡ�����ӽڵ����֣��������������š�
        std::vector<unsigned short> child_indexes;
        for (unsigned short j = 0; j < child_count; j++) {
            unsigned short child_index = 0;
            input_file_stream.read(reinterpret_cast<char*>(&child_index), sizeof(unsigned short));
            child_indexes.push_back(child_index);
        }
        bone_children_vector_.push_back(child_indexes);
    }
    //��ȡ����T-pose
    for (unsigned short bone_index = 0; bone_index < bone_count; bone_index++) {
        //��ȡ����T-pose
        Matrix4x4 bone_t_pose;
        input_file_stream.read(reinterpret_cast<char*>(&bone_t_pose), sizeof(float) * 16);
        bone_t_pose_vector_.push_back(bone_t_pose);
    }
    //��ȡ֡��
    input_file_stream.read(reinterpret_cast<char*>(&frame_count_), sizeof(unsigned short));

    //��ȡ��������
    for (int frame_index = 0; frame_index < frame_count_; frame_index++) {
        //��ȡһ֡�Ĺ�������
        std::vector<Matrix4x4> bone_matrices;
        for (unsigned short bone_index = 0; bone_index < bone_count; bone_index++) { // bone_count 2
            Matrix4x4 bone_matrix;
            input_file_stream.read(reinterpret_cast<char*>(&bone_matrix), sizeof(float) * 16);
            bone_matrices.push_back(bone_matrix);
        }
        bone_matrix_frames_vector_.push_back(bone_matrices);
    }
    input_file_stream.close();

    Bake();
}

void AnimationClip::Bake() {
    for (int i = 0; i < frame_count_; ++i) {
        LOG_INFO("AnimationClip::Bake: frame_index:{}", i);
        //���㵱ǰ֡�Ĺ�������
        std::vector<Matrix4x4>& current_frame_bone_matrices = bone_matrix_frames_vector_[i];
        CalculateBoneMatrix(current_frame_bone_matrices, 0, Matrix4x4());
    }
}

void AnimationClip::CalculateBoneMatrix(std::vector<Matrix4x4>& current_frame_bone_matrices, unsigned short bone_index, const Matrix4x4& parent_matrix) {
    Matrix4x4 bone_matrix = current_frame_bone_matrices[bone_index];
    Matrix4x4 bone_t_pos_matrix = bone_t_pose_vector_[bone_index];
    Matrix4x4 bone_matrix_with_parent = parent_matrix * bone_t_pos_matrix * bone_matrix;

    LOG_INFO("{} bone_matrix:{}", bone_names_[bone_index], Serializer::Write(bone_matrix_with_parent.ToMatrix4x4_()).dump());

    current_frame_bone_matrices[bone_index] = bone_matrix_with_parent;
    std::vector<unsigned short> child_indexes = bone_children_vector_[bone_index];
    for (unsigned short child_index : child_indexes) {
        CalculateBoneMatrix(current_frame_bone_matrices, child_index, bone_matrix_with_parent);
    }
}

void AnimationClip::Play() {
    //��¼��ǰʱ��
    start_time_ = Time::TimeSinceStartup();
    is_playing_ = true;
}

void AnimationClip::Update() {
    if (!is_playing_) {
        LOG_ERROR("AnimationClip is not playing");
        return;
    }
    //���㵱ǰʱ���Ӧ��֡���
    float current_time = Time::TimeSinceStartup() - start_time_;
    unsigned short current_frame_index = static_cast<unsigned short>(current_time * SKELETON_ANIMATION_FRAME_RATE);
    current_frame_ = current_frame_index % frame_count_;

}

void AnimationClip::Stop() {
    is_playing_ = false;
}

Matrix4x4& AnimationClip::GetBoneTPose(unsigned char bone_index) {
    return this->bone_t_pose_vector_[bone_index];
}

std::vector<Matrix4x4>& AnimationClip::GetCurrentFrameBoneMatrix() {
    if (is_playing_ == false) {
        LOG_ERROR("AnimationClip is not playing");
    }
    return bone_matrix_frames_vector_[current_frame_];
}
