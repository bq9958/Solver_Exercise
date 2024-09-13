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

void CoeffMatrix::convectionCoeff()
{
    // Central difference
    boost::multi_array<fp,2> u = material.getU();
    boost::multi_array<fp,2> rho = material.getrho();
    for (int i=0; i<ncy; i++){
        for (int j=0; j<ncx; j++){
            fp ue = (u[i][j]+u[i][j+1])/fp(2.0);
            fp uw = (u[i][j]+u[i][j-1])/fp(2.0);
            fp rhoe = (rho[i][j]+rho[i][j+1])/fp(2.0);
            fp rhow = (rho[i][j]+rho[i][j-1])/fp(2.0);
            Coeff[i][j].ae += rhoe*ue/fp(2.0);
            Coeff[i][j].aw += rhow*uw/fp(2.0);
            Coeff[i][j].ac += -(Coeff[i][j].ae+Coeff[i][j].aw);
        }
    }

    // 处理一维对流边界条件
    for (int i=0; i<ncy; i++){
        for (int j=0; j<ncx; j++){
            if (j==0){
                Coeff[i][j].ae = 0.0;
                Coeff[i][j].aw = 0.0;
                Coeff[i][j].an = 0.0;
                Coeff[i][j].as = 0.0;
                Coeff[i][j].ac = 1.0;
                Coeff[i][j].bsrc = 0.0;
            }   
            if (j==ncx-1){
                Coeff[i][j].ae = 0.0;
                Coeff[i][j].aw = 0.0;
                Coeff[i][j].an = 0.0;
                Coeff[i][j].as = 0.0;
                Coeff[i][j].ac = 1.0;
                Coeff[i][j].bsrc = 1.0;
            }
        }
    }
}

void CoeffMatrix::DiffusionCoeff(fp conductivity, fp dx, fp dy, int ncx, int ncy){
    for (int i=0; i<ncy; i++){
        for (int j=0; j<ncx; j++){
            Coeff[i][j].ae += -conductivity*dy/dx;
            Coeff[i][j].aw += -conductivity*dy/dx;
            Coeff[i][j].as += -conductivity*dx/dy;
            Coeff[i][j].an += -conductivity*dx/dy;
            Coeff[i][j].ac += -(Coeff[i][j].ae+Coeff[i][j].aw+Coeff[i][j].an+Coeff[i][j].as);
        }
    }

    // 处理扩散边界条件
    boost::multi_array<struct CELL_FACE,2> cellFacesID = mesh.getCellFacesID();
    FACE_POSITION pos;
    for (int i=0; i<ncy; i++){
        for (int j=0; j<ncx; j++){
            pos = cellFacesID[i][j].EAST;
            for (int item=0; item < sizeof(BoundaryInfo)/sizeof(BoundaryInfo[0]); item++){
                if (pos == BoundaryInfo[item].position){
                    if (BoundaryInfo[item].BC_T == DIRICHLET){
                        Coeff[i][j].ac = Coeff[i][j].ac + Coeff[i][j].ae - 2*Coeff[i][j].ae; 
                        Coeff[i][j].bsrc -= 2*Coeff[i][j].ae*BoundaryInfo[item].T;
                        Coeff[i][j].ae = 0.0;
                    }
                    else if(BoundaryInfo[item].BC_T == NEUMANN){
                        Coeff[i][j].ac = -(Coeff[i][j].aw + Coeff[i][j].an + Coeff[i][j].as);
                        Coeff[i][j].bsrc -= BoundaryInfo[item].heatflux*dy;
                    }
                }
            }

            pos = cellFacesID[i][j].WEST;
            for (int item=0; item < sizeof(BoundaryInfo)/sizeof(BoundaryInfo[0]); item++){
                if (pos == BoundaryInfo[item].position){
                    if (BoundaryInfo[item].BC_T == DIRICHLET){
                        Coeff[i][j].ac = Coeff[i][j].ac + Coeff[i][j].aw - 2*Coeff[i][j].aw; 
                        Coeff[i][j].bsrc -= 2*Coeff[i][j].aw*BoundaryInfo[item].T;
                        Coeff[i][j].aw = 0.0;
                    }
                    else if (BoundaryInfo[item].BC_T == NEUMANN){
                        Coeff[i][j].ac = -(Coeff[i][j].ae + Coeff[i][j].an + Coeff[i][j].as);
                        Coeff[i][j].bsrc -= BoundaryInfo[item].heatflux*dy;
                    }
                }
            }

            pos = cellFacesID[i][j].SOUTH;
            for (int item=0; item < sizeof(BoundaryInfo)/sizeof(BoundaryInfo[0]); item++){
                if (pos == BoundaryInfo[item].position){
                    if (BoundaryInfo[item].BC_T == DIRICHLET){
                        Coeff[i][j].ac = Coeff[i][j].ac + Coeff[i][j].as - 2*Coeff[i][j].as; 
                        Coeff[i][j].bsrc -= 2*Coeff[i][j].as*BoundaryInfo[item].T;
                        Coeff[i][j].as = 0.0;
                    }
                    else if (BoundaryInfo[item].BC_T == NEUMANN){
                        Coeff[i][j].ac = -(Coeff[i][j].ae + Coeff[i][j].an + Coeff[i][j].ae);
                        Coeff[i][j].bsrc -= BoundaryInfo[item].heatflux*dx;
                    }
                }
            }

            pos = cellFacesID[i][j].NORTH;
            for (int item=0; item < sizeof(BoundaryInfo)/sizeof(BoundaryInfo[0]); item++){
                if (pos == BoundaryInfo[item].position){
                    if (BoundaryInfo[item].BC_T == DIRICHLET){
                        Coeff[i][j].ac = Coeff[i][j].ac + Coeff[i][j].an - 2*Coeff[i][j].an; 
                        Coeff[i][j].bsrc -= 2*Coeff[i][j].an*BoundaryInfo[item].T;
                        Coeff[i][j].an = 0.0;
                    }
                    else if (BoundaryInfo[item].BC_T == NEUMANN){
                        Coeff[i][j].ac = -(Coeff[i][j].ae + Coeff[i][j].as + Coeff[i][j].ae);
                        Coeff[i][j].bsrc -= BoundaryInfo[item].heatflux*dx;
                    }
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