#include "font.h"
#include "rect.h"
#include "typeface.h"

namespace xemmai
{

using namespace xemmaix::skia;

void t_type_of<SkFontMetrics>::f_define(t_library* a_library)
{
	t_define{a_library}
	(L"ascent"sv, t_member<SkScalar(*)(const SkFontMetrics&), [](auto a_this)
	{
		return a_this.fAscent;
	}>())
	(L"descent"sv, t_member<SkScalar(*)(const SkFontMetrics&), [](auto a_this)
	{
		return a_this.fDescent;
	}>())
	(L"leading"sv, t_member<SkScalar(*)(const SkFontMetrics&), [](auto a_this)
	{
		return a_this.fLeading;
	}>())
	(L"avg_char_width"sv, t_member<SkScalar(*)(const SkFontMetrics&), [](auto a_this)
	{
		return a_this.fAvgCharWidth;
	}>())
	(L"max_char_width"sv, t_member<SkScalar(*)(const SkFontMetrics&), [](auto a_this)
	{
		return a_this.fMaxCharWidth;
	}>())
	(L"x_height"sv, t_member<SkScalar(*)(const SkFontMetrics&), [](auto a_this)
	{
		return a_this.fXHeight;
	}>())
	(L"cap_height"sv, t_member<SkScalar(*)(const SkFontMetrics&), [](auto a_this)
	{
		return a_this.fCapHeight;
	}>())
	(L"underline_thickness"sv, t_member<t_pvalue(*)(const SkFontMetrics&), [](auto a_this)
	{
		SkScalar value;
		return a_this.hasUnderlineThickness(&value) ? value : t_pvalue{};
	}>())
	(L"underline_position"sv, t_member<t_pvalue(*)(const SkFontMetrics&), [](auto a_this)
	{
		SkScalar value;
		return a_this.hasUnderlinePosition(&value) ? value : t_pvalue{};
	}>())
	(L"strikeout_thickness"sv, t_member<t_pvalue(*)(const SkFontMetrics&), [](auto a_this)
	{
		SkScalar value;
		return a_this.hasStrikeoutThickness(&value) ? value : t_pvalue{};
	}>())
	(L"strikeout_position"sv, t_member<t_pvalue(*)(const SkFontMetrics&), [](auto a_this)
	{
		SkScalar value;
		return a_this.hasStrikeoutPosition(&value) ? value : t_pvalue{};
	}>())
	.f_derive<SkFontMetrics, t_object>();
}

void t_type_of<t_font>::f_define(t_library* a_library)
{
	t_define{a_library}
	(L"measure_advance"sv, t_member<SkScalar(*)(const SkFont&, std::wstring_view), [](auto a_this, auto a_text)
	{
		return a_this.measureText(a_text.data(), a_text.size() * sizeof(wchar_t), SkTextEncoding::kUTF32);
	}>())
	(L"measure_bounds"sv, t_member<t_object*(*)(t_library*, const SkFont&, std::wstring_view), [](auto a_library, auto a_this, auto a_text)
	{
		SkRect bounds;
		auto advance = a_this.measureText(a_text.data(), a_text.size() * sizeof(wchar_t), SkTextEncoding::kUTF32, &bounds);
		return f_tuple(advance, xemmai::f_new<SkRect>(a_library, bounds));
	}>())
	(L"metrics"sv, t_member<t_object*(*)(t_library*, const SkFont&), [](auto a_library, auto a_this)
	{
		SkFontMetrics metrics;
		auto spacing = a_this.getMetrics(&metrics);
		return f_tuple(spacing, xemmai::f_new<SkFontMetrics>(a_library, metrics));
	}>())
	.f_derive<t_font, t_proxy>();
}

t_pvalue t_type_of<t_font>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_overload<
		t_construct<>,
		t_construct<sk_sp<SkTypeface>>,
		t_construct<sk_sp<SkTypeface>, SkScalar>,
		t_construct<sk_sp<SkTypeface>, SkScalar, SkScalar, SkScalar>
	>::t_bind<t_font>::f_do(this, a_stack, a_n);
}

}
