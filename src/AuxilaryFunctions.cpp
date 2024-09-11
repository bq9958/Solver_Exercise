#include "AuxilaryFunctions.h"

fp L2norm(const boost::multi_array<fp,2>& newField, const boost::multi_array<fp,2>& oldField)
{
    fp deviation = 0.0, result = 0.0;
    for(unsigned int j = 0; j < oldField.shape()[1]; ++j)
        for(unsigned int i = 0; i < oldField.shape()[0]; ++i)
        {
            deviation = newField[i][j] - oldField[i][j];
            result += std::pow(deviation, 2);
        }
    unsigned int ncell = oldField.shape()[0]*oldField.shape()[1];
    result = std::sqrt(result/ncell);
    return result;
}

std::string EnumFacePosition(FACE_POSITION pos)
{
	switch(pos){
	case 0: return "INTERIOR"; break;
	case 1: return "X_MIN"; break;
	case 2: return "X_MAX"; break;
	case 3: return "Y_MIN"; break;
	case 4: return "Y_MAX"; break;	
    default: return "UNKNOWN_POSITION";
    }
}
