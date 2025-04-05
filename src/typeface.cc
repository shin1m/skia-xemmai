#include "typeface.h"

namespace xemmai
{

void t_type_of<xemmaix::skia::t_typeface>::f_define(t_library* a_library)
{
	using namespace xemmaix::skia;
	t_define{a_library}
	.f_derive<t_typeface, t_proxy>();
}

}
