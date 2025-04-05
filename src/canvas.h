#ifndef XEMMAIX__SKIA__CANVAS_H
#define XEMMAIX__SKIA__CANVAS_H

#include "skia.h"

namespace xemmaix::skia
{

struct t_canvas
{
	t_session* v_session = t_session::f_instance();
	SkCanvas* v_p;

	t_canvas(SkCanvas* a_p) : v_p(a_p)
	{
	}
	void f_check()
	{
		if (v_session != t_session::f_instance()) f_throw(L"not valid."sv);
	}
	bool f_valid()
	{
		return v_session == t_session::f_instance();
	}
};

}

namespace xemmai
{

template<>
struct t_type_of<SkFilterMode> : t_enum_of<SkFilterMode, xemmaix::skia::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<SkMipmapMode> : t_enum_of<SkMipmapMode, xemmaix::skia::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<SkSamplingOptions> : t_holds<SkSamplingOptions>
{
	using t_library = xemmaix::skia::t_library;

	static void f_define(t_library* a_library);

	using t_base::t_base;
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

template<>
struct t_type_of<SkCanvas::SrcRectConstraint> : t_enum_of<SkCanvas::SrcRectConstraint, xemmaix::skia::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_fundamental<SkCanvas>
{
	using t_type = xemmaix::skia::t_canvas;
};

template<>
struct t_type_of<xemmaix::skia::t_canvas> : t_uninstantiatable<t_bears<xemmaix::skia::t_canvas>>
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

	static void f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
template<>
struct t_type_of<xemmaix::skia::t_canvas>::t_cast<SkCanvas&>
{
	static SkCanvas& f_as(auto&& a_object)
	{
		return *f_cast<xemmaix::skia::t_canvas>(std::forward<decltype(a_object)>(a_object)).v_p;
	}
	static bool f_is(t_object* a_object)
	{
		return t_cast<xemmaix::skia::t_canvas>::f_is(a_object);
	}
};

}

#endif
