#ifndef XEMMAIX__SKIA__SHADER_H
#define XEMMAIX__SKIA__SHADER_H

#include "skia.h"
#include <include/core/SkShader.h>

namespace xemmaix::skia
{

struct t_shader : t_proxy_of<sk_sp<SkShader>>
{
	using t_base::t_base;
};

}

namespace xemmai
{

template<>
struct t_type_of<SkTileMode> : t_enum_of<SkTileMode, xemmaix::skia::t_library>
{
	static t_object* f_define(t_library* a_library);

	using t_base::t_base;
};

template<>
struct t_fundamental<sk_sp<SkShader>>
{
	using t_type = xemmaix::skia::t_shader;
};

template<>
struct t_type_of<xemmaix::skia::t_shader> : t_uninstantiatable<t_bears<xemmaix::skia::t_shader, t_type_of<xemmaix::skia::t_proxy>>>
{
	static void f_define(t_library* a_library);

	using t_base::t_base;
};

}

#endif
