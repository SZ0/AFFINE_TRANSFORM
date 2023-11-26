#include <iostream>
#include <ImageFileReaderWriter.h>
#include <AffineTransformer2D.h>

/*!
 * Main function.
 * Has desired transform hardcoded and
 * runs classes that:
 * - read the image from the input file;
 * - does the transform;
 * - output the transformed image to a file.
 * @param argc does nothing; it is left here for convention or arguments in the future.
 * @param argv does nothing; it is left here for convention or arguments in the future.
 * @return returns 0 if the program exited without detected issues.
 */
int main (int argc, char* argv[])
{
    std::cout << "Program Affine Transform started." << std::endl;

    int imageRows = 1067;
    int imageColumns = 800;

    std::string inputDataFilepath = "./assets/input.txt";
    ImageFileReaderWriter inputImage = ImageFileReaderWriter(inputDataFilepath, imageRows, imageColumns);
    // std::string testInputFilepath = "./assets/inputWrittenBackForTest.txt";
		// inputImage.writeDataToFile(testInputFilepath);

		ImageFileReaderWriter outputImage = ImageFileReaderWriter(imageRows, imageColumns);
		std::vector<float> valuesInputTransformMatrix{ 1.465115, 0.284790, -374.387848, -0.284790, 1.465115, -86.353905 };
		// std::vector<float> valuesInputTransformMatrix{ 1., 0, 0, 0, 1., 0 };		// sanity check
		Matrix inputTransformMatrix = Matrix(valuesInputTransformMatrix, 2, 3);

		AffineTransformer2D affineTransformer2D;
		affineTransformer2D.TransformImage(inputTransformMatrix, inputImage, outputImage);

    std::string outputDataFilepath = "./assets/output.txt";
		outputImage.writeDataToFile(outputDataFilepath);
    return 0;
}				/* ----------  end of function main  ---------- */
