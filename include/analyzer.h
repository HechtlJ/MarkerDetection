/**
 * @file analyzer.h
 * @author Johannes Hechtl
 * @brief Provides means for analyzing coordinates.
 * @version 0.1
 * @date 2020-12-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef ANALYZER
#define ANALYZER

#include "vector"
#include "std_msgs/Float64.h"
#include <std_msgs/Float64MultiArray.h>
#include "my_types.h"



class Analyzer{
    public:
        Analyzer();

        /**
         * @brief 
         * 
         * @param data A double array of size 16, representing the 16 values of one transform.
         */
        void add_data(const std_msgs::Float64MultiArray::ConstPtr& msg);

        /**
         * @brief Returns the average of the given field
         * 
         * @param field index of data
         * @return double average of data[field]
         */
        void calculate_values();
        my_transform get_average();
        my_transform get_standard_deviation();
        my_transform get_min();
        my_transform get_max();
        int get_data_count();

    private:
        int data_count;
        std::vector<my_transform> data;
        void reset();
        my_transform average;
        my_transform standard_deviation;
        my_transform min;
        my_transform max;

        void calculate_average();
        void calculate_min();
};


#endif /* ANALYZER */