//
//  Point.cpp
//  PA2 ~ Intermediate
//
//  Created by Joshua Brummet on 2/15/16.
//  Copyright © 2016 C++. All rights reserved.
//

#include "Point.h"
#include "Cluster.h"
#include "Exceptions.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>

namespace Clustering
{
    void Point::rewindIdGen()
    {
        __idGen--;
        
    }
    
    unsigned int Point::__idGen = 0; // Id Generator
    const char Point::POINT_VALUE_DELIM = ',';
    
    //Constructor
    Point::Point(unsigned int dimensions)
    {
        if (dimensions == 0)
            throw ZeroDimensionsEx();
        
        __id = __idGen;
        
        __dim= dimensions;
        
        __values = new double[__dim];
        
        for (int i =0; i < __dim; ++i)
            __values[i] = 0;
        
        __idGen++;
        
    }
    
    Point::Point(unsigned int dimensions, double *array)
    {
        
        __id = __idGen;
        ++__idGen;
        
        __dim = dimensions;
        
        __values = new double[__dim];
        for (unsigned int i = 0; i < __dim; i++)
        {
            
            __values[i] = array[i];
            
        }
        
        
    }
    
    //Copy Constructor
    Point::Point(const Point & cpy)
    {
        
        __dim = cpy.__dim;
        __values = new double[__dim];
        __id = cpy.__id;
        //copy values into cpy array
        for (unsigned int i =0; i < __dim; i++)
            __values[i] = cpy.__values[i];
        
    }
    
    //Overloading operator=
    Point& Point::operator=(const Point & rhs)
    {
        if(__dim != rhs.__dim)
            throw DimensionalityMismatchEx(__dim,rhs.__dim);
        
        if (this != &rhs)
        {
            // delete & copy
            
            __id = rhs.__id;
            __dim = rhs.__dim;
            
            __values = new double[__dim];
            
            for (unsigned int i = 0; i < __dim; i++)
                __values[i] = rhs.__values[i];
            
        }
        
        return *this;
        
    }
    Point::~Point()
    {
        
        delete [] __values;
    }
    
    
    //Accessors
    int Point::getId() const
    {
        
        return __id;
        
    }
unsigned   int Point::getDims() const
    {
        
        return __dim;
        
    }
    
    void Point::setValue(unsigned int new_dim,double Value)
    {
        if (new_dim >= __dim)
            throw OutOfBoundsEx(__dim,new_dim);
        
           __values[new_dim] = Value;
        
        
    }
    
    double Point::getValue(unsigned int index) const
    {
        if (index >= __dim)
            throw OutOfBoundsEx(__dim,index);
        
        return __values[index];
        
    }
    
    //Distance Function for two poins objects
    double Point::distanceTo(const Point & other) const
    {
        if (__dim != other.__dim)
            throw DimensionalityMismatchEx(__dim,other.__dim);
        
        double total = 0;
        
        
        if (__dim != other.__dim)
            return false;
        
        for (unsigned int i = 0; i <__dim; ++i)
            
            total += ((other.getValue(i) - getValue(i)) * (other.getValue(i) - getValue(i)) );
        
        return sqrt(total);
        
    }
    
    
    //Compound assignment operatores
    Point& Point::operator*=(double rhs)
    {
        
        for(unsigned int i =0; i< __dim; i++)
            __values[i] *= rhs;
        
        return *this;
        
    }
    
    Point& Point::operator/=(double rhs)
    {
        for (unsigned int i =0; i<__dim; i++)
            __values[i]  /= rhs;
        
        return *this; // returing this object
        
    }
    
    const Point Point::operator*(double rhs) const
    {
        
        return Point (*this) *= rhs;
        
        
        
    }
    
    const Point Point::operator/(double rhs) const
    {
        
        return Point (*this) /= rhs;
        
        
        
    }
    
    //index operatore - return the index of a value
   double& Point::operator[](unsigned int index)
    {
        
        if( index >= __dim)
            throw OutOfBoundsEx(index,__dim);
        
        return __values[index];
        
    }
    
    const double & Point::operator[] (unsigned int index) const
    {
        if (index >= __dim)
            throw OutOfBoundsEx(__dim,index);
        
        return __values[index];
    }
    
    Point & operator+=(Point &lhs, const Point& rhs)
    {
        if (lhs.__dim != rhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim,rhs.__dim);
        
        
        if (&lhs == &rhs) //checking to see if points are equal
        {
            for (int count = 0; count < lhs.__dim; count++)
                lhs.__values[count] += rhs.__values[count];
        }
        
        else if (lhs.__dim == rhs.__dim) //if demensions are equal
            
        {
            for (int count = 0; count < lhs.__dim; count++)
                lhs.__values[count] += rhs.__values[count];
        }
        
        return lhs;
        
        
    }
    
    Point & operator -=(Point &lhs, const Point &rhs)
    {
        if (lhs.__dim != rhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim,rhs.__dim);
        
        if (&lhs == &rhs)
        {
            for (int count = 0; count < lhs.__dim; count++) {
                lhs.__values[count] = 0;
            }
        }
        else if (lhs.__dim == rhs.__dim)
        {
            for (int count = 0; count < lhs.__dim; count++)
                lhs.__values[count] -= rhs.__values[count];
        }
        
        return lhs;
        
    }
    
    
    const Point operator + (const Point & lhs, const Point & rhs)
    {
        if (lhs.__dim != rhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim,rhs.__dim);
        
        Point sum = lhs;
        sum += rhs; // using the overloaded compound assignment operator
        return sum;
        
    }
    
    const Point operator - (const Point & lhs, const Point & rhs)
    {
        if (lhs.__dim != rhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim,rhs.__dim);
        
        Point sum = lhs;
        sum -= rhs;
        return sum;
        
    }
    
    
    
    //**Comparison Functions**
    
    bool operator ==( const Point & lhs, const Point & rhs)
    {
        if (lhs.__dim != rhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim,rhs.__dim);
        
        
        if(lhs.__id != rhs.__id)
            return false;
        
        for (int i = 0; i < lhs.__dim; i++)
        {
            
            if  (lhs.getValue(i) != rhs.getValue(i))
                return false;
            
            
        }
        
        return true;
        
    }
    
    bool operator !=( const Point & lhs, const Point & rhs)
    {
        if (lhs.__dim != rhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim,rhs.__dim);
        
        return ! (lhs == rhs);
        
        
    }
    
    bool operator < (const Point & lhs, const Point & rhs)
    {
        
        if (lhs.__dim != rhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim,rhs.__dim);
        
        
        int localdim = std::max(lhs.__dim, rhs.__dim);
        
        
        if (lhs.__dim == rhs.__dim )
            
            for ( int i =0; i < localdim; i++)
                
                if (lhs.getValue(i) < rhs.getValue(i))
                    return true;
        
        return false;
        
    }
    
    bool operator > (const Point & lhs, const Point & rhs)
    {
        if (lhs.__dim != rhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim,rhs.__dim);
        
        return (rhs < lhs);
        
    }
    
    bool operator <= (const Point &lhs, const Point &rhs)
    {
        if (lhs.__dim != rhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim,rhs.__dim);
        
        return ! (lhs > rhs);
        
    }
    
    bool operator >=( const Point &lhs, const Point &rhs)
    {
        if (lhs.__dim != rhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim,rhs.__dim);
        
        return !(lhs < rhs);
    }
    
    //**File streaming Functions**
    std::istream &operator >> (std::istream &is, Point &p) {


        double point;
        int i = 0;
        std::string value, s;

        while (getline(is, value))
        {

          int size = std::count(value.begin(), value.end(), Point::POINT_VALUE_DELIM) + 1;

            if (p.getDims() != size)
                throw DimensionalityMismatchEx(p.getDims(), size);

            std::stringstream ss(value);
            while (getline(ss, s, Point::POINT_VALUE_DELIM))

            {
                point = stod(s);
                p.setValue(i, point);
                ++i;
            }
        }
        return is;
        
    }
    
    
    
    std::ostream &operator << (std::ostream & is,const Point & p)
    {
        int in = p.getDims() - 1;

        for (int i = 0; i < in; ++i)
            is << p.__values[i] << ", ";

        is << p.getValue(in);

        return is;
        
    }
    
}
