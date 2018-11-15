#include "fontsize.h"
/// @notice static class that computes the required font-sizes based on window width


/// @notice Maps value x in range [A,B] to new x in range [C, D]
/// @dev uses this Linear transform equation: newX = (X-A)/(B-A) * (D-C) + C
double FontSize::linearTransform(double X, int A, int B, int C, int D) {
    return (X-A)/(B-A) * (D-C) + C;
}

int FontSize::getBigFont(int *windowWidth) {
    return linearTransform(*windowWidth, minWidth, maxWidth, bigFontMin, bigFontMax);
}

int FontSize::getSmallFont(int *windowWidth) {
    return linearTransform(*windowWidth, minWidth, maxWidth, smallFontMin, smallFontMax);
}

int FontSize::getBorder(int *windowWidth) {
    return linearTransform(*windowWidth, minWidth, maxWidth, minBorder, maxBorder);
}
