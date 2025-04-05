math = Module("math"
skia = Module("skia"
Module("png").do(Module("system").arguments[0], @(canvas)
	canvas.clear(0xffffffff
	paint = skia.Paint(
	paint.style__(skia.Paint.Style.STROKE
	paint.stroke_width__(4.0
	paint.color__(0xffff0000
	rect = skia.Rect.make_xywh(50.0, 50.0, 40.0, 60.0
	canvas.draw_rect(rect, paint
	path = skia.Path().cubic_to(768.0, 0.0, -512.0, 256.0, 256.0, 256.0
	paint.color__(0xff00ff00
	canvas.draw_path(path, paint
