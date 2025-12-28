#include "surface.h"
#include "canvas.h"
#include "font.h"
#include "font_manager.h"
#include "image.h"
#include "paint.h"
#include "path.h"
#include "rect.h"
#include "shader.h"
#include "typeface.h"

namespace xemmaix::skia
{

t_session::~t_session()
{
	while (v_next != this) static_cast<t_proxy*>(v_next)->f_dispose();
	v_instance = nullptr;
}

void t_proxy::f_dispose()
{
	v_object = nullptr;
	this->~t_entry();
}

void t_library::f_scan(t_scan a_scan)
{
	XEMMAIX__SKIA__TYPES(XEMMAI__TYPE__SCAN)
}

std::vector<std::pair<t_root, t_rvalue>> t_library::f_define()
{
	t_type_of<t_proxy>::f_define(this);
	t_type_of<t_surface>::f_define(this);
	t_type_of<t_gl_context>::f_define(this);
	t_type_of<SkSamplingOptions>::f_define(this);
	t_type_of<t_canvas>::f_define(this);
	t_type_of<SkFontMetrics>::f_define(this);
	t_type_of<t_font>::f_define(this);
	t_type_of<SkFontStyle>::f_define(this);
	t_type_of<t_font_manager>::f_define(this);
	t_type_of<t_image>::f_define(this);
	t_type_of<t_paint>::f_define(this);
	t_type_of<t_path>::f_define(this);
	t_type_of<t_path_builder>::f_define(this);
	t_type_of<SkRect>::f_define(this);
	t_type_of<t_shader>::f_define(this);
	t_type_of<t_typeface>::f_define(this);
	return t_define(this)
	(L"Proxy"sv, static_cast<t_object*>(v_type_proxy))
	(L"Surface"sv, static_cast<t_object*>(v_type_surface))
	(L"GLContext"sv, static_cast<t_object*>(v_type_gl_context))
	(L"FilterMode"sv, t_type_of<SkFilterMode>::f_define(this))
	(L"MipmapMode"sv, t_type_of<SkMipmapMode>::f_define(this))
	(L"SamplingOptions"sv, static_cast<t_object*>(v_type_sampling_options))
	(L"Canvas"sv, static_cast<t_object*>(v_type_canvas))
	(L"FontMetrics"sv, static_cast<t_object*>(v_type_font_metrics))
	(L"Font"sv, static_cast<t_object*>(v_type_font))
	(L"FontStyle"sv, static_cast<t_object*>(v_type_font_style))
	(L"FontManager"sv, static_cast<t_object*>(v_type_font_manager))
	(L"Image"sv, static_cast<t_object*>(v_type_image))
	(L"Paint"sv, static_cast<t_object*>(v_type_paint))
	(L"Path"sv, static_cast<t_object*>(v_type_path))
	(L"PathBuilder"sv, static_cast<t_object*>(v_type_path_builder))
	(L"Rect"sv, static_cast<t_object*>(v_type_rect))
	(L"Shader"sv, static_cast<t_object*>(v_type_shader))
	(L"Typeface"sv, static_cast<t_object*>(v_type_typeface))
	(L"main"sv, t_static<void(*)(const t_pvalue&), [](auto a_callable)
	{
		t_session session;
		a_callable();
	}>())
	;
}

}

namespace xemmai
{

void t_type_of<xemmaix::skia::t_proxy>::f_define(t_library* a_library)
{
	using xemmaix::skia::t_proxy;
	t_define{a_library}
	(L"dispose"sv, t_member<void(t_proxy::*)(), &t_proxy::f_dispose>())
	.f_derive<t_proxy, t_object>();
}

}

XEMMAI__MODULE__FACTORY(xemmai::t_library::t_handle* a_handle)
{
	return xemmai::f_new<xemmaix::skia::t_library>(a_handle);
}
