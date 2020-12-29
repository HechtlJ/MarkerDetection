#include "analyzer.h"
#include "math.h"

Analyzer::Analyzer(){
    
}

/**
 * @brief 
 * 
 * @param data A double array of size 16, representing the 16 values of one transform.
 */
void Analyzer::add_data(const std_msgs::Float64MultiArray::ConstPtr& msg){
    my_transform new_data;
    new_data.x = msg->data[3];
    new_data.y = msg->data[7];
    new_data.z = msg->data[11];

    data.push_back(new_data);
}

my_transform Analyzer::get_average(){
    return average;
}

my_transform Analyzer::get_min(){
    return min;
}

my_transform Analyzer::get_max(){
    return max;
}

my_transform Analyzer::get_standard_deviation(){
    return standard_deviation;
}


void Analyzer::calculate_values(){
    calculate_average();
    calculate_min();
    calculate_max();
    calculate_standard_deviation();    
}



void Analyzer::calculate_average(){
    average = my_transform();
    for(my_transform tf : data){
        average = average + tf;
    }
    average = average / data.size();
}


int Analyzer::get_data_count(){
    return data.size();
}

void Analyzer::calculate_min(){
    // Checking if first value exists
    if(data.size()==0){
        min.x=0;
        min.y=0;
        min.z=0;
        return;
    }

    // Initialising minimal values with first values
    min.x = data[0].x;
    min.y = data[0].y;
    min.z = data[0].z;


    // Checking for smaller values than the first.
    for(my_transform tf : data){
        if(tf.x < min.x)
            min.x = tf.x;
        if(tf.y < min.y)
            min.y = tf.y;
        if(tf.z < min.z)
            min.z = tf.z;

    }
}


void Analyzer::calculate_max(){
    // Checking if first value exists
    if(data.size()==0){
        max.x=0;
        max.y=0;
        max.z=0;
        return;
    }

    // Initialising maximum values with first values
    max.x = data[0].x;
    max.y = data[0].y;
    max.z = data[0].z;


    // Checking for bigger values than the first.
    for(my_transform tf : data){
        if(tf.x > max.x)
            max.x = tf.x;
        if(tf.y > max.y)
            max.y = tf.y;
        if(tf.z > max.z)
            max.z = tf.z;

    }
}


/**
 * @brief Calculates @standard_deviation of @data from @average
 * 
 */
void Analyzer::calculate_standard_deviation(){
    standard_deviation.x = 0;
    standard_deviation.y = 0;
    standard_deviation.z = 0;

    for(my_transform tf : data){
        double diff_x = average.x - tf.x;
        double diff_y = average.y - tf.y;
        double diff_z = average.z - tf.z;

        standard_deviation.x = standard_deviation.x + abs(diff_x);
        standard_deviation.y = standard_deviation.y + abs(diff_y);
        standard_deviation.z = standard_deviation.z + abs(diff_z);

    }

    standard_deviation = standard_deviation / data.size();
}
