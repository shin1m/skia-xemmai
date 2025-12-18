math = Module("math"
skia = Module("skia"
Module("png").do(Module("system").arguments[0], @(canvas)
	surface = skia.Surface.raster(64, 64
	surface.draw(@(canvas)
		path = skia.PathBuilder()
			.move_to(16.0, 0.0
			.line_to(48.0, 0.0
			.line_to(64.0, 16.0
			.line_to(64.0, 48.0
			.line_to(48.0, 64.0
			.line_to(16.0, 64.0
			.line_to(0.0, 48.0
			.line_to(0.0, 16.0
			.close(
			.detach(
		paint = skia.Paint(
		paint.anti_alias__(true
		canvas.draw_path(path, paint
		path.dispose(
		paint.dispose(
	image = surface.make_image_snapshot(
	surface.dispose(
	canvas.save(
	canvas.translate(64.0, 64.0
	canvas.rotate(30.0
	canvas.draw_image(image, -32.0, -32.0
	canvas.restore(
	canvas.save(
	canvas.translate(192.0, 64.0
	canvas.rotate(30.0
	canvas.draw_image(image, -32.0, -32.0, skia.SamplingOptions(skia.FilterMode.LINEAR
	canvas.restore(
	canvas.save(
	canvas.translate(64.0, 192.0
	canvas.rotate(30.0
	canvas.draw_image_rect(image,
		skia.Rect.make_xywh(0.0, 0.0, 32.0, 32.0
		skia.Rect.make_xywh(-32.0, -32.0, 64.0, 48.0
		skia.SamplingOptions(skia.FilterMode.NEAREST
		null
		skia.Canvas.SourceRectConstraint.STRICT
	canvas.restore(
	canvas.save(
	canvas.translate(192.0, 192.0
	canvas.rotate(30.0
	canvas.draw_image_rect(image,
		skia.Rect.make_xywh(0.0, 0.0, 32.0, 32.0
		skia.Rect.make_xywh(-32.0, -32.0, 64.0, 48.0
		skia.SamplingOptions(skia.FilterMode.LINEAR
		null
		skia.Canvas.SourceRectConstraint.STRICT
	canvas.restore(
