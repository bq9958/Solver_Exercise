#include "StructuredMesh.h"


StructuredMesh::StructuredMesh()
{
    dx = (xmax - xmin)/ncx;
    dy = (ymax - ymin)/ncy;

    // std::cout << "xmin, xmax: " << xmin << " " << xmax << endl;
    // std::cout << "ymin, ymax: " << ymin << " " << ymax << endl;
    // std::cout << "dx, dy: " << dx << " " << dy << endl;
    this->createMesh();
    this->createBoundaryMesh();
}

StructuredMesh::~StructuredMesh(){}

void StructuredMesh::createMesh(){
    // 网格中心坐标
	for (int i = 0; i < ncx; i++)
		this->xc[i] = xmin + this->dx/2.0 + i*this->dx;
	for (int i = 0; i < ncy; i++)
		this->yc[i] = ymin + this->dy/2.0 + i*this->dy;

    // 网格面坐标
    for (int i=0; i < ncx+1; i++){
        this->xf[i] = xmin + i*this->dx;
    }
    for (int i=0; i < ncy+1; i++){
        this->yf[i] = ymin + i*this->dy;
    }    
    
    // std::cout << "Mesh has been created." << std::endl;
    // std::cout << "Face coordinates in direction x:" << std::endl;
	// for (fp i : xf)
	// 	std::cout << i << " ";
	// std::cout << std::endl;
	// std::cout << "Face coordinates in direction y:" << std::endl;
	// for (fp i : yf)
	// 	std::cout << i << " ";
	// std::cout << std::endl;
}

fp eps = 1.0E-6;

void StructuredMesh::createBoundaryMesh(){
    this->cellFacesID.resize(boost::extents[ncy][ncx]);
    
    for (int i=0; i<ncy; i++){
        for (int j=0; j<ncx; j++){
            cellFacesID[i][j].EAST = INTERIOR;
            cellFacesID[i][j].WEST = INTERIOR;
            cellFacesID[i][j].SOUTH = INTERIOR;
            cellFacesID[i][j].NORTH = INTERIOR;
        }
    }
    
    for (int i=0; i < ncy; i++){
        for (int j=0; j < ncx; j++){
            if (std::abs(xf[j]-xmin)<eps){
                cellFacesID[i][j].WEST = X_MIN;
            }
            if (std::abs(xf[j+1]-xmax)<eps){
                cellFacesID[i][j].EAST = X_MAX;
            }
            if (std::abs(yf[i]-ymin)<eps){
                cellFacesID[i][j].SOUTH = Y_MIN;
            }
            if (std::abs(yf[i+1]-ymax)<eps){
                cellFacesID[i][j].NORTH = Y_MAX;
            }
        }
    }

    // print
    // std::cout << "Boudary mesh has been created" << std::endl;
    // std::cout << std::left << std::setw(10) << "cellID" << std::setw(10) << "east" << std::setw(10) << "west" << std::setw(10) <<  "north" << std::setw(10) << "south" << std::endl;
	// for (int i = 0; i < ncy; ++i)
	// 	for (int j = 0; j < ncx; ++j)
	// 	{
	// 		std::cout << std::left << std::setw(10) << j + i*ncx 
	// 					  << std::setw(10) << EnumFacePosition(this->cellFacesID[i][j].EAST)
	// 					  << std::setw(10) << EnumFacePosition(this->cellFacesID[i][j].WEST)
	// 					  << std::setw(10) << EnumFacePosition(this->cellFacesID[i][j].NORTH)
	// 					  << std::setw(10) << EnumFacePosition(this->cellFacesID[i][j].SOUTH) << std::endl;
    //     }
}


