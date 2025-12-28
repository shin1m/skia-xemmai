#include "shader.h"
#include <include/effects/SkGradientShader.h>

namespace xemmai
{

t_object* t_type_of<SkTileMode>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"CLAMP"sv, SkTileMode::kClamp)
		(L"REPEAT"sv, SkTileMode::kRepeat)
		(L"MIRROR"sv, SkTileMode::kMirror)
		(L"DECAL"sv, SkTileMode::kDecal)
		;
	});
}

namespace
{

void f_extract(const t_pvalue& a_xs, auto a_do)
{
	auto list = [&](auto& xs)
	{
		a_do(xs.f_size(), [&](size_t i)
		{
			return t_pvalue(xs[i]);
		});
	};
	if (f_is<t_tuple>(a_xs)) {
		list(a_xs->f_as<t_tuple>());
	} else if (f_is<t_list>(a_xs)) {
		list(a_xs->f_as<t_list>());
	} else {
		static size_t index;
		auto size = a_xs.f_invoke(f_global()->f_symbol_size(), index);
		f_check<size_t>(size, L"size");
		a_do(f_as<size_t>(size), [&](size_t i)
		{
			return a_xs.f_get_at(i);
		});
	}
}

std::pair<std::vector<SkColor>, std::vector<SkScalar>> f_colors_positions(const t_pvalue& a_colors)
{
	std::vector<SkColor> colors;
	std::vector<SkScalar> positions;
	f_extract(a_colors, [&](size_t n, auto get)
	{
		for (size_t i = 0; i < n; ++i) f_extract(get(i), [&](size_t n, auto get)
		{
			if (n != 2) f_throw(L"must be pair");
			auto x = get(0);
			f_check<SkColor>(x, L"color");
			colors.push_back(f_as<SkColor>(x));
			x = get(1);
			f_check<SkScalar>(x, L"position");
			positions.push_back(f_as<SkScalar>(x));
		});
	});
	return {std::move(colors), std::move(positions)};
}

}

void t_type_of<xemmaix::skia::t_shader>::f_define(t_library* a_library)
{
	using namespace xemmaix::skia;
	t_define{a_library}
	(L"TileMode"sv, t_type_of<SkTileMode>::f_define(a_library))
	(L"make_linear"sv, t_static<t_object*(*)(t_library*, SkScalar, SkScalar, SkScalar, SkScalar, const t_pvalue&, SkTileMode), [](auto a_library, auto a_x0, auto a_y0, auto a_x1, auto a_y1, auto a_colors, auto a_mode)
	{
		SkPoint points[] = {{a_x0, a_y0}, {a_x1, a_y1}};
		auto [colors, positions] = f_colors_positions(a_colors);
		return xemmai::f_new<t_shader>(a_library, SkGradientShader::MakeLinear(points, colors.data(), positions.data(), colors.size(), a_mode));
	}>())
	(L"make_radial"sv, t_static<t_object*(*)(t_library*, SkScalar, SkScalar, SkScalar, const t_pvalue&, SkTileMode), [](auto a_library, auto a_x, auto a_y, auto a_radius, auto a_colors, auto a_mode)
	{
		auto [colors, positions] = f_colors_positions(a_colors);
		return xemmai::f_new<t_shader>(a_library, SkGradientShader::MakeRadial({a_x, a_y}, a_radius, colors.data(), positions.data(), colors.size(), a_mode));
	}>())
	(L"make_two_point_conical"sv, t_static<t_object*(*)(t_library*, SkScalar, SkScalar, SkScalar, SkScalar, SkScalar, SkScalar, const t_pvalue&, SkTileMode), [](auto a_library, auto a_x0, auto a_y0, auto a_radius0, auto a_x1, auto a_y1, auto a_radius1, auto a_colors, auto a_mode)
	{
		auto [colors, positions] = f_colors_positions(a_colors);
		return xemmai::f_new<t_shader>(a_library, SkGradientShader::MakeTwoPointConical({a_x0, a_y0}, a_radius0, {a_x1, a_y1}, a_radius1, colors.data(), positions.data(), colors.size(), a_mode));
	}>())
	(L"make_sweep"sv, t_static<t_object*(*)(t_library*, SkScalar, SkScalar, const t_pvalue&, SkTileMode, SkScalar, SkScalar), [](auto a_library, auto a_x, auto a_y, auto a_colors, auto a_mode, auto a_angle0, auto a_angle1)
	{
		auto [colors, positions] = f_colors_positions(a_colors);
		return xemmai::f_new<t_shader>(a_library, SkGradientShader::MakeSweep(a_x, a_y, colors.data(), positions.data(), colors.size(), a_mode, a_angle0, a_angle1, 0, nullptr));
	}>())
	.f_derive<t_shader, t_proxy>();
}

}
