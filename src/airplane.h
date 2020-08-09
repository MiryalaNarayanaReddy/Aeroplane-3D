#include "main.h"

#ifndef AIRPLANE_H
#define AIRPLANE_H


class Airplane {
public:
    Airplane() {}
    Airplane(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void move_up();
    void move_down();
    void move_forward();
    void stop();
    void yaw(int direction);
    void pitch(int direction);
    void roll(int direction);
    double rotation_speed;
    double g;
    double acc_z;
    double speed_y;
    double speed_z;
    float fuel_left;
    int health;
    int points;
private:
    VAO *object_body;
    VAO *object_cockpit;
    VAO *object_tail;
    VAO *object_wings;
};

#endif // AIRPLANE_H
