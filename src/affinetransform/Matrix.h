#pragma once
#include <vector>
#include <iostream>

class Matrix
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
        Matrix(int rowCount, int columnCount, bool suppressLog);
        Matrix(int rowCount, int columnCount);
        Matrix(std::vector<float> pixelData, int rowCount, int columnCount);

        /* ====================  ACCESSORS/SETTERS     ======================================= */
        int GetRows () const;
        int GetColumns () const;
        float GetValueAt (int row, int column) const;

        /* ==================== MUTATORS/GETTERS     ======================================= */
        void SetValueAtRowColumn(float value, int row, int column);

        /* ====================  OTHER ======================================= */

        void PrintMatrix ();

        static float MapPixelToCoordinate (int pixelIndex, float minCoordinate, float maxCoordinate, int pixelCount);
        static float MapCoordinateToFloatPixelCoordinate (float coor, float minCoordinate, float maxCoordinate, int pixelCount);

        static void GetMatrixOfInverseTransformOfAffineTransform2D (Matrix t, Matrix & out);
        static void MatrixMulti(Matrix left, Matrix right, Matrix & out);



    protected:
        int rowCount;
        int columnCount;
        std::vector<float> pixelData;
        


}; /* -----  end of class ImageFileReaderWriter  ----- */
