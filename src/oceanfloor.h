#include "main.h"

#ifndef OCEANFLOOR_H
#define OCEANFLOOR_H


class Oceanfloor {
public:
    Oceanfloor() {}
    Oceanfloor(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object_body;
};

#endif // OCEANFLOOR_H
