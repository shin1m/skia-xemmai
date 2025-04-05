#ifndef XEMMAIX__SKIA__FONT_MANAGER_H
#define XEMMAIX__SKIA__FONT_MANAGER_H

#include "skia.h"
#include <include/core/SkFontMgr.h>

namespace xemmaix::skia
{

struct t_font_manager : t_proxy_of<sk_sp<SkFontMgr>>
{
	using t_base::t_base;
};

}

namespace xemmai
{

template<>
struct t_type_of<SkFontStyle::Slant> : t_enum_of<SkFontStyle::Slant, xemmaix::skia::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<SkFontStyle> : t_holds<SkFontStyle>
{
	using t_library = xemmaix::skia::t_library;

	static void f_define(t_library* a_library);

	using t_base::t_base;
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

template<>
struct t_fundamental<sk_sp<SkFontMgr>>
{
	using t_type = xemmaix::skia::t_font_manager;
};

template<>
struct t_type_of<xemmaix::skia::t_font_manager> : t_uninstantiatable<t_bears<xemmaix::skia::t_font_manager, t_type_of<xemmaix::skia::t_proxy>>>
{
	static void f_define(t_library* a_library);

	using t_base::t_base;
};

}

#endif
