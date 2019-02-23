#include "main.h"

#ifndef BOMBS_H
#define BOMBS_H

class Bombs {
public:
    Bombs() {}
    Bombs(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 rotation;
    float speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z, float roation_x, float rotation_y, float rotation_z);
    void move();
private:
    VAO *object_body;
};

#endif // BOMBS_H
