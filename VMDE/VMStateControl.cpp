//=============================================================================
// ■ VMStateControl.cpp
//-----------------------------------------------------------------------------
//   VMDE的状态机管理
//=============================================================================

#include "global.hpp"

VMStateControl::StateMachineStruct VMStateControl::StateMachine;

void VMStateControl::ChangeVertexArray (GLuint index) {
	if (index != StateMachine.VERTEX_ARRAY) {
		StateMachine.VERTEX_ARRAY = index;
		glBindVertexArray(index);
	}
}

void VMStateControl::ChangeElementArrayBuffer (GLuint index) {
	if (index != StateMachine.ELEMENT_ARRAY_BUFFER) {
		StateMachine.ELEMENT_ARRAY_BUFFER = index;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	}
}

void VMStateControl::ChangeArrayBuffer (GLuint index) {
	if (index != StateMachine.ARRAY_BUFFER) {
		StateMachine.ARRAY_BUFFER = index;
		glBindBuffer(GL_ARRAY_BUFFER, index);
	}
}

void VMStateControl::ChangeTexture2D (GLuint index) {
	if (index != StateMachine.TEXTURE_2D) {
		StateMachine.TEXTURE_2D = index;
		glBindTexture(GL_TEXTURE_2D, index);
	}
}

void VMStateControl::ChangeTextureCubeMap (GLuint index) {
	if (index != StateMachine.TEXTURE_CUBE_MAP) {
		StateMachine.TEXTURE_CUBE_MAP = index;
		glBindTexture(GL_TEXTURE_2D, index);
	}
}

void VMStateControl::ChangeUniformBuffer (GLuint index) {
	if (index != StateMachine.UNIFORM_BUFFER) {
		StateMachine.UNIFORM_BUFFER = index;
		glBindBuffer(GL_UNIFORM_BUFFER, index);
	}
}

void VMStateControl::ChangeShaderProgram (GLuint index) {
	if (index != StateMachine.Shader_Program) {
		StateMachine.Shader_Program = index;
		glUseProgram(index);
	}
}


void VMStateControl::enable_cullface() {
	if (!StateMachine.CULL_FACE) {
		StateMachine.CULL_FACE = true;
		glEnable(GL_CULL_FACE);
	}
}

void VMStateControl::disable_cullface() {
	if (StateMachine.CULL_FACE) {
		StateMachine.CULL_FACE = false;
		glDisable(GL_CULL_FACE);
	}
}

void VMStateControl::enable_depth_test() {
	if (!StateMachine.DEPTH_TEST) {
		StateMachine.DEPTH_TEST = true;
		glEnable(GL_DEPTH_TEST);
	}
}

void VMStateControl::disable_depth_test() {
	if (StateMachine.DEPTH_TEST) {
		StateMachine.DEPTH_TEST = false;
		glDisable(GL_DEPTH_TEST);
	}
}

void VMStateControl::enable_stencil_test() {
	if (!StateMachine.STENCIL_TEST) {
		StateMachine.STENCIL_TEST = true;
		glEnable(GL_STENCIL_TEST);
	}
}

void VMStateControl::disable_stencil_test() {
	if (StateMachine.STENCIL_TEST) {
		StateMachine.STENCIL_TEST = false;
		glDisable(GL_STENCIL_TEST);
	}
}

void VMStateControl::enable_blend() {
	if (!StateMachine.BLEND) {
		StateMachine.BLEND = true;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}

void VMStateControl::disable_blend() {
	if (StateMachine.BLEND) {
		StateMachine.BLEND = false;
		glDisable(GL_BLEND);
	}
}

void VMStateControl::render_mode_wireframe() {
	if (StateMachine.PolygonMode != GL_LINE) {
		StateMachine.PolygonMode = GL_LINE;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

void VMStateControl::render_mode_fill() {
	if (StateMachine.PolygonMode != GL_FILL) {
		StateMachine.PolygonMode = GL_FILL;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}


void VMStateControl::init_graphics_state() {
	// 设置当前窗口GL上下文
	glfwMakeContextCurrent(window);
	// 垂直同步，拒绝鬼畜
	glfwSwapInterval(1);

	// 初始化GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		log("glewInit() (GLEW Initialization) failed.");
		return;
	}
	#ifdef __APPLE__
		if (glfwExtensionSupported("GL_APPLE_uniform_buffer_object") != GLFW_TRUE) {
			glfwTerminate();
			log("Your computer need OpenGL 3.3 with Uniform Buffer Object (UBO).");
			log("Uniform buffer object is NOT detected properlly");
			return;
		}
		log("UBO: Apple Uniform Buffer Object （__APPLE__)");
	#else
		if (glfwExtensionSupported("GL_ARB_uniform_buffer_object") != GLFW_TRUE) {
			glfwTerminate();
			error("Your computer need OpenGL 3.3 with Uniform Buffer Object (UBO).");
			return;
		}
		log("UBO: GL33 Uniform Buffer Object");
	#endif

	bool FP16_support = false;
	bool GPU_Shader5 = false;
	bool FP16_implicit_support = false;
	if (glfwExtensionSupported("GL_ARB_gpu_shader5") == GLFW_TRUE) {
		log("ARB GPU Shader 5 detected");
		GPU_Shader5 = true;
	}
	if (glfwExtensionSupported("GL_NV_gpu_shader5") == GLFW_TRUE) {
		log("NV GPU Shader 5 detected");
		GPU_Shader5 = true;
		FP16_support = true;
		if (glfwExtensionSupported("GL_ARB_gpu_shader_fp64") == GLFW_TRUE) FP16_implicit_support = true;
	}
	if (glfwExtensionSupported("GL_AMD_gpu_shader_half_float") == GLFW_TRUE) {
		log("AMD FP16 detected");
		GPU_Shader5 = true;
		FP16_support = true;
		FP16_implicit_support = true;
	}

	memset (&StateMachine, 0, sizeof(StateMachine));
}
