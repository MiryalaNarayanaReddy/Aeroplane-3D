#include "main.h"
#include "timer.h"
#include "airplane.h"
#include "oceanfloor.h"
#include "speedometer.h"
#include "fuelometer.h"
#include "altometer.h"
#include "compass.h"
#include "arrow.h"
#include "checkpoint.h"
#include "defencetower.h"
#include "defencemissile.h"
#include "volcano.h"
#include "smokerings.h"
#include "fuelup.h"
#include "missile.h"
#include "bombs.h"
#include "parachute.h"

using namespace std;

GLMatrices Matrices;
GLMatrices Matrices_ortho;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Airplane airplane;
Oceanfloor oceanfloor;
Speedometer speedometer;
Fuelometer fuelometer;
Altometer altometer;
Compass compass;
Arrow arrow;

#define number_of_checkpoints 100
Checkpoint checkpoint[number_of_checkpoints];
float checkpoint_location[number_of_checkpoints/10][2];
int checkpoint_iterator;
Defencetower defencetower[4*number_of_checkpoints/10];
Defencemissile defencemissile[15*4*number_of_checkpoints/10];
#define number_of_volcanos 1000
Volcano volcano[number_of_volcanos];
float volcano_location[number_of_volcanos/10][2];
#define number_of_smokerings 200
Smokerings smokerings[number_of_smokerings];
#define number_of_fuelups 50
Fuelup fuelups[number_of_fuelups];
#define number_of_parachutes 100
Parachute parachutes[number_of_parachutes];
#define number_of_missiles 100
Missile missiles[number_of_missiles];
int missile_iterator;
#define number_of_bombs 60
Bombs bombs[number_of_bombs];
int bomb_iterator;

float screen_zoom = 0.3, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int view_mode = 4;

Timer t60(1.0 / 60);

float eye_x, eye_y, eye_z;
float target_x, target_y, target_z;

float helicopter_rotation_x = 0;
float helicopter_rotation_z = 0;
double cursor_x, cursor_z;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    switch(view_mode){
       case 1:
            eye_x = airplane.position.x + 6.0f * sin(airplane.rotation.y * M_PI / 180.0f);
            eye_y = airplane.position.y;
            eye_z = airplane.position.z + 6.0f * cos(airplane.rotation.y * M_PI / 180.0f);
            target_x = airplane.position.x + 100.0f  * sin(airplane.rotation.y * M_PI / 180.0f);
            target_y = airplane.position.y;
            target_z = airplane.position.z + 100.0f  * cos(airplane.rotation.y * M_PI / 180.0f);
            break;
        case 2:
            eye_x = airplane.position.x + 4.0f * sin(airplane.rotation.y * M_PI / 180.0f);;
            eye_y = airplane.position.y + 20.0f;
            eye_z = airplane.position.z + 4.0f * cos(airplane.rotation.y * M_PI / 180.0f);;
            target_x = airplane.position.x + 6.0f * sin(airplane.rotation.y * M_PI / 180.0f);;
            target_y = airplane.position.y;
            target_z = airplane.position.z + 6.0f * cos(airplane.rotation.y * M_PI / 180.0f);;
            break;
        case 3:
            eye_x = -100.0f;
            eye_y = 100.0f;
            eye_z = -100.0f;
            target_x = airplane.position.x;
            target_y = airplane.position.y;
            target_z = airplane.position.z;
            break;
        case 4:
            eye_x = airplane.position.x;
            eye_y = airplane.position.y + 20.0f;
            eye_z = airplane.position.z;
            target_x = airplane.position.x + 6.0f * sin(airplane.rotation.y * M_PI / 180.0f);
            target_y = airplane.position.y;
            target_z = airplane.position.z + 6.0f * cos(airplane.rotation.y * M_PI / 180.0f);
            break;
        case 5:
            eye_x = airplane.position.x + 10.0f;
            eye_y = airplane.position.y;
            eye_z = airplane.position.z + 3.0f;
            target_x = airplane.position.x + 1.0f;
            target_y = airplane.position.y;
            target_z = airplane.position.z + 3.0f;
            break;
        case 6:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwGetCursorPos(window, &cursor_x, &cursor_z);
            glfwSetCursorPos(window, 300, 300);
            helicopter_rotation_x += (cursor_x - 300);
            helicopter_rotation_z += (cursor_z - 300);
            eye_x = airplane.position.x - 30.0f * sin(helicopter_rotation_x * M_PI / 180.0f);
            eye_y = airplane.position.y + 60.0f * cos(helicopter_rotation_z * M_PI / 180.0f);
            if(eye_y < 0)
                eye_y = 0;
            eye_z = airplane.position.z - 30.0f * sin(helicopter_rotation_x * M_PI / 180.0f);
            target_x = airplane.position.x + 6.0f * sin(airplane.rotation.y * M_PI / 180.0f);
            target_y = airplane.position.y;
            target_z = airplane.position.z + 6.0f * cos(airplane.rotation.y * M_PI / 180.0f);
    }

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( eye_x, eye_y, eye_z);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (target_x, target_y, target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    glm::vec3 eye_ortho ( 0, 0, 1 );
    glm::vec3 target_ortho ( 0, 0, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    Matrices_ortho.view = glm::lookAt( eye_ortho, target_ortho, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP_ortho = Matrices_ortho.projection * Matrices_ortho.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    airplane.draw(VP);
    oceanfloor.draw(VP);
    speedometer.draw(VP_ortho);
    fuelometer.draw(VP_ortho, airplane.fuel_left * 100.0f / 1000.0f);
    altometer.draw(VP_ortho, (airplane.position.y + 2.0f) * 100.0f / 10.0f);
    compass.draw(VP_ortho);
    arrow.draw(VP);
    for (int i = 0; i < number_of_checkpoints; i++) {
        checkpoint[i].draw(VP);
    }
    for (int i = 0; i < 4*number_of_checkpoints/10; i++) {
    	if(defencetower[i].alive){
        	defencetower[i].draw(VP);
    	}
    }
    for (int i = 0; i < 15*4*number_of_checkpoints/10; i++) {
	    defencemissile[i].draw(VP);
    }
    for (int i = 0; i < number_of_volcanos; i++) {
        volcano[i].draw(VP);
    }
    for (int i = 0; i < number_of_smokerings; i++) {
        smokerings[i].draw(VP);
    }
    for (int i = 0; i < number_of_fuelups; i++) {
        fuelups[i].draw(VP);
    }
    for (int i = 0; i < number_of_parachutes; i++) {
        parachutes[i].draw(VP);
    }
    for (int i = 0; i < number_of_missiles; i++) {
        missiles[i].draw(VP);
    }
    for (int i = 0; i < number_of_bombs; i++) {
        bombs[i].draw(VP);
    }
}


void tick_input(GLFWwindow *window, int register_input) {
    glfwSetScrollCallback(window, scroll_callback);
    int planeview = glfwGetKey(window, GLFW_KEY_1);
    int topview = glfwGetKey(window, GLFW_KEY_2);
    int towerview  = glfwGetKey(window, GLFW_KEY_3);
    int followcamview  = glfwGetKey(window, GLFW_KEY_4);
    int sideview  = glfwGetKey(window, GLFW_KEY_5);
    int helicoptercamview  = glfwGetKey(window, GLFW_KEY_6);
    if (planeview) {
       view_mode = 1;
    }
    else if (topview) {
        view_mode = 2;
    }
    else if (towerview) {
        view_mode = 3;
    }
    else if (followcamview) {
        view_mode = 4;
    }
    else if (sideview) {
        view_mode = 5;
    }
    else if (helicoptercamview) {
        view_mode = 6;
    }
    int fly_up = glfwGetKey(window, GLFW_KEY_SPACE);
    int fly_down = glfwGetKey(window, GLFW_KEY_S);
    if (fly_up) {
        airplane.move_up();
    }
    else if (fly_down) {
        airplane.move_down();
    }
    int accelerate = glfwGetKey(window, GLFW_KEY_W);
    if (accelerate) {
        airplane.move_forward();
    }
    else {
        airplane.stop();
    }
    int tiltleft = glfwGetKey(window, GLFW_KEY_A);
    int tiltright = glfwGetKey(window, GLFW_KEY_D);
    if (tiltleft) {
        airplane.roll(-1);
    }
    else if (tiltright) {
        airplane.roll(1);
    }
    else {
        airplane.roll(0);
    }
    int rotateccw = glfwGetKey(window, GLFW_KEY_Q);
    int rotatecw = glfwGetKey(window, GLFW_KEY_E);
    if (rotateccw) {
        airplane.yaw(1);
    }
    else if (rotatecw) {
        airplane.yaw(-1);
    }
    else {
        airplane.yaw(0);
    }
    int pitch_down = glfwGetKey(window, GLFW_KEY_Z);
    int pitch_up = glfwGetKey(window, GLFW_KEY_C);
    if (pitch_down) {
        airplane.pitch(1);
    }
    else if (pitch_up) {
        airplane.pitch(-1);
    }
    else {
        airplane.pitch(0);
    }
    reset_screen();
    int missile = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if(missile && register_input%4 == 0) {
        shoot_from_plane();
        printf("MISSILE\n");
    }
    int bomb = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if(bomb && register_input%8 == 0) {
        bomb_from_plane();
        printf("BOMB\n");
    }
}

// void tick_elements() {
//     // camera_rotation_angle += 1;
// }

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    airplane   = Airplane   (0, 0, 0, COLOR_GREEN);
    oceanfloor = Oceanfloor (0, -2.0f, 0, COLOR_OCEANBLUE);
    speedometer = Speedometer (-9.5f, -9.0f, 0, COLOR_RED);
    fuelometer = Fuelometer (-6.0f, -9.0f, 0, COLOR_RED, COLOR_YELLOW, COLOR_GREEN);
    altometer = Altometer (-9.5f, -5.5f, 0, COLOR_RED, COLOR_YELLOW, COLOR_GREEN);
    compass = Compass (6.0f, 6.0f, 0, COLOR_RED, COLOR_WHITE);
    arrow = Arrow (0, -10.0f, 0, COLOR_RED);
    generate_checkpoints();
    generate_defencetowers();
    generate_defencemissiles();
    generate_volcanos();
    generate_smokerings();
    generate_fuelups();
    generate_parachutes();
    generate_missiles();
    generate_bombs();

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    int register_input = 0;

    window = initGLFW(width, height);

    initGL (window, width, height);

    string title1 = "Health : ";
    string title2 = "Score : ";

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {

            ostringstream healthvalstream;
            ostringstream scorevalstream;
            healthvalstream << airplane.health;
            scorevalstream << airplane.points;
            string healthval = healthvalstream.str();
            string scoreval = scorevalstream.str();
            string title = title1 + healthval + "    " + title2 + scoreval;

            glfwSetWindowTitle(window, title.c_str());

            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            // tick_elements();
            register_input = (register_input+1)%200;
            tick_input(window, register_input);

            speedometer.set_angle(airplane.speed_z);
            compass.set_angle(airplane.rotation.y);
            airplane.fuel_left -= 0.3f;
            if(airplane.fuel_left <= 0){
            	quit(window);
            }
            captured_checkpoint();
            update_arrow();
            for (int i = 0; i < 15*4*number_of_checkpoints/10; i++) {
                defencemissile[i].move(defencetower[i/15].alive);
            }
            for (int i = 0; i < number_of_missiles; i++) {
                missiles[i].move();
            }
            for (int i = 0; i < number_of_bombs; i++) {
                bombs[i].move();
            }
            for (int i = 0; i < number_of_parachutes; i++) {
                parachutes[i].move(parachutes[i].alive);
            }
            if(collision_with_volcanos()){
            	quit(window);
            }
            if(collision_with_fuelups()){
            	airplane.fuel_left = 999.99f;
            }
            if(collision_with_parachutes()){
                airplane.points += 100;
            }
            if(collision_with_defencetowers()){
            	airplane.points += 20;
            }
            if(collision_with_defencemissiles()){
            	airplane.health--;
            	if(airplane.health == 0){
            		quit(window);
            	}
            }
            if(collision_with_smokerings()){
            	airplane.points += 100;
            }

            printf("Score : %d\n", airplane.points);
            printf("Health : %d\n", airplane.health);
            printf("%f %f %f\n", airplane.position.x, airplane.position.y, airplane.position.z);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, float x, float y, float z) {
	if(((a.x - x)*(a.x - x) + (a.y - y)*(a.y - y) + (a.z - z)*(a.z - z)) < (a.radius * a.radius))
		return true;
    return false;
}

void reset_screen() {
    float top    = screen_center_y + 4 / 0.3;
    float bottom = screen_center_y - 4 / 0.3;
    float left   = screen_center_x - 4 / 0.3;
    float right  = screen_center_x + 4 / 0.3;
    Matrices.projection = glm::perspective(60 * M_PI / 180.0, 1.0, 3.0, 1000.0);
    Matrices_ortho.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

void generate_checkpoints() {
    float x, z;
    int j;
    for (int i = 0; i < number_of_checkpoints; i+=10) {
        x = -200 + (rand() % 400);
        z = -200 + (rand() % 400);
        checkpoint_location[i/10][0] = x;
        checkpoint_location[i/10][1] = z;
        for (j = 0; j < 10; j++) {
            checkpoint[i+j] = Checkpoint(x, -2.0, z, COLOR_SANDYBROWN);
        }
    }
    checkpoint_iterator = 0;
    for (int i = 0; i < number_of_checkpoints/10; i++) {
        if(checkpoint_location[i][0] < 400 && checkpoint_location[i][0] > 0 &&  checkpoint_location[i][1] < 400 && checkpoint_location[i][1] > 0){
            checkpoint_iterator = i;
            break;
        }
    }
}

void generate_defencetowers() {
    float x, z;
    int j = 0;
    for (int i = 0; i < number_of_checkpoints/10; i++) {
        x = checkpoint_location[i][0];
        z = checkpoint_location[i][1];
        defencetower[j++] = Defencetower(x-4.0f, -2.0f, z-4.0f, COLOR_TOWER);
        defencetower[j++] = Defencetower(x-4.0f, -2.0f, z+4.0f, COLOR_TOWER);
        defencetower[j++] = Defencetower(x+4.0f, -2.0f, z-4.0f, COLOR_TOWER);
        defencetower[j++] = Defencetower(x+4.0f, -2.0f, z+4.0f, COLOR_TOWER);
    }
}

void generate_defencemissiles() {
	int k = 0;
    for (int i = 0; i < 4*number_of_checkpoints/10; i++) {
    	for(float j = 1.0; j <= 8.0; j+=0.5){
    		defencemissile[k++] = Defencemissile(defencetower[i].position.x, j, defencetower[i].position.z, COLOR_RED);
    	}
    }
}

void generate_volcanos() {
    float x, z;
    int j;
    for (int i = 0; i < number_of_volcanos; i+=10) {
        x = -2000 + (rand() % 4000);
        z = -2000 + (rand() % 4000);
        volcano_location[i/10][0] = x;
        volcano_location[i/10][1] = z;
        for (j = 0; j < 10; j++) {
            volcano[i+j] = Volcano(x, -2.0, z, COLOR_DARKBROWN, COLOR_LAVARED);
        }
    }
}

void generate_smokerings() {
    float x, y, z;
    for (int i = 0; i < number_of_smokerings; i++) {
        x = -2000 + (rand() % 4000);
        y = 0.5 + (rand() % 70) / 10.0f;
        z = -2000 + (rand() % 4000);
        smokerings[i] = Smokerings(x, y, z, COLOR_SMOKEGRAY);
    }
}

void generate_fuelups() {
    float x, y, z;
    for (int i = 0; i < number_of_fuelups; i++) {
        x = -2000 + (rand() % 4000);
        y = 0.5 + (rand() % 70) / 10.0f;
        z = -2000 + (rand() % 4000);
        fuelups[i] = Fuelup(x, y, z, COLOR_OILYELLOW);
    }
}

void generate_parachutes() {
    float x, y, z;
    for (int i = 0; i < number_of_parachutes; i++) {
        x = -2000 + (rand() % 4000);
        y = -2 + (rand() % 100) / 10.0f;
        z = -2000 + (rand() % 4000);
        parachutes[i] = Parachute(x, y, z, COLOR_RED);
    }
}

void generate_missiles() {
    for (int i = 0; i < number_of_missiles; i++) {
        missiles[i] = Missile(0.0f, -10.0, 0.0, COLOR_BLACK);
    }
    missile_iterator = 0;
}

void generate_bombs() {
    for (int i = 0; i < number_of_bombs; i++) {
        bombs[i] = Bombs(0.0f, -10.0, 0.0, COLOR_BLACK);
    }
    bomb_iterator = 0;
}

void shoot_from_plane() {
    missiles[missile_iterator].set_position(airplane.position.x, airplane.position.y, airplane.position.z, airplane.rotation.x, airplane.rotation.y, airplane.rotation.z);
    missile_iterator = (missile_iterator+1) % number_of_missiles;
}

void bomb_from_plane() {
    bombs[bomb_iterator].set_position(airplane.position.x, airplane.position.y, airplane.position.z, airplane.rotation.x, airplane.rotation.y, airplane.rotation.z);
    bomb_iterator = (bomb_iterator+1) % number_of_bombs;
}

void captured_checkpoint() {
	for (int i = 0; i < number_of_checkpoints/10; i++) {
		if(defencetower[4*i].alive == 0 && defencetower[4*i+1].alive == 0 && defencetower[4*i+2].alive == 0 && defencetower[4*i+3].alive == 0){
			checkpoint[10*i].claimed = 1;
		}
	}
}

void update_arrow() {
	if(defencetower[4*checkpoint_iterator].alive == 0 && defencetower[4*checkpoint_iterator+1].alive == 0 && defencetower[4*checkpoint_iterator+2].alive == 0 && defencetower[4*checkpoint_iterator+3].alive == 0){
		for (int i = 0; i < number_of_checkpoints/10; i++) {
	        if(checkpoint[10*i].claimed == 0 && (checkpoint_location[i][0] - airplane.position.x) < 100 && (checkpoint_location[i][0] - airplane.position.x) > -100 &&  (checkpoint_location[i][1] - airplane.position.z) < 100 && (checkpoint_location[i][1] - airplane.position.z) > -100){
	            checkpoint_iterator = i;
	            break;
	        }
        }
    }
    arrow.set_position(checkpoint[10*checkpoint_iterator].position.x, 4.0f, checkpoint[10*checkpoint_iterator].position.z);
}

bool collision_with_defencetowers() {
	float x, y, z;
	bounding_box_t box;
	box.radius = 0.75f;
	for(int j = 0; j < 4*number_of_checkpoints/10; j++){
		x = defencetower[j].position.x;
		y = defencetower[j].position.y;
		z = defencetower[j].position.z;
		for(float i = 0.5; i < 3.0; i+=0.5){
			y += 0.5;
			box.x = x;
			box.y = y;
			box.z = z;
			for(int k = 0; k < number_of_missiles; k++){
				if(detect_collision(box, missiles[k].position.x, missiles[k].position.y, missiles[k].position.z)){
					// printf("Tower destroyed : %d\n", j);
                    defencetower[j].alive = 0;
	        		missiles[k].set_position(0.0f, -10.0f, 0.0f, 0, 0, 0);
	        		defencetower[j].set_position(0, -10, 0);
					return true;
				}
			}
			for(int k = 0; k < number_of_bombs; k++){
				if(detect_collision(box, bombs[k].position.x, bombs[k].position.y, bombs[k].position.z)){
	        		// printf("Tower destroyed : %d\n", j);
                    defencetower[j].alive = 0;
	        		bombs[k].set_position(0, -10, 0, 0, 0, 0);
	        		defencetower[j].set_position(0, -10, 0);
					return true;
				}
			}
		}
	}
	return false;
}

bool collision_with_parachutes() {
    float x, y, z;
    bounding_box_t box;
    box.radius = 0.3f;
    for(int j = 0; j < number_of_parachutes; j++){
        x = parachutes[j].position.x;
        y = parachutes[j].position.y + 0.3;
        z = parachutes[j].position.z;
        for(int k = 0; k < number_of_missiles; k++){
                if(detect_collision(box, missiles[k].position.x, missiles[k].position.y, missiles[k].position.z)){
                    missiles[k].set_position(0.0f, -10.0f, 0.0f, 0, 0, 0);
                    parachutes[j].set_position(0, -10, 0);
                    parachutes[j].alive = 0;
                    return true;
                }
            }
    }
    return false;
}


bool collision_with_smokerings() {
	float x, y, z;
	bounding_box_t box;
	box.radius = 1.0f;
	for(int j = 0; j < number_of_smokerings; j++){
		x = airplane.position.x;
		y = airplane.position.y;
		z = airplane.position.z;
		for(float i = 0.5; i < 6.0; i+=0.5){
			y += (1.0 * sin(airplane.rotation.x * M_PI / 180.0f));
			z += (1.0 * cos(airplane.rotation.x * M_PI / 180.0f) * cos(airplane.rotation.y * M_PI / 180.0f));
			x += (1.0 * cos(airplane.rotation.x * M_PI / 180.0f) * sin(airplane.rotation.y * M_PI / 180.0f));
			box.x = x;
			box.y = y;
			box.z = z;
			if(detect_collision(box, smokerings[j].position.x, smokerings[j].position.y, smokerings[j].position.z)){
				x = -2000 + (rand() % 4000);
       			y = 0.5 + (rand() % 70) / 10.0f;
        		z = -2000 + (rand() % 4000);
        		smokerings[j].set_position(x, y, z);
				return true;
			}
		}
	}
	return false;
}

bool collision_with_fuelups() {
	float x, y, z;
	bounding_box_t box;
	box.radius = 1.0f;
	for(int j = 0; j < number_of_fuelups; j++){
		x = airplane.position.x;
		y = airplane.position.y;
		z = airplane.position.z;
		for(float i = 0.5; i < 6.0; i+=0.5){
			y += (1.0 * sin(airplane.rotation.x * M_PI / 180.0f));
			z += (1.0 * cos(airplane.rotation.x * M_PI / 180.0f) * cos(airplane.rotation.y * M_PI / 180.0f));
			x += (1.0 * cos(airplane.rotation.x * M_PI / 180.0f) * sin(airplane.rotation.y * M_PI / 180.0f));
			box.x = x;
			box.y = y;
			box.z = z;
			if(detect_collision(box, fuelups[j].position.x, fuelups[j].position.y, fuelups[j].position.z)){
				x = -2000 + (rand() % 4000);
       		 	y = 0.5 + (rand() % 70) / 10.0f;
        		z = -2000 + (rand() % 4000);
        		fuelups[j].set_position(x, y, z);
				return true;
			}
		}
	}
	return false;
}

bool collision_with_volcanos() {
	float x, y, z;
	bounding_box_t box;
	box.radius = 1.0f;
	for(int j = 0; j < number_of_volcanos/10; j++){
		x = airplane.position.x;
		y = airplane.position.y;
		z = airplane.position.z;
		for(float i = 0.5; i < 6.0; i+=0.5){
			y += (0.5 * sin(airplane.rotation.x * M_PI / 180.0f));
			z += (0.5 * cos(airplane.rotation.x * M_PI / 180.0f) * cos(airplane.rotation.y * M_PI / 180.0f));
			x += (0.5 * cos(airplane.rotation.x * M_PI / 180.0f) * sin(airplane.rotation.y * M_PI / 180.0f));
			if(((volcano[10*j].position.x - x)*(volcano[10*j].position.x - x) + (volcano[10*j].position.z - z)*(volcano[10*j].position.z - z)) < 55.0) {
				return true;
			}
		}
	}
	return false;
}

bool collision_with_defencemissiles() {
	float x, y, z;
	bounding_box_t box;
	box.radius = 1.0f;
	for(int j = 0; j < 15*4*number_of_checkpoints/10; j++){
		x = airplane.position.x;
		y = airplane.position.y;
		z = airplane.position.z;
		for(float i = 0.5; i < 6.0; i+=0.5){
			y += (1.0 * sin(airplane.rotation.x * M_PI / 180.0f));
			z += (1.0 * cos(airplane.rotation.x * M_PI / 180.0f) * cos(airplane.rotation.y * M_PI / 180.0f));
			x += (1.0 * cos(airplane.rotation.x * M_PI / 180.0f) * sin(airplane.rotation.y * M_PI / 180.0f));
			box.x = x;
			box.y = y;
			box.z = z;
			if(detect_collision(box, defencemissile[j].position.x, defencemissile[j].position.y, defencemissile[j].position.z)){
				return true;
			}
		}
	}
	return false;
}