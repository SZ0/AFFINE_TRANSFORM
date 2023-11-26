#include "AffineTransformer2D.h"

AffineTransformer2D::AffineTransformer2D(){}

float AffineTransformer2D::Clamp(float value, float min, float max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

void AffineTransformer2D::TransformImage(Matrix tran, ImageFileReaderWriter inIm, ImageFileReaderWriter & outIm) {
//     float coordinateSystemRangeMinX = -1.;
//     float coordinateSystemRangeMaxX = 1.;
//     float coordinateSystemRangeMinY = -1.;
//     float coordinateSystemRangeMaxY = 1.;

    float coordinateSystemRangeMinX = 0.f;
    float coordinateSystemRangeMaxX = 1067.;
    float coordinateSystemRangeMinY = 0.f;
    float coordinateSystemRangeMaxY = 800.;
    int rowCount = inIm.GetRows();
    int columnCount = inIm.GetColumns();

    Matrix tranInv = Matrix(3,3);
    Matrix::GetMatrixOfInverseTransformOfAffineTransform2D(tran, tranInv);

    std::cout << "print T: " << std::endl;
    tran.PrintMatrix();
    std::cout << "print Tinv: " << std::endl;
    tranInv.PrintMatrix();

    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < columnCount; c++) {
            float pixelValue = 0.0;

            float pX = Matrix::MapPixelToCoordinate (c, coordinateSystemRangeMinX, coordinateSystemRangeMaxX, columnCount);
            // sanity check that you get the same coordinate back
            // float cBack = Matrix::MapCoordinateToFloatPixelCoordinate (pX, coordinateSystemRangeMinX, coordinateSystemRangeMaxX, columnCount);
            // std::cout << "from : " << c << " to " << pX << " to " << cBack << std::endl;
            pX = AffineTransformer2D::Clamp(pX, coordinateSystemRangeMinX, coordinateSystemRangeMaxX);

            float pY = Matrix::MapPixelToCoordinate (r, coordinateSystemRangeMinY, coordinateSystemRangeMaxY, rowCount);
            // float rBack = Matrix::MapCoordinateToFloatPixelCoordinate (pY, coordinateSystemRangeMinY, coordinateSystemRangeMaxY, rowCount);
            //   std::cout << "from : " << r << " to " << rBack << std::endl;
            pY = AffineTransformer2D::Clamp(pY, coordinateSystemRangeMinY, coordinateSystemRangeMaxY);


            Matrix point = Matrix(3, 1, true);
            point.SetValueAtRowColumn(pX, 0, 0);
            point.SetValueAtRowColumn(pY, 1, 0);
            point.SetValueAtRowColumn(1.f, 2, 0);
            // get the inverse transform point that will be used to sample original image
            Matrix samplePoint = Matrix(3, 1, true);
            Matrix::MatrixMulti(tranInv, point, samplePoint);
            // now sample the original image

            // std::cout << "print p': " << std::endl;
            // samplePoint.PrintMatrix();

            float sampledValue = AffineTransformer2D::BilinearSample(inIm, samplePoint,
coordinateSystemRangeMinX, coordinateSystemRangeMaxX, coordinateSystemRangeMinY, coordinateSystemRangeMaxY);

            // find out the pixel color
            // write the pixel to the image
            outIm.SetValueAtRowColumn(sampledValue, r,c);
        }
    }
}


float AffineTransformer2D::BilinearSample(const ImageFileReaderWriter & inIm, Matrix samplePoint, float cooMinX, float cooMaxX, float cooMinY, float cooMaxY) {
    // get back the indices for an image
    float cBack = Matrix::MapCoordinateToFloatPixelCoordinate (samplePoint.GetValueAt(0,0), cooMinX, cooMaxX, inIm.GetColumns());

    float rBack = Matrix::MapCoordinateToFloatPixelCoordinate (samplePoint.GetValueAt(1,0), cooMinY, cooMaxY, inIm.GetRows());

    // find 4 neighbour indices
    int cLeft = 0;
    int cRight = 0;
    if ( cBack <= 0 ) {
        cLeft = 0;
        cRight = 0;
        cBack = 0;
    } else if (cBack >= inIm.GetColumns() -1) {
        cLeft = inIm.GetColumns() -1;
        cRight = inIm.GetColumns() -1;
        cBack = inIm.GetColumns() -1;;
    } else {
        cLeft = (int)cBack;
        cRight = cLeft + 1;
    }

    int rBottom = 0;
    int rTop = 0;
    if ( rBack <= 0 ) {
        rBottom = 0;
        rTop = 0;
        rBack = 0;
    } else if (rBack >= inIm.GetRows() -1) {
        rBottom = inIm.GetRows() -1;
        rTop = inIm.GetRows() -1;
        rBack = inIm.GetRows() -1;;
    } else {
        rBottom = (int)rBack;
        rTop = rBottom + 1;
    }

    // now we have four neighbour indices, get the four neighbour pixel values
    float alphaC = cBack - (float)cLeft;
    float alphaR = rBack - (float)rBottom;
    float vBL = inIm.GetValueAt(rBottom, cLeft);
    float vBR = inIm.GetValueAt(rBottom, cRight);
    float vTL = inIm.GetValueAt(rTop, cLeft);
    float vTR = inIm.GetValueAt(rTop, cRight);
    // interpolate the four neighbour values
    float sampledValue = (vBL * (1-alphaR) + vTL * alphaR) * (1 - alphaC) +
                     (vBR * (1-alphaR) + vTR * alphaR) * (alphaC);

    return sampledValue;
}
