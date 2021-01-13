#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>

#include "screen.h"

const int DEFAULT_WIDTH = 800;
const int DEFAULT_HEIGHT = 800;
const int DIMENSION = 2;
const int COLOR_DIMENSION = 4;
const int PIXEL_ENTRY_SIZE = DIMENSION + COLOR_DIMENSION;
const int DEFAULT_TRAIL_LENGTH = 20;

screen::screen()
{
    this->width = DEFAULT_WIDTH;
    this->height = DEFAULT_HEIGHT;
    this->world_height = (float) this->height / 10.0;
    this->world_width = (float) this->width / 10.0;
    this->trail_length = DEFAULT_TRAIL_LENGTH;
    this->center = Vec2(this->width / 2, this->height / 2);
}

screen::~screen()
{
    glDeleteBuffers(1, &(this->vbo));
}

void screen::set_dimensions(int width, int height)
{
    this->width = width;
    this->height = height;
}

void screen::set_vbo_buffer()
{
    glGenBuffers(1, &(this->vbo));
}

void screen::draw(std::vector<Body> bodies)
{

    glPointSize(1.0);

    if (this->reset_pixels)
    {
        this->reset_all_pixels();
        this->reset_pixels = false;
    }

    for (Body body : bodies)
    {
        this->pixel_buffer.push_back(body.position.x);
        this->pixel_buffer.push_back(body.position.y);
        this->pixel_buffer.push_back(body.color.red);
        this->pixel_buffer.push_back(body.color.green);
        this->pixel_buffer.push_back(body.color.blue);
        this->pixel_buffer.push_back(body.color.alpha);
    }

    draw_vertices();
}

void screen::reset_pixel(int i)
{
    std::vector<float>::iterator pixel_buffer_iter = this->pixel_buffer.begin() + i * (PIXEL_ENTRY_SIZE);
    this->pixel_buffer.erase(pixel_buffer_iter, pixel_buffer_iter + PIXEL_ENTRY_SIZE);
}

void screen::reset_all_pixels()
{
    this->pixel_buffer.clear();
}

void screen::reset_all_pixels_async()
{
    this->reset_pixels = true;
}

void screen::fade_all_pixels()
{
    std::vector<int> trash;
    for (size_t i = 0; i < this->pixel_buffer.size(); i+= PIXEL_ENTRY_SIZE)
    {
        this->pixel_buffer.at(i + 2) -= 1.0 / this->trail_length;
        this->pixel_buffer.at(i + 3) -= 1.0 / this->trail_length;
        this->pixel_buffer.at(i + 4) -= 1.0 / this->trail_length;

        if (this->pixel_buffer.at(i + 2) < 0 && this->pixel_buffer.at(i + 3) < 0 && this->pixel_buffer.at(i + 4) < 0)
        {
            trash.push_back(i);
        }
    }

    for (int i : trash)
    {
        reset_pixel(i);
    }
}

void screen::draw_vertices()
{
    const int array_size = pixel_buffer.size();

    /* Bind buffer and copy data to GPU. */
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, array_size * sizeof(float), pixel_buffer.data(), GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    /* Tell the GPU that this is the correct format. */
    glVertexPointer(DIMENSION, GL_FLOAT, PIXEL_ENTRY_SIZE * sizeof(float), 0);
    glColorPointer(COLOR_DIMENSION, GL_FLOAT, PIXEL_ENTRY_SIZE * sizeof(float), (void*)(DIMENSION * sizeof(float)));
    /* Draw using DrawArrays. */
    glDrawArrays(GL_POINTS, 0, array_size / DIMENSION);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    /* Unbind buffer. */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}