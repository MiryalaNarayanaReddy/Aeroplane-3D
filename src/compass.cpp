#include "compass.h"
#include "main.h"

Compass::Compass(float x, float y, float z, color_t color1, color_t color2) {
	this->position = glm::vec3(x, y, z);
	this->rotation = 0;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

	float l = 2.0f;
	GLfloat vertex_buffer_data_north[] = {
		-0.2f, 0.0f, 0.0f,
		0.2f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	GLfloat vertex_buffer_data_south[] = {
		-0.2f, 0.0f, 0.0f,
		0.2f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
	};
	
	this->object_north = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_north, color1, GL_FILL);
	this->object_south = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_south, color2, GL_FILL);
}

void Compass::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
	// No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object_north);
	draw3DObject(this->object_south);
}

void Compass::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Compass::set_angle(float rotation) {
	this->rotation = -(((int)rotation) % 360);
}

