#ifndef COEFFMATRIX_H
#define COEFFMATRIX_H

#include <iostream>
#include <iomanip>
#include "input.h"
#include "StructuredMesh.h"
#include "Material.h"

struct COEFF {
    fp ac, ae, aw, as, an, bsrc;
};

class CoeffMatrix {

    public:
        CoeffMatrix(StructuredMesh&, Material&);

        ~CoeffMatrix();

        void DiffusionCoeff(fp conductivity, fp dx, fp dy, int ncx, int ncy);

        void convectionCoeff();

        inline std::array<std::array<COEFF,ncx>,ncy>getCoeff() {return this->Coeff;} 
    private:
    std::array<std::array<COEFF,ncx>,ncy> Coeff;
    StructuredMesh& mesh;
    Material& material;
};

#endif