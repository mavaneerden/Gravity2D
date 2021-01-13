#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

#include "screen.h"
#include "body.h"
#include "mouse.h"

screen s;
MouseState mouse;
std::vector<Body> bodies;
Vec2 centerBodyVelocity = Vec2::zero;
Vec2 centerBodyPosition = Vec2::zero;
int centerBodyIndex = -1;
int time_passed = 0;
int trail_timer = 0;
bool paused = false;

void changeCenter()
{
    s.reset_all_pixels_async();
    trail_timer = 0;
}

void increaseCenterIndex()
{
    centerBodyIndex = centerBodyIndex < (int) bodies.size() - 1 ? centerBodyIndex + 1 : -1;
    changeCenter();
}

void decreaseCenterIndex()
{
    centerBodyIndex = centerBodyIndex > -1 ? centerBodyIndex - 1 : bodies.size() - 1;
    changeCenter();
}

void do_pysics()
{
    for (size_t i = 0; i < bodies.size(); i++)
    {
        bodies[i].timeStepStart(bodies);
    }

    for (size_t i = 0; i < bodies.size(); i++)
    {
        bodies[i].calculateVelocity();
    }

    centerBodyVelocity = centerBodyIndex >= 0 ? bodies[centerBodyIndex].velocity : Vec2::zero;
    centerBodyPosition = centerBodyIndex >= 0 ? bodies[centerBodyIndex].position - s.center : Vec2::zero;

    for (size_t i = 0; i < bodies.size(); i++)
    {
        bodies[i].velocity = bodies[i].velocity - centerBodyVelocity;
        bodies[i].calculatePosition();
        bodies[i].velocity = bodies[i].velocity + centerBodyVelocity;
        bodies[i].position = bodies[i].position - centerBodyPosition;
    }
}

void bodies_after_draw()
{
    for (size_t i = 0; i < bodies.size(); i++)
    {
        bodies[i].position = bodies[i].position + centerBodyPosition;
    }

}

void draw()
{
    if (!paused)
    {
        /* Set to background color and clear. */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        s.fade_all_pixels();

        do_pysics();
        s.draw(bodies);
        bodies_after_draw();

        glutSwapBuffers();
        time_passed++;
        trail_timer++;

        if (trail_timer > s.trail_length) {
            for (size_t i = 0; i < bodies.size(); i++)
            {
                s.reset_pixel(i);
            }

        }
    }
}

void resize_window(int width, int height)
{
    glViewport(0, 0, width, height);
    s.set_dimensions(width, height); // TODO: keep aspect ratio
}

void initialize_bodies()
{
    /* Two moons */
    bodies.push_back(Body(33.3, Vec2(s.width / 2, s.height / 2)));
    bodies[0].color = Color(1, 1, 0);
    bodies.push_back(Body(0.1, Vec2(s.width / 2, s.height / 6)));
    bodies.push_back(Body(0.00003, Vec2(s.width / 2, bodies[1].position.y - 2)));
    bodies.push_back(Body(0.00002, Vec2(s.width / 2, bodies[1].position.y - 5)));
    bodies.push_back(Body(0.00001, Vec2(s.width / 2, bodies[1].position.y - 8)));
    bodies[1].setCircularVelocity(bodies[0]);
    bodies[2].setCircularVelocity(bodies[1]);
    bodies[3].setCircularVelocity(bodies[1]);
    bodies[4].setCircularVelocity(bodies[1]);
    bodies[1].color = Color(0.0, 0.0, 1.0);
    bodies[2].color = Color(1.0, 0.0, 0.0);
    bodies[3].color = Color(0.0, 1.0, 0.0);
    bodies[4].color = Color(1.0, 0.0, 1.0);

    /* Double planet */
    // bodies.push_back(Body(33.3, Vec2(s.width / 2, s.height / 2)));
    // bodies[0].color = Color(1, 1, 0);
    // bodies.push_back(Body(0.1, Vec2(s.width / 2, s.height / 4)));
    // bodies.push_back(Body(0.1, Vec2(s.width / 2, s.height / 4 - 10)));
    // bodies[1].setCircularVelocity(bodies[0]);
    // bodies[2].setCircularVelocity(bodies[1]);

    /* Gravity Slowdown */
    // bodies.push_back(Body(100, Vec2(s.width, s.height / 2), Vec2(-4.5, 0)));
    // bodies.push_back(Body(0.01, Vec2(s.width, 0), Vec2(-5, 5)));

    /* Gravity Assist */
    // bodies.push_back(Body(100, Vec2(s.width, s.height / 2), Vec2(-5.35, 0)));
    // bodies.push_back(Body(0.01, Vec2(s.width, 0), Vec2(-5, 5)));

    // /* Solar System */
    // double dist_earth = 200;
    // double mass_earth = 0.001;
    // // Sol
    // bodies.push_back(Body(33.3, Vec2(s.width / 2, s.height / 2)));
    // bodies[0].color = Color(1, 1, 0);
    // // Terra
    // bodies.push_back(Body(mass_earth, Vec2(s.width / 2, s.height / 2 - dist_earth)));
    // Vec2 vel_earth = bodies[1].getCircularVelocity(bodies[0]);
    // bodies[1].velocity = vel_earth;
    // bodies[1].color = Color(0.2, 0.5, 1);
    // // Mercurius
    // bodies.push_back(Body(0.0553 * mass_earth, Vec2(s.width / 2, s.height / 2 - 0.387 * dist_earth), vel_earth * 1.59));
    // bodies[2].color = Color(0.6, 0.6, 0.6);
    // // Venus
    // bodies.push_back(Body(0.815 * mass_earth, Vec2(s.width / 2, s.height / 2 - 0.723 * dist_earth), vel_earth * 1.18));
    // bodies[3].color = Color(1, 0.8, 0.2);
    // // Luna
    // bodies.push_back(Body(0.0123 * mass_earth, Vec2(s.width / 2, s.height / 2 - dist_earth - 0.009 * dist_earth)));
    // bodies[4].setCircularVelocity(bodies[1]);
    // bodies[4].color = Color(0.8, 0.8, 0.8);
    // // Mars
    // bodies.push_back(Body(0.107 * mass_earth, Vec2(s.width / 2, s.height / 2 - 1.52 * dist_earth), vel_earth * 0.808));
    // bodies[5].color = Color(1, 0.2, 0.2);
}

void initialize()
{
    s.set_vbo_buffer();
    initialize_bodies();
    s.trail_length = 100;
}

void special_key_pressed(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        decreaseCenterIndex();
        break;
    case GLUT_KEY_RIGHT:
        increaseCenterIndex();
        break;
    default:
        break;
    }
}

void key_pressed(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        paused = !paused;
        break;
    default:
        break;
    }
}

void mouse_clicked(int button, int state, int x, int y)
{
    mouse.changeState(button, state);
}

void mouse_moved(int x, int y)
{
    mouse.changePosition(x, y);
}

int main(int argc, char *argv[])
{
    /* Create an OpenGL context and a GLUT window. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(s.width, s.height);
    glutCreateWindow("Gravity2D");

    glewInit();

    /* Bind all GLUT events do callback function. */
    glutDisplayFunc(&draw);
    glutIdleFunc(&draw);
    glutReshapeFunc(&resize_window);
    glutKeyboardFunc(&key_pressed);
    glutSpecialFunc(&special_key_pressed);
    glutMouseFunc(&mouse_clicked);
    glutMotionFunc(&mouse_moved);
    glutPassiveMotionFunc(&mouse_moved);

    /* Initialize the matrices so we have an orthogonal world with the same size
     * as the levels, and no other transformations.
     */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, s.width, 0, s.height, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    initialize();

    glutMainLoop();

    return 0;
}
