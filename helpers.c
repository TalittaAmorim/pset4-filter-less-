#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for( int row= 0; row < height; row++) // passando por todos pixel na vertical/ altura.
    {
        for(int col =0; col < width; col++) // passando por cada pixel na horizontal da imagem
        {
            // Valor médio de todas as cores.
            int colorGray = round((image[row][col].rgbtBlue + image[row][col].rgbtGreen + image[row][col].rgbtRed)/3.0);

            // Cada pixel de determinado grupo de cor, vai modificar a sua porcentagem de RGB, somando com o valor original. Isso faz com que cada traço/iluminação da imagem seja conservado.
            image[row][col].rgbtBlue = colorGray;
            image[row][col].rgbtGreen = colorGray;
            image[row][col].rgbtRed = colorGray;
        }
    }
    return;
}

void sepia(int height, int width, RGBTRIPLE image[height][width]) 
{
     for( int row= 0; row < height; row++)
     {
         for(int col =0; col < width; col++)
         {
           int  sepiaRed = round((0.393 * image[row][col].rgbtRed) + (0.769 *image[row][col].rgbtGreen)+ (0.189 * image[row][col].rgbtBlue));

            if (sepiaRed > 255)
            {
                image[row][col].rgbtRed = 255;
            }
            else
            {
                image[row][col].rgbtRed = sepiaRed;
            }

           int  sepiaGreen = round((0.349 * image[row][col].rgbtRed + 0.686 * image[row][col].rgbtGreen + 0.168 *  image[row][col].rgbtBlue));


           if (sepiaGreen > 255)
            {
                image[row][col].rgbtGreen = 255;
            }
            else
            {
                image[row][col].rgbtGreen = sepiaGreen;
            }


           int  sepiaBlue = round((0.272 * image[row][col].rgbtRed + 0.534 * image[row][col].rgbtGreen + 0.131 *  image[row][col].rgbtBlue));


           if (sepiaBlue > 255)
            {
                image[row][col].rgbtBlue = 255;
            }
            else
            {
                image[row][col].rgbtBlue = sepiaBlue;
            }

         }
     }
  return;
}
// Refletir a imagem horizontalmente
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for( int row =0; row < height; row++) 
    {
        for(int col =0; col < ( width/2); col++) // divisão da coluna no meio 
        {
           RGBTRIPLE temp = image[row][col]; // armazenar lado esquerdo em uma var temporária

            image[row][col] = image[row][width - (col + 1)];  //armazenar lado direito no esquerdo
            image[row][width - (col + 1)] = temp; // adiciona o lado esquerdo no direito

        }
    }
    return;
}

// Efeito desfocar
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp[height][width];
    for(int row =0; row<height; row++)
    {
        for(int col =0; col < width; col++)
        {
            temp[row][col] = image[row][col];

            float som_red;
            float som_blue;
            float som_green;
            int count;

            som_red = som_blue = som_green = count= 0;

            for( int c = -1; c < 2; c++)
            {
                for(int e = -1; e<2;e++)
                {
                    if(row+c < 0 || row +c >=height) 
                    {
                        continue;
                    }

                      if(col+e < 0 || col +e >= width)
                    {
                        continue;
                    }
                    else
                    {
                       som_red += temp[row+c][col+e].rgbtRed; 
                       som_blue += temp[row+c][col+e].rgbtBlue;
                       som_green += temp[row+c][col+e].rgbtGreen;
                       count++;
                    }
                }
                 image[row][col].rgbtRed = round(som_red/count);
                 image[row][col].rgbtBlue = round(som_blue/count);;
                 image[row][col].rgbtGreen = round(som_green/count);

            }
        }

    }
    return;
}

// Detecta bordas
void edges(int height, int width, RGBTRIPLE image[height][width])
{
     RGBTRIPLE temp[height][width]; // Armazenamento dos pixels da imagem original.
    for(int row =0; row < height; row++)
    {
        for(int col =0; col<width; col++)
        {
           temp[row][col] = image[row][col]; //Duplicação da imagem e seus repectivos pixels.

           // matriz convolucional
      int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
      int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

      float gx_red = 0;
      float gy_red = 0;
      float gx_blue = 0;
      float gy_blue = 0;
      float gx_green = 0;
      float gy_green=0;

      for(int e = -1; e < 2; e++) // Esquerda/Direita dos pixels circundantes.
      {
          for(int c = -1; c < 2; c++) // Cima/Baixo
          {
             if(row+c < 0 || row +c >=height)
              {
                  continue;
              }
              if(col+c < 0 || col +c >=width)
              {
                    continue;
              }
              else
              {
               //   multiplicando os pixels circundantes por seus respectivos operadores na matriz de Sobel.
                  gx_red += temp[row+e][col+c].rgbtRed * gx[e +1][c+1];
                  gy_red += temp[row+e][col+c].rgbtRed * gy[e +1][c+1];
                  gx_blue += temp[row+e][col+c].rgbtBlue * gx[e +1][c+1];
                  gy_blue += temp[row+e][col+c].rgbtRed * gy[e +1][c+1];
                  gx_green += temp[row+e][col+c].rgbtGreen * gx[e +1][c+1];
              }

               // Calcula o operador Sobel
            int red = round(sqrt(gx_red * gx_red + gy_red * gy_red)); // A função sqrt() retorna a raiz quadrada de um número  x  .
            int green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int blue= round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));

            if(red > 255) // Não pode ser ser maior que a escala do sistema RGB.
            {
               red = 255;
            }
            if(green > 255)
            {
                green = 255;
            }
            if(blue > 255)
            {
               blue = 255;
            }
            else
            {
                // Adiciona nos pixels originais os resultados da operações para ocorrer as modificações.

               image[row][col].rgbtRed = red;
               image[row][col].rgbtBlue = blue;
               image[row][col].rgbtGreen = green;
            }
          }
      }
        }
    }
    return;
}
