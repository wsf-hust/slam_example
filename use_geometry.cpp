//
// Created by wsf on 23-8-31.
//
#include <iostream>
#include <cmath>
using namespace std;
//EIGEN部分
#include <Eigen/Core>
//几何模块部分
#include <Eigen/Geometry>

#define MATRIX_SIZE 100
/*
 * 本程序演示了Eigen基本类型的使用
 * */

int main() {
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    Eigen::AngleAxisd rotation_vector(M_PI/4, Eigen::Vector3d(0,0,1)); //旋转向量，角度+轴
    cout.precision(3);
    cout<<"rotation matrix = \n"<<rotation_vector.matrix()<<endl; //从旋转向量变为旋转矩阵

    rotation_matrix=rotation_vector.toRotationMatrix();

    Eigen::Vector3d v(1,0,0);  //列向量
    Eigen::Vector3d v_rotated = rotation_vector*v; //注意这里，这里是旋转向量直接去乘了
    cout<<"(1,0,0) after rotation ="<<v_rotated.transpose()<<endl;

    v_rotated =rotation_matrix*v;
    cout<<"(1,0,0) after rotation ="<<v_rotated.transpose()<<endl;

    //旋转矩阵转换为欧拉角 ZYX顺序
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles(2,1,0);
    cout<<"yaw pitch roll="<<euler_angles.transpose()<<endl;

    Eigen::Isometry3d T=Eigen::Isometry3d::Identity(); //名为3d，实际为4*4矩阵
    T.rotate(rotation_vector); //注意这里，可以直接赋旋转变量，也能丢旋转矩阵
    //T.rotate(rotation_matrix);
    T.pretranslate(Eigen::Vector3d(1,3,4)); //平移矩阵
    cout<<"Transform matrix =\n"<<T.matrix()<<endl;

    Eigen::Vector3d v_transformed =T*v;
    cout<<"v tranformed ="<<v_transformed.transpose()<<endl;

    Eigen::Quaterniond q=Eigen::Quaterniond(rotation_vector); //注意这里 旋转变量直接丢进去转为四元数
    cout<<"quaternion =\n"<<q.coeffs()<<endl; //coeffs的顺序是（x,y,z,w）前三个虚部，最后是实部
    q=Eigen::Quaterniond(rotation_matrix);
    cout<<"quaternion =\n"<<q.coeffs()<<endl; //coeffs的顺序是（x,y,z,w）前三个虚部，最后是实部

    v_rotated =q*v; //注意这里的乘法，他是四元素直接去乘（与数学上的写法不一样），即把四元数当作是旋转矩阵
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;

    return 0;
}

