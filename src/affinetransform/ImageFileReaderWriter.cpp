#include "ImageFileReaderWriter.h"
#include <fstream>


// initializing static members

ImageFileReaderWriter::ImageFileReaderWriter(std::string filepath, int rowCount, int columnCount) : Matrix(rowCount, columnCount) {
    std::cout << "Reading image at path \"" << filepath << "\" of expected size : " << this->rowCount << " rows x " << this->columnCount << " columns." << std::endl;

    std::ifstream inputDataFile (filepath);
    std::string line;
    int idx = 0;
    if (inputDataFile.is_open()) {
        while ( getline (inputDataFile, line) )
        {
            auto chr = line.begin();
            do {
                auto begin = chr;
                while(*chr != ' ' && *chr)
                chr++;
                this->pixelData[idx++] = std::stof(std::string(begin, chr));
            } while (0 != *chr++);
        }
        inputDataFile.close();
        std::cout << "Finish loading image. Value count: " << idx << std::endl;
    }
}

ImageFileReaderWriter::ImageFileReaderWriter(int rowCount, int columnCount) : Matrix(rowCount, columnCount) {
}

void ImageFileReaderWriter::writeDataToFile(std::string filepath) {
		std::cout << "Attempting to write image to : " << filepath << std::endl;
		std::ofstream outputDataFile (filepath);
		if (outputDataFile.is_open())
		{
				for (int r = 0; r < this->rowCount; r++) {
						for (int c = 0; c < this->columnCount; c++) {
								outputDataFile << std::to_string(this->pixelData[r * this->columnCount + c]);
								if (c != this->columnCount) {
										outputDataFile << " ";
								}
						}
						if (r != this->rowCount) {
								outputDataFile << std::endl;
						}
				}
				outputDataFile.close();
		}
}
