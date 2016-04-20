#ifndef __RAYTRACING_H
#define __RAYTRACING_H

#include "objects.h"
#include <stdint.h>

typedef struct ray {
    uint8_t *pixels;
    double *background_color;
    rectangular_node rectangulars;
    sphere_node spheres;
    light_node lights;
    const viewpoint *view;
    int width;
    int height;
    int tid;
    int tnum;
} rays;

rays *new_rays(uint8_t *pixels, color background_color,rectangular_node retangular,sphere_node spheres,light_node lights,const viewpoint *view,int width,int height,int tid,int tnum);

void raytracing(void *r);
#endif
