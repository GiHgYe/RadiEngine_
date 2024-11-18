require("utils/lua_extension")
require("renderer/camera")
require("renderer/mesh_filter")
require("renderer/mesh_renderer")
require("renderer/animation_clip")
require("renderer/material")
require("control/input")
require("control/key_code")
require("utils/screen")
require("utils/time")

LoginScene=Class("LoginScene",Component)

--- 登录场景
---@class LoginScene
function LoginScene:ctor()
    LoginScene.super.ctor(self)
    self.go_camera_1_=nil
    self.camera_1_=nil
    self.transofrm_camera_1 =nil
    self.last_frame_mouse_position_=nil
end

function LoginScene:Awake()
    print("LoginScene Awake")
    LoginScene.super.Awake(self)
    -- self.animation_clip_=AnimationClip.new()
    -- self.animation_clip_:LoadFromFile("./asset/animation/export.skeleton_anim")
    -- self.animation_clip_:Play()
    
    LoginScene.super.Awake(self)
    --创建相机1 GameObject
    self.go_camera_1_= GameObject.new("main_camera")
    --挂上 Transform 组件
    self.transofrm_camera_1 = self.go_camera_1_:AddComponent(Transform)
    self.transofrm_camera_1:set_position(Math.Vector3(0, 0, 10))
    --挂上 Camera 组件
    self.camera_1_=self.go_camera_1_:AddComponent(Camera)
    self.camera_1_:set_depth(0)
    self.last_frame_mouse_position_=Input.mousePosition()
    self:CreateCube()
end

function LoginScene:Update()
    LoginScene.super.Update(self)
    -- self.animation_clip_:Update()
    LoginScene.super.Update(self)
    self.camera_1_:set_depth(0)
    self.camera_1_:SetView(Math.Vector3(0.0,0.0,0.0), Math.Vector3(0.0,1.0,0.0))
    self.camera_1_:SetPerspective(60, Screen.aspect_ratio(), 1, 1000)

    --旋转相机
    if Input.GetKeyDown(KeyCode.KEY_CODE_LEFT_ALT) and Input.GetMouseButtonDown(KeyCode.MOUSE_BUTTON_LEFT) then
        local degrees= Input.mousePosition().x - self.last_frame_mouse_position_.x
        local radian = Math.Radian(Math.Degree(-degrees))
        local q = Math.Quaternion.GetQuaternionFromAngleAxis(radian, Math.Vector3(0,1,0))
        self.transofrm_camera_1:set_position(q * self.transofrm_camera_1:position())
    end

    self.last_frame_mouse_position_=Input.mousePosition()

    --鼠标滚轮控制相机远近
    local transform = self.go_camera_1_:GetComponent(Transform)
    transform:set_position(transform:position() *(10 - Input.mouse_scroll())/10)

end

function LoginScene:CreateCube()
    local go_cube = GameObject.new("Cube")
    local transform = go_cube:AddComponent(Transform)
    local mesh_filter = go_cube:AddComponent(MeshFilter)
    mesh_filter:LoadMesh("./asset/model/cube.mesh")
    local mesh_renderer = go_cube:AddComponent(MeshRenderer)
    local material = Material.new()
    material:Parse("./asset/material/cube.mat")
    mesh_renderer:SetMaterial(material)

end

-- function LoginScene:CreateAudioSource()
--     self.go_audio_source_bgm_= GameObject.new("audio_source_bgm")
--     --挂上 Transform 组件
--     local transform = self.go_audio_source_bgm_:AddComponent(Transform)
--     --挂上 MeshFilter 组件
--     local mesh_filter= self.go_audio_source_bgm_:AddComponent(MeshFilter)
--     mesh_filter:LoadMesh("model/sphere.mesh")
--     --挂上 MeshRenderer 组件
--     local mesh_renderer= self.go_audio_source_bgm_:AddComponent(MeshRenderer)
--     self.material_player_ = Material.new()--设置材质
--     self.material_player_:Parse("material/sphere_audio_source_3d_music.mat")
--     mesh_renderer:SetMaterial(self.material_player_)

--     --加载bank
--     AudioStudio:LoadBankFile("audio/test.bank")
--     AudioStudio:LoadBankFile("audio/test.strings.bank")
--     self.audio_studio_event_=AudioStudio:CreateEventInstance("event:/footstep")
-- end

-- function LoginScene:CreateAudioListener()
--     self.go_player_= GameObject.new("Player")
--     self.transform_player_ =self.go_player_:AddComponent(Transform)
--     self.transform_player_:set_position(Math.Vector3(2.0,0.0,0.0))
--     local mesh_filter=self.go_player_:AddComponent(MeshFilter)
--     mesh_filter:LoadMesh("model/sphere.mesh")
--     local mesh_renderer=self.go_player_:AddComponent(MeshRenderer)
--     self.material_audio_listener_ = Material.new()--设置材质
--     self.material_audio_listener_:Parse("material/sphere_audio_source_3d_listener.mat")
--     mesh_renderer:SetMaterial(self.material_audio_listener_)

--     --设置听者位置
--     AudioStudio:SetListenerAttributes(0,0,0)
-- end


