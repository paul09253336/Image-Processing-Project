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
	int a=0;//判斷是否第一次進入迴圈 
	// 開啟並讀取全彩(24bits)bmp 影像圖檔
	// RGB 三個 channel 的值存入 R, G, B 三個自訂的陣列中
	// 陣列大小不得大於 1024x1024
	//open_bmp("lenna.bmp", R, G, B, width, height); for true color images
	open_bmp("boat.bmp", R, R, R, width, height); // for gray images

////////////////////////////////////////////////////
/*計算灰階值出現次數 */ 
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
	  	scale_number[i]=(int)(((v[i]-number)/(1-number))*255+0.5)/*四捨五入*/;
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
   
	// 儲存處理結果至新的圖檔中
	//save_bmp("lenna_new1.bmp", r, g, b); // for true color images
	save_bmp("boat_new.bmp", R, R, R); // for gray images
	printf("Job Finished!\n");

	// 關閉 bmp 影像圖檔
	close_bmp();

	system("PAUSE"); /* so that the command window holds a while */
	return 0;
}

