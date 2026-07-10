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

using namespace xemmaix::skia;

void t_type_of<t_surface>::f_define(t_library* a_library)
{
	t_define{a_library}
	(L"raster"sv, t_static<t_object*(*)(t_library*, int, int), [](auto a_library, auto a_width, auto a_height)
	{
		if (auto p = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(a_width, a_height))) return t_proxy::f_own(xemmai::f_new<t_surface>(a_library, p));
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
		return t_proxy::f_own(xemmai::f_new<t_surface>(a_library, surface));
	}>())
	(L"width"sv, t_member<int(*)(const sk_sp<SkSurface>&), [](auto a_this)
	{
		return a_this->width();
	}>())
	(L"height"sv, t_member<int(*)(const sk_sp<SkSurface>&), [](auto a_this)
	{
		return a_this->height();
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
		if (auto p = a_this->makeImageSnapshot()) return t_proxy::f_own(xemmai::f_new<t_image>(a_library, p));
		f_throw(L"SkSurface::makeImageSnapshot"sv);
	}>())
	(L"read_pixels"sv, t_member<t_object*(*)(const sk_sp<SkSurface>&, int, int, SkColorType, SkAlphaType, int, int), [](auto a_this, auto a_width, auto a_height, auto a_color_type, auto a_alpha_type, auto a_x, auto a_y)
	{
		auto row = a_width;
		switch (a_color_type) {
		case kRGB_565_SkColorType:
		case kARGB_4444_SkColorType:
		case kR8G8_unorm_SkColorType:
		case kA16_float_SkColorType:
		case kA16_unorm_SkColorType:
		case kR16_unorm_SkColorType:
			row *= 2;
			break;
		case kRGBA_8888_SkColorType:
		case kRGB_888x_SkColorType:
		case kBGRA_8888_SkColorType:
		case kRGBA_1010102_SkColorType:
		case kBGRA_1010102_SkColorType:
		case kRGB_101010x_SkColorType:
		case kBGR_101010x_SkColorType:
		case kBGR_101010x_XR_SkColorType:
		case kR16G16_float_SkColorType:
		case kR16G16_unorm_SkColorType:
		case kSRGBA_8888_SkColorType:
			row *= 4;
			break;
		case kBGRA_10101010_XR_SkColorType:
		case kRGBA_10x6_SkColorType:
		case kRGBA_F16Norm_SkColorType:
		case kRGBA_F16_SkColorType:
		case kRGB_F16F16F16x_SkColorType:
		case kR16G16B16A16_unorm_SkColorType:
			row *= 8;
			break;
		case kRGBA_F32_SkColorType:
			row *= 16;
			break;
		}
		auto p = t_bytes::f_instantiate(row * a_height);
		if (a_this->readPixels(SkImageInfo::Make(a_width, a_height, a_color_type, a_alpha_type), &f_as<t_bytes&>(p)[0], row, a_x, a_y)) return p;
		f_throw(L"SkSurface::readPixels"sv);
	}>())
	.f_derive<t_surface, t_proxy>();
}

void t_type_of<t_gl_context>::f_define(t_library* a_library)
{
	t_define{a_library}
	(L"flush"sv, t_member<void(*)(const t_gl_context&, const sk_sp<SkSurface>&), [](auto a_this, auto a_surface)
	{
		a_this->flushAndSubmit(a_surface.get());
	}>())
	.f_derive<t_gl_context, t_proxy>();
}

t_pvalue t_type_of<t_gl_context>::f_do_construct(t_pvalue* a_stack, size_t a_n)
{
	return t_construct_with<t_object*(*)(t_type*), [](auto a_class)
	{
		//auto interface = GrGLInterfaces::MakeEGL();
		//if (!interface) f_throw(L"GrGLInterfaces::MakeEGL"sv);
		auto interface = GrGLMakeNativeInterface();
		if (!interface) f_throw(L"GrGLMakeNativeInterface"sv);
		auto context = GrDirectContexts::MakeGL(interface);
		if (!context) f_throw(L"GrDirectContexts::MakeGL"sv);
		return t_proxy::f_new<t_gl_context>(a_class, context);
	}>::f_do(this, a_stack, a_n);
}

}
