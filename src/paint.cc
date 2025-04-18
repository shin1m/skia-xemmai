#include "paint.h"

namespace xemmai
{

using namespace xemmaix::skia;

t_object* t_type_of<SkPaint::Style>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"FILL"sv, SkPaint::kFill_Style)
		(L"STROKE"sv, SkPaint::kStroke_Style)
		(L"STROKE_AND_FILL"sv, SkPaint::kStrokeAndFill_Style)
		;
	});
}

void t_type_of<t_paint>::f_define(t_library* a_library)
{
	t_define{a_library}
	(L"Style"sv, t_type_of<SkPaint::Style>::f_define(a_library))
	(L"anti_alias__"sv, t_member<void(SkPaint::*)(bool), &SkPaint::setAntiAlias>())
	(L"style__"sv, t_member<void(SkPaint::*)(SkPaint::Style), &SkPaint::setStyle>())
	(L"color__"sv, t_member<void(SkPaint::*)(SkColor), &SkPaint::setColor>())
	(L"stroke_width__"sv, t_member<void(SkPaint::*)(SkScalar), &SkPaint::setStrokeWidth>())
	.f_derive<t_paint, t_proxy>();
}

t_pvalue t_type_of<t_paint>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct<>::t_bind<t_paint>::f_do(this, a_stack, a_n);
}

}
