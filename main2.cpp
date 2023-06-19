#include <fstream>
#include <iostream>
using namespace std;

struct FileHeader
{

};

struct Image{
    uint8_t *data;
    size_t size;

    FileHeader img_header;
};

uint8_t read_file(const char *path, size_t size)
{
    // Open file
    FILE *file = fopen(path, "rb");

    // Read file lenght
    fseek(file, 0, SEEK_END);
    size_t len = ftell(file);
    size = len;
    fseek(file, 0, SEEK_SET);

    // Allocate buffer
    uint8_t *buffer = (uint8_t *)malloc(len + 1);
    buffer[len] = '\0';

    // Read content
    fread(buffer, 1, len, file);
    return (*buffer);
}

int main()
{
    Image img;
    img.data = (uint8_t*)read_file("bmp_24.bmp",0);
    printf("%X\n",img.data);
    return 0;
}