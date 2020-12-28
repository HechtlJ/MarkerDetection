#include "analyzer.h"

Analyzer::Analyzer(){
    data_count = 0;
    
}

void Analyzer::add_data(const std_msgs::Float64MultiArray::ConstPtr& msg){
    my_transform new_data;
    data_count++;
    new_data.x = msg->data[3];
    new_data.y = msg->data[7];
    new_data.z = msg->data[11];

    data.push_back(new_data);
}

my_transform Analyzer::get_average(){
    return average;
}



void Analyzer::calculate_values(){
    calculate_average();
    //calculate_min();

    
}



void Analyzer::calculate_average(){
    average = my_transform();
    for(my_transform tf : data){
        average = average + tf;
    }
    average = average / data_count;
}


int Analyzer::get_data_count(){
    return data_count;
}
/*
void Analyzer::calculate_min(){
    // Initialising minimal values with first values
    for(int dim=0; dim<16;dim++){
        min[dim] = data[0][dim];
    }

    // Checking for smaller values than the first.
    for(double * coordinates : data){
        for(int dim=0; dim<16;dim++){
            if(coordinates[dim] < min[dim]){
                min[dim] = coordinates[dim];
            }
        }
    }
}*/
