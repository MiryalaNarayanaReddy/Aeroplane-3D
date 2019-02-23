#include "fuelometer.h"
#include "main.h"

Fuelometer::Fuelometer(float x, float y, float z, color_t color1, color_t color2, color_t color3) {
	this->position = glm::vec3(x, y, z);
	this->rotation = 0;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

	double l = 1.0, t = 0.4;
	GLfloat vertex_buffer_data_radar[10][18];
	for (int i = 0; i < 10; i++, t += 0.4) {
		vertex_buffer_data_radar[i][0] = -l;
		vertex_buffer_data_radar[i][1] = t - 0.4;
		vertex_buffer_data_radar[i][2] = 0.0;
		vertex_buffer_data_radar[i][3] = -l;
		vertex_buffer_data_radar[i][4] = t;
		vertex_buffer_data_radar[i][5] = 0.0;
		vertex_buffer_data_radar[i][6] = l;
		vertex_buffer_data_radar[i][7] = t - 0.4;
		vertex_buffer_data_radar[i][8] = 0.0;
		vertex_buffer_data_radar[i][9] = -l;
		vertex_buffer_data_radar[i][10] = t;
		vertex_buffer_data_radar[i][11] = 0.0;
		vertex_buffer_data_radar[i][12] = l;
		vertex_buffer_data_radar[i][13] = t - 0.4;
		vertex_buffer_data_radar[i][14] = 0.0;
		vertex_buffer_data_radar[i][15] = l;
		vertex_buffer_data_radar[i][16] = t;
		vertex_buffer_data_radar[i][17] = 0.0;
	}

	this->object_radar[0] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_radar[0], color1, GL_FILL);
	this->object_radar[1] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_radar[1], color1, GL_FILL);
	this->object_radar[2] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_radar[2], color1, GL_FILL);
	this->object_radar[3] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_radar[3], color2, GL_FILL);
	this->object_radar[4] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_radar[4], color2, GL_FILL);
	this->object_radar[5] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_radar[5], color2, GL_FILL);
	this->object_radar[6] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_radar[6], color3, GL_FILL);
	this->object_radar[7] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_radar[7], color3, GL_FILL);
	this->object_radar[8] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_radar[8], color3, GL_FILL);
	this->object_radar[9] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_radar[9], color3, GL_FILL);
}

void Fuelometer::draw(glm::mat4 VP, float percentage) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
	// No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	int number_of_bars = (int)(percentage / 10);
	for (int i = 0; i <= number_of_bars; i++) {
		draw3DObject(this->object_radar[i]);
	}
}

void Fuelometer::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

