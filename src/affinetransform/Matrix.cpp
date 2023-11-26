#include "Matrix.h"

Matrix::Matrix(int rowCount, int columnCount) : Matrix(rowCount, columnCount, false) {}

Matrix::Matrix(int rowCount, int columnCount, bool suppressLog) {
    this->rowCount = rowCount;
    this->columnCount = columnCount;
    this->pixelData = std::vector<float>(rowCount * columnCount);
    if (!suppressLog) {
        std::cout << "Creating a matrix of size: " << this->rowCount << " rows x " << this->columnCount << " columns." << std::endl;
    }
}


Matrix::Matrix(std::vector<float> pixelData, int rowCount, int columnCount) : Matrix(rowCount, columnCount) {
    this->pixelData = pixelData;
}


int Matrix::GetRows () const {
    return this->rowCount;
}


int Matrix::GetColumns () const {
    return this->columnCount;
}


float Matrix::GetValueAt (int row, int column) const {
    return this->pixelData[row * this->columnCount + column];
}


void Matrix::SetValueAtRowColumn(float value, int row, int column) {
    this->pixelData[row * this->columnCount + column] = value;
}


float Matrix::MapPixelToCoordinate (int pixelIndex, float minCoordinate, float maxCoordinate, int pixelCount /*as in: max pixel index + 1*/) {
    float chunk = (maxCoordinate - minCoordinate) / (float)pixelCount;
    float coordinatePosition = minCoordinate + chunk / 2 + chunk * pixelIndex;
    return coordinatePosition;
}

float Matrix::MapCoordinateToFloatPixelCoordinate (float coor, float minCoordinate, float maxCoordinate, int pixelCount) {
    float coordinateStripLength = maxCoordinate - minCoordinate;
    float distanceToMinCoordinate = coor - minCoordinate;
    float shareOfCoordinateStrip = distanceToMinCoordinate / coordinateStripLength;
    return (float)pixelCount * shareOfCoordinateStrip - 0.5f;
}

void Matrix::MatrixMulti(Matrix left, Matrix right, Matrix & out) {
    for (int io = 0; io < out.GetRows(); io++) {
        for (int jo = 0; jo < out.GetColumns(); jo++) {
            float sum = 0;
            for (int ii = 0; ii < out.GetRows(); ii++) {
                sum += left.GetValueAt(io, ii) * right.GetValueAt(ii, jo);
            }
            out.SetValueAtRowColumn(sum, io, jo);
        }
    }
}


void Matrix::GetMatrixOfInverseTransformOfAffineTransform2D (Matrix t, Matrix & out/*t inverse transformation*/) {
    float a11 = t.GetValueAt(0, 0);
    float a12 = t.GetValueAt(0, 1);
    float a21 = t.GetValueAt(1, 0);
    float a22 = t.GetValueAt(1, 1);
    float b1 = t.GetValueAt(0, 2);
    float b2 = t.GetValueAt(1, 2);
    float tmpF = 1 / (a11*a22 - a12*a21);
		std::vector<float> valuesAInv { tmpF*a22, -tmpF*a12, -tmpF*a21, tmpF*a11 };
		Matrix AInv = Matrix(valuesAInv, 2, 2);
		std::vector<float> valuestInvTranslationColumn { b1, b2 };
		Matrix tTranslationColumn = Matrix(valuestInvTranslationColumn, 2, 1);
		Matrix tInvTranslationColumn = Matrix(2, 1);
    
    Matrix::MatrixMulti(AInv, tTranslationColumn, tInvTranslationColumn);

    out.SetValueAtRowColumn(AInv.GetValueAt(0,0),                  0,0);
    out.SetValueAtRowColumn(AInv.GetValueAt(0,1),                  0,1);
    out.SetValueAtRowColumn(- tInvTranslationColumn.GetValueAt(0,0), 0,2);
    out.SetValueAtRowColumn(AInv.GetValueAt(1,0),                  1,0);
    out.SetValueAtRowColumn(AInv.GetValueAt(1,1),                  1,1);
    out.SetValueAtRowColumn(- tInvTranslationColumn.GetValueAt(1,0), 1,2);
    out.SetValueAtRowColumn(0.f,                                   2,0);
    out.SetValueAtRowColumn(0.f,                                   2,1);
    out.SetValueAtRowColumn(1.f,                                   2,2);
}


void Matrix::PrintMatrix () {
    for (int r = 0; r < this->rowCount; r++) {
        for (int c = 0; c < this->columnCount; c++) {
            std::cout << std::to_string(this->pixelData[r * this->columnCount + c]);
            if (c != this->columnCount) {
                std::cout << " ";
            }
        }
        if (r != this->rowCount) {
            std::cout << std::endl;
        }
    }
}
