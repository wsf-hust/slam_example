#include <iostream>
#include <ctime>
using namespace std;
//EIGEN部分
#include <Eigen/Core>
//稠密矩阵部分
#include <Eigen/Dense>

#define MATRIX_SIZE 100
/*
 * 本程序演示了Eigen基本类型的使用
 * */

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Hello, SLAM!" << std::endl;
    Eigen::Matrix<float, 2, 3> matrix2_3;
    Eigen::Vector3d v3d;
    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero();
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic;
    Eigen::MatrixXd matrix_x;
    matrix2_3 <<1,2,3,4,5,6;
    cout<<matrix2_3<<endl;

    for (int i=0;i<1;i++)
        for (int j=0; j<2; j++)
            cout<<matrix2_3(i,j)<<endl;

    v3d<<1,2,3;
    Eigen::Matrix<double, 2, 1> result = matrix2_3.cast<double >() * v3d;
    cout<<result<<endl;

    matrix_33 = Eigen::Matrix3d::Random();
    cout<<matrix_33<<endl;

    cout<<matrix_33.transpose()<<endl;
    cout<<matrix_33.sum()<<endl;
    cout<<matrix_33.trace()<<endl;
    cout<<10*matrix_33<<endl;
    cout<<matrix_33.inverse()<<endl;
    cout<<matrix_33.determinant()<<endl;  //行列式

    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(matrix_33.transpose()*matrix_33);  //实对称矩阵求解特征值
    cout<<"Eigen values ="<<eigen_solver.eigenvalues()<<endl;
    cout<<"Eigen vectors ="<<eigen_solver.eigenvectors()<<endl;

    Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN;
    matrix_NN = Eigen::MatrixXd::Random(MATRIX_SIZE,MATRIX_SIZE);
    Eigen::Matrix <double , MATRIX_SIZE, 1> v_Nd;
    v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE,1);

    clock_t time_stt =clock();
    Eigen::Matrix<double , MATRIX_SIZE,1> x= matrix_NN.inverse()*v_Nd;  //矩阵逆求解方程
    cout<<"time use in normal invers is "<<1000*(clock()-time_stt)/(double )CLOCKS_PER_SEC<<"ms"<<endl;

    time_stt =clock();
    x=matrix_NN.colPivHouseholderQr().solve(v_Nd);  //QR分解方程
    cout<<"time use in Qr compsition is "<<1000*(clock()-time_stt)/(double )CLOCKS_PER_SEC<<"ms"<<endl;
    return 0;
}
