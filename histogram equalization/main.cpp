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

int R[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
//int G[1024][1024];
//int B[1024][1024];
int r[MaxBMPSizeX][MaxBMPSizeY];
//int g[1024][1024];
//int b[1024][1024];

int main(int argc, char *argv[])
{
	int width, height;
	int i,j,k;
	float h[255]={0};
	float v[255]={0};
	int scale_number[255]={0};
	int p[255]={0};
	float number=0;
	int a=0;//�P�_�O�_�Ĥ@���i�J�j�� 
	// �}�Ҩ�Ū�����m(24bits)bmp �v������
	// RGB �T�� channel ���Ȧs�J R, G, B �T�Ӧۭq���}�C��
	// �}�C�j�p���o�j�� 1024x1024
	//open_bmp("lenna.bmp", R, G, B, width, height); for true color images
	open_bmp("boat.bmp", R, R, R, width, height); // for gray images

////////////////////////////////////////////////////
/*�p��Ƕ��ȥX�{���� */ 
/////////////////////////////////////////////////// 
    for (i = 0; i < height; i++){
       for (j = 0; j < width; j++){
        h[R[i][j]]= h[R[i][j]]+1;
        
       }
    }

	for (i = 0; i < 255; i++){
	
	  if(h[i]!=0)
	  {
	  	a=a+1; 
	  	 
	  	v[i]=v[i-1]+(h[i]/(height*width));
	  	if(a==1)
	  	{
	  		number=v[i];
	  	}
	  	scale_number[i]=(int)(((v[i]-number)/(1-number))*255+0.5)/*�|�ˤ��J*/;
	  }	
	  
    
    }
    for(int k=0;k<256;k++)
    {	
    	if(h[k]!=0){
    
    		for (i = 0; i < height; i++){
       			for (j = 0; j < width; j++){
         			
         		
         				if(R[i][j]==k)
         				{
         				R[i][j]=scale_number[k];
         				
         				}
         		
         			
       			}
    		}
		
		}
    }
   
	// �x�s�B�z���G�ܷs�����ɤ�
	//save_bmp("lenna_new1.bmp", r, g, b); // for true color images
	save_bmp("boat_new.bmp", R, R, R); // for gray images
	printf("Job Finished!\n");

	// ���� bmp �v������
	close_bmp();

	system("PAUSE"); /* so that the command window holds a while */
	return 0;
}

