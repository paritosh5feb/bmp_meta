/* bmpimage1.c
 * Routines in C for reading BMP images.
 * 
 * @uthor: PARITOSH KUMAR RAKESH
 * Programming Language:- C
 * Compiler:- GCC
 * Compilation command:- gcc bmpimage1.c -o bmpimage1 -lm
 *
 * This program has been written in order to gain access 
 * of the individual pixels present in the images and manipulate them.
 *
 * Note:- To ensure portability across devices, the conventional integer types should be changed to standard integer data types as defined in <stdint.h> file.
 * int64_t ->64 bit integer
 * int32_t ->32 bit integer
 * int8_t ->8 bit integer
 * int16_t ->16 bit integer
 * ____________________________________________________________________
 *
 * 
 *_____________________________________________________________________
 *************************************************************************/
#include <linux/types.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#define HEX 0x4d42 //HEX Identifier of BMP Files
#define LSB 1
#define GRAY_LEVELS 255 //shades of GRAY

struct bmpheader
{
    unsigned short type;           // 2 bytes
    unsigned int size;             // 4 bytes
    unsigned short reserved1;      // 2 bytes 
    unsigned short reserved2;      // 2 bytes
    unsigned int offset;           // 4 bytes
    unsigned int  dib_header_size; // 4 bytes
    int width;                     // 4 bytes 
    int height;                    // 4 bytes
    unsigned short planes;         // 2 bytes
    unsigned short bits_per_pixel; // 2 bytes
    unsigned int compression;      // 4 bytes
    unsigned int image_size;       // 4 bytes
    unsigned int x_resolution_ppm;         // 4 bytes
    unsigned int y_resolution_ppm;         // 4 bytes
    unsigned int colors;                   // 4 bytes
    unsigned int important_colors;         // 4 bytes
};
struct ctstruct{
   unsigned char blue;
   unsigned char green;
   unsigned char red;
};
struct readField
{
    char type[3];
    char size[5];
    char reserved1[3];
    char reserved2[3];
    char offset[5];
    char dib_header_size[5];
    char width[5];
    char height[5];
    char planes[3];
    char bits_per_pixel[3];
    char compression[5];
    char image_size[5];
    char x_resolution_ppm[5];
    char y_resolution_ppm[5];
    char colors[5];
    char important_colors[5];
};
struct bmpimage
{
    struct bmpheader header;
    unsigned char* data; // RGB values of pixels in the bmp image
}; 
union short_char_union{
    short s_num; 
    unsigned char  s_alpha[2];
};
union ushort_char_union{
    short s_num;
    unsigned char  s_alpha[2];
};
union int_char_union{
   int  i_num;
   unsigned char i_alpha[4];
};
union uint_char_union{
   int  i_num;
   unsigned char i_alpha[4];
};
struct bmpimage* read_bmpimage(char* filename, struct readField* rf, struct bmpheader* header, struct bmpimage* image)
{   
    FILE* fp;
    int i,j;
    unsigned char* data; 
    int width;  
    int height;  
    int size;
    union short_char_union scu;   
    union ushort_char_union uscu; 
    union int_char_union icu;     
    union uint_char_union uicu;   
    fp = fopen(filename,"rb");
    
    fread(rf->type, 1, 2, fp);
    uscu.s_alpha[0] = rf->type[0];
    uscu.s_alpha[1] = rf->type[1];
    header->type = uscu.s_num;
    fread(rf->size, 1, 4, fp); 
    uicu.i_alpha[0] = rf->size[0];
    uicu.i_alpha[1] = rf->size[1];
    uicu.i_alpha[2] = rf->size[2];
    uicu.i_alpha[3] = rf->size[3];
    header->size = uicu.i_num;
    fread(rf->reserved1, 1, 2, fp); 
    uscu.s_alpha[0] = rf->reserved1[0];
    uscu.s_alpha[1] = rf->reserved1[1];
    header->reserved1 = uscu.s_num;
    fread(rf->reserved2, 1, 2, fp); 
    uscu.s_alpha[0] = rf->reserved2[0];
    uscu.s_alpha[1] = rf->reserved2[1];
    header->reserved2 = uscu.s_num;
    fread(rf->offset, 1, 4, fp); 
    uicu.i_alpha[0] = rf->offset[0];
    uicu.i_alpha[1] = rf->offset[1];
    uicu.i_alpha[2] = rf->offset[2];
    uicu.i_alpha[3] = rf->offset[3];
    header->offset = uicu.i_num;
    fread(rf->dib_header_size, 1, 4, fp); 
    uicu.i_alpha[0] = rf->dib_header_size[0];
    uicu.i_alpha[1] = rf->dib_header_size[1];
    uicu.i_alpha[2] = rf->dib_header_size[2];
    uicu.i_alpha[3] = rf->dib_header_size[3];
    header->dib_header_size = uicu.i_num;
    fread(rf->width, 1, 4, fp); 
    icu.i_alpha[0] = rf->width[0];
    icu.i_alpha[1] = rf->width[1];
    icu.i_alpha[2] = rf->width[2];
    icu.i_alpha[3] = rf->width[3];
    header->width = icu.i_num;
    fread(rf->height, 1, 4, fp); 
    icu.i_alpha[0] = rf->height[0];
    icu.i_alpha[1] = rf->height[1];
    icu.i_alpha[2] = rf->height[2];
    icu.i_alpha[3] = rf->height[3];
    header->height = icu.i_num;
    fread(rf->planes, 1, 2, fp); 
    uscu.s_alpha[0] = rf->planes[0];
    uscu.s_alpha[1] = rf->planes[1];
    header->planes = uscu.s_num;
    fread(rf->bits_per_pixel, 1, 2, fp); 
    uscu.s_alpha[0] = rf->bits_per_pixel[0];
    uscu.s_alpha[1] = rf->bits_per_pixel[1];
    header->bits_per_pixel = uscu.s_num;
    fread(rf->compression, 1, 4, fp); 
    uicu.i_alpha[0] = rf->compression[0];
    uicu.i_alpha[1] = rf->compression[1];
    uicu.i_alpha[2] = rf->compression[2];
    uicu.i_alpha[3] = rf->compression[3];
    header->compression = uicu.i_num;
    fread(rf->image_size, 1, 4, fp); 
    uicu.i_alpha[0] = rf->image_size[0];
    uicu.i_alpha[1] = rf->image_size[1];
    uicu.i_alpha[2] = rf->image_size[2];
    uicu.i_alpha[3] = rf->image_size[3];
    header->image_size = uicu.i_num;
    fread(rf->x_resolution_ppm, 1, 4, fp); 
    uicu.i_alpha[0] = rf->x_resolution_ppm[0];
    uicu.i_alpha[1] = rf->x_resolution_ppm[1];
    uicu.i_alpha[2] = rf->x_resolution_ppm[2];
    uicu.i_alpha[3] = rf->x_resolution_ppm[3];
    header->x_resolution_ppm = uicu.i_num;
    fread(rf->y_resolution_ppm, 1, 4, fp); 
    uicu.i_alpha[0] = rf->y_resolution_ppm[0];
    uicu.i_alpha[1] = rf->y_resolution_ppm[1];
    uicu.i_alpha[2] = rf->y_resolution_ppm[2];
    uicu.i_alpha[3] = rf->y_resolution_ppm[3];
    header->y_resolution_ppm = uicu.i_num;
    fread(rf->colors, 1, 4, fp); 
    uicu.i_alpha[0] = rf->colors[0];
    uicu.i_alpha[1] = rf->colors[1];
    uicu.i_alpha[2] = rf->colors[2];
    uicu.i_alpha[3] = rf->colors[3];
    header->colors = uicu.i_num;
    fread(rf->important_colors, 1, 4, fp); 
    uicu.i_alpha[0] = rf->important_colors[0];
    uicu.i_alpha[1] = rf->important_colors[1];
    uicu.i_alpha[2] = rf->important_colors[2];
    uicu.i_alpha[3] = rf->important_colors[3];
    header->important_colors = uicu.i_num;
    image->header = *header;
    width = header->width;
    height = header->height;
    size = 3*width*height;
    data = (unsigned char*)malloc(sizeof(unsigned char)*size);
    fseek(fp, header->offset, SEEK_SET);
    fread(data, sizeof(unsigned char), size, fp);
    image->data = data;
    fclose(fp);
    return image;
}

int main()
{
    char filename[10];
    unsigned char* pixels;
    int size, width, height;
    int i,j;
    FILE* pixels_dat = fopen("pixels.dat","wb");
    system("clear");
    printf("Filename >>> ");
    scanf("%s",&filename);
    struct bmpimage image;
    struct bmpheader header;
    struct readField rf;
    read_bmpimage(filename,&rf,&header,&image);
    printf("\nImage Data\n");
    printf("\nType >>> %x",image.header.type);
    printf("\nFile Size >>> %x",image.header.size);
    printf("\nReserved1 >>> %x",image.header.reserved1);
    printf("\nReserved2 >>> %x",image.header.reserved2);
    printf("\nPixels Offset >>> %u",image.header.offset);
    printf("\ndib_header_size >>> %x",image.header.dib_header_size);
    printf("\nWidth >>> %x",image.header.width);
    printf("\nHeight >>> %x",image.header.height);
    printf("\nPlanes >>> %x",image.header.planes);
    printf("\nBits per pixel >>> %x",image.header.bits_per_pixel);
    printf("\nCompression >>> %x",image.header.compression);
    printf("\nImage size >>> %x",image.header.image_size);
    printf("\nX_resolution >>> %x",image.header.x_resolution_ppm);
    printf("\nY_resolution >>> %x",image.header.x_resolution_ppm);
    printf("\ncolors >>> %x",image.header.colors);
    printf("\nImportant Colors >>> %x",image.header.important_colors);
    printf("\n\n");
    printf("Pixel Values:-\n\n");
    width = image.header.width;
    height = image.header.height;
    size = 3*width*height;
    pixels = (unsigned char*)malloc(sizeof(unsigned char)*size);
    pixels = image.data;
    for(i=1;i<size;i++)
    {   
        j = i-1;
        if(i/width == 1 && i%width==0)printf("%x \n",*(pixels+j));
        else printf("%d ",*(pixels+j));
    }
    for(j=0;j<height;j++)
    {
        for(i=0;i<width;i++)
        {
            fprintf(pixels_dat,"%d ",*(pixels+j*width+i));
        }
        fprintf(pixels_dat,"\n");
    }
    
    return 0;
}
    
    
    


    
    
    


 
 
 
 
 
 
 
 
 


