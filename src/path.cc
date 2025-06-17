#include "path.h"
#include "rect.h"

namespace xemmai
{

using namespace xemmaix::skia;

t_object* t_type_of<SkPath::ArcSize>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"SMALL"sv, SkPath::kSmall_ArcSize)
		(L"LARGE"sv, SkPath::kLarge_ArcSize)
		;
	});
}

t_object* t_type_of<SkPathDirection>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"CW"sv, SkPathDirection::kCW)
		(L"CCW"sv, SkPathDirection::kCCW)
		;
	});
}

t_object* t_type_of<SkPathFillType>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"WINDING"sv, SkPathFillType::kWinding)
		(L"EVEN_ODD"sv, SkPathFillType::kEvenOdd)
		(L"INVERSE_WINDING"sv, SkPathFillType::kInverseWinding)
		(L"INVERSE_EVEN_ODD"sv, SkPathFillType::kInverseEvenOdd)
		;
	});
}

void t_type_of<t_path>::f_define(t_library* a_library)
{
	t_define{a_library}
	(L"ArcSize"sv, t_type_of<SkPath::ArcSize>::f_define(a_library))
	(L"Direction"sv, t_type_of<SkPathDirection>::f_define(a_library))
	(L"FillType"sv, t_type_of<SkPathFillType>::f_define(a_library))
	(L"fill_type__"sv, t_member<void(SkPath::*)(SkPathFillType), &SkPath::setFillType>())
	(L"move_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar), &SkPath::moveTo>())
	(L"r_move_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar), &SkPath::rMoveTo>())
	(L"line_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar), &SkPath::lineTo>())
	(L"r_line_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar), &SkPath::rLineTo>())
	(L"quad_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar, SkScalar, SkScalar), &SkPath::quadTo>())
	(L"r_quad_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar, SkScalar, SkScalar), &SkPath::rQuadTo>())
	(L"conic_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar, SkScalar, SkScalar, SkScalar), &SkPath::conicTo>())
	(L"r_conic_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar, SkScalar, SkScalar, SkScalar), &SkPath::rConicTo>())
	(L"cubic_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar, SkScalar, SkScalar, SkScalar, SkScalar), &SkPath::cubicTo>())
	(L"r_cubic_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar, SkScalar, SkScalar, SkScalar, SkScalar), &SkPath::rCubicTo>())
	(L"arc_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar, SkScalar, SkPath::ArcSize, SkPathDirection, SkScalar, SkScalar), &SkPath::arcTo>())
	(L"r_arc_to"sv, t_member<SkPath&(SkPath::*)(SkScalar, SkScalar, SkScalar, SkPath::ArcSize, SkPathDirection, SkScalar, SkScalar), &SkPath::rArcTo>())
	(L"close"sv, t_member<SkPath&(SkPath::*)(), &SkPath::close>())
	(L"add_rect"sv, t_member<SkPath&(SkPath::*)(const SkRect&, SkPathDirection, unsigned), &SkPath::addRect>())
	.f_derive<t_path, t_proxy>();
}

t_pvalue t_type_of<t_path>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct<>::t_bind<t_path>::f_do(this, a_stack, a_n);
}

}
