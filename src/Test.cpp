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

    coeffmatrix.DiffusionCoeff(conductivity, dx, dy, ncx, ncy);

    int ntotal_iter;
    fp L2norm_max = -1.0E20;
    fp nonLinearRes;
    bool stopSim = false;

    for (int nl_iter=1; nl_iter<nNonLinIter+1; nl_iter++){
        IterativeSolver iterativesolver(coeffmatrix, material, nl_iter, ntotal_iter);
        fp L2norm = iterativesolver.solve();
        L2norm_max = std::max(L2norm,L2norm_max);
        nonLinearRes = L2norm/L2norm_max;

        std::cout << nonLinearRes << std::endl;

        if (nl_iter == 9)
        {
            iterativesolver.printField();
        }

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