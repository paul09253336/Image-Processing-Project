/*===========================================================================
  This demonstrative example is provided by the teaching assistant,
  Mr. Shih-Hung Liao (���@��), and modified by the instructor, Prof. Lan.

  (1) It can be compiled and executed correctly under the DEV-C++, and Visual C++
      environments.
  (2) In order to run this program, you should also have the "bmp.h" and
      "bmp.cpp" files installed in your current directory or whichever directory
      the C++ compiler is directed to search for.
  (3) The DEV-C++ is a free C++ development environment that is recommended for
      this course. Refer to http://www.bloodshed.net/dev/devcpp.html.

                             Apr. 3, 2006
============================================================================*/
#include <iostream>
#include <stdlib.h>
#include "bmp.h" 

using namespace std;

//int Procees(int image[MaxBMPSizeX][MaxBMPSizeY],int a,int b, int c,int d);

int R[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
int G[1024][1024];
int B[1024][1024];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[1024][1024];
int b[1024][1024];

int main(int argc, char *argv[])
{
	int width, height;
	int i, j;
	int E=0;
	// �}�Ҩ�Ū�����m(24bits)bmp �v������
	// RGB �T�� channel ���Ȧs�J R, G, B �T�Ӧۭq���}�C��
	// �}�C�j�p���o�j�� 1024x1024
	//open_bmp("lena.bmp", R, G, B, width, height); //for true color images
	open_bmp("lena.bmp", R ,R, R, width, height);  // for gray images


    /*----------------------------------------------------------------------------
	      �d�ҡG���ͼƦ�t���]�бN�D�{����b���B�^
    ----------------------------------------------------------------------------*/
    for(i=0;i<height;i++)
    {
    	for (j = 0; j < width; j++){
		r[i][j]=R[i][j];
		}
    }
    for (i = 0; i < height; i++){
       for (j = 0; j < width; j++){
       	if(r[i][j]<128)
       	{
       		E=r[i][j];
       		R[i][j]=0;
       		//printf("112");
        }
       	else
        {
       		E=r[i][j]-255;
       		R[i][j]=255;
       		
       	}
       	
       	
          r[i][j+1]=(E*7)/16+r[i][j+1];//right
          
          r[i+1][j+1]=(E*1)/16+r[i+1][j+1];//right-down
          r[i][j]=(E*5)/16+r[i+1][j];//down
          r[i+1][j-1]=(E*3)/16+r[i+1][j-1];//left-down
          
         
       }
    }

	// �x�s�B�z���G�ܷs�����ɤ�
	//save_bmp("lenna_new1.bmp", r, g, b); // for true color images
	//printf("%d",R[0][100]); 
	save_bmp("lena_new.bmp", R, R, R); // for gray images
	printf("Job Finished!\n");

	// ���� bmp �v������
	close_bmp();

	system("PAUSE"); /* so that the command window holds a while */
	return 0;
}

