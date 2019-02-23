#include "main.h"

#ifndef CHECKPOINT_H
#define CHECKPOINT_H


class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x, float y, float z, color_t color);
    glm::vec3 position;
    int claimed;
    float rotation;
    float tip_x;
    float tip_y;
    float tip_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
private:
    VAO *object_body;
};

#endif // CHECKPOINT_H
