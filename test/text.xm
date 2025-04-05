math = Module("math"
skia = Module("skia"
Module("png").do(Module("system").arguments[0], @(canvas)
	fm = skia.FontManager.make_default(
	paint = skia.Paint(
	canvas.clear(0xffffffff
	typeface = fm.match_family_style(null, skia.FontStyle.Normal(
	font = skia.Font(typeface, 18.0
	metrics = font.metrics(
	canvas.draw_text("Hello, Skia!", 0.0, -metrics[1].ascent(), font, paint
	canvas.save(
	canvas.translate(128.0, 64.0
	canvas.rotate(-45.0
	typeface = fm.match_family_style(null, skia.FontStyle.Normal(
	font = skia.Font(typeface, 18.0
	width = font.measure_advance("Hello, Skia!"
	metrics = font.metrics(
	canvas.draw_text("Hello, Skia!", width * -0.5, metrics[0] * -0.5 - metrics[1].ascent(), font, paint
	canvas.restore(
	canvas.save(
	canvas.translate(128.0, 192.0
	canvas.rotate(-45.0
	typeface = fm.match_family_style(null, skia.FontStyle.Bold(
	font = skia.Font(typeface, 18.0
	width = font.measure_advance("Hello, Skia!"
	metrics = font.metrics(
	canvas.draw_text("Hello, Skia!", width * -0.5, metrics[0] * -0.5 - metrics[1].ascent(), font, paint
	canvas.restore(
