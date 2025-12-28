add_library(skia-xemmai MODULE
	skia.cc
	surface.cc
	canvas.cc
	font.cc
	font_manager.cc
	image.cc
	paint.cc
	path.cc
	rect.cc
	shader.cc
	typeface.cc
)
target_link_libraries(skia-xemmai PRIVATE skia xemmai)
set_target_properties(skia-xemmai PROPERTIES OUTPUT_NAME skia PREFIX "")
