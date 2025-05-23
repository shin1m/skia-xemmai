#ifndef XEMMAIX__SKIA__SURFACE_H
#define XEMMAIX__SKIA__SURFACE_H

#include "skia.h"
#include <include/core/SkSurface.h>

namespace xemmaix::skia
{

struct t_surface : t_proxy_of<sk_sp<SkSurface>>
{
	using t_base::t_base;
};

struct t_gl_context : t_proxy_of<sk_sp<GrDirectContext>>
{
	using t_base::t_base;
};

}

namespace xemmai
{

template<>
struct t_fundamental<sk_sp<SkSurface>>
{
	using t_type = xemmaix::skia::t_surface;
};

template<>
struct t_type_of<xemmaix::skia::t_surface> : t_uninstantiatable<t_bears<xemmaix::skia::t_surface, t_type_of<xemmaix::skia::t_proxy>>>
{
	static void f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_type_of<xemmaix::skia::t_gl_context> : t_bears<xemmaix::skia::t_gl_context, t_type_of<xemmaix::skia::t_proxy>>
{
	static void f_define(t_library* a_library);

	using t_base::t_base;
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

}

#endif
