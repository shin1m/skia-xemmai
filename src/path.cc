#include "path.h"

namespace xemmai
{

using namespace xemmaix::skia;

void t_type_of<t_path>::f_define(t_library* a_library)
{
	t_define{a_library}
	(L"move_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar), &SkPath::moveTo>())
	(L"line_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar), &SkPath::lineTo>())
	(L"quad_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar, SkScalar, SkScalar), &SkPath::quadTo>())
	(L"cubic_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar, SkScalar, SkScalar, SkScalar, SkScalar), &SkPath::cubicTo>())
	(L"close"sv, t_member<SkPath&(SkPath::*)(), &SkPath::close>())
	.f_derive<t_path, t_proxy>();
}

t_pvalue t_type_of<t_path>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct<>::t_bind<t_path>::f_do(this, a_stack, a_n);
}

}
