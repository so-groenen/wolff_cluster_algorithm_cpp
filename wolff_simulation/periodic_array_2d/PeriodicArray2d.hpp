// #ifndef MATRIX_H
// #define MATRIX_H
#ifndef PERIODIC_ARRAY_2D_HPP
#define PERIODIC_ARRAY_2D_HPP
 
#include <iostream>
#include <cstdint>
#include <cstring>
#include <memory>
#include <exception>
#include <cmath>
#include <array>
#include "array_point.hpp"


 
using pair_t = std::pair<int, int> ;

template<typename T>
concept SpinType = std::is_integral_v<T> || std::is_floating_point_v<T>;  //SPins can only be integers or floating point values!

namespace periodic_array_2d
{
    template<SpinType T>
    class PeriodicArray2d
    {
        std::unique_ptr<T[]> m_spin_data{}; 
        T* m_raw_spin_data{};
        int m_rows{};
        int m_columns{};
        size_t n_elements{};
        void set_modX(int& i);
        void set_modY(int& j);

    public:
        PeriodicArray2d(int rows, int cols)
            : m_rows{rows}, m_columns{cols}
        {
            if (rows <= 0 || cols <= 0)
            {
            throw std::underflow_error("Matrix cannot have zero or negative rows or columns!");
            }

            n_elements      = static_cast<size_t>(rows*cols);
            m_spin_data     = std::make_unique<T[]>(n_elements);
            m_raw_spin_data = m_spin_data.get();

            for(size_t i = 0; i < n_elements; i++ )               
            {
                m_spin_data[i] = static_cast<T>(1.);
            }
        }

        PeriodicArray2d(const PeriodicArray2d<T>& other)       // copy cons
            : m_columns{other.m_columns}, 
            m_rows{other.m_rows},
            m_spin_data{std::make_unique<T[]>(m_columns*m_rows)},
            m_raw_spin_data{m_spin_data.get()}

        {       
            std::memcpy(m_raw_spin_data, other.m_raw_spin_data, (m_columns*m_rows)*sizeof(T));
        }
        PeriodicArray2d(PeriodicArray2d<T>&& other)       
            : m_columns{other.m_columns}, 
            m_rows{other.m_rows},
            m_spin_data{std::move(other.m_spin_data)},
            m_raw_spin_data{m_spin_data.get()}
        {       
            other.m_columns       = 0;
            other.m_rows          = 0;
            other.m_raw_spin_data = nullptr;
        }
        size_t numberOfElements() const 
        {
            return static_cast<size_t>(m_rows*m_columns);
        }
        PeriodicArray2d<T>& operator=(const PeriodicArray2d<T>& other) // copy assignement
        {
            if (&other != this)
            {
                m_rows    = other.m_rows;
                m_columns = other.m_columns;
                n_elements = other.n_elements;

                
                auto new_spin_data = std::make_unique<T[]>(n_elements);
                m_spin_data.reset(new_spin_data);

                m_raw_spin_data = m_spin_data.get();
                std::memcpy(m_raw_spin_data, other.m_raw_spin_data, n_elements*sizeof(T));        
            }
            return *this;
        }
        PeriodicArray2d<T>& operator=(PeriodicArray2d<T>&& other) // move assignement
        {
            if (other.m_raw_spin_data == nullptr)
            {
                return *this;
            }
            
            if (&other != this)
            {
                m_rows     = other.m_rows;
                m_columns  = other.m_columns;
                n_elements = other.n_elements;

                m_spin_data     = std::move(other.m_spin_data);
                m_raw_spin_data = m_spin_data.get();
                
                other.m_columns       = 0;
                other.m_rows          = 0;
                other.m_raw_spin_data = nullptr;
            }
            return *this;
        }
        ~PeriodicArray2d()
        {
        }
        T& operator()(int i, int j)  // not const -> we need to be able to change the values.
        {                                         // use int64 instead of size t for modulus operator.
            // set_modX(i);
            // set_modY(j);
            const int i_m {get_modY(i)};    
            const int j_m {get_modX(j)};
            // return this->m_raw_spin_data[i_m + j_m*m_columns];
            return m_raw_spin_data[j_m + i_m*m_columns];
        }
        const T& operator()(int i, int j) const        // "R-value" version: spin_t result = myarray(i,j).
        {                                   
            const int i_m {get_modY(i)};                                 
            const int j_m {get_modX(j)};
            return m_raw_spin_data[j_m + i_m*m_columns];
        }
        T& operator()(const ArrayPoint& coordinate) 
        {
            const int i {get_modY(coordinate.y)};
            const int j {get_modX(coordinate.x)};
            return m_raw_spin_data[j+i*m_columns];
        }
        const T& operator()(const ArrayPoint& coordinate) const
        {
            const int i {get_modY(coordinate.y)};
            const int j {get_modX(coordinate.x)};
            return m_raw_spin_data[j+i*m_columns];
        }
        template<typename U>
        friend std::ostream& operator<<(std::ostream& stream, const PeriodicArray2d<U>& spin) requires SpinType<U>;
        size_t get_cols() const;
        size_t get_rows() const;
        std::array<ArrayPoint,4> get_neighbourhood(const ArrayPoint& coordinate) const;
        void set_neighbourhood(const ArrayPoint& coordinate, std::array<ArrayPoint,4> & neigbourhood) const;
        int get_modX(int j) const;
        int get_modY(int i) const;
    };


    inline std::ostream& operator<<(std::ostream& stream, const ArrayPoint& point)
    {
        stream << "(" << point.x << "," << point.y << ")\n";
        return stream; 
    }
    


    template<typename T>
    inline std::ostream& operator<< (std::ostream& stream, const PeriodicArray2d<T>& Spin ) requires SpinType<T>
    {   
        for (int y = 0; y < Spin.get_rows(); y++)
        {
            for (int x = 0; x < Spin.get_cols(); x++)
            {
                if (Spin(x,y) == (1))
                {
                    std::cout << "O" << " ";
                }
                if (Spin(x,y) == (-1))
                {
                    std::cout << "." << " ";
                }
            }
            std::cout << std::endl;
        }
        return stream;
    }

    template<SpinType T>
    inline void PeriodicArray2d<T>::set_modX(int& i) //
    {
        i = i%m_columns;
        if (i < 0)
        {
            i += m_columns;
        }
    }
    template<SpinType T>
    void PeriodicArray2d<T>::set_modY(int& j) //requires SpinType<T>
    {
        j = j%m_rows;
        if (j < 0)
        {
            j += m_rows;
        }
    }

    template<SpinType T>
    int PeriodicArray2d<T>::get_modX(int j) const
    {
        int j_m = j%m_columns;
        if (j_m < 0)
        {
            j_m += m_columns;
        }
        return j_m;
    }
    template<SpinType T>
    int PeriodicArray2d<T>::get_modY(int i) const
    {
        int i_m = i%m_rows;
        if (i_m < 0)
        {
            i_m += m_rows;
        }
        return i_m;
    }


    template<SpinType T>
    size_t PeriodicArray2d<T>::get_cols() const
    {
        return static_cast<size_t>(m_columns);
    }
    template<SpinType T>
    size_t PeriodicArray2d<T>::get_rows() const
    {
        return static_cast<size_t>(m_rows);
    }




    template<SpinType T>
    std::array<ArrayPoint,4> PeriodicArray2d<T>::get_neighbourhood(const ArrayPoint& coordinate) const  
    {
        const int j = coordinate.x;
        const int i = coordinate.y;

        ArrayPoint right {get_modX(j+1), i};
        ArrayPoint left  {get_modX(j-1), i};
        ArrayPoint up    {j, get_modY(i+1)};
        ArrayPoint down  {j, get_modY(i-1)};
        std::array<ArrayPoint,4> my_array = {right, left, up, down};
        return my_array;
    }


    template<SpinType T>
    void PeriodicArray2d<T>::set_neighbourhood(const ArrayPoint& coordinate, std::array<ArrayPoint,4>& neigbourhood) const
    {
        const int i {coordinate.y};
        const int j {coordinate.x};

        neigbourhood[0] = ArrayPoint{get_modX(j+1), i}; 
        neigbourhood[1] = ArrayPoint{get_modX(j-1), i};
        neigbourhood[2] = ArrayPoint{j, get_modY(i+1)};
        neigbourhood[3] = ArrayPoint{j, get_modY(i-1)};
    }
}

#endif