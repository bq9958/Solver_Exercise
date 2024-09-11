#ifndef MATERIAL_H
#define MATERIAL_H
#include "input.h"
#include <boost/multi_array.hpp>
#include <iostream>
#include <iomanip>

using namespace std;

class Material
{
    public:
        Material();

        ~Material();

        inline boost::multi_array<fp,2> getT() {return T;}
        inline boost::multi_array<fp,2> getrho() {return rho;}
        inline boost::multi_array<fp,2> getU() {return u;}

        void updateField(unsigned int i, unsigned int j, fp Tnew) { this->T[i][j] = Tnew; }

        void printT();
    
    private: 
        fp k;
        boost::multi_array<fp,2> T;
        boost::multi_array<fp,2> rho;
        boost::multi_array<fp,2> u; // 考虑一维情况
};
#endif