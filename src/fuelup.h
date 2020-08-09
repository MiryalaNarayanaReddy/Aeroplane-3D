#include "main.h"

#ifndef FUELUP_H
#define FUELUP_H


class Fuelup {
public:
    Fuelup() {}
    Fuelup(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
private:
    VAO *object_body;
};

#endif // FUELUP_H
