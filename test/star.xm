math = Module("math"
skia = Module("skia"
Module("png").do(Module("system").arguments[0], @(canvas)
	scale = 256.0
	R = 0.45 * scale
	TAU = 6.2831853
	builder = skia.PathBuilder().move_to(R, 0.0
	for i = 1; i < 7; i = i + 1
		theta = 3 * i * TAU / 7
		builder.line_to(R * math.cos(theta), R * math.sin(theta
	path = builder.close().detach(
	paint = skia.Paint(
	paint.anti_alias__(true
	canvas.clear(0xffffffff
	canvas.translate(0.5 * scale, 0.5 * scale
	canvas.draw_path(path, paint
