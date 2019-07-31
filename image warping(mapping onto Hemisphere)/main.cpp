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
#include <math.h>
#include "bmp.h"
#define PI 3.14159
using namespace std;


int R[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[MaxBMPSizeX][MaxBMPSizeY];
int b[MaxBMPSizeX][MaxBMPSizeY];
int Bi_Interp(double ,double,int arr[MaxBMPSizeX][MaxBMPSizeY]);
int main(int argc, char *argv[])
{
	int width, height;
	int i, j;
	int f_xy=0;
	double a=0,c=0,d=0,x=0,y=0;
	double Dout=0,Din=0;

	open_bmp("building2.bmp", R, G, B, width, height); // for true images

	int Win=(width)/2;
	int Wout=(width)/2;
	
    
    for (i = 0; i < height; i++){
       for (j = 0; j < width; j++){
       	
       	c=(double)abs(j-((width)/2));
       	d=(double)abs(i-((width)/2));
       	Dout=hypot(c,d);
   
       	if(Dout>Win )
       	{
       		r[i][j]=0;
       		b[i][j]=0;
       		g[i][j]=0;
       	}
       	else if (Dout<=Win && Dout!=0)
       	{
       	
       		Din=((2*Win)/PI)*asin(Dout/Wout);
       	
       		x=Din*((i-((width-1)/2))/Dout)+(width-1)/2;
       		y=Din*((j-((width-1)/2))/Dout)+(width-1)/2;
       	
       		r[i][j]=Bi_Interp(x,y,R);//進行Bilinear_Interp 
       		g[i][j]=Bi_Interp(x,y,G);
       		b[i][j]=Bi_Interp(x,y,B);
      
       	}
        
       }
    }

	// 儲存處理結果至新的圖檔中
	save_bmp("building2_new.bmp", r, g, b); // for true color images
//	save_bmp("lena_new.bmp", r, r,r); // for gray images
	printf("Job Finished!\n");

	// 關閉 bmp 影像圖檔
	close_bmp();

	system("PAUSE"); /* so that the command window holds a while */
	return 0;
}

int Bi_Interp(double image_x,double image_y ,int color_arr[MaxBMPSizeX][MaxBMPSizeY])
{
	int f_pt=0,s_pt=0,t_pt=0,fth_pt=0,nimage_x=0,nimage_y=0,tr_value=0;
	double a=0,b=0;
	nimage_x=(int)(image_x);
	nimage_y=(int)(image_y);
	
	f_pt=color_arr[nimage_x][nimage_y];
	s_pt=color_arr[nimage_x+1][nimage_y];
	t_pt=color_arr[nimage_x][nimage_y+1];
	fth_pt=color_arr[nimage_x+1][nimage_y+1];
	
	a=((nimage_x+1)-image_x);
	b=((nimage_y+1)-image_y);
		
	tr_value=(int)(a*b*f_pt+(1-a)*b*s_pt+a*(1-b)*t_pt+(1-a)*(1-b)*fth_pt+0.5);
	
	return tr_value;
}





