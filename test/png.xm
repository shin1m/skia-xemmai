skia = Module("skia"
$do = @(path, draw) skia.main(@
	surface = skia.Surface.raster(256, 256
	surface.draw(draw
	image = surface.make_image_snapshot(
	image.save(path
