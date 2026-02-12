#ifndef util_h
#define util_h

#include <cmath>
#include <memory>
#include <iostream>
#include <limits>
#include <random>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


// util

inline double degrees_to_rads(double deg) { // use inline to prevent linkage errors
    return deg * (pi / 180.0);
}

inline double random_uniform_dist_num() {
    // [0, 1)
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    static std::mt19937 gen;
    return dist(gen);
}

inline double random_uniform_dist_num(double min, double max) {
    return min + (max - min) * random_uniform_dist_num();
}

inline double random_int(double min, double max) {
    return int(random_uniform_dist_num(min, max + 1));
}

#include "utils/color.h"
#include "math/ray.h"
#include "math/vec3.h"
#include "math/interval.h"

#endif 