#ifndef XEMMAIX__SKIA__PATH_H
#define XEMMAIX__SKIA__PATH_H

#include "skia.h"
#include <include/core/SkPath.h>

namespace xemmaix::skia
{

struct t_path : t_proxy_of<SkPath>
{
	using t_base::t_base;
};

}

namespace xemmai
{

template<>
struct t_fundamental<SkPath>
{
	using t_type = xemmaix::skia::t_path;
};

template<>
struct t_type_of<xemmaix::skia::t_path> : t_bears<xemmaix::skia::t_path, t_type_of<xemmaix::skia::t_proxy>>
{
	static void f_define(t_library* a_library);

	using t_base::t_base;
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

}

#endif
