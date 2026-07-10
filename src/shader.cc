#include "shader.h"
#include <include/effects/SkGradient.h>

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

std::pair<std::vector<SkColor4f>, std::vector<float>> f_colors_positions(const t_pvalue& a_colors)
{
	std::vector<SkColor4f> colors;
	std::vector<float> positions;
	f_extract(a_colors, [&](size_t n, auto get)
	{
		for (size_t i = 0; i < n; ++i) f_extract(get(i), [&](size_t n, auto get)
		{
			if (n != 2) f_throw(L"must be pair");
			auto x = get(0);
			f_check<SkColor>(x, L"color");
			colors.push_back(SkColor4f::FromColor(f_as<SkColor>(x)));
			x = get(1);
			f_check<float>(x, L"position");
			positions.push_back(f_as<float>(x));
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
	(L"linear_gradient"sv, t_static<t_object*(*)(t_library*, float, float, float, float, const t_pvalue&, SkTileMode), [](auto a_library, auto a_x0, auto a_y0, auto a_x1, auto a_y1, auto a_colors, auto a_mode)
	{
		SkPoint points[] = {{a_x0, a_y0}, {a_x1, a_y1}};
		auto [colors, positions] = f_colors_positions(a_colors);
		return t_proxy::f_own(xemmai::f_new<t_shader>(a_library, SkShaders::LinearGradient(points, {{colors, positions, a_mode}, {}})));
	}>())
	(L"radial_gradient"sv, t_static<t_object*(*)(t_library*, float, float, float, const t_pvalue&, SkTileMode), [](auto a_library, auto a_x, auto a_y, auto a_radius, auto a_colors, auto a_mode)
	{
		auto [colors, positions] = f_colors_positions(a_colors);
		return t_proxy::f_own(xemmai::f_new<t_shader>(a_library, SkShaders::RadialGradient({a_x, a_y}, a_radius, {{colors, positions, a_mode}, {}})));
	}>())
	(L"two_point_conical_gradient"sv, t_static<t_object*(*)(t_library*, float, float, float, float, float, float, const t_pvalue&, SkTileMode), [](auto a_library, auto a_x0, auto a_y0, auto a_radius0, auto a_x1, auto a_y1, auto a_radius1, auto a_colors, auto a_mode)
	{
		auto [colors, positions] = f_colors_positions(a_colors);
		return t_proxy::f_own(xemmai::f_new<t_shader>(a_library, SkShaders::TwoPointConicalGradient({a_x0, a_y0}, a_radius0, {a_x1, a_y1}, a_radius1, {{colors, positions, a_mode}, {}})));
	}>())
	(L"sweep_gradient"sv, t_static<t_object*(*)(t_library*, float, float, float, float, const t_pvalue&, SkTileMode), [](auto a_library, auto a_x, auto a_y, auto a_angle0, auto a_angle1, auto a_colors, auto a_mode)
	{
		auto [colors, positions] = f_colors_positions(a_colors);
		return t_proxy::f_own(xemmai::f_new<t_shader>(a_library, SkShaders::SweepGradient({a_x, a_y}, a_angle0, a_angle1, {{colors, positions, a_mode}, {}})));
	}>())
	.f_derive<t_shader, t_proxy>();
}

}
