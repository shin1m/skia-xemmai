math = Module("math"
skia = Module("skia"
Module("png").do(Module("system").arguments[0], @(canvas)
	rect = skia.Rect.make_xywh(64.0, 64.0, 128.0, 128.0
	paint = skia.Paint(
	paint.shader__(skia.Shader.linear_gradient(
		0.0, 64.0, 0.0, 192.0
		'(
			'(0xffff0000, 0.0
			'(0x0000ffff, 1.0
		skia.Shader.TileMode.CLAMP
	canvas.draw_rect(rect, paint
