#ifndef AUXILARYFUNCTIONS_H
#define AUXILARYFUNCTIONS_H

#include "input.h"
#include <boost/multi_array.hpp>
#include <iostream>

using namespace std;

fp L2norm(const boost::multi_array<fp,2>& newField, const boost::multi_array<fp,2>& oldField);

std::string EnumFacePosition(FACE_POSITION pos); 


#endif