#include "ui/ui_button.h"
#include "component/game_object.h"
#include "component/transform.h"
#include "renderer/texture2d.h"
#include "utils/debug.h"
#include "utils/screen.h"
#include "control/input.h"
#include "control/key_code.h"

UIButton::UIButton() :pressed_(false), click_callback_(nullptr) {

}

UIButton::~UIButton() {

}

void UIButton::Update() {
    Component::Update();

    if (image_normal_ == nullptr || image_press_ == nullptr) {
        return;
    }

    Transform* transform = game_object()->GetComponent<Transform>();
    //��ť��ͼƬ �� ��ť����ͬ��
    Transform* transform_image_normal = image_normal_->game_object()->GetComponent<Transform>();
    Transform* transform_image_press = image_press_->game_object()->GetComponent<Transform>();
    transform_image_normal->m_position = transform->m_position;
    transform_image_press->m_position = transform->m_position;

    if (Input::GetMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        auto transform_position = transform->m_position;
        //��ȡ������꣬�������Ͻ���㣬ת��Ϊ��Ļ������㡣
        auto mouse_position = Input::mousePosition();
        mouse_position.x = mouse_position.x - Screen::width() / 2;
        mouse_position.y = Screen::height() / 2.0f - mouse_position.y;
        //��ȡ��ťͼƬ���
        float image_normal_width = image_normal_->width();
        float image_normal_height = image_normal_->height();
        //����������Ƿ��ڰ�ťͼƬ��Χ��
        if ((mouse_position.x > transform_position.x && mouse_position.x < transform_position.x + image_normal_width) &&
            (mouse_position.y > transform_position.y && mouse_position.y < transform_position.y + image_normal_height)) {
            if (pressed_) return;
            pressed_ = true;
            //������ť����ص�
            if (click_callback_) {
                click_callback_();
            }
        }
        else {
            pressed_ = false;
        }
    }
    else {
        pressed_ = false;
    }

    transform_image_normal->game_object()->set_active(!pressed_);
    transform_image_press->game_object()->set_active(pressed_);
}

