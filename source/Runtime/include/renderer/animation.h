#pragma once
#include <unordered_map>
#include "component/component.h"

class AnimationClip;

REFLECTION_TYPE(Animation)
CLASS (Animation : public Component, WhiteListFields)
{
	REFLECTION_BODY(Animation)
	REFLECTION_INFO(Animation)
public:
    Animation();
    ~Animation();

    /// ���� skeleton_anim �ļ�
    /// \param path skeleton_anim �ļ�·��
    /// \param alias_name �����������������һ���������������
    void LoadAnimationClipFromFile(const char* path, const char* alias_name);

    /// ���Ŷ���
    /// \param alias_name ��������
    void Play(const char* alias_name);

    /// ��ȡ��ǰ���ŵĶ���
    AnimationClip* current_animation_clip() const { return current_animation_clip_; }

public:
    // ˢ֡
    void Update() override;

private:
    /// �����б�
    std::unordered_map<std::string, AnimationClip*> animation_clips_map_;
    /// ��ǰ���ŵĶ���
    AnimationClip* current_animation_clip_;
};
