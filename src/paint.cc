#include "paint.h"
#include "shader.h"

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

t_object* t_type_of<SkPaint::Cap>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"BUTT"sv, SkPaint::kButt_Cap)
		(L"ROUND"sv, SkPaint::kRound_Cap)
		(L"SQUARE"sv, SkPaint::kSquare_Cap)
		;
	});
}

t_object* t_type_of<SkPaint::Join>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"MITER"sv, SkPaint::kMiter_Join)
		(L"ROUND"sv, SkPaint::kRound_Join)
		(L"BEVEL"sv, SkPaint::kBevel_Join)
		;
	});
}

t_object* t_type_of<SkBlendMode>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"CLEAR"sv, SkBlendMode::kClear)
		(L"SRC"sv, SkBlendMode::kSrc)
		(L"DST"sv, SkBlendMode::kDst)
		(L"SRC_OVER"sv, SkBlendMode::kSrcOver)
		(L"DST_OVER"sv, SkBlendMode::kDstOver)
		(L"SRC_IN"sv, SkBlendMode::kSrcIn)
		(L"DST_IN"sv, SkBlendMode::kDstIn)
		(L"SRC_OUT"sv, SkBlendMode::kSrcOut)
		(L"DST_OUT"sv, SkBlendMode::kDstOut)
		(L"SRC_A_TOP"sv, SkBlendMode::kSrcATop)
		(L"DST_A_TOP"sv, SkBlendMode::kDstATop)
		(L"XOR"sv, SkBlendMode::kXor)
		(L"PLUS"sv, SkBlendMode::kPlus)
		(L"MODULATE"sv, SkBlendMode::kModulate)
		(L"SCREEN"sv, SkBlendMode::kScreen)
		(L"OVERLAY"sv, SkBlendMode::kOverlay)
		(L"DARKEN"sv, SkBlendMode::kDarken)
		(L"LIGHTEN"sv, SkBlendMode::kLighten)
		(L"COLOR_DODGE"sv, SkBlendMode::kColorDodge)
		(L"COLOR_BURN"sv, SkBlendMode::kColorBurn)
		(L"HARD_LIGHT"sv, SkBlendMode::kHardLight)
		(L"SOFT_LIGHT"sv, SkBlendMode::kSoftLight)
		(L"DIFFERENCE"sv, SkBlendMode::kDifference)
		(L"EXCLUSION"sv, SkBlendMode::kExclusion)
		(L"MULTIPLY"sv, SkBlendMode::kMultiply)
		(L"HUE"sv, SkBlendMode::kHue)
		(L"SATURATION"sv, SkBlendMode::kSaturation)
		(L"COLOR"sv, SkBlendMode::kColor)
		(L"LUMINOSITY"sv, SkBlendMode::kLuminosity)
		;
	});
}

void t_type_of<t_paint>::f_define(t_library* a_library)
{
	t_define{a_library}
	(L"Style"sv, t_type_of<SkPaint::Style>::f_define(a_library))
	(L"Cap"sv, t_type_of<SkPaint::Cap>::f_define(a_library))
	(L"Join"sv, t_type_of<SkPaint::Join>::f_define(a_library))
	(L"BlendMode"sv, t_type_of<SkBlendMode>::f_define(a_library))
	(L"anti_alias__"sv, t_member<void(SkPaint::*)(bool), &SkPaint::setAntiAlias>())
	(L"style__"sv, t_member<void(SkPaint::*)(SkPaint::Style), &SkPaint::setStyle>())
	(L"color__"sv, t_member<void(SkPaint::*)(SkColor), &SkPaint::setColor>())
	(L"stroke_width__"sv, t_member<void(SkPaint::*)(SkScalar), &SkPaint::setStrokeWidth>())
	(L"stroke_miter__"sv, t_member<void(SkPaint::*)(SkScalar), &SkPaint::setStrokeMiter>())
	(L"stroke_cap__"sv, t_member<void(SkPaint::*)(SkPaint::Cap), &SkPaint::setStrokeCap>())
	(L"stroke_join__"sv, t_member<void(SkPaint::*)(SkPaint::Join), &SkPaint::setStrokeJoin>())
	(L"shader__"sv, t_member<void(SkPaint::*)(sk_sp<SkShader>), &SkPaint::setShader>())
	(L"blend_mode__"sv, t_member<void(SkPaint::*)(SkBlendMode), &SkPaint::setBlendMode>())
	.f_derive<t_paint, t_proxy>();
}

t_pvalue t_type_of<t_paint>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct<>::t_bind<t_paint>::f_do(this, a_stack, a_n);
}

}
