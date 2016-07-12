#include "engine.hpp"

void init_RClass() {
  GResPic = rb_define_class_under(Global_module, "GRes_Picture", rb_cObject);

  rb_define_method(GResPic, "load_pic", (RB_F_R) warp_load_pic, 1);

}

void init_RModule() {
  Global_module = rb_define_module("VMDE");

  rb_define_module_function(Global_module, "init_engine", (RB_F_R) wrap_init_engine, 2);
  rb_define_module_function(Global_module, "update", (RB_F_R) warp_main_draw_loop, 0);
  rb_define_module_function(Global_module, "get_frame_count", (RB_F_R) warp_main_get_frame_count, 0);
  rb_define_module_function(Global_module, "get_fps", (RB_F_R) warp_main_get_fps, 0);

}

void init_shaders() {
}

int init_engine(int w, int h) {
  printf("%s[init_engine]: ENGINE INIT\n", DBG_HEAD);

  // 初始化VMDE结构
  VMDE = (VMDE_t*) malloc(sizeof(VMDE));
  VMDE->States = (VMDE_State_t*) malloc(sizeof(VMDE->States));
  VMDE->States->freeze = false;
  VMDE->framecount = 0;
  VMDE->fps = 0;


	// GLFW库初始化
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) {
		throw std::runtime_error("glfwInit failed");
	}

	// OpenGL 向前&向后兼容，使用GL 3.2 Core Profile，窗口大小不可变
	// 指定版本后便无需再检查是否支持指定版本，因为GLFW会处理此问题
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(w, h, GAME_NAME, NULL, NULL);
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");
	}

	// 设置当前窗口GL上下文
	glfwMakeContextCurrent(window);

	// 初始化GLEW
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("glewInit failed");
	}

	// 初始化着色器「OpenGL 3.2没有固定管线了，着色器是被钦定的」
	init_shaders();

	return 0;
}
