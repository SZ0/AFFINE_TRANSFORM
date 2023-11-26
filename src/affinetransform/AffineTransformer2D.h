#pragma once
#include "ImageFileReaderWriter.h"

class AffineTransformer2D
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
        AffineTransformer2D();

        /* ====================  other functions     ======================================= */
void TransformImage(Matrix tran, ImageFileReaderWriter inIm, ImageFileReaderWriter & outIm);


static float BilinearSample(const ImageFileReaderWriter & inIm, Matrix samplePoint, float cooMinX, float cooMaxX, float cooMinY, float cooMaxY);

static float Clamp(float value, float min, float max);
}; /* -----  end of class ImageFileReaderWriter  ----- */
