#ifndef XEMMAIX__SKIA__RECT_H
#define XEMMAIX__SKIA__RECT_H

#include "skia.h"

namespace xemmai
{

template<>
struct t_type_of<SkRect> : t_holds<SkRect>
{
	using t_library = xemmaix::skia::t_library;

	static t_pvalue f_transfer(auto* a_library, auto&& a_value)
	{
		return xemmai::f_new<SkRect>(a_library, std::forward<decltype(a_value)>(a_value));
	}
	static void f_define(t_library* a_library);

	using t_base::t_base;
	t_pvalue f_do_construct(t_pvalue* a_stack, size_t a_n);
};

}

#endif
