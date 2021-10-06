//
// Created by azari on 28.09.2021.
//

#include "morphology.h"

#define WHITE 0
#define BLACK 1
#define WHITE_VALUE 255

auto Morph::erosion(const QImage &inputImg, const IP::Kernel &kernel) -> QImage {
    auto outputImage = inputImg.copy();
    auto xKernelSize = kernel.size();
    auto yKernelSize = kernel[0].size();
    auto xLen = inputImg.width() - xKernelSize + 1;
    auto yLen = inputImg.height() - yKernelSize + 1;
    int xOut = 1;
    for (int i = 0; i < xLen; ++i) {
        int yOut = 1;
        for (int j = 0; j < yLen; ++j) {
            bool isForegroundPixel = true;
            for (int kernelI = 0; kernelI < xKernelSize; ++kernelI) {
                for (int kernelJ = 0; kernelJ < yKernelSize; ++kernelJ) {
                    if (kernel[kernelI][kernelJ] != 0) {
                        if (inputImg.pixelColor(i + kernelI, j + kernelJ).value() != WHITE_VALUE) {
                            isForegroundPixel = false;
                            goto theEnd;

                        }
                    }
                }
            }
            theEnd:
            int newPixelColor = isForegroundPixel ? WHITE : BLACK;
            outputImage.setPixel(xOut, yOut, newPixelColor);
            yOut++;
        }
        xOut++;
    }
    return outputImage;
}


auto Morph::dilation(const QImage &inputImg, const IP::Kernel &kernel) -> QImage {
    auto outputImage = inputImg.copy();
    auto xKernelSize = kernel.size();
    auto yKernelSize = kernel[0].size();
    auto xLen = inputImg.width() - xKernelSize + 1;
    auto yLen = inputImg.height() - yKernelSize + 1;
    int xOut = 1;
    for (int i = 0; i < xLen; ++i) {
        int yOut = 1;
        for (int j = 0; j < yLen; ++j) {
            bool isForegroundPixel = false;
            for (int kernelI = 0; kernelI < xKernelSize; ++kernelI) {
                for (int kernelJ = 0; kernelJ < yKernelSize; ++kernelJ) {
                    if (kernel[kernelI][kernelJ] != 0) {
                        if (inputImg.pixelColor(i + kernelI, j + kernelJ).value() == WHITE_VALUE) {
                            isForegroundPixel = true;
                            goto theEnd;
                        }
                    }
                }
            }
            theEnd:
            int newPixelColor = isForegroundPixel ? WHITE : BLACK;
            outputImage.setPixel(xOut, yOut, newPixelColor);
            yOut++;
        }
        xOut++;
    }
    return outputImage;
}

auto Morph::opening(const QImage &inputImg, const IP::Kernel &kernel) -> QImage {
    return dilation(erosion(inputImg, kernel), kernel);
}

auto Morph::closing(const QImage &inputImg, const IP::Kernel &kernel) -> QImage {
    return erosion(dilation(inputImg, kernel), kernel);
}


auto Morph::opening(const QImage &inputImg, const IP::Kernel &kernel, int iterations) -> QImage {
    auto outputImage = inputImg.copy();
    for (auto i = 0; i < iterations; ++i) {
        outputImage = opening(outputImage, kernel);
    }
    return outputImage;
}

auto Morph::closing(const QImage &inputImg, const IP::Kernel &kernel, int iterations) -> QImage {
    auto outputImage = inputImg.copy();
    for (auto i = 0; i < iterations; ++i) {
        outputImage = closing(outputImage, kernel);
    }
    return outputImage;
}

auto Morph::erosion(const QImage &inputImg, const IP::Kernel &kernel, int iterations) -> QImage {
    auto outputImage = inputImg.copy();
    for (auto i = 0; i < iterations; ++i) {
        outputImage = erosion(outputImage, kernel);
    }
    return outputImage;
}

auto Morph::dilation(const QImage &inputImg, const IP::Kernel &kernel, int iterations) -> QImage {
    auto outputImage = inputImg.copy();
    for (auto i = 0; i < iterations; ++i) {
        outputImage = dilation(outputImage, kernel);
    }
    return outputImage;
}