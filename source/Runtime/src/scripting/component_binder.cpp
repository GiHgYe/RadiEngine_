#include "scripting/component_binder.h"
#include "component/component.h"
#include "component/game_object.h"
#include "component/transform.h"
#include "ui/ui_image.h"
#include "ui/ui_text.h"
#include "ui/ui_mask.h"
#include "ui/ui_camera.h"
#include "ui/ui_button.h"
#include "audio/audio.h"
#include "audio/core/audio_clip.h"
#include "audio/core/audio_listener.h"
#include "audio/core/audio_source.h"

void LuaComponentBinder::binding(sol::state& sol_state_)
{
	auto cpp_ns_table = sol_state_["Cpp"].get_or_create<sol::table>();

	// Component
	cpp_ns_table.new_usertype<GameObject>("GameObject", sol::call_constructor, sol::constructors<GameObject(const std::string&)>(),
		"name", &GameObject::name,
		"set_name", &GameObject::set_name,
		"layer", &GameObject::layer,
		"set_layer", &GameObject::set_layer,
		"SetParent", &GameObject::SetParent,
		"ForeachComponent", &GameObject::ForeachComponent,
		"Foreach", &GameObject::Foreach,
		"AttachComponent", &GameObject::AttachComponent
	);

	cpp_ns_table.new_usertype<Component>("Component", sol::call_constructor, sol::constructors<Component()>(),
		"Awake", &Component::Awake,
		"Update", &Component::Update,
		"game_object", &Component::game_object,
		"set_game_object", &Component::set_game_object,
		"set_lua_component_instance", &Component::set_lua_component_instance
	);

	cpp_ns_table.new_usertype<Transform>("Transform", sol::call_constructor,
		sol::constructors<Transform(), Transform(const Vector3&, const Quaternion&, const Vector3&)>(),
		sol::base_classes, sol::bases<Component>(),
		"position", &Transform::m_position,
		"rotation", &Transform::m_rotation,
		"scale", &Transform::m_scale,
		"GetMatrix", &Transform::GetMatrix
	);

	// UI
	cpp_ns_table.new_usertype<UIImage>("UIImage", sol::call_constructor, sol::constructors<UIImage()>(),
		"set_texture", &UIImage::set_texture,
		"Update", &UIImage::Update,
		"OnPreRender", &UIImage::OnPreRender,
		"OnPostRender", &UIImage::OnPostRender
	);
	cpp_ns_table.new_usertype<UIText>("UIText", sol::call_constructor, sol::constructors<UIText()>(),
		"set_font", &UIText::set_font,
		"set_text", &UIText::set_text,
		"set_color", &UIText::set_color,
		"color", &UIText::color,
		"Update", &UIText::Update,
		"OnPreRender", &UIText::OnPreRender,
		"OnPostRender", &UIText::OnPostRender
	);
	cpp_ns_table.new_usertype<UIMask>("UIMask", sol::call_constructor, sol::constructors<UIMask()>(),
		"texture2D", &UIMask::texture2D,
		"set_texture", &UIMask::set_texture,
		"Update", &UIMask::Update,
		"OnPreRender", &UIMask::OnPreRender,
		"OnPostRender", &UIMask::OnPostRender,
		"OnEnable", &UIMask::OnEnable,
		"OnDisable", &UIMask::OnDisable
	);
	cpp_ns_table.new_usertype<UIButton>("UIButton", sol::call_constructor, sol::constructors<UIButton()>(),
		"set_image_normal", &UIButton::set_image_normal,
		"set_image_press", &UIButton::set_image_press,
		"set_click_callback", &UIButton::set_click_callback,
		"Update", &UIButton::Update
	);
	cpp_ns_table.new_usertype<UICamera>("UICamera", sol::call_constructor, sol::constructors<UICamera()>());

	// Audio
	cpp_ns_table.new_usertype<Audio>("Audio",
		"Init", &Audio::Init,
		"Update", &Audio::Update
	);

	// cpp_ns_table.new_usertype<AudioClip>("AudioClip", sol::call_constructor, sol::constructors<AudioClip()>(), "LoadFromFile", &AudioClip::LoadFromFile);

	// cpp_ns_table.new_usertype<AudioListener>("AudioListener", sol::call_constructor, sol::constructors<AudioListener()>(),
	// 	"Awake", &AudioListener::Awake, "Update", &AudioListener::Update);

	// cpp_ns_table.new_usertype<AudioSource>("AudioClip", sol::call_constructor, sol::constructors<AudioSource()>(),
	// 	"set_audio_clip", &AudioSource::set_audio_clip,
	// 	"Set3DMode", &AudioSource::Set3DMode,
	// 	"SetLoop", &AudioSource::SetLoop,
	// 	"Play", &AudioSource::Play,
	// 	"Pause", &AudioSource::Pause,
	// 	"Stop", &AudioSource::Stop,
	// 	"Paused", &AudioSource::Paused
	// );

	//cpp_ns_table.new_enum<FMOD_RESULT, true>("FMOD_RESULT", {
	//		{"FMOD_OK",FMOD_RESULT::FMOD_OK},
	//		{"FMOD_ERR_BADCOMMAND",FMOD_RESULT::FMOD_ERR_BADCOMMAND},
	//		{"FMOD_ERR_CHANNEL_ALLOC",FMOD_RESULT::FMOD_ERR_CHANNEL_ALLOC},
	//		{"FMOD_ERR_CHANNEL_STOLEN",FMOD_RESULT::FMOD_ERR_CHANNEL_STOLEN},
	//		{"FMOD_ERR_DMA",FMOD_RESULT::FMOD_ERR_DMA},
	//		{"FMOD_ERR_DSP_CONNECTION",FMOD_RESULT::FMOD_ERR_DSP_CONNECTION},
	//		{"FMOD_ERR_DSP_DONTPROCESS",FMOD_RESULT::FMOD_ERR_DSP_DONTPROCESS},
	//		{"FMOD_ERR_DSP_FORMAT",FMOD_RESULT::FMOD_ERR_DSP_FORMAT},
	//		{"FMOD_ERR_DSP_INUSE",FMOD_RESULT::FMOD_ERR_DSP_INUSE},
	//		{"FMOD_ERR_DSP_NOTFOUND",FMOD_RESULT::FMOD_ERR_DSP_NOTFOUND},
	//		{"FMOD_ERR_DSP_RESERVED",FMOD_RESULT::FMOD_ERR_DSP_RESERVED},
	//		{"FMOD_ERR_DSP_SILENCE",FMOD_RESULT::FMOD_ERR_DSP_SILENCE},
	//		{"FMOD_ERR_DSP_TYPE",FMOD_RESULT::FMOD_ERR_DSP_TYPE},
	//		{"FMOD_ERR_FILE_BAD",FMOD_RESULT::FMOD_ERR_FILE_BAD},
	//		{"FMOD_ERR_FILE_COULDNOTSEEK",FMOD_RESULT::FMOD_ERR_FILE_COULDNOTSEEK},
	//		{"FMOD_ERR_FILE_DISKEJECTED",FMOD_RESULT::FMOD_ERR_FILE_DISKEJECTED},
	//		{"FMOD_ERR_FILE_EOF",FMOD_RESULT::FMOD_ERR_FILE_EOF},
	//		{"FMOD_ERR_FILE_ENDOFDATA",FMOD_RESULT::FMOD_ERR_FILE_ENDOFDATA},
	//		{"FMOD_ERR_FILE_NOTFOUND",FMOD_RESULT::FMOD_ERR_FILE_NOTFOUND},
	//		{"FMOD_ERR_FORMAT",FMOD_RESULT::FMOD_ERR_FORMAT},
	//		{"FMOD_ERR_HEADER_MISMATCH",FMOD_RESULT::FMOD_ERR_HEADER_MISMATCH},
	//		{"FMOD_ERR_HTTP",FMOD_RESULT::FMOD_ERR_HTTP},
	//		{"FMOD_ERR_HTTP_ACCESS",FMOD_RESULT::FMOD_ERR_HTTP_ACCESS},
	//		{"FMOD_ERR_HTTP_PROXY_AUTH",FMOD_RESULT::FMOD_ERR_HTTP_PROXY_AUTH},
	//		{"FMOD_ERR_HTTP_SERVER_ERROR",FMOD_RESULT::FMOD_ERR_HTTP_SERVER_ERROR},
	//		{"FMOD_ERR_HTTP_TIMEOUT",FMOD_RESULT::FMOD_ERR_HTTP_TIMEOUT},
	//		{"FMOD_ERR_INITIALIZATION",FMOD_RESULT::FMOD_ERR_INITIALIZATION},
	//		{"FMOD_ERR_INITIALIZED",FMOD_RESULT::FMOD_ERR_INITIALIZED},
	//		{"FMOD_ERR_INTERNAL",FMOD_RESULT::FMOD_ERR_INTERNAL},
	//		{"FMOD_ERR_INVALID_FLOAT",FMOD_RESULT::FMOD_ERR_INVALID_FLOAT},
	//		{"FMOD_ERR_INVALID_HANDLE",FMOD_RESULT::FMOD_ERR_INVALID_HANDLE},
	//		{"FMOD_ERR_INVALID_PARAM",FMOD_RESULT::FMOD_ERR_INVALID_PARAM},
	//		{"FMOD_ERR_INVALID_POSITION",FMOD_RESULT::FMOD_ERR_INVALID_POSITION},
	//		{"FMOD_ERR_INVALID_SPEAKER",FMOD_RESULT::FMOD_ERR_INVALID_SPEAKER},
	//		{"FMOD_ERR_INVALID_SYNCPOINT",FMOD_RESULT::FMOD_ERR_INVALID_SYNCPOINT},
	//		{"FMOD_ERR_INVALID_THREAD",FMOD_RESULT::FMOD_ERR_INVALID_THREAD},
	//		{"FMOD_ERR_INVALID_VECTOR",FMOD_RESULT::FMOD_ERR_INVALID_VECTOR},
	//		{"FMOD_ERR_MAXAUDIBLE",FMOD_RESULT::FMOD_ERR_MAXAUDIBLE},
	//		{"FMOD_ERR_MEMORY",FMOD_RESULT::FMOD_ERR_MEMORY},
	//		{"FMOD_ERR_MEMORY_CANTPOINT",FMOD_RESULT::FMOD_ERR_MEMORY_CANTPOINT},
	//		{"FMOD_ERR_NEEDS3D",FMOD_RESULT::FMOD_ERR_NEEDS3D},
	//		{"FMOD_ERR_NEEDSHARDWARE",FMOD_RESULT::FMOD_ERR_NEEDSHARDWARE},
	//		{"FMOD_ERR_NET_CONNECT",FMOD_RESULT::FMOD_ERR_NET_CONNECT},
	//		{"FMOD_ERR_NET_SOCKET_ERROR",FMOD_RESULT::FMOD_ERR_NET_SOCKET_ERROR},
	//		{"FMOD_ERR_NET_URL",FMOD_RESULT::FMOD_ERR_NET_URL},
	//		{"FMOD_ERR_NET_WOULD_BLOCK",FMOD_RESULT::FMOD_ERR_NET_WOULD_BLOCK},
	//		{"FMOD_ERR_NOTREADY",FMOD_RESULT::FMOD_ERR_NOTREADY},
	//		{"FMOD_ERR_OUTPUT_ALLOCATED",FMOD_RESULT::FMOD_ERR_OUTPUT_ALLOCATED},
	//		{"FMOD_ERR_OUTPUT_CREATEBUFFER",FMOD_RESULT::FMOD_ERR_OUTPUT_CREATEBUFFER},
	//		{"FMOD_ERR_OUTPUT_DRIVERCALL",FMOD_RESULT::FMOD_ERR_OUTPUT_DRIVERCALL},
	//		{"FMOD_ERR_OUTPUT_FORMAT",FMOD_RESULT::FMOD_ERR_OUTPUT_FORMAT},
	//		{"FMOD_ERR_OUTPUT_INIT",FMOD_RESULT::FMOD_ERR_OUTPUT_INIT},
	//		{"FMOD_ERR_OUTPUT_NODRIVERS",FMOD_RESULT::FMOD_ERR_OUTPUT_NODRIVERS},
	//		{"FMOD_ERR_PLUGIN",FMOD_RESULT::FMOD_ERR_PLUGIN},
	//		{"FMOD_ERR_PLUGIN_MISSING",FMOD_RESULT::FMOD_ERR_PLUGIN_MISSING},
	//		{"FMOD_ERR_PLUGIN_RESOURCE",FMOD_RESULT::FMOD_ERR_PLUGIN_RESOURCE},
	//		{"FMOD_ERR_PLUGIN_VERSION",FMOD_RESULT::FMOD_ERR_PLUGIN_VERSION},
	//		{"FMOD_ERR_RECORD",FMOD_RESULT::FMOD_ERR_RECORD},
	//		{"FMOD_ERR_REVERB_CHANNELGROUP",FMOD_RESULT::FMOD_ERR_REVERB_CHANNELGROUP},
	//		{"FMOD_ERR_REVERB_INSTANCE",FMOD_RESULT::FMOD_ERR_REVERB_INSTANCE},
	//		{"FMOD_ERR_SUBSOUNDS",FMOD_RESULT::FMOD_ERR_SUBSOUNDS},
	//		{"FMOD_ERR_SUBSOUND_ALLOCATED",FMOD_RESULT::FMOD_ERR_SUBSOUND_ALLOCATED},
	//		{"FMOD_ERR_SUBSOUND_CANTMOVE",FMOD_RESULT::FMOD_ERR_SUBSOUND_CANTMOVE},
	//		{"FMOD_ERR_TAGNOTFOUND",FMOD_RESULT::FMOD_ERR_TAGNOTFOUND},
	//		{"FMOD_ERR_TOOMANYCHANNELS",FMOD_RESULT::FMOD_ERR_TOOMANYCHANNELS},
	//		{"FMOD_ERR_TRUNCATED",FMOD_RESULT::FMOD_ERR_TRUNCATED},
	//		{"FMOD_ERR_UNIMPLEMENTED",FMOD_RESULT::FMOD_ERR_UNIMPLEMENTED},
	//		{"FMOD_ERR_UNINITIALIZED",FMOD_RESULT::FMOD_ERR_UNINITIALIZED},
	//		{"FMOD_ERR_UNSUPPORTED",FMOD_RESULT::FMOD_ERR_UNSUPPORTED},
	//		{"FMOD_ERR_VERSION",FMOD_RESULT::FMOD_ERR_VERSION},
	//		{"FMOD_ERR_EVENT_ALREADY_LOADED",FMOD_RESULT::FMOD_ERR_EVENT_ALREADY_LOADED},
	//		{"FMOD_ERR_EVENT_LIVEUPDATE_BUSY",FMOD_RESULT::FMOD_ERR_EVENT_LIVEUPDATE_BUSY},
	//		{"FMOD_ERR_EVENT_LIVEUPDATE_MISMATCH",FMOD_RESULT::FMOD_ERR_EVENT_LIVEUPDATE_MISMATCH},
	//		{"FMOD_ERR_EVENT_LIVEUPDATE_TIMEOUT",FMOD_RESULT::FMOD_ERR_EVENT_LIVEUPDATE_TIMEOUT},
	//		{"FMOD_ERR_EVENT_NOTFOUND",FMOD_RESULT::FMOD_ERR_EVENT_NOTFOUND},
	//		{"FMOD_ERR_STUDIO_UNINITIALIZED",FMOD_RESULT::FMOD_ERR_STUDIO_UNINITIALIZED},
	//		{"FMOD_ERR_STUDIO_NOT_LOADED",FMOD_RESULT::FMOD_ERR_STUDIO_NOT_LOADED},
	//		{"FMOD_ERR_INVALID_STRING",FMOD_RESULT::FMOD_ERR_INVALID_STRING},
	//		{"FMOD_ERR_ALREADY_LOCKED",FMOD_RESULT::FMOD_ERR_ALREADY_LOCKED},
	//		{"FMOD_ERR_NOT_LOCKED",FMOD_RESULT::FMOD_ERR_NOT_LOCKED},
	//		{"FMOD_ERR_RECORD_DISCONNECTED",FMOD_RESULT::FMOD_ERR_RECORD_DISCONNECTED},
	//		{"FMOD_ERR_TOOMANYSAMPLES",FMOD_RESULT::FMOD_ERR_TOOMANYSAMPLES},
	//		{"FMOD_RESULT_FORCEINT",FMOD_RESULT::FMOD_RESULT_FORCEINT}
	//});


}
