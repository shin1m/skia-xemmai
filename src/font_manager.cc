#include "font_manager.h"
#include "typeface.h"
#include <include/ports/SkFontMgr_fontconfig.h>

namespace xemmai
{

t_object* t_type_of<SkFontStyle::Slant>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"UPRIGHT"sv, SkFontStyle::Slant::kUpright_Slant)
		(L"ITALIC"sv, SkFontStyle::Slant::kItalic_Slant)
		(L"OBLIQUE"sv, SkFontStyle::Slant::kOblique_Slant)
		;
	});
}

void t_type_of<SkFontStyle>::f_define(t_library* a_library)
{
	t_define{a_library}
	(L"Slant"sv, t_type_of<SkFontStyle::Slant>::f_define(a_library))
	(L"Normal"sv, t_static<t_object*(*)(t_library*), [](auto a_library)
	{
		return xemmai::f_new<SkFontStyle>(a_library, SkFontStyle::Normal());
	}>())
	(L"Bold"sv, t_static<t_object*(*)(t_library*), [](auto a_library)
	{
		return xemmai::f_new<SkFontStyle>(a_library, SkFontStyle::Bold());
	}>())
	(L"Italic"sv, t_static<t_object*(*)(t_library*), [](auto a_library)
	{
		return xemmai::f_new<SkFontStyle>(a_library, SkFontStyle::Italic());
	}>())
	(L"BoldItalic"sv, t_static<t_object*(*)(t_library*), [](auto a_library)
	{
		return xemmai::f_new<SkFontStyle>(a_library, SkFontStyle::BoldItalic());
	}>())
	(L"weight"sv, t_member<int(SkFontStyle::*)() const, &SkFontStyle::weight>())
	(L"width"sv, t_member<int(SkFontStyle::*)() const, &SkFontStyle::width>())
	(L"slant"sv, t_member<SkFontStyle::Slant(SkFontStyle::*)() const, &SkFontStyle::slant>())
	.f_derive<SkFontStyle, t_object>();
}

t_pvalue t_type_of<SkFontStyle>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_overload<
		t_construct<>,
		t_construct<int, int, SkFontStyle::Slant>
	>::t_bind<SkFontStyle>::f_do(this, a_stack, a_n);
}

void t_type_of<xemmaix::skia::t_font_manager>::f_define(t_library* a_library)
{
	using namespace xemmaix::skia;
	t_define{a_library}
	(L"make_default"sv, t_static<t_object*(*)(t_library*), [](auto a_library)
	{
		return xemmai::f_new<t_font_manager>(a_library, SkFontMgr_New_FontConfig(nullptr));
	}>())
	(L"match_family_style"sv, t_member<t_object*(*)(t_library*, const sk_sp<SkFontMgr>&, const t_string*, const SkFontStyle&), [](auto a_library, auto a_this, auto a_family, auto a_style)
	{
		auto typeface = a_this->matchFamilyStyle(a_family ? portable::f_convert(*a_family).c_str() : nullptr, a_style);
		return typeface ? xemmai::f_new<t_typeface>(a_library, typeface) : nullptr;
	}>())
	.f_derive<t_font_manager, t_proxy>();
}

}
