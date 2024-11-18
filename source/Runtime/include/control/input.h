#pragma once
#include <unordered_map>
#include <math/math_headers.h>

class Input {
public:
    /// �жϵ�ǰ֡ ���̰����Ƿ���
    /// \param key_code
    /// \return
    static bool GetKey(unsigned short key_code);

    /// �жϵ�ǰ֡ ���̰����Ƿ��ڰ���״̬
    /// \param key_code
    /// \return
    static bool GetKeyDown(unsigned short key_code);

    /// �жϵ�ǰ֡ ���̰����Ƿ��²��ɿ�
    /// \param key_code
    /// \return
    static bool GetKeyUp(unsigned short key_code);

    /// ��¼�����¼������̰��¼�¼��+1�����̵����¼��-1������¼��Ϊ0��˵����ʱû�а�����
    /// \param key_code
    /// \param action 0���� 1���� 2��������
    static void RecordKey(int key_code, unsigned char key_action);

    /// ˢ֡
    static void Update();

    /// �ж��Ƿ������ĳ����ť
    /// \param mouse_button_index   0 ��ʾ����ť��ͨ��Ϊ��ť����1 ��ʾ����ť��2 ��ʾ�м䰴ť��
    /// \return
    static bool GetMouseButton(unsigned short mouse_button_index);

    /// ָ����갴���Ƿ��ڰ��µ�״̬
    /// \param mouse_button_index   0 ��ʾ����ť��ͨ��Ϊ��ť����1 ��ʾ����ť��2 ��ʾ�м䰴ť��
    /// \return
    static bool GetMouseButtonDown(unsigned short mouse_button_index);

    /// ��갴ť�Ƿ��ɿ�
    /// \param mouse_button_index   0 ��ʾ����ť��ͨ��Ϊ��ť����1 ��ʾ����ť��2 ��ʾ�м䰴ť��
    /// \return
    static bool GetMouseButtonUp(unsigned short mouse_button_index);

    static Vector2 mousePosition() { return mouse_position_; }

    /// �������λ��
    /// \param x
    /// \param y
    static void set_mousePosition(unsigned short x, unsigned short y) { mouse_position_.x = x; mouse_position_.y = y; }

    static short mouse_scroll() { return mouse_scroll_; }

    /// ��¼�������¼�
    /// \param mouse_scroll
    static void RecordScroll(short mouse_scroll) { mouse_scroll_ += mouse_scroll; }

private:
    static std::unordered_map<unsigned short, unsigned char> key_event_map_;//����״̬ 0���� 1���� 2��������
    static Vector2 mouse_position_;//���λ��
    static short mouse_scroll_;//������ֵ
};