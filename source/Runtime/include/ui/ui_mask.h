#pragma once

#include "component/component.h"

class Texture2D;

REFLECTION_TYPE(UIMask)
CLASS(UIMask : public Component, WhiteListFields)
{
	REFLECTION_BODY(UIMask)
	REFLECTION_INFO(UIMask)
public:
	UIMask();
	~UIMask() override;

    Texture2D* texture2D() { return texture2D_; }
    void set_texture(Texture2D * texture2D) { texture2D_ = texture2D; }

public:
    void Update() override;
    
    void OnPreRender() override;
    
    void OnPostRender() override;

    void OnEnable() override;

    void OnDisable() override;

private:
	Texture2D* texture2D_ = nullptr;//Texture
};