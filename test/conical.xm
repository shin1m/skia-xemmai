math = Module("math"
skia = Module("skia"
Module("png").do(Module("system").arguments[0], @(canvas)
	rect = skia.Rect.make_xywh(64.0, 64.0, 128.0, 128.0
	paint = skia.Paint(
	paint.shader__(skia.Shader.two_point_conical_gradient(
		96.0, 96.0, 16.0
		160.0, 160.0, 32.0
		'(
			'(0xffff0000, 0.0
			'(0x0000ffff, 1.0
		skia.Shader.TileMode.MIRROR
	canvas.draw_rect(rect, paint
