#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include "StructuredMesh.h"
#include "Material.h"
#include <fstream>


class Postprocessing
{
    public:
        Postprocessing();

        ~Postprocessing();

        void writeVTKCollocated(StructuredMesh&, Material&);

    private:


};

#endif