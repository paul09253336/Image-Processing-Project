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
#include <math.h>
using namespace std;
void dilation(int color[MaxBMPSizeX][MaxBMPSizeY], int w,int h);
void erosion(int color[MaxBMPSizeX][MaxBMPSizeY], int w,int h);
int R[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
//int G[1024][1024];
//int B[1024][1024];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[1024][1024];
//int b[1024][1024];

int main(int argc, char *argv[])
{
	int width, height;
	int i, j;

	// �}�Ҩ�Ū�����m(24bits)bmp �v������
	// RGB �T�� channel ���Ȧs�J R, G, B �T�Ӧۭq���}�C��
	// �}�C�j�p���o�j�� 1024x1024
	//open_bmp("lenna.bmp", R, G, B, width, height); for true color images
	open_bmp("noise_remov_morph_gray.bmp", R, R, R, width, height); // for gray images


   
	erosion(R,width,height);
  	dilation(R,width,height);
  	dilation(R,width,height);
  
	// �x�s�B�z���G�ܷs�����ɤ�
	//save_bmp("lenna_new1.bmp", r, g, b); // for true color images
	save_bmp("morphgray_new.bmp", R,R,R); // for gray images
	printf("Job Finished!\n");

	// ���� bmp �v������
	close_bmp();

	system("PAUSE"); /* so that the command window holds a while */
	return 0;
}

void dilation(int color[MaxBMPSizeX][MaxBMPSizeY], int w,int h)
{ 
	int n=1,angle,rc;
	int x,y;
	for (int i = 0; i < h; i++){
       for (int j = 0; j < w; j++){
		 if(color[i][j]>0)
			{
					r[i][j]=100;
			}
		}
	}
	for (int i = 0; i < h; i++){
       for (int j = 0; j < w; j++){
       	 if(r[i][j]==100)
       	{
       			color[i][j]=255;
       			color[i+1][j]=255;
       			color[i][j+1]=255;
       			color[i][j-1]=255;
       			color[i-1][j]=255;
       	}
       	
		}
	}
}

void erosion(int color[MaxBMPSizeX][MaxBMPSizeY], int w,int h)
{
	int rc,angle,n=1;
	int x,y;
 	for (int i = 0; i < h; i++){
       for (int j = 0; j < w; j++){
		 if( color[i][j]>0)
			{
					if( color[i][j+1]==0 ||  color[i][j-1]==0 ||  color[i+1][j]==0 ||  color[i-1][j]==0 ||  color[i][j]==0) 
					{
						 color[i][j]=100;
					}
			}
		}
	}
	
	for (int i = 0; i < h; i++){
       for (int j = 0; j < w; j++){
		
			if( color[i][j]==100 ||  color[i][j]==0)
			{
			 color[i][j]=0;
			}
		}
	}
	
	
}


