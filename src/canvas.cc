#include "canvas.h"
#include "font.h"
#include "image.h"
#include "paint.h"
#include "path.h"
#include "rect.h"

namespace xemmai
{

t_object* t_type_of<SkFilterMode>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"NEAREST"sv, SkFilterMode::kNearest)
		(L"LINEAR"sv, SkFilterMode::kLinear)
		;
	});
}

t_object* t_type_of<SkMipmapMode>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"NONE"sv, SkMipmapMode::kNone)
		(L"NEAREST"sv, SkMipmapMode::kNearest)
		(L"LINEAR"sv, SkMipmapMode::kLinear)
		;
	});
}

void t_type_of<SkSamplingOptions>::f_define(t_library* a_library)
{
	t_define{a_library}
	(L"is_aniso"sv, t_member<bool(SkSamplingOptions::*)() const, &SkSamplingOptions::isAniso>())
	.f_derive<SkSamplingOptions, t_object>();
}

t_pvalue t_type_of<SkSamplingOptions>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_overload<
		t_construct<>,
		t_construct<SkFilterMode>,
		t_construct<SkFilterMode, SkMipmapMode>
	>::t_bind<SkSamplingOptions>::f_do(this, a_stack, a_n);
}

t_object* t_type_of<SkCanvas::SrcRectConstraint>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"STRICT"sv, SkCanvas::kStrict_SrcRectConstraint)
		(L"FAST"sv, SkCanvas::kFast_SrcRectConstraint)
		;
	});
}

void t_type_of<xemmaix::skia::t_canvas>::f_define(t_library* a_library)
{
	t_define{a_library}
	(L"SourceRectConstraint"sv, t_type_of<SkCanvas::SrcRectConstraint>::f_define(a_library))
	(L"save"sv, t_member<int(SkCanvas::*)(), &SkCanvas::save>())
	(L"restore"sv, t_member<void(SkCanvas::*)(), &SkCanvas::restore>())
	(L"translate"sv, t_member<void(SkCanvas::*)(SkScalar, SkScalar), &SkCanvas::translate>())
	(L"rotate"sv, t_member<void(SkCanvas::*)(SkScalar), &SkCanvas::rotate>())
	(L"clear"sv, t_member<void(SkCanvas::*)(SkColor), &SkCanvas::clear>())
	(L"draw_rect"sv, t_member<void(SkCanvas::*)(const SkRect&, const SkPaint&), &SkCanvas::drawRect>())
	(L"draw_path"sv, t_member<void(SkCanvas::*)(const SkPath&, const SkPaint&), &SkCanvas::drawPath>())
	(L"draw_image"sv,
		t_member<void(SkCanvas::*)(const sk_sp<SkImage>&, SkScalar, SkScalar), &SkCanvas::drawImage>(),
		t_member<void(*)(SkCanvas&, const sk_sp<SkImage>&, SkScalar, SkScalar, const SkSamplingOptions&), [](auto a_this, auto a_image, auto a_x, auto a_y, auto a_sampling)
		{
			a_this.drawImage(a_image, a_x, a_y, a_sampling);
		}>(),
		t_member<void(SkCanvas::*)(const sk_sp<SkImage>&, SkScalar, SkScalar, const SkSamplingOptions&, const SkPaint*), &SkCanvas::drawImage>()
	)
	(L"draw_image_rect"sv,
		t_member<void(*)(SkCanvas&, const sk_sp<SkImage>&, const SkRect&, const SkSamplingOptions&), [](auto a_this, auto a_image, auto a_destination, auto a_sampling)
		{
			a_this.drawImageRect(a_image, a_destination, a_sampling);
		}>(),
		t_member<void(SkCanvas::*)(const sk_sp<SkImage>&, const SkRect&, const SkSamplingOptions&, const SkPaint*), &SkCanvas::drawImageRect>(),
		t_member<void(SkCanvas::*)(const sk_sp<SkImage>&, const SkRect&, const SkRect&, const SkSamplingOptions&, const SkPaint*, SkCanvas::SrcRectConstraint), &SkCanvas::drawImageRect>()
	)
	(L"draw_text"sv, t_member<void(*)(SkCanvas&, std::wstring_view, SkScalar, SkScalar, const SkFont&, const SkPaint&), [](auto a_this, auto a_text, auto a_x, auto a_y, auto a_font, auto a_paint)
	{
		a_this.drawSimpleText(a_text.data(), a_text.size() * sizeof(wchar_t), SkTextEncoding::kUTF32, a_x, a_y, a_font, a_paint);
	}>())
	.f_derive<xemmaix::skia::t_canvas, t_object>();
}

}
