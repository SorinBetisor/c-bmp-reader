#include <fstream>
#include <stdint.h>
#include <stdio.h>
using namespace std;

// https://solarianprogrammer.com/2018/11/19/cpp-reading-writing-bmp-images/

// uint8_t char
// uint16_t shortint
// uint32_t int
// uint64_t longlong

typedef uint8_t ubyte;

static const int fileHeaderSize = 14;
static const int informationHeaderSize = 40;

struct Color
{
    ubyte b;
    ubyte g;
    ubyte r;
};

struct Image
{
    char *path;

    size_t size;
    uint16_t file_type;

    ubyte fileHeader[fileHeaderSize];
    ubyte informationHeader[informationHeaderSize];

    uint32_t width;
    uint32_t height;
    uint16_t padding_amount;

    Color **color_matrix;
};

void calc_file_type(Image *image)
{
    ubyte file_type_low = image->fileHeader[0];
    uint16_t file_type_high = image->fileHeader[1] << 8;
    uint16_t file_type = file_type_low + file_type_high;

    image->file_type = file_type;
}

void calc_file_size(Image *image)
{
    uint32_t file_size = image->fileHeader[2] + (image->fileHeader[3] << 8) + (image->fileHeader[4] << 16) + (image->fileHeader[5] << 24);
    image->size = file_size;
}

void calc_width(Image *image)
{
    uint32_t width = image->informationHeader[4] + (image->informationHeader[5] << 8) + (image->informationHeader[6] << 16) + (image->informationHeader[7] << 24);
    image->width = width;
}

void calc_height(Image *image)
{
    uint32_t height = image->informationHeader[8] + (image->informationHeader[9] << 8) + (image->informationHeader[10] << 16) + (image->informationHeader[11] << 24);
    image->height = height;
}

Image init_image(char *path)
{
    Image New_Image = {};

    ifstream fin;
    fin.open(path, ios::in | ios::binary);

    // read the 54 byte header
    fin.read((char *)New_Image.fileHeader, fileHeaderSize);
    fin.read((char *)New_Image.informationHeader, informationHeaderSize);

    New_Image.path = path;

    return New_Image;
}

void init_proprieties(Image *new_image)
{
    calc_file_type(new_image);
    calc_file_size(new_image);
    calc_width(new_image);
    calc_height(new_image);
    //!!
    new_image->padding_amount = (((4 - (new_image->width) * 3) % 4) % 4);

    new_image->color_matrix = new Color *[new_image->height];

    for (int w_x = 0; w_x < new_image->width; w_x++)
    {
        new_image->color_matrix[w_x] = new Color[new_image->width];
    }
}

void read_colors(Image *new_image)
{
    ifstream fin;
    fin.open(new_image->path, ios::binary | ios::in);
    fin.seekg(54);

    for (int i = 0; i < (new_image->height); i++)
    {
        for (int j = 0; j < (new_image->width); j++)
        {
            ubyte color[3];
            fin.read((char *)color, 3);
            // printf("%X%X%X%X",color[0],color[1],color[2],color[3]);
            new_image->color_matrix[i][j].b = static_cast<float>(color[0]) / 255.0f;
            new_image->color_matrix[i][j].g = static_cast<float>(color[1]) / 255.0f;
            new_image->color_matrix[i][j].r = static_cast<float>(color[2]) / 255.0f;
        }
        fin.ignore(new_image->padding_amount);
    }
    fin.close();
}

void writeFile(Image *new_image)
{
    ofstream fout;
    fout.open("colors.data", ios::out | ios::binary);

    fout.write((char *)new_image->fileHeader, fileHeaderSize);
    fout.write((char *)new_image->informationHeader, informationHeaderSize);

    for (int i = 0; i < (new_image->height); i++)
    {
        for (int j = 0; j < (new_image->width); j++)
        {
            ubyte r = new_image->color_matrix[i][j].r * 255.0f;
            ubyte g = new_image->color_matrix[i][j].g * 255.0f;
            ubyte b = new_image->color_matrix[i][j].b * 255.0f;

            ubyte color[] = {r, g, b};

            fout.write((char *)color, 3);
        }
    }

    fout.close();
}

int main()
{
    Image bmp_1 = init_image("bmp_24.bmp");
    init_proprieties(&bmp_1);

    // printf("%d\n",bmp_1.width);
    // printf("%d\n",bmp_1.height);
    // printf("%d\n",bmp_1.padding_amount);

    if (bmp_1.file_type != 0x4D42)
    {
        printf("Error! Unrecognized file format.\n");
        return EXIT_FAILURE;
    }

    read_colors(&bmp_1);
    writeFile(&bmp_1);

    return 0;
}
