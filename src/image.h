#ifndef XEMMAIX__SKIA__IMAGE_H
#define XEMMAIX__SKIA__IMAGE_H

#include "skia.h"
#include <include/core/SkImage.h>

namespace xemmaix::skia
{

struct t_image : t_proxy_of<sk_sp<SkImage>>
{
	using t_base::t_base;
};

}

namespace xemmai
{

template<>
struct t_fundamental<sk_sp<SkImage>>
{
	using t_type = xemmaix::skia::t_image;
};

template<>
struct t_type_of<xemmaix::skia::t_image> : t_uninstantiatable<t_bears<xemmaix::skia::t_image, t_type_of<xemmaix::skia::t_proxy>>>
{
	static void f_define(t_library* a_library);

	using t_base::t_base;
};

}

#endif
