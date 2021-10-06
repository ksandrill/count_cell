//
// Created by azari on 28.09.2021.
//

#ifndef CELL_COUNT_IMAGEPROCESSING_H
#define CELL_COUNT_IMAGEPROCESSING_H

#include <QImage>

namespace IP {
    using HsvThreshold = std::tuple<int, int, int>;
    using Kernel = std::vector<std::vector<int>>;

    auto inRange(const QImage &inputImage, const HsvThreshold &lowThr, const HsvThreshold &highThr) -> QImage;

    auto swapGround(const QImage &inputImage) -> QImage;

    Kernel getEllipticKernel(int xSize, int ySize);

    Kernel getRectangleKernel(int xSize, int ySize);

}
#endif //CELL_COUNT_IMAGEPROCESSING_H
