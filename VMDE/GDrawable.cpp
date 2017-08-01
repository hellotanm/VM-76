//=============================================================================
// ■ GDrawable.cpp
//-----------------------------------------------------------------------------
//   VMDE中GDrawable的控制与类。
//=============================================================================

#include "global.hpp"

void GDrawable::renderOnce() {
	VMSC::ChangeVertexArray(data.VAO);
	glDrawElements(GL_TRIANGLES, data.ind_c, GL_UNSIGNED_INT, 0);
}

void GDrawable::render() {
	VMSC::ChangeVertexArray(data.VAO);
	glDrawElementsInstanced(
		GL_TRIANGLES, data.ind_c, GL_UNSIGNED_INT, 0, data.mat_c);
}

void GDrawable::fbind() {
	VMSC::ChangeVertexArray(data.VAO);
	VMSC::ChangeElementArrayBuffer(data.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.ind_c * sizeof(GLuint), data.indices, GL_STATIC_DRAW);

	const size_t vec4Size = sizeof(glm::vec4);
	const size_t vertex_size = sizeof(Vertex); // X,Y,Z,  R,G,B,A,  S,T, Normal
	if (VMDE->gl_ver == GL_43) {
		// GL43 Vertex Attribute Format & Binding
		VMSC::ChangeArrayBuffer(data.VBO);
		glBufferData(GL_ARRAY_BUFFER, data.vtx_c * vertex_size, (GLfloat*) data.vertices, GL_STATIC_DRAW);

		glVertexAttribFormat(0, 3, GL_FLOAT, false, 0); // XYZ
		glVertexAttribFormat(1, 4, GL_FLOAT, false, 3 * sizeof(GLfloat)); // RGBA
		glVertexAttribFormat(2, 2, GL_FLOAT, false, 7 * sizeof(GLfloat)); // ST
		glVertexAttribFormat(3, 3, GL_FLOAT, false, 9 * sizeof(GLfloat)); // Normal
		glVertexAttribBinding(0, 0); // XYZ -> stream 0
		glVertexAttribBinding(1, 0); // RGBA -> stream 0
		glVertexAttribBinding(2, 0); // ST -> stream 0
		glVertexAttribBinding(3, 0); // Normal -> stream 0

		glBindVertexBuffer(0, data.VBO, 0, vertex_size);
	} else {
		// GL33 Vertex Attribute Pointer
		VMSC::ChangeArrayBuffer(data.VBO);
		glBufferData(GL_ARRAY_BUFFER, data.vtx_c * vertex_size, data.vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_size, (GLvoid*) 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertex_size, (GLvoid*) (3 * sizeof(GLfloat)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_size, (GLvoid*) (7 * sizeof(GLfloat)));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, vertex_size, (GLvoid*) (9 * sizeof(GLfloat)));
	}
	// GL33 Vertex Attribute Pointer Instanced
	VMSC::ChangeArrayBuffer(data.MBO);
	glBufferData(GL_ARRAY_BUFFER, data.mat_c * sizeof(glm::mat4), data.mat, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*) 0);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*) (vec4Size));
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*) (2 * vec4Size));
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*) (3 * vec4Size));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);
	glEnableVertexAttribArray(7);

	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	VMSC::ChangeVertexArray(0);
}

void GDrawable::update() {
	VMSC::ChangeVertexArray(data.VAO);

	VMSC::ChangeArrayBuffer(data.VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, data.vtx_c * sizeof(Vertex), data.vertices);

	VMSC::ChangeElementArrayBuffer(data.EBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data.ind_c * sizeof(GLuint), data.indices);
}

void GDrawable::update_instance() {
	VMSC::ChangeVertexArray(data.VAO);
	VMSC::ChangeArrayBuffer(data.MBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, data.mat_c * sizeof(glm::mat4), data.mat);
	//glBindBuffer(GL_ARRAY_BUFFER,0);
}

void GDrawable::update_instance_alien_size() {
	VMSC::ChangeVertexArray(data.VAO);
	VMSC::ChangeArrayBuffer(data.MBO);
	glBufferData(GL_ARRAY_BUFFER, data.mat_c * sizeof(glm::mat4), data.mat, GL_DYNAMIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER,0);
}

GDrawable::~GDrawable() {
	glDeleteVertexArrays(1, &data.VAO);
	glDeleteBuffers(1, &data.VBO);
	glDeleteBuffers(1, &data.EBO);
	glDeleteBuffers(1, &data.MBO);
}

GDrawable::GDrawable() {
	glGenVertexArrays(1, &data.VAO);
	glGenBuffers(1, &data.VBO);
	glGenBuffers(1, &data.EBO);
	glGenBuffers(1, &data.MBO);
	data.vertices = NULL;
	data.indices = NULL;
	data.mat = NULL;
}
