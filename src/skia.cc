#include "surface.h"
#include "canvas.h"
#include "font.h"
#include "font_manager.h"
#include "image.h"
#include "paint.h"
#include "path.h"
#include "rect.h"
#include "typeface.h"

namespace xemmaix::skia
{

void t_entry::f_dispose()
{
	v_previous->v_next = v_next;
	v_next->v_previous = v_previous;
}

void t_proxy::f_dispose()
{
	t_entry::f_dispose();
	v_object = nullptr;
}

void t_library::f_main(const t_pvalue& a_callable)
{
	t_session session;
	a_callable();
}

void t_library::f_scan(t_scan a_scan)
{
	a_scan(v_type_proxy);
	a_scan(v_type_surface);
	a_scan(v_type_filter_mode);
	a_scan(v_type_mipmap_mode);
	a_scan(v_type_sampling_options);
	a_scan(v_type_source_rect_constraint);
	a_scan(v_type_canvas);
	a_scan(v_type_font);
	a_scan(v_type_font_manager);
	a_scan(v_type_font_metrics);
	a_scan(v_type_font_style);
	a_scan(v_type_font_style_slant);
	a_scan(v_type_image);
	a_scan(v_type_paint);
	a_scan(v_type_paint_style);
	a_scan(v_type_path);
	a_scan(v_type_rect);
	a_scan(v_type_typeface);
}

std::vector<std::pair<t_root, t_rvalue>> t_library::f_define()
{
	t_type_of<t_proxy>::f_define(this);
	t_type_of<t_surface>::f_define(this);
	t_type_of<SkSamplingOptions>::f_define(this);
	t_type_of<t_canvas>::f_define(this);
	t_type_of<t_font>::f_define(this);
	t_type_of<t_font_manager>::f_define(this);
	t_type_of<SkFontMetrics>::f_define(this);
	t_type_of<SkFontStyle>::f_define(this);
	t_type_of<t_image>::f_define(this);
	t_type_of<t_paint>::f_define(this);
	t_type_of<t_path>::f_define(this);
	t_type_of<SkRect>::f_define(this);
	t_type_of<t_typeface>::f_define(this);
	return t_define(this)
		(L"Proxy"sv, static_cast<t_object*>(v_type_proxy))
		(L"Surface"sv, static_cast<t_object*>(v_type_surface))
		(L"FilterMode"sv, t_type_of<SkFilterMode>::f_define(this))
		(L"MipmapMode"sv, t_type_of<SkMipmapMode>::f_define(this))
		(L"SamplingOptions"sv, static_cast<t_object*>(v_type_sampling_options))
		(L"Canvas"sv, static_cast<t_object*>(v_type_canvas))
		(L"Font"sv, static_cast<t_object*>(v_type_font))
		(L"FontManager"sv, static_cast<t_object*>(v_type_font_manager))
		(L"FontMetrics"sv, static_cast<t_object*>(v_type_font_metrics))
		(L"FontStyle"sv, static_cast<t_object*>(v_type_font_style))
		(L"Image"sv, static_cast<t_object*>(v_type_image))
		(L"Paint"sv, static_cast<t_object*>(v_type_paint))
		(L"Path"sv, static_cast<t_object*>(v_type_path))
		(L"Rect"sv, static_cast<t_object*>(v_type_rect))
		(L"Typeface"sv, static_cast<t_object*>(v_type_typeface))
		(L"main"sv, t_static<void(*)(const t_pvalue&), f_main>())
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
