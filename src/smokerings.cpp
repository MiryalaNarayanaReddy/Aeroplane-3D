#include "smokerings.h"
#include "main.h"

Smokerings::Smokerings(float x, float y, float z, color_t color) {
	this->position = glm::vec3(x, y, z);
	this->rotation = rand() % 360;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

	int n = 100;
	float l = 0.4f, R = 1.0f, r = 0.8f;
	GLfloat vertex_buffer_data_outerbody[18*n];
	for(int i=0; i<18*n; i+=18){ 
		vertex_buffer_data_outerbody[i]    = (float)R*cos(((i/18))*2*3.14159265/n);
		vertex_buffer_data_outerbody[i+1]  = (float)R*sin(((i/18))*2*3.14159265/n);
		vertex_buffer_data_outerbody[i+2]  = 0.0f;
		vertex_buffer_data_outerbody[i+3]  = (float)R*cos(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_outerbody[i+4]  = (float)R*sin(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_outerbody[i+5]  = 0.0f;
		vertex_buffer_data_outerbody[i+6]  = (float)R*cos(((i/18))*2*3.14159265/n);
		vertex_buffer_data_outerbody[i+7]  = (float)R*sin(((i/18))*2*3.14159265/n);
		vertex_buffer_data_outerbody[i+8]  = l;
		vertex_buffer_data_outerbody[i+9]  = (float)R*cos(((i/18))*2*3.14159265/n);
		vertex_buffer_data_outerbody[i+10] = (float)R*sin(((i/18))*2*3.14159265/n);
		vertex_buffer_data_outerbody[i+11] = l;
		vertex_buffer_data_outerbody[i+12] = (float)R*cos(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_outerbody[i+13] = (float)R*sin(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_outerbody[i+14] = l;
		vertex_buffer_data_outerbody[i+15] = (float)R*cos(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_outerbody[i+16] = (float)R*sin(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_outerbody[i+17] = 0.0f;
	}

	GLfloat vertex_buffer_data_innerbody[18*n];
	for(int i=0; i<18*n; i+=18){ 
		vertex_buffer_data_innerbody[i]    = (float)r*cos(((i/18))*2*3.14159265/n);
		vertex_buffer_data_innerbody[i+1]  = (float)r*sin(((i/18))*2*3.14159265/n);
		vertex_buffer_data_innerbody[i+2]  = 0.0f;
		vertex_buffer_data_innerbody[i+3]  = (float)r*cos(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_innerbody[i+4]  = (float)r*sin(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_innerbody[i+5]  = 0.0f;
		vertex_buffer_data_innerbody[i+6]  = (float)r*cos(((i/18))*2*3.14159265/n);
		vertex_buffer_data_innerbody[i+7]  = (float)r*sin(((i/18))*2*3.14159265/n);
		vertex_buffer_data_innerbody[i+8]  = l;
		vertex_buffer_data_innerbody[i+9]  = (float)r*cos(((i/18))*2*3.14159265/n);
		vertex_buffer_data_innerbody[i+10] = (float)r*sin(((i/18))*2*3.14159265/n);
		vertex_buffer_data_innerbody[i+11] = l;
		vertex_buffer_data_innerbody[i+12] = (float)r*cos(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_innerbody[i+13] = (float)r*sin(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_innerbody[i+14] = l;
		vertex_buffer_data_innerbody[i+15] = (float)r*cos(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_innerbody[i+16] = (float)r*sin(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_innerbody[i+17] = 0.0f;
	}

	GLfloat vertex_buffer_data_rim1[18*n];
	for(int i=0; i<18*n; i+=18){ 
		vertex_buffer_data_rim1[i]    = (float)R*cos(((i/18))*2*3.14159265/n);
		vertex_buffer_data_rim1[i+1]  = (float)R*sin(((i/18))*2*3.14159265/n);
		vertex_buffer_data_rim1[i+2]  = 0.0f;
		vertex_buffer_data_rim1[i+3]  = (float)r*cos(((i/18))*2*3.14159265/n);
		vertex_buffer_data_rim1[i+4]  = (float)r*sin(((i/18))*2*3.14159265/n);
		vertex_buffer_data_rim1[i+5]  = 0.0f;
		vertex_buffer_data_rim1[i+6]  = (float)R*cos(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_rim1[i+7]  = (float)R*sin(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_rim1[i+8]  = 0.0f;
		vertex_buffer_data_rim1[i+9]  = (float)r*cos(((i/18))*2*3.14159265/n);
		vertex_buffer_data_rim1[i+10] = (float)r*sin(((i/18))*2*3.14159265/n);
		vertex_buffer_data_rim1[i+11] = 0.0f;
		vertex_buffer_data_rim1[i+12] = (float)R*cos(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_rim1[i+13] = (float)R*sin(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_rim1[i+14] = 0.0f;
		vertex_buffer_data_rim1[i+15] = (float)r*cos(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_rim1[i+16] = (float)r*sin(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_rim1[i+17] = 0.0f;
	}

	GLfloat vertex_buffer_data_rim2[18*n];
	for(int i=0; i<18*n; i+=18){ 
		vertex_buffer_data_rim2[i]    = (float)R*cos(((i/18))*2*3.14159265/n);
		vertex_buffer_data_rim2[i+1]  = (float)R*sin(((i/18))*2*3.14159265/n);
		vertex_buffer_data_rim2[i+2]  = 0.0f;
		vertex_buffer_data_rim2[i+3]  = (float)r*cos(((i/18))*2*3.14159265/n);
		vertex_buffer_data_rim2[i+4]  = (float)r*sin(((i/18))*2*3.14159265/n);
		vertex_buffer_data_rim2[i+5]  = 0.0f;
		vertex_buffer_data_rim2[i+6]  = (float)R*cos(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_rim2[i+7]  = (float)R*sin(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_rim2[i+8]  = 0.0f;
		vertex_buffer_data_rim2[i+9]  = (float)r*cos(((i/18))*2*3.14159265/n);
		vertex_buffer_data_rim2[i+10] = (float)r*sin(((i/18))*2*3.14159265/n);
		vertex_buffer_data_rim2[i+11] = 0.0f;
		vertex_buffer_data_rim2[i+12] = (float)R*cos(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_rim2[i+13] = (float)R*sin(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_rim2[i+14] = 0.0f;
		vertex_buffer_data_rim2[i+15] = (float)r*cos(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_rim2[i+16] = (float)r*sin(((i/18)+1)*2*3.14159265/n);
		vertex_buffer_data_rim2[i+17] = 0.0f;
	}

	this->object_outerbody = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data_outerbody, color, GL_FILL);
	this->object_innerbody = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data_innerbody, color, GL_FILL);
	this->object_rim1 = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data_rim1, color, GL_FILL);
	this->object_rim2 = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data_rim2, color, GL_FILL);
}

void Smokerings::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
	// No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object_outerbody);
	draw3DObject(this->object_innerbody);
	draw3DObject(this->object_rim1);
	draw3DObject(this->object_rim2);
}

void Smokerings::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

