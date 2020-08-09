#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    int alive;
    float speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void move(int flag);
private:
    VAO *object_body;
};

#endif // PARACHUTE_H
