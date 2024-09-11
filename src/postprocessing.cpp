#include "postprocessing.h"

Postprocessing::Postprocessing(){};

Postprocessing::~Postprocessing(){};

void Postprocessing::writeVTKCollocated(StructuredMesh &mesh, Material &material)
{
    const int nx = ncx + 1;
    const int ny = ncy + 1;
    std::array<fp, nx> x = mesh.getxf();
    std::array<fp, ny> y = mesh.getyf();
    boost::multi_array<fp,2> T = material.getT();

    std::ofstream vtk_fid(vtkFileName);
    if (!vtk_fid)
        std::cout << "File opening error!" << std::endl;
    else
    {
        // Write header
        vtk_fid<<"# vtk DataFile Version 3.0"<<std::endl;
        vtk_fid<<"flash 2d grid and solution"<<std::endl;
        vtk_fid<<"ASCII"<<std::endl;
        vtk_fid<<"DATASET RECTILINEAR_GRID"<<std::endl;

        // Write mesh information
        vtk_fid<<"DIMENSIONS "<< nx <<" "<< ny << " " << "1" << std::endl;

        vtk_fid<<"X_COORDINATES "<< nx <<" float"<<std::endl;
        for(fp i:x)
            vtk_fid<< i << " ";
        vtk_fid << std::endl;

        vtk_fid<<"Y_COORDINATES "<< ny <<" float"<<std::endl;
        for(fp i:y)
            vtk_fid<< i << " ";
        vtk_fid << std::endl;

        vtk_fid<<"Z_COORDINATES "<< "2" <<" float"<<std::endl;
        vtk_fid << "0.0" << " " << "0.0";
        vtk_fid << std::endl;

        // Write cell data
        int ncell = (nx-1)*(ny-1);
        vtk_fid<<"CELL_DATA "<<ncell<<std::endl;
        vtk_fid<<"FIELD FieldData 1"<<std::endl;

        // Write temperature field data
        vtk_fid<<"T 1 "<<ncell<<" float"<<std::endl;
        for (int j = 0; j < T.shape()[1]; ++j)
            for (int i = 0; i < T.shape()[0]; ++i)
                vtk_fid<< T[i][j] << " ";
        vtk_fid << std::endl;
    }
    vtk_fid.close();
};