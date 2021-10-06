//
// Created by azari on 28.09.2021.
//

#ifndef CELL_COUNT_MORPHOLOGY_H
#define CELL_COUNT_MORPHOLOGY_H

#include <QImage>
#include "imageProcessing.h"

namespace Morph {
    auto erosion(const QImage &inputImg, const IP::Kernel &kernel) -> QImage;

    auto dilation(const QImage &inputImg, const IP::Kernel &kernel) -> QImage;

    auto opening(const QImage &inputImg, const IP::Kernel &kernel) -> QImage;

    auto closing(const QImage &inputImg, const IP::Kernel &kernel) -> QImage;

    auto erosion(const QImage &inputImg, const IP::Kernel &kernel, int iterations) -> QImage;

    auto dilation(const QImage &inputImg, const IP::Kernel &kernel, int iterations) -> QImage;

    auto opening(const QImage &inputImg, const IP::Kernel &kernel, int iterations) -> QImage;

    auto closing(const QImage &inputImg, const IP::Kernel &kernel, int iterations) -> QImage;


}

#endif //CELL_COUNT_MORPHOLOGY_H
