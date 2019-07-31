/*===========================================================================
  This demonstrative example is provided by the teaching assistant,
  Mr. Shih-Hung Liao (廖世宏), and modified by the instructor, Prof. Lan.

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
int G[1024][1024];
int B[1024][1024];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[1024][1024];
int b[1024][1024];

int main(int argc, char *argv[])
{
	int width, height;
	int i, j;

	// 開啟並讀取全彩(24bits)bmp 影像圖檔
	// RGB 三個 channel 的值存入 R, G, B 三個自訂的陣列中
	// 陣列大小不得大於 1024x1024
	open_bmp("skin_det_1.bmp", R, G, B, width, height);// for true color images

    for (i = 0; i < height; i++){
       for (j = 0; j < width; j++){
         float max=0,min=0,v_a,v_g,v_b,H,S,V;
         
         v_a=((float)(R[i][j])/255);
        
          v_g=((float)(G[i][j])/255);
          v_b=((float)(B[i][j])/255);
          
          if(v_a>=v_b && v_a>=v_g)
          {
          	max=v_a;
          	if(v_b>=v_g)
          	{
          		min=v_g;
          		H=((v_b-v_g)/(max-min))/6;
          	}
          	else
          	{
          		min=v_b;
          		H=((v_g-v_b)/(max-min))/6;
         
          	}
          
          	S=(max-min)/max;
          	
          }
          
       	  if(v_b>v_a && v_b>v_g)
          {
          	max=v_b;
          		if(v_a>=v_g)
          	{
          		min=v_g;
          	}
          	else
          	{
          		min=v_a;
          	}
          	H=((v_a-v_g)/(max-min)+4)/6;
          	S=(max-min)/max;
         
          }
       if(v_g>v_a && v_g>v_b)
          {
          	max=v_g;
          		if(v_a>=v_b)
          	{
          		min=v_b;
          	}
          	else
          	{
          		min=v_a;
          	}
          	H=((v_b-v_a)/(max-min)+2)/6;
          	S=(max-min)/max;
          	
          }
          
           if (v_a==v_b && v_a==v_g)
          {
          	H=0;
          	S=0;
          }
       
         if((H>=((float)6/360) && H<=((float)38/360)) && (S>=0.23 && S<=0.68))
         {
         	R[i][j]=255;
         }
         else
         {
         	R[i][j]=0;
         }
       }
    }

	// 儲存處理結果至新的圖檔中
	//save_bmp("lenna_new1.bmp", r, g, b); // for true color images
	save_bmp("skin_det_1_new.bmp", R, R, R); // for gray images
	printf("Job Finished!\n");

	// 關閉 bmp 影像圖檔
	close_bmp();

	system("PAUSE"); /* so that the command window holds a while */
	return 0;
}

