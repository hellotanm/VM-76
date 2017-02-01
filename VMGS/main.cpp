//=============================================================================
// ■ main.cpp
//-----------------------------------------------------------------------------
//   VMGS的主程序。
//=============================================================================

#include "VMGS.hpp"

namespace VM76 {
	Shaders* main_shader = NULL;
	Res::Texture* tile_texture = NULL;

	Cube* c;
	Cube* c2;

	Object* obj = new Object();

	int map_count = 0;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		#define PRESS(n) key == n && action == GLFW_PRESS
		if (PRESS(GLFW_KEY_A)) obj->move(glm::vec3(0.5, 0.0, 0.0));
		if (PRESS(GLFW_KEY_D)) obj->move(glm::vec3(-0.5, 0.0, 0.0));
		if (PRESS(GLFW_KEY_W)) obj->move(glm::vec3(0.0, 0.0, -0.5));
		if (PRESS(GLFW_KEY_S)) obj->move(glm::vec3(0.0, 0.0, 0.5));
		if (PRESS(GLFW_KEY_UP)) obj->move(glm::vec3(0.0, -0.5, 0.0));
		if (PRESS(GLFW_KEY_DOWN)) obj->move(glm::vec3(0.0, 0.5, 0.0));

		if (PRESS(GLFW_KEY_O)) obj->scale += glm::vec3(0.1, 0.1, 0.1);
		if (PRESS(GLFW_KEY_P)) obj->scale -= glm::vec3(0.1, 0.1, 0.1);

		if (PRESS(GLFW_KEY_SPACE)) {
			c->mat[map_count] = obj->transform();
			c->update_instance(map_count + 1);
			map_count ++;
		}
	}

	void loop() {
		for (;;) {
			::main_draw_start();
			update_control();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			main_shader->use();

			// Setup uniforms
			main_shader->set_float("brightness", VMDE->state.brightness);

			main_shader->ProjectionView(projection, view);
			c->render();

			// Setup uniforms
			main_shader->set_float("brightness", 0.5);
			c2->mat[0] = obj->transform();
			c2->update_instance(1);
			c2->render();

			::main_draw_end();
			if (VMDE->done) break;
		}
	}

	void init_textures() {
		main_shader->set_texture("colortex0", tile_texture, 0);
	}

	void start_game() {
		// 先设好事件回调然后再启动引擎，最大地避免段错误
		on_terminate = terminate;
		::init_engine(860, 540, "VM / 76");
		init_control();

		tile_texture = new Res::Texture("../Media/terrain.png");

		main_shader = Shaders::CreateFromFile("../Media/shaders/gbuffers_basic.vsh", "../Media/shaders/gbuffers_basic.fsh");

		projection = glm::perspective(1.3f, float(VMDE->width) / float(VMDE->height), 0.1f, 1000.0f);
		view = glm::lookAt(glm::vec3(0.0, 2.6, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

		// GL settings initialize
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glDepthRange(0.0f, 1.0f);
		glClearDepth(1.0f);
		glDepthMask(GL_TRUE);

		init_textures();

		c = new Cube(1);
		c2 = new Cube(1);
		c2->obj->data.mat_c = 1;
		glfwSetKeyCallback(window, key_callback);

		loop();
	}

	void terminate() {
		VMDE_Dispose(tile_texture);
		VMDE_Dispose(c);VMDE_Dispose(c2);
	}
}

int main() {
	log("Hello! This is VM76. Nice to meet you!");
	VM76::start_game();
}
