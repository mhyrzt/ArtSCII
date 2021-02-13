/*
    @author -> Mahyar Riazati [mhyrzt]
    @email  -> mr.riazati1999@gmail.com
    @date   -> Februray 2021 
*/

#include <stdio.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize.h"


#define TURING          "turing.jpg"
#define HIGH_QUALITY    100
#define BW_IMAGE_NAME   "image_bw_out.jpg"
#define ASCII_CHARS     "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'."
#define ASCII_CHARS_LEN (strlen(ASCII_CHARS) - 1)
#define RESIZE_X        512
#define RESIZE_Y        512
#define RANGE_MIN       33
#define RANGE_MAX       126
#define IMAGE_DATA_IN   unsigned char *img, int w, int h, int c
#define IMAGE_DATA_PASS img, w, h, c
#define PIXEL_DATA_IN   int x, int y
#define PIXEL_DATA_PASS x, y
#define MAX_INTENSE     255.000000
#define GET_BW_VALUE    getPixelValueBw(IMAGE_DATA_PASS, PIXEL_DATA_PASS)
#define GET_RATIO       (GET_BW_VALUE / MAX_INTENSE)
#define ASCII_INDEX     getIndexASCII(IMAGE_DATA_PASS, PIXEL_DATA_PASS)


int getPixelValueBw(IMAGE_DATA_IN, PIXEL_DATA_IN){
    return img[c * (y * w + x)];
}

int getIndexASCII(IMAGE_DATA_IN, PIXEL_DATA_IN){
    return GET_RATIO * ASCII_CHARS_LEN;
}

char getCharASCII(IMAGE_DATA_IN, PIXEL_DATA_IN){
    return ASCII_CHARS[ASCII_INDEX];
}

char getASCII(IMAGE_DATA_IN, PIXEL_DATA_IN){
    return (char) GET_RATIO * (RANGE_MAX - RANGE_MIN) + RANGE_MIN;
}


size_t calcSize(int w, int h, int c){
    return w * h * c;
}

int bwChannels(int c){
    return c == 4 ? 2 : 1;
}

size_t calcSizeBW(int w, int h, int c){
    return bwChannels(c) * w * h; 
}

unsigned char *bwImage(IMAGE_DATA_IN){
    unsigned char* bw_image = malloc(calcSizeBW(w, h, c));
    
    if (!bw_image){
        printf("can't allocate memory :( \n");
        exit(1);
    }
    
    int bw_channels = bwChannels(c);
    size_t img_size = calcSize(w, h, c);
    
    for (
        unsigned char *p = img, *pg  = bw_image;
        p != img + img_size;
        p += c, pg += bw_channels
    ){
        *pg = (uint8_t)((*p + *(p + 1) + *(p + 2)) / 3.0);
        if (c == 4) *(pg + 1) = *(p + 3); 
    }
    return bw_image;
}

void printASCII(IMAGE_DATA_IN){
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++)
            printf("%c", getCharASCII(img, w, h, c, j, i));
        printf("\n");
    }
}

int main(int argc, char **argv){
    int width   ,
        height  ,
        channels;
    
    unsigned char *img  = stbi_load(
        argc > 1 ? argv[1] : TURING,
        &width,
        &height,
        &channels,
        0
    );
   printf("%d %d %d \n", width, height, channels); 
    if (!img) {
        printf("AN ERROR HAPPEND ! :(\n");
        exit(1);
    }
    
    unsigned char* bw_image = bwImage(img, width, height, channels);
    stbi_write_jpg(
        BW_IMAGE_NAME, 
        width, 
        height, 
        bwChannels(channels),
        bw_image,
        HIGH_QUALITY
    );

    printASCII(bw_image, width, height, channels);

    stbi_image_free(img);
    free(bw_image);
    return 0;
}

