#ifndef SCREEN_H_
#define SCREEN_H_

#include <array>
#include <vector>
#include <map>

#include "color.h"
#include "body.h"
#include "vec2.h"

class screen
{
public:
    int width;
    int height;
    int trail_length;
    Vec2 center;

private:
    unsigned int vbo;
    float world_width;
    float world_height;
    std::vector<Vertex> vertex_buffer;
    std::vector<float> pixel_buffer;
    bool reset_pixels = false;

public:
    screen();
    ~screen();

public:
    void set_dimensions(int width, int height);
    void draw(std::vector<Body>);
    void set_vbo_buffer();
    void reset_pixel(int i);
    void reset_all_pixels();
    void reset_all_pixels_async();
    void fade_all_pixels();
private:
    void draw_vertices();
};

#endif /* SCREEN_H_ */
