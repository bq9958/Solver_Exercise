#include "IterativeSolver.h"

IterativeSolver::IterativeSolver(CoeffMatrix& coeffmatrix, Material& material, int& nl_iter, int& ntotal_iter) : 
    coeffmatrix(coeffmatrix), material(material), nl_iter(nl_iter), ntotal_iter(ntotal_iter)
{
    this->l_iter = 0;
    this->norm2_init = 0.0;
    this->norm2 = 0.0;
    this->norm2_max = 0.0;
}

IterativeSolver::~IterativeSolver(){};

fp IterativeSolver::jacobi()
{
    this->Told.resize(boost::extents[ncy][ncx]);
    this->Told = material.getT();
    std::array<std::array<COEFF,ncx>,ncy> coeff = coeffmatrix.getCoeff();

    fp TE, TW, TS, TN;

    for (int i=0; i<Told.size(); i++){
        for (int j=0; j<Told[0].size(); j++){
            if (j==0) TW = 0;
            else TW = Told[i][j-1];

            if (j==Told[0].size()-1) TE = 0;
            else TE = Told[i][j+1];

            if (i==0) TS = 0;
            else TS = Told[i-1][j];

            if (i==Told.size()-1) TN = 0;
            else TN = Told[i+1][j];

            fp T_new = -coeff[i][j].ae*TE - coeff[i][j].aw*TW - coeff[i][j].as*TS \
                                    - coeff[i][j].an*TN + coeff[i][j].bsrc;
            T_new = T_new / coeff[i][j].ac;
            material.updateField(i, j, T_new);
        }
    }

    fp norm2 = L2norm(material.getT(), Told);
    return norm2;
}

void IterativeSolver::printResidual()
{
    std::cout << "Begin iteration " << this->nl_iter << std::endl;
    std::cout << "-----------------------------------------------------------------------" << std::endl;
    std::cout << std::scientific;
    std::cout << std::left << std::setw(15) << "Step" << std::setw(15) << "linIter" << std::setw(15) << "TotIter" << std::setw(15) << "norm2" << std::setw(15) << "initNorm2" << std::setw(15) << "maxNorm2" << std::setw(15) << "linear_rel" << std::endl;
    std::cout << std::left << std::setw(15) << this->nl_iter << std::setw(15) << this->l_iter << std::setw(15) << this->ntotal_iter << std::setw(15) << this->norm2 << std::setw(15) << this->norm2_init << std::setw(15) << this->norm2_max << std::setw(15) << this->residual << std::endl;
    std::cout << "-----------------------------------------------------------------------" << std::endl;
}

fp IterativeSolver::solve()
{
    for (this->l_iter=1; l_iter< nLinearIter+1; l_iter++)
    {
        this->norm2 = this->jacobi();
        if (this->l_iter==1){
            this->norm2_init = this->norm2;
        }
        this->norm2_max = std::max(this->norm2, this->norm2_max) + 1.0E-20;
        this->residual = this->norm2 / this->norm2_max;

        if (this->residual < linearResLimit || this->l_iter==nLinearIter){
            this->ntotal_iter += l_iter;
            std::cout << std::endl;
            this->printResidual();
            return this->norm2;
        }
    }
    return this->norm2;
}

void IterativeSolver::printField()
{
    std::cout << "------------- Told --------------" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    for (int i=0; i<ncy; i++){
        for (int j=0; j<ncx; j++){
            std::cout << std::setw(12) << Told[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "------------- T --------------" << std::endl;
    material.printT();
}


