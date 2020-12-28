#ifndef MY_TYPES
#define MY_TYPES

struct my_transform{
    double x;
    double y;
    double z;
    //double rot_mat[9];

    my_transform(double x=0, double y=0, double z=0) : x(x), y(y), z(z)
    {
    }

    my_transform operator+(const my_transform& a) const{
        return my_transform(a.x+x, a.y+y, a.z+z);
    }

    my_transform operator/(const int& i){
        my_transform result;
        result.x = x / (double)i;
        result.y = y / (double)i;
        result.z = z / (double)i;
        return result;
    }

};

#endif /* MY_TYPES */