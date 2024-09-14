#include "StructuredMesh.h"
#include "Material.h"
#include "CoeffMatrix.h"
#include "IterativeSolver.h"
#include "postprocessing.h"

int main(){
    StructuredMesh mesh;
    Material material;
    CoeffMatrix coeffmatrix(mesh,material);

    fp dx = mesh.getdx();
    fp dy = mesh.getdy();

    coeffmatrix.DiffusionCoeff(dx, dy);
    // coeffmatrix.convectionCoeff(dx, dy);
    std::array<std::array<COEFF,ncx>,ncy> Coeff = coeffmatrix.getCoeff();

    // std::cout << "-------bsrc------" << std::endl;
    // for (int i=0; i<ncy; i++){
    //     for (int j=0; j<ncx; j++){
    //         std::cout << std::left << std::setw(6) << Coeff[i][j].bsrc;
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << "-------ae------" << std::endl;
    // for (int i=0; i<ncy; i++){
    //     for (int j=0; j<ncx; j++){
    //         std::cout << std::left << std::setw(6) << Coeff[i][j].ae;
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << "-------aw------" << std::endl;
    // for (int i=0; i<ncy; i++){
    //     for (int j=0; j<ncx; j++){
    //         std::cout << std::left << std::setw(6) << Coeff[i][j].aw;
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << "-------as------" << std::endl;
    // for (int i=0; i<ncy; i++){
    //     for (int j=0; j<ncx; j++){
    //         std::cout << std::left << std::setw(6) << Coeff[i][j].as;
    //     }
    //     std::cout << std::endl;
    // }       

    // std::cout << "-------an------" << std::endl;
    // for (int i=0; i<ncy; i++){
    //     for (int j=0; j<ncx; j++){
    //         std::cout << std::left << std::setw(6) << Coeff[i][j].an;
    //     }
    //     std::cout << std::endl;
    // }   

    int ntotal_iter;
    fp L2norm_max = -1.0E20;
    fp nonLinearRes;
    bool stopSim = false;

    for (int nl_iter=1; nl_iter<nNonLinIter+1; nl_iter++){
        IterativeSolver iterativesolver(coeffmatrix, material, nl_iter, ntotal_iter);
        fp L2norm = iterativesolver.solve();
        L2norm_max = std::max(L2norm,L2norm_max) + 1.0E-20;
        nonLinearRes = L2norm/L2norm_max;

        std::cout << "nonLinearRes: " << nonLinearRes << std::endl;

        if(nonLinearRes < nonLinearResLimit)
            stopSim = true;
        if (stopSim == true)
        {
            iterativesolver.printField();
            Postprocessing post;
            post.writeVTKCollocated(mesh,material);
            break;
        }
    }
}