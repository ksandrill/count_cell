//
// Created by azari on 28.09.2021.
//

#include <iostream>
#include "imageProcessing.h"

auto IP::inRange(const QImage &inputImage, const IP::HsvThreshold &lowThr, const IP::HsvThreshold &highThr) -> QImage {
    auto outputImage = inputImage.copy();
    auto width = inputImage.width();
    auto height = inputImage.height();
    auto[lowH, lowS, lowV] = lowThr;
    auto[highH, highS, highV] = highThr;
    for (auto i = 0; i < width; ++i) {
        for (auto j = 0; j < height; ++j) {
            int imgH, imgS, imgV;
            auto pixelColor = inputImage.pixelColor(i, j);
            pixelColor.getHsv(&imgH, &imgS, &imgV);
            //// std::cout << imgH << " ," << imgS << "," << imgV << " type : ";
            if ((lowH <= imgH and imgH <= highH) and (lowS <= imgS and imgS <= highS) and
                (lowV <= imgV and imgV <= highV)) {
                outputImage.setPixel(i, j, QColor(255, 255, 255).rgb());
                //// std::cout << "white" << std::endl;

            } else {
                outputImage.setPixel(i, j, QColor(0, 0, 0).rgb());
                //// std::cout << "black" << std::endl;


            }
        }
    }
    return outputImage.convertToFormat(QImage::Format_Mono);
}

auto isDotInEllipse(int x, int y, float a, float b) -> bool {
    return (pow(x, 2) / pow(a, 2) + pow(y, 2) / pow(b, 2)) <= 1;
}


auto IP::getEllipticKernel(int xSize, int ySize) -> IP::Kernel {
    auto kernel = Kernel(xSize, std::vector<int>(ySize, 0));
    auto xCenter = xSize / 2;
    auto yCenter = ySize / 2;
    auto a = float(xSize) / 2;
    auto b = float(ySize) / 2;
    for (auto i = 0; i < xSize; ++i) {
        int xPos = i - xCenter;
        for (auto j = 0; j < ySize; ++j) {
            int yPos = j - yCenter;
            if (isDotInEllipse(xPos, yPos, a, b)) {
                kernel[i][j] = 1;
            }
        }
    }
    return kernel;
}


auto IP::getRectangleKernel(int xSize, int ySize) -> IP::Kernel {
    auto kernel = Kernel(xSize, std::vector<int>(ySize, 1));
    return kernel;
}

auto IP::swapGround(const QImage &inputImage) -> QImage {
    auto outputImage = inputImage.copy();
    auto width = outputImage.width();
    auto height = outputImage.height();
    for (auto i = 0; i < width; ++i) {
        for (auto j = 0; j < height; ++j) {
            auto colorValue = inputImage.pixelColor(i, j).value();
            auto newColor = 0;
            if (colorValue == 255) {
                newColor = 1;
            }
            outputImage.setPixel(i, j, newColor);
        }
    }
    return outputImage;
}
