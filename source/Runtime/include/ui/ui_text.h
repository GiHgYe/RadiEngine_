#pragma once
#include "component/component.h"
#include "renderer/font.h"
#include "math/math_headers.h"

REFLECTION_TYPE(UIText)
CLASS(UIText : public Component, WhiteListFields)
{
	REFLECTION_BODY(UIText)
	REFLECTION_INFO(UIText)
public:
	UIText();
	~UIText();

	void set_font(Font * font) { font_ = font; }
	Font* font() { return font_; }

	void set_text(std::string text);
	std::string text() { return text_; }

	void set_color(Vector4 color) { color_ = color; }
	Vector4 color() { return color_; }

public:
	void Update() override;
	/// 渲染之前
	void OnPreRender() override;
	void OnPostRender() override;

private:
	Font* font_{ nullptr };
	std::string text_;
	bool dirty_{ false };	//是否变化需要重新生成Mesh
	Vector4 color_;			//字体颜色
};