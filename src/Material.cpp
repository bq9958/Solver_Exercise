#include "Material.h"

Material::Material(){
    this->k = conductivity;
    this->T.resize(boost::extents[ncy][ncx]);
    for (int i=0; i < ncy; i++){
        for (int j=0; j < ncx; j++){
            T[i][j] = T_init;
        }
    }
}

Material::~Material() {}

void Material::printT()
{
    std::cout << std::fixed << std::setprecision(4);
    for (int i=0; i<ncy; i++){
        for (int j=0; j<ncx; j++){
            std::cout << std::setw(12) << T[i][j];
        }
        std::cout << std::endl;
    }
}