#include <iostream>
#include <QApplication>
#include <QLabel>
#include <stack>
#include "image_processing/imageProcessing.h"
#include "image_processing/morphology.h"
#include "image_processing/algorithms/filters.h"
#include "image_processing/algorithms/algorithms.h"


auto imageProcessing(const QImage &inputImage) -> QImage {
    auto outputImg = inputImage.copy();
    outputImg = Algorithms::OtsuBinarization(outputImg).convertToFormat(QImage::Format_Mono);
    ///outputImg = IP::inRange(outputImg, {-1, 0, 0}, {0, 0, 245});
    outputImg = IP::swapGround(outputImg);
    auto kernel3 = IP::getEllipticKernel(3, 3);
    outputImg = Morph::opening(outputImg, kernel3);
    outputImg = Morph::dilation(outputImg, kernel3);
    outputImg = Morph::closing(outputImg, kernel3);

    return outputImg;
}

auto spanFIll(const QImage &inputImage, std::pair<int, int> startPixelPos) -> QImage {
    auto outImage = inputImage.copy();
    auto pixelStack = std::stack<std::pair<int, int>>{};
    pixelStack.push(startPixelPos);
    while (not pixelStack.empty()) {
        auto curPixelPos = pixelStack.top();
        int x = curPixelPos.first;
        int y = curPixelPos.second;
        pixelStack.pop();
        if (x < 0 or x >= outImage.width() or y < 0 or y >= outImage.height()) {
            continue;
        }
        int r, g, b;
        outImage.pixelColor(x, y).getRgb(&r, &g, &b);
        if (r == 255 and g == 255 and b == 255) {
            outImage.setPixel(x, y, QColor(255, 0, 0).rgb());
            pixelStack.push({x, y + 1});
            pixelStack.push({x, y - 1});
            auto left_x = x + 1;
            if (left_x < outImage.width()) {
                outImage.pixelColor(left_x, y).getRgb(&r, &g, &b);
                while (r == 255 and g == 255 and b == 255) {
                    outImage.setPixel(left_x, y, QColor(255, 0, 0).rgb());
                    pixelStack.push({left_x, y + 1});
                    pixelStack.push({left_x, y - 1});
                    left_x++;
                    if (left_x >= outImage.width()) {
                        break;
                    }
                    outImage.pixelColor(left_x, y).getRgb(&r, &g, &b);
                }
            }
            auto right_x = x - 1;
            if (right_x >= 0) {
                outImage.pixelColor(right_x, y).getRgb(&r, &g, &b);
                while (r == 255 and g == 255 and b == 255) {
                    outImage.setPixel(right_x, y, QColor(255, 0, 0).rgb());
                    pixelStack.push({right_x, y + 1});
                    pixelStack.push({right_x, y - 1});
                    right_x--;
                    if (right_x < 0) {
                        break;
                    }
                    outImage.pixelColor(right_x, y).getRgb(&r, &g, &b);

                }
            }

        }

    }
    return outImage;

}

auto findCells(const QImage &inputImage) -> std::pair<QImage, int> {
    auto outputImage = inputImage.copy();
    auto countCells = 0;
    auto width = inputImage.width();
    auto height = inputImage.height();
    for (auto i = 0; i < width; ++i) {
        for (auto j = 0; j < height; ++j) {
            int r, g, b;
            outputImage.pixelColor(i, j).getRgb(&r, &g, &b);
            if (r == 255 and g == 255 and b == 255) {
                countCells++;
                outputImage = spanFIll(outputImage, {i, j});
            }


        }
    }
    return {outputImage, countCells};
}

auto main(int argc, char *argv[]) -> int {
    QApplication a(argc, argv);
    auto label = std::make_unique<QLabel>();
    auto img = imageProcessing(QImage("../cell_pictures/pic1.jpg"));
    img = img.convertToFormat(QImage::Format_RGB32);
    int counter;
    std::tie(img, counter) = findCells(img);;
    std::cout << " cells number: " << counter;
    label->setPixmap(QPixmap::fromImage(img));
    label->show();
    return QApplication::exec();
}
