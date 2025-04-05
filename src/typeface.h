#ifndef XEMMAIX__SKIA__TYPEFACE_H
#define XEMMAIX__SKIA__TYPEFACE_H

#include "skia.h"
#include <include/core/SkTypeface.h>

namespace xemmaix::skia
{

struct t_typeface : t_proxy_of<sk_sp<SkTypeface>>
{
	using t_base::t_base;
};

}

namespace xemmai
{

template<>
struct t_fundamental<sk_sp<SkTypeface>>
{
	using t_type = xemmaix::skia::t_typeface;
};

template<>
struct t_type_of<xemmaix::skia::t_typeface> : t_uninstantiatable<t_bears<xemmaix::skia::t_typeface, t_type_of<xemmaix::skia::t_proxy>>>
{
	static void f_define(t_library* a_library);

	using t_base::t_base;
};

}

#endif
