#pragma once
#include <fmod/core/fmod.hpp>

class AudioCore {
public:
    /// ��ʼ��fmod
    static void Init();

    /// ������Ч
    /// \param name_or_data
    /// \param mode
    /// \param ex_info
    /// \param sound
    /// \return
    static FMOD_RESULT CreateSound(const char* name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* ex_info, FMOD::Sound** sound);

    /// ����sound��Ӧ����Ч
    /// \param sound
    /// \param channel_group
    /// \param paused
    /// \param channel
    /// \return
    static FMOD_RESULT PlaySound(FMOD::Sound* sound, FMOD::ChannelGroup* channel_group, bool paused, FMOD::Channel** channel);

    /// ˢ֡
    /// \return
    static FMOD_RESULT Update();

    /// ������������
    /// \param listener
    /// \param pos
    /// \param vel
    /// \param forward
    /// \param up
    /// \return
    static FMOD_RESULT Set3DListenerAttributes(int listener, const FMOD_VECTOR* pos, const FMOD_VECTOR* vel, const FMOD_VECTOR* forward, const FMOD_VECTOR* up);
private:
    static FMOD::System* fmod_system_;//fmod��Ч����ϵͳ
};
