math = Module("math"
skia = Module("skia"
Module("png").do(Module("system").arguments[0], @(canvas)
	rect = skia.Rect.make_xywh(64.0, 64.0, 128.0, 128.0
	paint = skia.Paint(
	paint.shader__(skia.Shader.sweep_gradient(
		128.0, 128.0, 45.0, 135.0
		'(
			'(0xffff0000, 0.0
			'(0x0000ffff, 1.0
		skia.Shader.TileMode.DECAL
	canvas.draw_rect(rect, paint
