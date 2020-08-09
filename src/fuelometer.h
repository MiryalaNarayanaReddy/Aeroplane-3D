#include "main.h"

#ifndef FUELOMETER_H
#define FUELOMETER_H

class Fuelometer {
public:
    Fuelometer() {}
    Fuelometer(float x, float y, float z, color_t color1, color_t color2, color_t color3);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, float percentage);
    void set_position(float x, float y, float z);

private:
    VAO *object_radar[10];
};

#endif // FUELOMETER_H
