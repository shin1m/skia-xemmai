math = Module("math"
skia = Module("skia"
Module("png").do(Module("system").arguments[0], @(canvas)
	canvas.save(
	canvas.translate(128.0, 128.0
	canvas.rotate(45.0
	rect = skia.Rect.make_xywh(-90.5, -90.5, 181.0, 181.0
	paint = skia.Paint(
	paint.color__(0xff0000ff
	canvas.draw_rect(rect, paint
	canvas.restore(
