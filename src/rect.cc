#include "rect.h"

namespace xemmai
{

void t_type_of<SkRect>::f_define(t_library* a_library)
{
	t_define{a_library}
		(L"make_ltrb"sv, t_static<SkRect(*)(float, float, float, float), SkRect::MakeLTRB>())
		(L"make_xywh"sv, t_static<SkRect(*)(float, float, float, float), SkRect::MakeXYWH>())
		(L"x"sv, t_member<float(SkRect::*)() const, &SkRect::x>())
		(L"y"sv, t_member<float(SkRect::*)() const, &SkRect::y>())
		(L"left"sv, t_member<float(SkRect::*)() const, &SkRect::left>())
		(L"top"sv, t_member<float(SkRect::*)() const, &SkRect::top>())
		(L"right"sv, t_member<float(SkRect::*)() const, &SkRect::right>())
		(L"bottom"sv, t_member<float(SkRect::*)() const, &SkRect::bottom>())
		(L"width"sv, t_member<float(SkRect::*)() const, &SkRect::width>())
		(L"height"sv, t_member<float(SkRect::*)() const, &SkRect::height>())
	.f_derive<SkRect, t_object>();
}

t_pvalue t_type_of<SkRect>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct<>::t_bind<SkRect>::f_do(this, a_stack, a_n);
}

}
