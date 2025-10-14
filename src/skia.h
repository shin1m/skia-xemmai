#ifndef XEMMAIX__SKIA__SKIA_H
#define XEMMAIX__SKIA__SKIA_H

#include <xemmai/convert.h>
#include <include/core/SkCanvas.h>
#include <include/core/SkFontMetrics.h>
#include <include/core/SkFontStyle.h>
#include <include/core/SkPath.h>
#include <include/core/SkRect.h>
#include <include/core/SkSamplingOptions.h>

namespace xemmaix::skia
{

using namespace xemmai;

class t_entry
{
protected:
	t_entry* v_previous;
	t_entry* v_next;

	t_entry() : v_previous(this), v_next(this)
	{
	}
	t_entry(t_entry* a_previous) : v_previous(a_previous), v_next(a_previous->v_next)
	{
		v_previous->v_next = v_next->v_previous = this;
	}
	~t_entry()
	{
		v_previous->v_next = v_next;
		v_next->v_previous = v_previous;
	}
};

class t_session : public t_entry
{
	static inline XEMMAI__PORTABLE__THREAD t_session* v_instance;

public:
	static t_session* f_instance()
	{
		if (!v_instance) f_throw(L"must be inside main."sv);
		return v_instance;
	}

	t_session()
	{
		if (v_instance) f_throw(L"already inside main."sv);
		v_instance = this;
	}
	~t_session();
};

class t_proxy : public t_entry
{
	t_entry* v_session = v_previous;
	t_root v_object = t_object::f_of(this);

protected:
	t_proxy() : t_entry(t_session::f_instance())
	{
	}

public:
	virtual void f_dispose();
	bool f_valid()
	{
		return v_session == t_session::f_instance() && v_object;
	}
};

template<typename T>
struct t_proxy_of : t_proxy, T
{
	using t_base = t_proxy_of;

	template<typename... T_n>
	t_proxy_of(T_n&&... a_n) : T(std::forward<T_n>(a_n)...)
	{
	}
	virtual void f_dispose()
	{
		T::~T();
		t_proxy::f_dispose();
	}
};

struct t_surface;
struct t_gl_context;
struct t_canvas;
struct t_font;
struct t_font_manager;
struct t_image;
struct t_paint;
struct t_path;
struct t_typeface;

class t_library : public xemmai::t_library
{
#define XEMMAIX__SKIA__TYPES(_)\
	_(proxy)\
	_(surface)\
	_(gl_context)\
	_##_AS(SkFilterMode, filter_mode)\
	_##_AS(SkMipmapMode, mipmap_mode)\
	_##_AS(SkSamplingOptions, sampling_options)\
	_##_AS(SkCanvas::SrcRectConstraint, source_rect_constraint)\
	_(canvas)\
	_(font)\
	_(font_manager)\
	_##_AS(SkFontMetrics, font_metrics)\
	_##_AS(SkFontStyle, font_style)\
	_##_AS(SkFontStyle::Slant, font_style_slant)\
	_(image)\
	_(paint)\
	_##_AS(SkPaint::Style, paint_style)\
	_(path)\
	_##_AS(SkPath::ArcSize, path_arc_size)\
	_##_AS(SkPathDirection, path_direction)\
	_##_AS(SkPathFillType, path_fill_type)\
	_##_AS(SkRect, rect)\
	_(typeface)
	XEMMAIX__SKIA__TYPES(XEMMAI__TYPE__DECLARE)

public:
	using xemmai::t_library::t_library;
	XEMMAI__LIBRARY__MEMBERS
};

XEMMAI__LIBRARY__BASE(t_library, t_global, f_global())
#define XEMMAI__TYPE__LIBRARY t_library
XEMMAIX__SKIA__TYPES(XEMMAI__TYPE__DEFINE)
#undef XEMMAI__TYPE__LIBRARY

}

namespace xemmai
{

template<>
struct t_type_of<xemmaix::skia::t_proxy> : t_bears<xemmaix::skia::t_proxy>
{
	template<typename T>
	static T& f_cast(auto&& a_object)
	{
		auto& p = static_cast<t_object*>(a_object)->f_as<T>();
		if (!p.f_valid()) f_throw(L"not valid."sv);
		return p;
	}
	template<typename T>
	struct t_cast
	{
		static T f_as(auto&& a_object)
		{
			return std::forward<T>(f_cast<typename t_fundamental<T>::t_type>(std::forward<decltype(a_object)>(a_object)));
		}
		static bool f_is(t_object* a_object)
		{
			return reinterpret_cast<uintptr_t>(a_object) >= c_tag__OBJECT && a_object->f_type()->f_derives<typename t_fundamental<T>::t_type>();
		}
	};
	template<typename T>
	struct t_cast<T*>
	{
		static T* f_as(auto&& a_object)
		{
			return static_cast<t_object*>(a_object) ? &f_cast<typename t_fundamental<T>::t_type>(std::forward<decltype(a_object)>(a_object)) : nullptr;
		}
		static bool f_is(t_object* a_object)
		{
			return reinterpret_cast<uintptr_t>(a_object) == c_tag__NULL || reinterpret_cast<uintptr_t>(a_object) >= c_tag__OBJECT && a_object->f_type()->f_derives<typename t_fundamental<T>::t_type>();
		}
	};

	using t_library = xemmaix::skia::t_library;

	static t_pvalue f_transfer(auto* a_library, auto&& a_value)
	{
		return t_object::f_of(reinterpret_cast<xemmaix::skia::t_proxy*>(&a_value) - 1);
	}
	static void f_define(t_library* a_library);

	using t_base::t_base;
};

}

#endif
