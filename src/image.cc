#include "image.h"
#include <include/core/SkStream.h>
#include <include/encode/SkPngEncoder.h>

namespace xemmai
{

void t_type_of<xemmaix::skia::t_image>::f_define(t_library* a_library)
{
	using namespace xemmaix::skia;
	t_define{a_library}
	(L"save"sv, t_member<void(*)(const sk_sp<SkImage>&, std::wstring_view), [](auto a_this, auto a_path)
	{
		auto png = SkPngEncoder::Encode(nullptr, a_this.get(), {});
		if (!png) f_throw(L"SkPngEncoder::Encode");
		SkFILEWStream out(portable::f_convert(a_path).c_str());
		if (!out.write(png->data(), png->size())) f_throw(L"SkFILEWStream::write");
	}>())
	.f_derive<t_image, t_proxy>();
}

}
