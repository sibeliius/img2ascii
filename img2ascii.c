#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


void toGrayscale(unsigned char *img, unsigned char *grayImg, int channels, int grayChannels, int x, int y, FILE *asciiText);
unsigned char toGrayVal(unsigned char *img, int i);
unsigned char getGrayscaleChar(unsigned char grayVal);
void toASCII(unsigned char grayscaleChar, FILE *asciiText);

int main(int argc, char **argv) {
    FILE *asciiText;
    asciiText = fopen("asciitext.txt", "w");
    int x, y, channels;
    const char *fname = argv[1];
    char *ext = strrchr(fname, '.'); 

    if (fname == NULL) {
        printf("No filepath provided. Please try again.");
        return 1;
    }
    unsigned char *image = stbi_load(fname, &x, &y, &channels, 0);
    int grayChannels = channels == 4 ? 2 : 1;
    size_t grayImgSize = x * y * grayChannels;
    unsigned char *grayImg = malloc(grayImgSize);
    
    toGrayscale(image, grayImg, channels, grayChannels, x, y, asciiText);
    

    if (strcmp(ext, ".png") == 0) {
        stbi_write_png(fname, x, y, grayChannels, grayImg, x * grayChannels);
    } else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
        stbi_write_jpg(fname, x, y, grayChannels, grayImg, 100);
    }

    free(grayImg);
    stbi_image_free(image);
    return 0;
}

unsigned char toGrayVal(unsigned char *img, int i) {
    return (unsigned char)(0.21 * img[i] + 0.72 * img[i + 1] + 0.07 * img[i + 2]);
}

void toGrayscale(unsigned char *img, unsigned char *grayImg, int channels, int grayChannels, int x, int y, FILE *asciiText) {
    for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                int index = (i * x + j) * channels;
                int grayIndex = (i * x + j) * grayChannels;
                unsigned char grayVal = toGrayVal(img, index);
                grayImg[grayIndex] = grayVal;
                if (grayChannels == 2) {
                    grayImg[grayIndex + 1] = img[index + 3];
                }
                if ((index + 1) % y == 0) {
                    fputc("\n", asciiText);
                }
                else toASCII(getGrayscaleChar((grayVal)), asciiText);
            }
        }
}

unsigned char getGrayscaleChar(unsigned char grayVal) {
    char* charList = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`\'.";
    return charList[(int)ceil(strlen(charList) - 1 ) * grayVal / 255];
}

void toASCII(unsigned char grayscaleChar, FILE *asciiText) {
    fputc(grayscaleChar, asciiText);
}
