#include "assignments/ev/euclidean_vector.h"

#include <algorithm> // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm
#include <cassert>
#include <cmath>
#include <exception>
#include <list>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

// Basic constructor with only dimensions
EuclideanVector::EuclideanVector(int size) : EuclideanVector(0.0)
{
    this->size_ = size;
}

// Basic constructor with only magnitudes when they already have dimensions
EuclideanVector::EuclideanVector(double value)
{
    this->magnitudes_ = std::make_unique<double[]>(this->size_);
    for (int i = 0; i < this->size_; i++)
    {
        this->magnitudes_[i] = value;
    }
}

// Overloaded constructor with both dimensions and magnitudes
EuclideanVector::EuclideanVector(int size, double value) : EuclideanVector(size)
{
    this->magnitudes_ = std::make_unique<double[]>(this->size_);
    for (int i = 0; i < this->size_; i++)
    {
        this->magnitudes_[i] = value;
    }
}

// Overloaded constructor to convert from vector
EuclideanVector::EuclideanVector(std::vector<double>::const_iterator start,
                                 std::vector<double>::const_iterator end)
{
    auto temp = start;
    this->size_ = 0;
    while (temp != end)
    {
        this->size_++;
        temp++;
    }
    this->magnitudes_ = std::make_unique<double[]>(this->size_);
    int i = 0;
    while (start != end)
    {
        this->magnitudes_[i] = *start;
        i++;
        start++;
    }
}

// Copy constructor
EuclideanVector::EuclideanVector(const EuclideanVector &source)
{
    this->size_ = source.size_;
    this->magnitudes_ = std::make_unique<double[]>(this->size_);
    for (int i = 0; i < this->size_; i++)
        this->magnitudes_[i] = source.magnitudes_[i];
}

// Move constructor
EuclideanVector::EuclideanVector(EuclideanVector &&o) noexcept
    : magnitudes_{std::move(o.magnitudes_)}, size_{o.size_}
{
    o.size_ = 0;
}

// Default destructor
EuclideanVector::~EuclideanVector() noexcept = default;

// At function ev.at(index) const
double EuclideanVector::at(int index) const
{
    if (index < 0 || index >= this->size_)
        throw EuclideanVectorError("Index " + std::to_string(index) +
                                   " is not valid for this EuclideanVector object");
    return this->magnitudes_[index];
}

// At function ev.at(index)
double &EuclideanVector::at(int index)
{
    if (index < 0 || index >= this->size_)
        throw EuclideanVectorError("Index " + std::to_string(index) +
                                   " is not valid for this EuclideanVector object");
    return this->magnitudes_[index];
}
// ev.GetNumDimensions() to return dimensions
int EuclideanVector::GetNumDimensions()
{
    return this->size_;
}
// ev.GetNumDimensions() to return dimensions const
int EuclideanVector::GetNumDimensions() const
{
    return this->size_;
}

// Get EuclideanNorm
double EuclideanVector::GetEuclideanNorm()
{
    if (!this->GetNumDimensions())
        throw EuclideanVectorError("EuclideanVector with no dimensions does not have a norm");
    double norm = 0.0;
    for (int i = 0; i < this->GetNumDimensions(); i++)
        norm += pow(this->magnitudes_[i], 2);
    return sqrt(norm);
}

// Get EuclideanNorm const
double EuclideanVector::GetEuclideanNorm() const
{
    if (!this->GetNumDimensions())
        throw EuclideanVectorError("EuclideanVector with no dimensions does not have a norm");
    double norm = 0.0;
    for (int i = 0; i < this->GetNumDimensions(); i++)
        norm += pow(this->magnitudes_[i], 2);
    return sqrt(norm);
}

// Create unit vector
EuclideanVector EuclideanVector::CreateUnitVector()
{
    if (!this->GetNumDimensions())
        throw EuclideanVectorError("EuclideanVector with no dimensions does not have a unit vector");
    double norm = this->GetEuclideanNorm();

    if (norm == 0)
    {
        throw EuclideanVectorError(
            "EuclideanVector with euclidean normal of 0 does not have a unit vector");
    }

    EuclideanVector unit_vector{*this};
    for (int i = 0; i < this->GetNumDimensions(); i++)
        unit_vector.magnitudes_[i] = unit_vector.magnitudes_[i] / norm;

    return unit_vector;
}

// Shorthand assignment operator
EuclideanVector &EuclideanVector::operator=(const EuclideanVector &source)
{
    this->size_ = source.size_;
    this->magnitudes_ = std::make_unique<double[]>(this->size_);
    for (int i = 0; i < this->size_; i++)
        this->magnitudes_[i] = source.magnitudes_[i];
    return *this;
}

// Std::move
EuclideanVector &EuclideanVector::operator=(EuclideanVector &&o) noexcept
{
    magnitudes_ = std::move(o.magnitudes_);
    size_ = o.size_;
    o.size_ = 0;
    return *this;
}

// Shorthand add operator
EuclideanVector &EuclideanVector::operator+=(const EuclideanVector &source)
{
    if (this->GetNumDimensions() != source.GetNumDimensions())
    {
        throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(this->GetNumDimensions()) +
                                   ") and RHS(" + std::to_string(source.GetNumDimensions()) +
                                   ") do not match");
    }

    for (int i = 0; i < this->GetNumDimensions(); i++)
    {
        this->magnitudes_[i] += source.magnitudes_[i];
    }

    return *this;
}

// Shorthand subtract operator
EuclideanVector &EuclideanVector::operator-=(const EuclideanVector &source)
{
    if (this->GetNumDimensions() != source.GetNumDimensions())
    {
        throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(this->GetNumDimensions()) +
                                   ") and RHS(" + std::to_string(source.GetNumDimensions()) +
                                   ") do not match");
    }

    for (int i = 0; i < this->GetNumDimensions(); i++)
    {
        this->magnitudes_[i] -= source.magnitudes_[i];
    }

    return *this;
}

// Shorthand multiply operator
EuclideanVector &EuclideanVector::operator*=(const double multiplier)
{
    for (int i = 0; i < this->GetNumDimensions(); i++)
    {
        this->magnitudes_[i] *= multiplier;
    }

    return *this;
}

// Shorthand divide operator
EuclideanVector &EuclideanVector::operator/=(const double divisor)
{
    if (divisor == 0)
    {
        throw EuclideanVectorError("Invalid vector division by 0");
    }

    for (int i = 0; i < this->GetNumDimensions(); i++)
    {
        this->magnitudes_[i] /= divisor;
    }

    return *this;
}

// Indexing operator
double &EuclideanVector::operator[](int index)
{
    assert(index >= 0 && index < this->GetNumDimensions());
    return this->magnitudes_[index];
}

// Indexing operator const
double EuclideanVector::operator[](int index) const
{
    assert(index >= 0 && index < this->GetNumDimensions());
    return this->magnitudes_[index];
}

// EV to Vector
EuclideanVector::operator std::vector<double>()
{
    std::vector<double> euclid_as_vector;
    euclid_as_vector.reserve(this->GetNumDimensions());
    for (int i = 0; i < this->GetNumDimensions(); i++)
    {
        euclid_as_vector.emplace_back(this->magnitudes_[i]);
    }
    return euclid_as_vector;
}

// EV to list
EuclideanVector::operator std::list<double>()
{
    std::list<double> euclid_as_list;
    for (int i = 0; i < this->GetNumDimensions(); i++)
    {
        euclid_as_list.emplace_back(this->magnitudes_[i]);
    }
    return euclid_as_list;
}