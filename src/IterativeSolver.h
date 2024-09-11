#ifndef ITERATIVESOLVER_H
#define ITERATIVESOLVER_H

#include "CoeffMatrix.h"
#include "Material.h"
#include "AuxilaryFunctions.h"


class IterativeSolver{
    public:
    IterativeSolver(CoeffMatrix&, Material&, int& nl_iter, int& ntotal_iter);

    ~IterativeSolver();

    fp jacobi();

    void printResidual();

    void printField();

    fp solve();

    private:
    int l_iter;
    fp residual;
    fp norm2_init;
    fp norm2;
    fp norm2_max;
    boost::multi_array<fp,2> Told;


    // 引用
    CoeffMatrix& coeffmatrix;
    Material& material;
    int& nl_iter;
    int& ntotal_iter;

    
};

#endif