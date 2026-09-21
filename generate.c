#include "generate.h"

#include <stdio.h>
#include <stdlib.h>

#define POS_RANGE 1.0f
#define VEL_RANGE 0.1f
#define MASS_MIN 1.0f
#define MASS_MAX 10.0f

static float rand_range(float min, float max) {
    return min + (max - min) * ((float) rand() / (float) RAND_MAX);
}

Particle *generate_bodies(unsigned int N, unsigned int seed) {
    Particle *p = malloc(N * sizeof(Particle));
    if (p == NULL) {
        fprintf(stderr, "Error: could not allocate memory for %u particles\n", N);
        exit(1);
    }

    srand(seed);

    for (unsigned int i = 0; i < N; i++) {
        p[i].x = rand_range(-POS_RANGE, POS_RANGE);
        p[i].y = rand_range(-POS_RANGE, POS_RANGE);
        p[i].z = rand_range(-POS_RANGE, POS_RANGE);

        p[i].x_old = p[i].x;
        p[i].y_old = p[i].y;
        p[i].z_old = p[i].z;

        p[i].vx = rand_range(-VEL_RANGE, VEL_RANGE);
        p[i].vy = rand_range(-VEL_RANGE, VEL_RANGE);
        p[i].vz = rand_range(-VEL_RANGE, VEL_RANGE);

        p[i].ax = 0;
        p[i].ay = 0;
        p[i].az = 0;

        p[i].mass = rand_range(MASS_MIN, MASS_MAX);
    }

    return p;
}
