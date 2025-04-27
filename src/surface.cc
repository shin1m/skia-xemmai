#include "surface.h"
#include "canvas.h"
#include "image.h"
#include <GLES3/gl3.h>
#include <include/core/SkColorSpace.h>
#include <include/gpu/ganesh/GrBackendSurface.h>
#include <include/gpu/ganesh/GrDirectContext.h>
#include <include/gpu/ganesh/SkSurfaceGanesh.h>
#include <include/gpu/ganesh/gl/GrGLBackendSurface.h>
#include <include/gpu/ganesh/gl/GrGLDirectContext.h>
#include <include/gpu/ganesh/gl/GrGLInterface.h>
#include <include/gpu/ganesh/gl/egl/GrGLMakeEGLInterface.h>

namespace xemmai
{

void t_type_of<xemmaix::skia::t_surface>::f_define(t_library* a_library)
{
	using namespace xemmaix::skia;
	t_define{a_library}
	(L"raster"sv, t_static<t_object*(*)(t_library*, int, int), [](auto a_library, auto a_width, auto a_height)
	{
		if (auto p = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(a_width, a_height))) return xemmai::f_new<t_surface>(a_library, p);
		f_throw(L"SkSurfaces::Raster"sv);
	}>())
	(L"gl"sv, t_static<t_object*(*)(t_library*, const t_gl_context&, GLuint, int, int), [](auto a_library, auto a_context, auto a_framebuffer, auto a_width, auto a_height)
	{
		GrGLFramebufferInfo fi;
		fi.fFBOID = a_framebuffer;
		fi.fFormat = GL_RGBA8;
		auto target = GrBackendRenderTargets::MakeGL(a_width, a_height, 0, 0, fi);
		if (!target.isValid()) f_throw(L"GrBackendRenderTargets::MakeGL"sv);
		auto surface = SkSurfaces::WrapBackendRenderTarget(a_context.get(), target, kBottomLeft_GrSurfaceOrigin, kRGBA_8888_SkColorType, {}, nullptr);
		if (!surface) f_throw(L"SkSurfaces::WrapBackendRenderTarget"sv);
		return xemmai::f_new<t_surface>(a_library, surface);
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
		f_throw(L"SkSurface::makeImageSnapshot"sv);
	}>())
	.f_derive<t_surface, t_proxy>();
}

void t_type_of<xemmaix::skia::t_gl_context>::f_define(t_library* a_library)
{
	using namespace xemmaix::skia;
	t_define{a_library}
	(L"flush"sv, t_member<void(*)(const t_gl_context&, const sk_sp<SkSurface>&), [](auto a_this, auto a_surface)
	{
		a_this->flushAndSubmit(a_surface.get());
	}>())
	.f_derive<t_gl_context, t_proxy>();
}

t_pvalue t_type_of<xemmaix::skia::t_gl_context>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct_with<t_object*(*)(t_type*), [](auto a_class)
	{
		//auto interface = GrGLInterfaces::MakeEGL();
		//if (!interface) f_throw(L"GrGLInterfaces::MakeEGL"sv);
		auto interface = GrGLMakeNativeInterface();
		if (!interface) f_throw(L"GrGLMakeNativeInterface"sv);
		auto context = GrDirectContexts::MakeGL(interface);
		if (!context) f_throw(L"GrDirectContexts::MakeGL"sv);
		return a_class->template f_new<xemmaix::skia::t_gl_context>(context);
	}>::f_do(this, a_stack, a_n);
}

}
