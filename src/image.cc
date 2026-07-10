#include "image.h"
#include <format>
#include <include/core/SkStream.h>
#include <include/codec/SkCodec.h>
#include <include/codec/SkGifDecoder.h>
#include <include/codec/SkJpegDecoder.h>
#include <include/codec/SkPngDecoder.h>
#include <include/encode/SkPngEncoder.h>

namespace xemmai
{

t_object* t_type_of<SkColorType>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"UNKNOWN"sv, kUnknown_SkColorType)
		(L"ALPHA_8", kAlpha_8_SkColorType)
		(L"RGB_565", kRGB_565_SkColorType)
		(L"ARGB_4444", kARGB_4444_SkColorType)
		(L"RGBA_8888", kRGBA_8888_SkColorType)
		(L"RGB_888X", kRGB_888x_SkColorType)
		(L"BGRA_8888", kBGRA_8888_SkColorType)
		(L"RGBA_1010102", kRGBA_1010102_SkColorType)
		(L"BGRA_1010102", kBGRA_1010102_SkColorType)
		(L"RGB_101010X", kRGB_101010x_SkColorType)
		(L"BGR_101010X", kBGR_101010x_SkColorType)
		(L"BGR_101010X_XR", kBGR_101010x_XR_SkColorType)
		(L"BGRA_10101010_XR", kBGRA_10101010_XR_SkColorType)
		(L"RGBA_10X6", kRGBA_10x6_SkColorType)
		(L"GRAY_8", kGray_8_SkColorType)
		(L"RGBA_F16NORM", kRGBA_F16Norm_SkColorType)
		(L"RGBA_F16", kRGBA_F16_SkColorType)
		(L"RGB_F16F16F16X", kRGB_F16F16F16x_SkColorType)
		(L"RGBA_F32", kRGBA_F32_SkColorType)
		(L"R8G8_UNORM", kR8G8_unorm_SkColorType)
		(L"A16_FLOAT", kA16_float_SkColorType)
		(L"R16G16_FLOAT", kR16G16_float_SkColorType)
		(L"A16_UNORM", kA16_unorm_SkColorType)
		(L"R16_UNORM", kR16_unorm_SkColorType)
		(L"R16G16_UNORM", kR16G16_unorm_SkColorType)
		(L"R16G16B16A16_UNORM", kR16G16B16A16_unorm_SkColorType)
		(L"SRGBA_8888", kSRGBA_8888_SkColorType)
		(L"R8_UNORM", kR8_unorm_SkColorType)
		;
	});
}

t_object* t_type_of<SkAlphaType>::f_define(t_library* a_library)
{
	return t_base::f_define(a_library, [](auto a_fields)
	{
		a_fields
		(L"UNKNOWN"sv, kUnknown_SkAlphaType)
		(L"OPAQUE", kOpaque_SkAlphaType)
		(L"PREMUL", kPremul_SkAlphaType)
		(L"UNPREMUL", kUnpremul_SkAlphaType)
		;
	});
}

namespace
{

struct t_stream : SkStream
{
	t_pvalue v_read;
	t_root v_buffer = t_bytes::f_instantiate(1024);
	unsigned char* v_head = &f_as<t_bytes&>(v_buffer)[0];
	unsigned char* v_tail;

	size_t f_read(size_t a_n)
	{
		auto n = v_read(v_buffer, 0, a_n);
		f_check<size_t>(n, L"result of read");
		return f_as<size_t>(n);
	}

	t_stream(const t_pvalue& a_read) : v_read(a_read), v_tail(v_head + f_read(f_as<t_bytes&>(v_buffer).f_size()))
	{
	}
	virtual size_t read(void* a_buffer, size_t a_size)
	{
		auto left = a_size;
		if (left <= 0) return 0;
		auto p = static_cast<unsigned char*>(a_buffer);
		if (v_head < v_tail) {
			auto n = std::min(left, static_cast<size_t>(v_tail - v_head));
			if (p) p = std::copy_n(v_head, n, p);
			v_head += n;
			left -= n;
			if (left <= 0) return a_size;
		}
		v_tail = nullptr;
		auto& bytes = f_as<t_bytes&>(v_buffer);
		do {
			auto n = f_read(std::min(left, bytes.f_size()));
			if (n <= 0) {
				v_head = nullptr;
				break;
			}
			if (p) p = std::copy_n(&bytes[0], n, p);
			left -= n;
		} while (left > 0);
		return a_size - left;
	}
	virtual bool isAtEnd() const
	{
		return !v_head;
	}
	virtual bool rewind()
	{
		if (!v_tail) return false;
		v_head = &f_as<t_bytes&>(v_buffer)[0];
		return true;
	}
};

}

void t_type_of<xemmaix::skia::t_image>::f_define(t_library* a_library)
{
	using namespace xemmaix::skia;
	t_define{a_library}
	(L"create_from_stream"sv, t_static<t_object*(*)(t_library*, const t_pvalue&), [](auto a_library, auto a_read)
	{
		SkCodec::Result result0;
		auto codec = SkCodec::MakeFromStream(std::make_unique<t_stream>(a_read), {
			SkGifDecoder::Decoder(),
			SkJpegDecoder::Decoder(),
			SkPngDecoder::Decoder()
		}, &result0);
		if (!codec) f_throw(std::format(L"SkCodec::MakeFromStream: {}"sv, static_cast<int>(result0)));
		auto [image, result1] = codec->getImage();
		if (!image) f_throw(std::format(L"SkCodec::getImage: {}"sv, static_cast<int>(result1)));
		return t_proxy::f_own(xemmai::f_new<xemmaix::skia::t_image>(a_library, image));
	}>())
	(L"width"sv, t_member<int(*)(const sk_sp<SkImage>&), [](auto a_this)
	{
		return a_this->width();
	}>())
	(L"height"sv, t_member<int(*)(const sk_sp<SkImage>&), [](auto a_this)
	{
		return a_this->height();
	}>())
	(L"save"sv, t_member<void(*)(const sk_sp<SkImage>&, std::wstring_view), [](auto a_this, auto a_path)
	{
		auto png = SkPngEncoder::Encode(nullptr, a_this.get(), {});
		if (!png) f_throw(L"SkPngEncoder::Encode"sv);
		SkFILEWStream out(portable::f_convert(a_path).c_str());
		if (!out.write(png->data(), png->size())) f_throw(L"SkFILEWStream::write"sv);
	}>())
	.f_derive<t_image, t_proxy>();
}

}
