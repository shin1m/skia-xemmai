#ifndef XEMMAIX__SKIA__PAINT_H
#define XEMMAIX__SKIA__PAINT_H

#include "skia.h"
#include <include/core/SkPaint.h>

namespace xemmaix::skia
{

struct t_paint : t_proxy_of<SkPaint>
{
	using t_base::t_base;
};

}

namespace xemmai
{

template<>
struct t_type_of<SkPaint::Style> : t_enum_of<SkPaint::Style, xemmaix::skia::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_fundamental<SkPaint>
{
	using t_type = xemmaix::skia::t_paint;
};

template<>
struct t_type_of<xemmaix::skia::t_paint> : t_bears<xemmaix::skia::t_paint, t_type_of<xemmaix::skia::t_proxy>>
{
	static void f_define(t_library* a_library);

	using t_base::t_base;
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

}

#endif
