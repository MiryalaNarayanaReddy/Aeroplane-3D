#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y, float z, color_t color1, color_t color2);
    glm::vec3 position;
    float rotation;
    float tip_x;
    float tip_y;
    float tip_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
private:
    VAO *object_body;
    VAO *object_firepit;
};

#endif // VOLCANO_H
