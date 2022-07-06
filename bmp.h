// Tipos de dados relacionados a BMP baseados nos próprios dados da Microsoft

#include <stdint.h>

/**
 * Tipos de dados comuns
 *
 * Os tipos de dados nesta seção são essencialmente pseudônimos para C/C++
 * tipos de dados primitivos.
 *
 * Adaptado de http://msdn.microsoft.com/en-us/library/cc230309.aspx.
 * Ver http://en.wikipedia.org/wiki/Stdint.h para mais informações sobre a stdint.h.
 */
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

/**
 * BITMAPFILEHEADER
 *
 * A estrutura do BITMAPFILEHEADER contém informações sobre o tipo, tamanho,
 * e layout de um arquivo que contém um DIB [bitmap independente do dispositivo].
 *
 * Adaptado de http://msdn.microsoft.com/en-us/library/dd183374(VS.85).aspx.
 */
typedef struct
{
    WORD   bfType;
    DWORD  bfSize;
    WORD   bfReserved1;
    WORD   bfReserved2;
    DWORD  bfOffBits;
} __attribute__((__packed__))
BITMAPFILEHEADER;

/**
 * BITMAPINFOHEADER
 *
 * A estrutura BITMAPINFOHEADER contém informações sobre o
 * dimensões e formato de cor de um DIB [bitmap independente do dispositivo].
 *
 * Adaptado de http://msdn.microsoft.com/en-us/library/dd183376(VS.85).aspx.
 */
typedef struct
{
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} __attribute__((__packed__))
BITMAPINFOHEADER;

/**
 * RGBTRIPLE
 *
 * Esta estrutura descreve uma cor que consiste em intensidades relativas de
 * vermelho, verde e azul.
 *
 * Adaptado de http://msdn.microsoft.com/en-us/library/aa922590.aspx.
 */

typedef struct
{
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;
