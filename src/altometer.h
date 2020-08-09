#include "main.h"

#ifndef ALTOMETER_H
#define ALTOMETER_H

class Altometer {
public:
    Altometer() {}
    Altometer(float x, float y, float z, color_t color1, color_t color2, color_t color3);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, float percentage);
    void set_position(float x, float y, float z);

private:
    VAO *object_radar[10];
};

#endif // ALTOMETER_H
