#include "main.h"

#ifndef SMOKERINGS_H
#define SMOKERINGS_H


class Smokerings {
public:
    Smokerings() {}
    Smokerings(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
private:
    VAO *object_outerbody;
    VAO *object_innerbody;
    VAO *object_rim1;
    VAO *object_rim2;
};

#endif // SMOKERINGS_H
