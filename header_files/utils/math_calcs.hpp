#include <cmath>
class MathCalcs {
    public:

    static double euclideanDistance(double *v1, double *v2) {
        double d = 0.0;
        int n = sizeof(v1);
        for(int i = 0; i < n; i++) {
            d += (v1[i] - v2[i]) * (v1[i] - v2[i]);
        }
        return sqrt(d);
    }
};