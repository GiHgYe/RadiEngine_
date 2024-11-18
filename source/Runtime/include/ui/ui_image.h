#pragma once
#include <iostream>
#include <vector>
#include "component/component.h"
#include "renderer/texture2d.h"

class Texture2D;

REFLECTION_TYPE(UIImage)
CLASS(UIImage : public Component, WhiteListFields)
{
	REFLECTION_BODY(UIImage)
	REFLECTION_INFO(UIImage)
public:
	UIImage();
	~UIImage() override;

	Texture2D* texture2D() { return texture2D_; }
	void set_texture(Texture2D * texture2D) { 
		texture2D_ = texture2D; 
		width_ = texture2D->width();
		height_ = texture2D->height();
	}

	int width() { return width_; }
	int height() { return height_; }

public:
	void Awake() override;
	void Update() override;

	void OnPreRender() override;
	void OnPostRender() override;

private:
	Texture2D* texture2D_;
	int width_;
	int height_;
};
