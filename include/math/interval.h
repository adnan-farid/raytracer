#ifndef interval_h
#define interval_h

class Interval {
public:
    Interval() : min(-infinity), max(+infinity) {};
    Interval(double min, double max) : min(min), max(max) {};

    Interval(const Interval& a, const Interval&b) {
        min = a.min <= b.min ? a.min : b.min;
        max = a.max >= b.max ? a.max : b.max;
    }

    double size() const {
        return (max - min);
    }

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    double clamp(double x) const {
        if (x < min) { return min; };
        if (x > max) { return max; };
        return x;
    }

    Interval pad(double amt) {
        double padding = amt / 2;
        return Interval(min - padding, max + padding);
    }



    static const Interval empty, universe;



    double min;
    double max;
};

inline const Interval Interval::empty = Interval(+infinity, -infinity); // no number can ever match
inline const Interval Interval::universe = Interval(-infinity, +infinity);

#endif