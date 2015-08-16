#include <heman.h>
#include "hut.h"

#define COUNT(a) (sizeof(a) / sizeof(a[0]))
#define OUTFOLDER "build/"
#define HEIGHT 256

static int CP_LOCATIONS[] = {
    000,  // Dark Blue
    126,  // Light Blue
    127,  // Yellow
    150,  // Dark Green
    170,  // Brown
    200,  // Brown
    240,  // White
    255,  // White
};

static heman_color CP_COLORS[] = {
    0x001070,  // Dark Blue
    0x2C5A7C,  // Light Blue
    0xE0F0A0,  // Yellow
    0x5D943C,  // Dark Green
    0x606011,  // Brown
    0x606011,  // Brown
    0xFFFFFF,  // White
    0xFFFFFF,  // White
};

static float LIGHTPOS[] = {-0.5f, 0.5f, 1.0f};

heman_image* make_planet(int seed, heman_image* grad)
{
    heman_image* hmap = heman_generate_planet_heightmap(HEIGHT * 2, HEIGHT, seed);
    heman_image* albedo = heman_color_apply_gradient(hmap, -0.5, 0.5, grad);
    heman_image* planet =
        heman_lighting_apply(hmap, albedo, 1, 1, 0.75, LIGHTPOS);
    heman_image_destroy(hmap);
    heman_image_destroy(albedo);
    return planet;
}

int main(int argc, char** argv)
{
    heman_image* grad = heman_color_create_gradient(
        256, COUNT(CP_COLORS), CP_LOCATIONS, CP_COLORS);
    heman_image* tiles[2];
    tiles[0] = make_planet(1000, grad);
    tiles[1] = make_planet(1001, grad);
    heman_image* planets = heman_ops_stitch_vertical(tiles, 2);
    heman_image_destroy(tiles[0]);
    heman_image_destroy(tiles[1]);
    hut_write_image(OUTFOLDER "planets.png", planets, 0, 1);
    heman_image_destroy(planets);
    heman_image_destroy(grad);
}
