#include "main.h"

#ifndef DEFENCEMISSILE_H
#define DEFENCEMISSILE_H


class Defencemissile {
public:
    Defencemissile() {}
    Defencemissile(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void move(int flag);
private:
    VAO *object_body;
};

#endif // DEFENCEMISSILE_H
