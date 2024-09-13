#ifndef STRUCTUREDMESH_H
#define STRUCTUREDMESH_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include "precisionFloat.h"
#include <boost/multi_array.hpp>
#include "AuxilaryFunctions.h"

using namespace std;

class StructuredMesh
{
    public:

        StructuredMesh();
        
        ~StructuredMesh();

        void createMesh();

        void createBoundaryMesh();

        inline boost::multi_array<struct CELL_FACE, 2> getCellFacesID() const {return this->cellFacesID;}
        inline fp getdx() const {return this->dx;}
        inline fp getdy() const {return this->dy;}
        inline std::array<fp, ncx+1> getxf() const {return this->xf;}
        inline std::array<fp, ncy+1> getyf() const {return this->yf;}

    private:
        fp dx, dy;
        std::array<fp, ncx> xc;   // cell center
        std::array<fp, ncy> yc;   // cell center
        std::array<fp, ncx+1> xf;   // face
        std::array<fp, ncy+1> yf;   // face
        boost::multi_array<struct CELL_FACE, 2> cellFacesID;
};

#endif