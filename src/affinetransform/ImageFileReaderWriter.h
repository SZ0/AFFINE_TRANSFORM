#pragma once
#include <iostream>
#include <vector>
#include "Matrix.h"

class ImageFileReaderWriter : public Matrix
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
        ImageFileReaderWriter(std::string filepath, int rowCount, int columnCount);
        ImageFileReaderWriter(int rowCount, int columnCount);

        /* ====================  other functions     ======================================= */
        void writeDataToFile(std::string filepath);
}; /* -----  end of class ImageFileReaderWriter  ----- */
