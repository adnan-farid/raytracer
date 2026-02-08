#ifndef vec3_h
#define vec3_h

class vec3 {
public:
    double vec[3];
    vec3(): vec{0,0,0} {}; //default constructor
    vec3(double x1, double x2, double x3) : vec{x1,x2,x3} {};

    double x() const {return vec[0];}
    double y() const {return vec[1];}
    double z() const {return vec[2];}

    vec3 operator-() const {return vec3(-vec[0], -vec[1], -vec[2]);}
    double operator[](int i) const { return vec[i]; } // no reference because this is read only
    double& operator[] (int i) { return vec[i]; } // referenced because read/write


    //TODO: implement *, +, -, /, +=, -=, /=, *=
    vec3& operator+=(const double num) {
        vec[0] = vec[0] + num;
        vec[1] = vec[1] + num;
        vec[2] = vec[2] + num;
        return *this; // must return dereferenced object, this is a pointer
    }

    vec3& operator+=(const vec3 otherVec) {
        vec[0] = vec[0] + otherVec[0];
        vec[1] = vec[1] + otherVec[1];
        vec[2] = vec[2] + otherVec[2];
        return *this; // must return dereferenced object, this is a pointer
    }

    vec3& operator-=(const double num) {
        vec[0] = vec[0] - num;
        vec[1] = vec[1] - num;
        vec[2] = vec[2] - num;
        return *this;
    }

    vec3& operator*=(const double num) {
        vec[0] = vec[0] * num;
        vec[1] = vec[1] * num;
        vec[2] = vec[2] * num;
        return *this;
    }

    vec3& operator/=(const double num) {
        vec[0] = vec[0] / num;
        vec[1] = vec[1] / num;
        vec[2] = vec[2] / num;
        return *this;
    }

    double length_squared() const {
        return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    static vec3 random() {
        return vec3(random_uniform_dist_num(), random_uniform_dist_num(), random_uniform_dist_num());
    }

    static vec3 random(double min, double max) {
        return vec3(random_uniform_dist_num(min, max), random_uniform_dist_num(min, max), random_uniform_dist_num(min, max));
    }

};


vec3 operator*(const vec3& firstVec, const vec3& otherVec) { //component wise multiply 
    return vec3(firstVec[0] * otherVec[0], firstVec[1] * otherVec[1], firstVec[2] * otherVec[2]);
}

vec3 operator*(const vec3& v, double num) {
    return vec3(v[0] * num, v[1] * num, v[2] * num);
}

vec3 operator*(double num, const vec3& v) {
    return v * num;
}

vec3 operator+(const vec3& firstVec, const vec3& otherVec) {
    return vec3(firstVec[0] + otherVec[0], firstVec[1] + otherVec[1], firstVec[2] + otherVec[2]);
}

vec3 operator+(const vec3& vec, const double num) {
    return vec3(vec[0] + num, vec[1] + num, vec[2] + num);
}

vec3 operator-(const vec3& firstVec, const vec3& otherVec) {
    return vec3(firstVec[0] - otherVec[0], firstVec[1] - otherVec[1], firstVec[2] - otherVec[2]);
}

vec3 operator-(const vec3& vec, const double num) {
    return vec3(vec[0] - num, vec[1] - num, vec[2] - num);
}

vec3 operator/(const vec3& firstVec, const vec3& otherVec) {
    return vec3(firstVec[0] / otherVec[0], firstVec[1] / otherVec[1], firstVec[2] / otherVec[2]);
}

vec3 operator/(const vec3& vec, const double num) {
    return vec3(vec[0] / num, vec[1] / num, vec[2] / num);
}

std::ostream& operator<<(std::ostream& output_stream, const vec3& vector_to_write) {
    output_stream << vector_to_write.x() << ' ' << vector_to_write.y() << ' ' << vector_to_write.z() << '\n';
    return output_stream;
}

vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

vec3 random_unit_vector() {
    while (true) {
        vec3 rand = vec3::random();
        double length_sq = rand.length_squared();
        if (1e-160 < length_sq && length_sq <= 1) { return rand / length_sq; } // degeneracy if vector is close to center of sphere
    }
}

double dot(const vec3& firstVec, const vec3& secondVec) {
    return (firstVec.x() * secondVec.x() + firstVec.y() * secondVec.y() + firstVec.z() * secondVec.z());
}

vec3 random_on_hemisphere(const vec3& normal) {
    vec3 rand = vec3::random();
    if (dot(normal, rand) < 0.0) {
        return -rand;
    }
    return rand;
}


#endif