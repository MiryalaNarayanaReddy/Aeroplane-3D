#include "airplane.h"
#include "main.h"

Airplane::Airplane(float x, float y, float z, color_t color) {
	this->position = glm::vec3(x, y, z);
	this->rotation = glm::vec3(0, 0, 0);
	this->rotation_speed = 1;
	this->speed_y = 0.1;
	this->g = 0.01;
	this->acc_z = 0.01;
	this->fuel_left = 999.99f;
	this->health = 1000;
	this->points = 0;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

	int n = 100;
	float l = 5.0f, r = 1.0f;
	GLfloat vertex_buffer_data_body[27*n];
	for(int i=0; i<27*n; i+=27){ 
		vertex_buffer_data_body[i]    = (float)r*cos(((i/27))*2*3.14159265/n);
		vertex_buffer_data_body[i+1]  = (float)r*sin(((i/27))*2*3.14159265/n);
		vertex_buffer_data_body[i+2]  = 0.0f;
		vertex_buffer_data_body[i+3]  = (float)r*cos(((i/27)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+4]  = (float)r*sin(((i/27)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+5]  = 0.0f;
		vertex_buffer_data_body[i+6]  = (float)r*cos(((i/27))*2*3.14159265/n);
		vertex_buffer_data_body[i+7]  = (float)r*sin(((i/27))*2*3.14159265/n);
		vertex_buffer_data_body[i+8]  = l;
		vertex_buffer_data_body[i+9]  = (float)r*cos(((i/27))*2*3.14159265/n);
		vertex_buffer_data_body[i+10] = (float)r*sin(((i/27))*2*3.14159265/n);
		vertex_buffer_data_body[i+11] = l;
		vertex_buffer_data_body[i+12] = (float)r*cos(((i/27)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+13] = (float)r*sin(((i/27)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+14] = l;
		vertex_buffer_data_body[i+15] = (float)r*cos(((i/27)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+16] = (float)r*sin(((i/27)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+17] = 0.0f;
		vertex_buffer_data_body[i+18] = (float)r*cos(((i/27))*2*3.14159265/n);
		vertex_buffer_data_body[i+19] = (float)r*sin(((i/27))*2*3.14159265/n);
		vertex_buffer_data_body[i+20] = 0.0f;
		vertex_buffer_data_body[i+21] = (float)r*cos(((i/27)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+22] = (float)r*sin(((i/27)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+23] = 0.0f;
		vertex_buffer_data_body[i+24] = 0.0f;
		vertex_buffer_data_body[i+25] = 0.0f;
		vertex_buffer_data_body[i+26] = 0.0f;
	}

	GLfloat vertex_buffer_data_cockpit[9*n];
	for(int i=0; i<9*n; i+=9){ 
		vertex_buffer_data_cockpit[i]   = (float)r*cos(((i/9))*2*3.14159265/n);
		vertex_buffer_data_cockpit[i+1] = (float)r*sin(((i/9))*2*3.14159265/n);
		vertex_buffer_data_cockpit[i+2] = l;
		vertex_buffer_data_cockpit[i+3] = (float)r*cos(((i/9)+1)*2*3.14159265/n);
		vertex_buffer_data_cockpit[i+4] = (float)r*sin(((i/9)+1)*2*3.14159265/n);
		vertex_buffer_data_cockpit[i+5] = l;
		vertex_buffer_data_cockpit[i+6] = 0.0f;
		vertex_buffer_data_cockpit[i+7] = 0.0f;
		vertex_buffer_data_cockpit[i+8] = l+1.0f;
	}

	GLfloat vertex_buffer_data_tail[] = {
		0.5*r, 0.0f, 0.0f,
		0.0f, 2*r, 0.0f,
		0.0f, r, 1.5*r,
		-0.5*r, 0.0f, 0.0f,
		0.0f, 2*r, 0.0f,
		0.0f, r, 1.5*r,
		0.5*r, 0.0f, 0.0f,
		-0.5*r, 0.0f, 0.0f,
		0.0f, 2*r, 0.0f,
	};

	GLfloat vertex_buffer_data_wings[] = {
		3*r, -0.25*r, 0.5*l,
		3*r, -0.25*r, 0.7*l,
		0.0f, -0.25*r, 0.5*r,
		3*r, -0.25*r, 0.7*l,
		0.0f, -0.25*r, 0.5*r,
		0.0f, -0.25*r, 0.7*l,
		3*r, -0.25*r, 0.5*l,
		3*r, -0.25*r, 0.7*l,
		0.0f, 0.25*r, 0.5*r,
		3*r, -0.25*r, 0.7*l,
		0.0f, 0.25*r, 0.5*r,
		0.0f, 0.25*r, 0.7*l,
		-3*r, -0.25*r, 0.5*l,
		-3*r, -0.25*r, 0.7*l,
		0.0f, -0.25*r, 0.5*r,
		-3*r, -0.25*r, 0.7*l,
		0.0f, -0.25*r, 0.5*r,
		0.0f, -0.25*r, 0.7*l,
		-3*r, -0.25*r, 0.5*l,
		-3*r, -0.25*r, 0.7*l,
		0.0f, 0.25*r, 0.5*r,
		-3*r, -0.25*r, 0.7*l,
		0.0f, 0.25*r, 0.5*r,
		0.0f, 0.25*r, 0.7*l,
		3*r, -0.25*r, 0.5*l,
		0.0f, -0.25*r, 0.5*r,
		0.0f, 0.25*r, 0.5*r,
		3*r, -0.25*r, 0.7*l,
		0.0f, -0.25*r, 0.7*r,
		0.0f, 0.25*r, 0.7*r,
		-3*r, -0.25*r, 0.5*l,
		0.0f, -0.25*r, 0.5*r,
		0.0f, 0.25*r, 0.5*r,
		-3*r, -0.25*r, 0.7*l,
		0.0f, -0.25*r, 0.7*r,
		0.0f, 0.25*r, 0.7*r,
	};


	this->object_body = create3DObject(GL_TRIANGLES, 9*n, vertex_buffer_data_body, color, GL_FILL);
	this->object_cockpit = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data_cockpit, color, GL_FILL);
	this->object_tail = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data_tail, color, GL_FILL);
	this->object_wings = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_wings, color, GL_FILL);
}

void Airplane::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate_x    = glm::rotate((float) (this->rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0));
	glm::mat4 rotate_y    = glm::rotate((float) (this->rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
	glm::mat4 rotate_z    = glm::rotate((float) (this->rotation.z * M_PI / 180.0f), glm::vec3(0, 0, 1));
	// No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate_x * rotate_y * rotate_z);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object_body);
	draw3DObject(this->object_cockpit);
	draw3DObject(this->object_tail);
	draw3DObject(this->object_wings);
}

void Airplane::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void Airplane::tick() {
	// this->rotation += speed;
	// this->position.x -= speed;
	// this->position.y -= speed;
}

void Airplane::move_up() {
	if(this->position.y < 8.0f){
		this->position.y += this->speed_y;
	}
}

void Airplane::move_down() {
	if(this->position.y > -1.0f){
		this->position.y -= this->speed_y;
	}
}

void Airplane::move_forward() {
	if(this->speed_z < 3.0f){
		this->speed_z += this->acc_z;
	}
	if((sin(this->rotation.x * M_PI / 180.0f) > 0 && this->position.y < 8.0f) || (sin(this->rotation.x * M_PI / 180.0f) < 0 && this->position.y > -1.0f))
		this->position.y += (this->speed_z * sin(this->rotation.x * M_PI / 180.0f));
	this->position.z += (this->speed_z * cos(this->rotation.x * M_PI / 180.0f) * cos(this->rotation.y * M_PI / 180.0f));
	this->position.x += (this->speed_z * cos(this->rotation.x * M_PI / 180.0f) * sin(this->rotation.y * M_PI / 180.0f));
}

void Airplane::stop() {
	this->speed_z = 0;
}

void Airplane::yaw(int direction) {
	// if(this->rotation_y <= 30 && this-> rotation_y >= -30){
		this->rotation.y += (direction * rotation_speed);
	// }
	// else if(this->rotation_y > 30) {
	// 	this->rotation_y = 30;
	// }
	// else {
	// 	this->rotation_y = -30;
	// }
}

void Airplane::pitch(int direction) {
	// if(this->rotation.x <= 30 && this-> rotation.x >= -30){
		this->rotation.x += (-direction * rotation_speed);
	// }
	// else if(this->rotation.x > 30) {
	// 	this->rotation.x = 30;
	// }
	// else {
	// 	this->rotation.x = -30;
	// }
}

void Airplane::roll(int direction) {
	// if(this->rotation.z <= 30 && this-> rotation.z >= -30){
		this->rotation.z += (direction * rotation_speed);
	// }
	// else if(this->rotation.z > 30) {
	// 	this->rotation.z = 30;
	// }
	// else {
	// 	this->rotation.z = -30;
	// }
}
