#include "main.h"

#ifndef DEFENCETOWER_H
#define DEFENCETOWER_H


class Defencetower {
public:
    Defencetower() {}
    Defencetower(float x, float y, float z, color_t color);
    glm::vec3 position;
    int alive;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
private:
    VAO *object_body;
};

#endif // DEFENCETOWER_H
