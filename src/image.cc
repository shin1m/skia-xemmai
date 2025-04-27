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

namespace
{

struct t_stream : SkStream
{
	t_pvalue v_read;
	t_object* v_buffer = t_bytes::f_instantiate(1024);
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
		return xemmai::f_new<xemmaix::skia::t_image>(a_library, image);
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
