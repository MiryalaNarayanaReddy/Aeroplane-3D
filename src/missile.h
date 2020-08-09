#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 rotation;
    float speed;
    float g;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z, float roation_x, float rotation_y, float rotation_z);
    void move();
private:
    VAO *object_body;
};

#endif // MISSILE_H
