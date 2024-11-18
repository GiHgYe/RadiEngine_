#include "renderer/animation.h"
#include "renderer/animation_clip.h"
#include "utils/debug.h"

Animation::Animation() :current_animation_clip_(nullptr) {}

Animation::~Animation() {
    for (auto iter : animation_clips_map_) {
        delete iter.second;
    }
}

void Animation::LoadAnimationClipFromFile(const char* path, const char* alias_name) {
    AnimationClip* animationClip = new AnimationClip();
    animationClip->LoadFromFile(path);
    animation_clips_map_[alias_name] = animationClip;
}

void Animation::Play(const char* alias_name) {
    if (animation_clips_map_.find(alias_name) == animation_clips_map_.end()) {
        LOG_ERROR("AnimationClip not found: {}", alias_name);
        return;
    }
    current_animation_clip_ = animation_clips_map_[alias_name];
    current_animation_clip_->Play();
}

void Animation::Update() {
    if (current_animation_clip_) {
        current_animation_clip_->Update();
    }
}