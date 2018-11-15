#ifndef FONTSIZE_H
#define FONTSIZE_H


class FontSize
{
public:
    static double linearTransform(double X, int A, int B, int C, int D);
    static int getBigFont(int *windowWidth);
    static int getSmallFont(int *windowWidth);

private:
    FontSize () {} // dissalow creation of an instance of this class
    // Font sizes for min and max values
    static const int bigFontMax = 31;
    static const int bigFontMin = 10;
    static const int smallFontMax = 24;
    static const int smallFontMin = 5;

    // min and max window width
    static const int minWidth = 0;
    static const int maxWidth = 3840;

};

#endif // FONTSIZE_H
