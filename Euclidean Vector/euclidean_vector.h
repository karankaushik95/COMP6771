#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <algorithm>
#include <cassert>
#include <cmath>
#include <exception>
#include <list>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

class EuclideanVectorError : public std::exception
{
public:
    explicit EuclideanVectorError(const std::string &what) : what_(what) {}
    const char *what() const noexcept { return what_.c_str(); }

private:
    std::string what_;
};

class EuclideanVector
{
public:
    // Constructors
    explicit EuclideanVector(int size);
    explicit EuclideanVector(double value);
    explicit EuclideanVector(int size, double value);
    EuclideanVector(std::vector<double>::const_iterator, std::vector<double>::const_iterator);
    EuclideanVector(const EuclideanVector &);
    EuclideanVector(EuclideanVector &&) noexcept;
    // Destructor
    ~EuclideanVector() noexcept;
    // functions
    double at(int) const;
    double &at(int);
    int GetNumDimensions();
    int GetNumDimensions() const;
    double GetEuclideanNorm();
    double GetEuclideanNorm() const;
    EuclideanVector CreateUnitVector();
    // Operator overloads
    EuclideanVector &operator=(const EuclideanVector &);
    EuclideanVector &operator=(EuclideanVector &&) noexcept;
    double &operator[](int index);
    double operator[](int index) const;
    EuclideanVector &operator+=(const EuclideanVector &);
    EuclideanVector &operator-=(const EuclideanVector &);
    EuclideanVector &operator*=(double);
    EuclideanVector &operator/=(double);
    explicit operator std::vector<double>();
    explicit operator std::list<double>();

    // Friends
    // Output stream
    friend std::ostream &operator<<(std::ostream &os, const EuclideanVector &v)
    {
        if (v.size_ == 0)
        {
            os << "[]";
            return os;
        }
        os << "[";
        for (int i = 0; i < v.size_ - 1; i++)
        {
            os << v.magnitudes_[i] << " ";
        }
        os << v.magnitudes_[v.size_ - 1] << "]";
        return os;
    }
    // Equality
    friend bool operator==(const EuclideanVector &first, const EuclideanVector &second)
    {
        if (first.GetNumDimensions() != second.GetNumDimensions())
        {
            return false;
        }
        for (int i = 0; i < first.GetNumDimensions(); i++)
        {
            if (first.magnitudes_[i] != second.magnitudes_[i])
            {
                return false;
            }
        }
        return true;
    }

    // Inequality
    friend bool operator!=(const EuclideanVector &first, const EuclideanVector &second)
    {
        return !(first == second);
    }

    // Addition
    friend EuclideanVector operator+(const EuclideanVector &first, const EuclideanVector &second)
    {
        if (first.GetNumDimensions() != second.GetNumDimensions())
        {
            throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(first.GetNumDimensions()) +
                                       ") and RHS(" + std::to_string(second.GetNumDimensions()) +
                                       ") do not match");
        }

        EuclideanVector add(first.GetNumDimensions());
        add.magnitudes_ = std::make_unique<double[]>(add.size_);
        for (int i = 0; i < add.size_; i++)
        {
            add.magnitudes_[i] = first[i] + second[i]; // Made the operators, might as well use it hey
        }
        return add;
    }

    // Subtraction
    friend EuclideanVector operator-(const EuclideanVector &first, const EuclideanVector &second)
    {
        if (first.GetNumDimensions() != second.GetNumDimensions())
        {
            throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(first.GetNumDimensions()) +
                                       ") and RHS(" + std::to_string(second.GetNumDimensions()) +
                                       ") do not match");
        }

        EuclideanVector subtract(first.GetNumDimensions());
        subtract.magnitudes_ = std::make_unique<double[]>(subtract.size_);
        for (int i = 0; i < subtract.size_; i++)
        {
            subtract.magnitudes_[i] =
                first[i] - second[i]; // Made the operators, might as well use it hey
        }
        return subtract;
    }

    // Multiplication
    friend double operator*(const EuclideanVector &first, const EuclideanVector &second)
    {
        if (first.GetNumDimensions() != second.GetNumDimensions())
        {
            throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(first.GetNumDimensions()) +
                                       ") and RHS(" + std::to_string(second.GetNumDimensions()) +
                                       ") do not match");
        }

        double product = 0;
        for (int i = 0; i < first.GetNumDimensions(); i++)
        {
            product += first[i] * second[i]; // Made the operators, might as well use it hey
        }
        return product;
    }

    // Scalar multiplication
    friend EuclideanVector operator*(const EuclideanVector &vector, double scalar)
    {
        EuclideanVector product(vector.GetNumDimensions());
        product.magnitudes_ = std::make_unique<double[]>(product.size_);
        for (int i = 0; i < product.GetNumDimensions(); i++)
        {
            product.magnitudes_[i] = vector[i] * scalar; // Made the operators, might as well use it hey
        }
        return product;
    }
    // Scalar multiplication
    friend EuclideanVector operator*(double scalar, const EuclideanVector &vector)
    {
        return vector * scalar; // Has to be the hardest piece of code I've ever written
    }

    // Division
    friend EuclideanVector operator/(const EuclideanVector &vector, double scalar)
    {
        if (scalar == 0)
        {
            throw EuclideanVectorError("Invalid vector division by 0");
        }

        EuclideanVector division(vector.GetNumDimensions());
        division.magnitudes_ = std::make_unique<double[]>(division.GetNumDimensions());
        for (int i = 0; i < division.GetNumDimensions(); i++)
        {
            division.magnitudes_[i] = vector[i] / scalar; // Made the operators, might as well use it hey
        }
        return division;
    }

private:
    std::unique_ptr<double[]> magnitudes_;
    int size_{};
};

#endif // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_"