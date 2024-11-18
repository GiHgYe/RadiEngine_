#pragma once
#include "component/component.h"
#include "ui/ui_image.h"


REFLECTION_TYPE(UIButton)
CLASS(UIButton : public Component, WhiteListFields)
{
	REFLECTION_BODY(UIButton)
	REFLECTION_INFO(UIButton)
public:
	UIButton();
	~UIButton();

	void set_image_normal(UIImage * image) { image_normal_ = image; }
	void set_image_press(UIImage * image) { image_press_ = image; }
	/// ���ð�ť����ص�
	/// \param callback
	void set_click_callback(std::function<void()> click_callback) { click_callback_ = click_callback; }

public:
	void Update() override;

private:
	UIImage* image_normal_;	//��ͨ״̬��ʾͼƬ
	UIImage* image_press_;	//��ѹ״̬��ʾͼƬ
	bool pressed_;			//��ǰ��ť״̬�Ƿ���
	std::function<void()> click_callback_;//��ť����ص�
};