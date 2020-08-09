#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H

class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z, color_t color1, color_t color2);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void set_angle(float rotation);

private:
    VAO *object_north;
    VAO *object_south;
};

#endif // COMPASS_H
