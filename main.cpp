#include <fstream>
#include <stdint.h>
#include <stdio.h>
using namespace std;

//https://solarianprogrammer.com/2018/11/19/cpp-reading-writing-bmp-images/

// uint8_t char
// uint16_t shortint
// uint32_t int
// uint64_t longlong

typedef uint8_t ubyte;

static const int fileHeaderSize=14;
static const int informationHeaderSize = 40;

struct Image
{
   size_t size;
   uint16_t file_type;

   ubyte fileHeader[fileHeaderSize];
   ubyte informationHeader[informationHeaderSize];

   uint32_t width;
   uint32_t height;
   uint16_t padding_amount;
};



uint16_t calc_file_type(Image *image)
{
    ubyte file_type_low = image->fileHeader[0];
    uint16_t file_type_high = image->fileHeader[1] << 8;
    uint16_t file_type = file_type_low + file_type_high;

    return file_type;
}

uint32_t calc_file_size(Image *image)
{
    uint32_t file_size= image->fileHeader[2] + (image->fileHeader[3]<<8) + (image->fileHeader[4]<<16) + (image->fileHeader[5]<<24);
    return file_size;
}

uint32_t calc_width(Image *image){
    uint32_t width = image->informationHeader[4] + (image->informationHeader[5]<<8) + (image->informationHeader[6]<<16) + (image->informationHeader[7]<<24);
    return width;
}

uint32_t calc_height(Image *image){
    uint32_t height = image->informationHeader[8] + (image->informationHeader[9]<<8) + (image->informationHeader[10]<<16) + (image->informationHeader[11]<<24);
    return height;
}

Image init_image(const char* path)
{
    Image New_Image={};

    ifstream fin;
    fin.open(path, ios::in | ios::binary);

    // read the 54 byte header
    fin.read((char*)New_Image.fileHeader,fileHeaderSize);
    fin.read((char*)New_Image.informationHeader, informationHeaderSize);
    //TODO reading for the pixel color information (b,g,r)

    return New_Image;
}

void init_proprieties(Image *new_image)
{
    new_image->file_type = calc_file_type(new_image);
    new_image->size = calc_file_size(new_image);
    new_image->width = calc_width(new_image);
    new_image->height = calc_height(new_image);
    new_image->padding_amount = ((4 - (calc_width(new_image) * 3) % 4)% 4);
}

int main()
{
    Image bmp_1= init_image("bmp_24.bmp");
    init_proprieties(&bmp_1);

    printf("%d\n",bmp_1.width);
    printf("%d\n",bmp_1.height);
    printf("%d\n",bmp_1.padding_amount);

    if(bmp_1.file_type != 0x4D42){
        throw runtime_error("Error! Unrecognized file format.");
    }

    

    return 0;
}
