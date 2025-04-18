#include "surface.h"
#include "canvas.h"
#include "image.h"

namespace xemmai
{

void t_type_of<xemmaix::skia::t_surface>::f_define(t_library* a_library)
{
	using namespace xemmaix::skia;
	t_define{a_library}
	(L"raster"sv, t_static<t_object*(*)(t_library*, int, int), [](auto a_library, auto a_width, auto a_height)
	{
		if (auto p = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(a_width, a_height))) return xemmai::f_new<t_surface>(a_library, p);
		f_throw(L"SkSurfaces::Raster");
	}>())
	(L"draw"sv, t_member<void(*)(t_library*, const sk_sp<SkSurface>&, const t_pvalue&), [](auto a_library, auto a_this, auto a_callable)
	{
		auto object = xemmai::f_new<t_canvas>(a_library, a_this->getCanvas());
		try {
			a_callable(object);
			object->template f_as<t_canvas>().v_session = nullptr;
		} catch (...) {
			object->template f_as<t_canvas>().v_session = nullptr;
			throw;
		}
	}>())
	(L"make_image_snapshot"sv, t_member<t_object*(*)(t_library*, const sk_sp<SkSurface>&), [](auto a_library, auto a_this)
	{
		if (auto p = a_this->makeImageSnapshot()) return xemmai::f_new<xemmaix::skia::t_image>(a_library, p);
		f_throw(L"SkSurface::makeImageSnapshot");
	}>())
	.f_derive<t_surface, t_proxy>();
}

}
