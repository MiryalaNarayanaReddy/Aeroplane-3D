#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float y, float z, color_t color1, color_t color2) {
	this->position = glm::vec3(x, y, z);
	this->rotation = rand() % 360;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

	float size = 5.0;
	this->tip_x = -size + (rand() % 20*size)/10.0;
	this->tip_z = -size + (rand() % 20*size)/10.0;
	this->tip_y = (rand() % 20)/10.0;
	GLfloat vertex_buffer_data_body[] = {
        -size, 0.0f, -size,
        -size, 0.0f, size,
        size, 0.0f, -size,
        -size, 0.0f, size,
        size, 0.0f, -size,
        size, 0.0f, size,
        -size, 0.0f, -size,
        -size, 0.0f, size,
        this->tip_x, this->tip_y, this->tip_z,
        -size, 0.0f, -size,
        size, 0.0f, -size,
        this->tip_x, this->tip_y, this->tip_z,
        -size, 0.0f, size,
        size, 0.0f, size,
        this->tip_x, this->tip_y, this->tip_z,
        size, 0.0f, -size,
        size, 0.0f, size,
        this->tip_x, this->tip_y, this->tip_z,
	};

	int n = 100;
	float r = 0.5;
    GLfloat vertex_buffer_data_firepit[9*n];
    for(int i=0; i<9*n; i+=9){
        vertex_buffer_data_firepit[i]   = this->tip_x + (float)r*cos(((i/9))*2*3.14159265/n);
        vertex_buffer_data_firepit[i+1] = this->tip_y - 0.2;
        vertex_buffer_data_firepit[i+2] = this->tip_z + (float)r*sin(((i/9))*2*3.14159265/n);
        vertex_buffer_data_firepit[i+3] = this->tip_x + (float)r*cos(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_firepit[i+4] = this->tip_y - 0.2;
        vertex_buffer_data_firepit[i+5] = this->tip_z + (float)r*sin(((i/9)+1)*2*3.14159265/n);
        vertex_buffer_data_firepit[i+6] = this->tip_x;
        vertex_buffer_data_firepit[i+7] = this->tip_y;
        vertex_buffer_data_firepit[i+8] = this->tip_z;
    }

	this->object_body = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data_body, color1, GL_FILL);
	this->object_firepit = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_firepit, color2, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
	// No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object_body);
	draw3DObject(this->object_firepit);
}

void Volcano::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

