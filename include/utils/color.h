#ifndef color_h
#define color_h


#include "math/interval.h"
#include "math/vec3.h"

using color = vec3;


double linear_to_gamma(double linear_component) {
    if (linear_component > 0) {
        return std::sqrt(linear_component);
    } 

    return 0;
}


void writeSinglePixel(std::ostream& out, const vec3& pixel_col) {
    double r = pixel_col.x();
    double g = pixel_col.y();
    double b = pixel_col.z();

    r =  linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);
    // [0,1] -> [0, 255]
    static const Interval intensity(0.000, 0.999);

    int r_norm = int(256 * intensity.clamp(r));
    int g_norm = int(256 * intensity.clamp(g));
    int b_norm = int(256 * intensity.clamp(b));


    std::cout << r_norm << ' ' << g_norm << ' ' <<  b_norm << '\n';
}

#endif