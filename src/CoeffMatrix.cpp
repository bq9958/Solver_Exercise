#include "CoeffMatrix.h"

CoeffMatrix::CoeffMatrix(StructuredMesh& mesh, Material& material):
    mesh(mesh), material(material)
{
    for (int i=0; i < ncy; i++){
        for (int j=0; j < ncx; j++){
            Coeff[i][j].ac = 0.0;
            Coeff[i][j].ae = 0.0;
            Coeff[i][j].aw = 0.0;
            Coeff[i][j].as = 0.0;
            Coeff[i][j].an = 0.0;
            Coeff[i][j].bsrc = 0.0;
        }
    }
}

CoeffMatrix::~CoeffMatrix(){}

void convCoeff()
{
    
}

void CoeffMatrix::DiffusionCoeff(fp conductivity, fp dx, fp dy, int ncx, int ncy){
    for (int i=0; i<ncy; i++){
        for (int j=0; j<ncx; j++){
            Coeff[i][j].ae = -conductivity*dy/dx;
            Coeff[i][j].aw = -conductivity*dy/dx;
            Coeff[i][j].as = -conductivity*dx/dy;
            Coeff[i][j].an = -conductivity*dx/dy;
            Coeff[i][j].ac = -(Coeff[i][j].ae+Coeff[i][j].aw+Coeff[i][j].an+Coeff[i][j].as);
        }
    }

    boost::multi_array<struct CELL_FACE,2> cellFacesID = mesh.getCellFacesID();
    FACE_POSITION pos;
    for (int i=0; i<ncy; i++){
        for (int j=0; j<ncx; j++){
            pos = cellFacesID[i][j].EAST;
            for (int item=0; item < sizeof(BoundaryInfo)/sizeof(BoundaryInfo[0]); item++){
                if (pos == BoundaryInfo[item].position){
                    Coeff[i][j].ac = Coeff[i][j].ac + Coeff[i][j].ae - 2*Coeff[i][j].ae; 
                    Coeff[i][j].bsrc -= 2*Coeff[i][j].ae*BoundaryInfo[item].T;
                    Coeff[i][j].ae = 0.0;
                }
            }

            pos = cellFacesID[i][j].WEST;
            for (int item=0; item < sizeof(BoundaryInfo)/sizeof(BoundaryInfo[0]); item++){
                if (pos == BoundaryInfo[item].position){
                    Coeff[i][j].ac = Coeff[i][j].ac + Coeff[i][j].aw - 2*Coeff[i][j].aw; 
                    Coeff[i][j].bsrc -= 2*Coeff[i][j].aw*BoundaryInfo[item].T;
                    Coeff[i][j].aw = 0.0;
                }
            }

            pos = cellFacesID[i][j].SOUTH;
            for (int item=0; item < sizeof(BoundaryInfo)/sizeof(BoundaryInfo[0]); item++){
                if (pos == BoundaryInfo[item].position){
                    Coeff[i][j].ac = Coeff[i][j].ac + Coeff[i][j].as - 2*Coeff[i][j].as; 
                    Coeff[i][j].bsrc -= 2*Coeff[i][j].as*BoundaryInfo[item].T;
                    Coeff[i][j].as = 0.0;
                }
            }

            pos = cellFacesID[i][j].NORTH;
            for (int item=0; item < sizeof(BoundaryInfo)/sizeof(BoundaryInfo[0]); item++){
                if (pos == BoundaryInfo[item].position){
                    Coeff[i][j].ac = Coeff[i][j].ac + Coeff[i][j].an - 2*Coeff[i][j].an; 
                    Coeff[i][j].bsrc -= 2*Coeff[i][j].an*BoundaryInfo[item].T;
                    Coeff[i][j].an = 0.0;
                }
            }                        
        }
    }
    
    //print 
    // std::cout << "Coefficient matrix has been created" << std::endl;
    // for (int i=0; i<ncy; i++){
    //     for (int j=0; j<ncx; j++){
    //         std::cout << std::setw(6) << Coeff[i][j].bsrc ;
    //     }
    //     std::cout << std::endl;
    // }
}