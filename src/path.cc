#include "path.h"
#include "rect.h"

namespace xemmai
{

using namespace xemmaix::skia;

t_object* t_type_of<SkPathBuilder::ArcSize>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"SMALL"sv, SkPathBuilder::kSmall_ArcSize)
		(L"LARGE"sv, SkPathBuilder::kLarge_ArcSize)
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
	(L"ArcSize"sv, t_type_of<SkPathBuilder::ArcSize>::f_define(a_library))
	(L"Direction"sv, t_type_of<SkPathDirection>::f_define(a_library))
	(L"FillType"sv, t_type_of<SkPathFillType>::f_define(a_library))
	.f_derive<t_path, t_proxy>();
}

t_pvalue t_type_of<t_path>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct<>::t_bind<t_path>::f_do(this, a_stack, a_n);
}

void t_type_of<t_path_builder>::f_define(t_library* a_library)
{
	t_define{a_library}
	(L"snapshot"sv, t_member<t_object*(*)(t_library*, SkPathBuilder&), [](auto a_library, auto a_this)
	{
		return xemmai::f_new<t_path>(a_library, a_this.snapshot());
	}>())
	(L"detach"sv, t_member<t_object*(*)(t_library*, SkPathBuilder&), [](auto a_library, auto a_this)
	{
		return xemmai::f_new<t_path>(a_library, a_this.detach());
	}>())
	(L"fill_type__"sv, t_member<SkPathBuilder&(SkPathBuilder::*)(SkPathFillType), &SkPathBuilder::setFillType>())
	(L"move_to"sv, t_member<SkPathBuilder&(SkPathBuilder::*)(SkScalar, SkScalar), &SkPathBuilder::moveTo>())
	(L"r_move_to"sv, t_member<SkPathBuilder&(SkPathBuilder::*)(SkScalar, SkScalar), &SkPathBuilder::rMoveTo>())
	(L"line_to"sv, t_member<SkPathBuilder&(SkPathBuilder::*)(SkScalar, SkScalar), &SkPathBuilder::lineTo>())
	(L"r_line_to"sv, t_member<SkPathBuilder&(SkPathBuilder::*)(SkScalar, SkScalar), &SkPathBuilder::rLineTo>())
	(L"quad_to"sv, t_member<SkPathBuilder&(SkPathBuilder::*)(SkScalar, SkScalar, SkScalar, SkScalar), &SkPathBuilder::quadTo>())
	(L"r_quad_to"sv, t_member<SkPathBuilder&(SkPathBuilder::*)(SkScalar, SkScalar, SkScalar, SkScalar), &SkPathBuilder::rQuadTo>())
	(L"conic_to"sv, t_member<SkPathBuilder&(SkPathBuilder::*)(SkScalar, SkScalar, SkScalar, SkScalar, SkScalar), &SkPathBuilder::conicTo>())
	(L"r_conic_to"sv, t_member<SkPathBuilder&(SkPathBuilder::*)(SkScalar, SkScalar, SkScalar, SkScalar, SkScalar), &SkPathBuilder::rConicTo>())
	(L"cubic_to"sv, t_member<SkPathBuilder&(SkPathBuilder::*)(SkScalar, SkScalar, SkScalar, SkScalar, SkScalar, SkScalar), &SkPathBuilder::cubicTo>())
	(L"r_cubic_to"sv, t_member<SkPathBuilder&(SkPathBuilder::*)(SkScalar, SkScalar, SkScalar, SkScalar, SkScalar, SkScalar), &SkPathBuilder::rCubicTo>())
	(L"arc_to"sv, t_member<SkPathBuilder&(*)(SkPathBuilder&, SkScalar, SkScalar, SkScalar, SkPathBuilder::ArcSize, SkPathDirection, SkScalar, SkScalar), [](auto a_this, auto a_rx, auto a_ry, auto a_rotate, auto a_size, auto a_sweep, auto a_x, auto a_y) -> SkPathBuilder&
	{
		return a_this.arcTo(SkPoint{a_rx, a_ry}, a_rotate, a_size, a_sweep, SkPoint{a_x, a_y});
	}>())
	(L"r_arc_to"sv, t_member<SkPathBuilder&(*)(SkPathBuilder&, SkScalar, SkScalar, SkScalar, SkPathBuilder::ArcSize, SkPathDirection, SkScalar, SkScalar), [](auto a_this, auto a_rx, auto a_ry, auto a_rotate, auto a_size, auto a_sweep, auto a_x, auto a_y) -> SkPathBuilder&
	{
		return a_this.rArcTo(SkPoint{a_rx, a_ry}, a_rotate, a_size, a_sweep, SkPoint{a_x, a_y});
	}>())
	(L"close"sv, t_member<SkPathBuilder&(SkPathBuilder::*)(), &SkPathBuilder::close>())
	(L"add_rect"sv, t_member<SkPathBuilder&(SkPathBuilder::*)(const SkRect&, SkPathDirection, unsigned), &SkPathBuilder::addRect>())
	.f_derive<t_path_builder, t_proxy>();
}

t_pvalue t_type_of<t_path_builder>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_overload<
		t_construct<>,
		t_construct<SkPathFillType>,
		t_construct<const SkPath&>,
		t_construct<const SkPathBuilder&>
	>::t_bind<t_path_builder>::f_do(this, a_stack, a_n);
}

}
