/*
    @author -> Mahyar Riazati [mhyrzt]
    @email  -> mr.riazati1999@gmail.com
    @date   -> Februray 2021 
*/

#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#define TURING "turing.jpg"
#define HIGH_QUALITY 100
#define BW_IMAGE_NAME "image_bw_out.jpg"

size_t calcSize(int w, int h, int c){
    return w * h * c;
}

int bwChannels(int c){
    return c == 4 ? 2 : 1;
}

size_t calcSizeBW(int w, int h, int c){
    return bwChannels(c) * w * h; 
}

unsigned char *bwImage(unsigned char *img, int w, int h, int c){
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
    
    if (!img) {
        printf("AN ERROR HAPPEND ! :(\n");
        exit(1);
    }
    
    printf(
        "Height = %d px\nWidth = %d px\nChannels = %d\n",
        height,
        width,
        channels
    );
    unsigned char* bw_image = bwImage(img, width, height, channels);
    stbi_write_jpg(
        BW_IMAGE_NAME, 
        width, 
        height, 
        bwChannels(channels),
        bw_image,
        HIGH_QUALITY
    );
    printf("BW IMAGE WRITED SUCCESFULLY! ^~^\n");

    stbi_image_free(img);
    free(bw_image);
    return 0;
}

