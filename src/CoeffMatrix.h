#ifndef COEFFMATRIX_H
#define COEFFMATRIX_H

#include <iostream>
#include <iomanip>
#include "input.h"
#include "StructuredMesh.h"
#include "Material.h"
#include "debug_macro.h"

struct COEFF {
    fp ac, ae, aw, as, an, bsrc;
};

class CoeffMatrix {

    public:
        CoeffMatrix(StructuredMesh&, Material&);

        ~CoeffMatrix();

        void DiffusionCoeff(fp dx, fp dy);

        void convectionCoeff(fp dx, fp dy);

        inline std::array<std::array<COEFF,ncx>,ncy>getCoeff() {return this->Coeff;} 
    private:
    std::array<std::array<COEFF,ncx>,ncy> Coeff;
    StructuredMesh& mesh;
    Material& material;
};

#endif