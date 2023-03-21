#include <vector>
#include <utility>
#include <iostream>

class Poly{
    private:
        std::vector<double> koef;
        void del_zeros();
        std::pair<Poly, Poly> dividing(const Poly &other) const;
    public:
        Poly();
        Poly(const std::vector<double> elems);
        Poly(const float *arr, unsigned n);
        Poly(const double *arr, unsigned n);
        Poly(std::initializer_list<float> elems);
        Poly(std::initializer_list<double> elems);
        Poly(const Poly &other);
        Poly(Poly &&other);
        Poly &operator=(const Poly &another);
        Poly &operator=(Poly &&another);
        ~Poly();
        const double operator[](int index) const;
        double &operator[](int index);
        double at(unsigned int index);
        Poly operator+() const;
        Poly operator-() const;

        Poly operator+(const Poly &other) const;
        Poly operator-(const Poly &other) const;
        Poly operator*(const Poly &other) const;
        Poly operator/(const Poly &other) const;
        Poly operator%(const Poly &other) const;

        Poly operator+=(const Poly &other);
        Poly operator-=(const Poly &other);
        Poly operator*=(const Poly &other);
        Poly operator/=(const Poly &other);
        Poly operator%=(const Poly &other);

        bool operator==(const Poly &other) const;
        bool operator!=(const Poly &other) const;
        operator std::string() const;
        friend std::ostream &operator<<(std::ostream &out, const Poly &poly); 
        int degree() const;
        double evaluate(double x) const;
};
inline bool isEqual(double a, double b, double epsilon = 0.000001){
    return abs(a - b) < epsilon;
}
