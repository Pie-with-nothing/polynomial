#include "polychlen.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <utility>
#include <sstream>

Poly::Poly(){
    this->koef = {0.};
}
Poly::Poly(const std::vector<double> elems){
    this->koef = elems;
    this->del_zeros();
}
Poly::Poly(const double *arr, unsigned n){
    if(arr == nullptr || n == 0){
        throw std::invalid_argument(
            "Array pointer can't be nullptr or have 0 length"
        );
    }
    for(int i = 0; i < n; i++){
        this->koef.push_back(arr[i]);
    }
    this->del_zeros();
}
Poly::Poly(const float *arr, unsigned n){
    if(arr == nullptr || n == 0){
        throw std::invalid_argument(
            "Array pointer can't be nullptr or have 0 length"
        );
    }
    for(int i = 0; i < n; i++){
        this->koef.push_back(arr[i]);
    }
    this->del_zeros();
}
Poly::Poly(std::initializer_list<float> elems){
    for(float i : elems) {
        this->koef.push_back(i);
    }
    this->del_zeros();
}
Poly::Poly(std::initializer_list<double> elems){
    for(double i : elems) {
        this->koef.push_back(i);
    }
    this->del_zeros();
}
Poly::Poly(const Poly &other){
    this->koef = other.koef;
}
Poly::Poly(Poly &&other){
    this->koef = move(other.koef);
}
Poly &Poly::operator=(const Poly &another){
    if(this != &another) {
        this->koef = another.koef;
    }
    return *this;
}
Poly &Poly::operator=(Poly &&another){
    this->koef = move(another.koef);
    return *this;
}
Poly::~Poly(){
    this->koef.clear();
}
void Poly::del_zeros(){
    for(int i = this->degree() - 1; i >= 0; i--){
        if(!isEqual(i, 0)){
            break;
        }
        else{
            this->koef.pop_back();
        }
    }
    if(this->koef.empty()){
        this->koef.push_back(0.);
    }
}
std::pair<Poly, Poly> Poly::dividing(const Poly &other) const{
    if(other == Poly()) {
        throw std::runtime_error("Division by zero");
    }
    std::vector<double> quotient(this->degree() - other.degree() + 1);
    std::vector<double> remainder(this->koef);
    for(int i = this->degree() - other.degree(); i >= 0; i--) {
        quotient[i] = remainder[i + other.degree()] / other[other.degree()];
        for(int j = 0; j <= other.degree(); j++) {
            remainder[i + j] -= quotient[i] * other[j];
        }
    }
    while(remainder.size() > 0 && isEqual(remainder.back(), 0)) {
        remainder.pop_back();
    }
    return std::make_pair(Poly(quotient), Poly(remainder));
}
int Poly::degree() const{
    return this->koef.size() - 1;
}
double Poly::evaluate(double x) const{
    double result = 0;
    for (int i = degree(); i >= 0; i--) {
        result = result * x + this->koef[i];
    }
    return result;
}
const double Poly::operator[](int index) const{
    if(index < 0 || index > degree()){
        throw std::out_of_range("Index out of range");
    }
    return this->koef[index];
}
double &Poly::operator[](int index){
    if(index < 0){
        throw std::out_of_range("Index out of range");
    }
    else if(index > degree()){
        this->koef.resize(index + 1, 0);
    }
    return this->koef[index];
}
double Poly::at(unsigned int index){
    return this->koef.at(index);
}
Poly Poly::operator+() const{
    return Poly(*this);
}
Poly Poly::operator-() const{
    return Poly() - *this;
}
Poly Poly::operator+(const Poly &other) const{
    std::vector<double> result(std::max(this->degree(), other.degree()) + 1);
    for(int i = 0; i <= degree(); i++){
        result[i] += this->koef[i];
    }
    for(int i = 0; i <= other.degree(); i++){
        result[i] += other[i];
    }
    return Poly(result);
}
Poly Poly::operator-(const Poly &other) const{
    std::vector<double> result(std::max(this->degree(), other.degree()) + 1);
    for(int i = 0; i <= degree(); i++){
        result[i] += this->koef[i];
    }
    for(int i = 0; i <= other.degree(); i++){
        result[i] -= other[i];
    }
    return Poly(result);
}
Poly Poly::operator*(const Poly &other) const{
    std::vector<double> result(this->degree() + other.degree() + 1);
    for(int i = 0; i <= this->degree(); i++) {
        for(int j = 0; j <= other.degree(); j++) {
            result[i+j] += this->koef[i] * other[j];
        }
    }
    return Poly(result);
}
Poly Poly::operator/(const Poly &other) const{
    return this->dividing(other).first;
}
Poly Poly::operator%(const Poly &other) const{
    return this->dividing(other).second;
}
Poly Poly::operator+=(const Poly &other){
	*this = *this + other;
	return *this;
}
Poly Poly::operator-=(const Poly &other){
	*this = *this - other;
	return *this;
}
Poly Poly::operator*=(const Poly &other){
	*this = *this * other;
	return *this;
}
Poly Poly::operator/=(const Poly &other){
	*this = *this / other;
	return *this;
}
Poly Poly::operator%=(const Poly &other){
	*this = *this % other;
	return *this;
}
bool Poly::operator==(const Poly &other) const{
    if(this->degree() != other.degree()){
       return false;
    }
    for(int i = 0; i < this->degree(); i++){
        if(!isEqual(this->koef[i], other.koef[i])){
            return false;
        } 
    }
    return true;
}
bool Poly::operator!=(const Poly &other) const{
    return !(*this == other);
}
Poly::operator std::string() const{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}
std::ostream &operator<<(std::ostream &os, const Poly &poly){
    for(int i = poly.degree(); i >= 0; i--){
        if(isEqual(poly.koef[i], 0) && i != 0){
            continue;
        }
        else if(!isEqual(poly.koef[i], 1) || i == 0){
            os << poly.koef[i];
        }
        switch(i){
            case 0:
                break;
            case 1:
                os << "x";
                break;
            default:
                os << "x^" << i;
                break;
        }
        if(i != 0){
            os << " + ";
        }
    }
    return os;
}