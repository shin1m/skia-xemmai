#ifndef XEMMAIX__SKIA__FONT_H
#define XEMMAIX__SKIA__FONT_H

#include "skia.h"
#include <include/core/SkFont.h>

namespace xemmaix::skia
{

struct t_font : t_proxy_of<SkFont>
{
	using t_base::t_base;
};

}

namespace xemmai
{

template<>
struct t_type_of<SkFontMetrics> : t_holds<SkFontMetrics>
{
	using t_library = xemmaix::skia::t_library;

	static void f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_fundamental<SkFont>
{
	using t_type = xemmaix::skia::t_font;
};

template<>
struct t_type_of<xemmaix::skia::t_font> : t_bears<xemmaix::skia::t_font, t_type_of<xemmaix::skia::t_proxy>>
{
	static void f_define(t_library* a_library);

	using t_base::t_base;
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

}

#endif
