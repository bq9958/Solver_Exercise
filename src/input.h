#ifndef INPUT_H
#define INPUT_H

#include "precisionFloat.h"
#include <array>
#include <vector> 

// 网格参数
const fp xmin = 0.0;
const fp xmax = 1.0;
const fp ymin = 0.0;
const fp ymax = 1.0;
const int ncx = 32; 
const int ncy = 32;

// 物性参数
const fp conductivity = 1.0;  // 导热系数
const fp density = 1.0;  // 密度
const fp vel_init = 1.0; // 流场初始速度
const fp T_init = 373.0;

// 求解器参数 
const int nNonLinIter = 100;
const fp nonLinearResLimit = 1.0E-6;
const int nLinearIter = 100;
const fp linearResLimit = 1.0E-2;

const std::string vtkFileName = "../post_temp.vtk";


// 边界条件
enum FACE_POSITION {INTERIOR, X_MIN, X_MAX, Y_MIN, Y_MAX};
enum BOUNDARY_TYPE_T {DIRICHLET, NEUMANN};

struct CELL_FACE
{
    FACE_POSITION EAST, WEST, NORTH, SOUTH;
};


typedef struct BoundaryCondition 
{
    FACE_POSITION position;
    BOUNDARY_TYPE_T BC_T;
    fp T; 
    fp heatflux;
} BC;


const BC BoundaryInfo[4]
{
    {X_MIN, DIRICHLET, 373.0, 0.0},
    {X_MAX, DIRICHLET, 373.0, 0.0},
    {Y_MIN, NEUMANN, 0.0, 0.0},
    {Y_MAX, NEUMANN, 0.0, 0.0},
};       

// const BC BoundaryInfo[4]
// {
//     {X_MIN, DIRICHLET, 373.0, 0.0},
//     {X_MAX, DIRICHLET, 373.0, 0.0},
//     {Y_MIN, DIRICHLET, 373.0, 0.0},
//     {Y_MAX, DIRICHLET, 293.0, 0.0},
// };






#endif