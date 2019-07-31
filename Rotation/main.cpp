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
#include <math.h>
#define DegToRad 3.141592653/180.  
using namespace std;
int Bi_Interp(double ,double,int arr[MaxBMPSizeX][MaxBMPSizeY]);
int R[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
int G[1024][1024];
int B[1024][1024];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[1024][1024];
int b[1024][1024];

int main(int argc, char *argv[])
{
	int width, height;
	int i,j;
	double x,y;
	int x_max=0,y_max=0,x_min=10000;
	int Bond_x_max=0,Bond_x_min=0,Bond_y_max=0,Bond_y_min=0,Angle =45;
	// 開啟並讀取全彩(24bits)bmp 影像圖檔
	// RGB 三個 channel 的值存入 R, G, B 三個自訂的陣列中
	// 陣列大小不得大於 1024x1024
	//open_bmp("lenna.bmp", R, G, B, width, height); for true color images
	open_bmp("lena_ro.bmp", R, G, B, width, height); // for gray images


    /*----------------------------------------------------------------------------
	    計算圖片大小 
    ----------------------------------------------------------------------------*/
   /* for (i = 0; i < height; i++){
       for (j = 0; j < width; j++){
         if(R[i][j]!=0)
         {
         	if(i>x_max)
         	{x_max=i;}
         	else if(i<x_min)
         	{x_min=i;}
     		if(j>y_max)
         	{y_max=j;}
         	else if(j<y_min)
         	{y_min=j;}
         	
         }
         
       }
    }*/
  //  printf("%d %d\n",y_min,x_max);
    
    
    ///計算BondingBox///
	
	Bond_x_min=(int)((cos(Angle*DegToRad)*0)-(sin(Angle*DegToRad)*512));
	Bond_x_max=(int)((cos(Angle*DegToRad)*512-sin(Angle*DegToRad)*0));
	Bond_y_max=(int)((sin(Angle*DegToRad)*512+cos(Angle*DegToRad)*512));
	Bond_y_min= (int)((sin(Angle*DegToRad)*0+cos(Angle*DegToRad)*0));
	
	/////////////////
	int width_range = abs(Bond_x_min) + abs(Bond_x_max) ;	
	int height_range = abs(Bond_y_max) + abs(Bond_y_min) ;
	int width_n = ((width_range/10)+1)*10;
	int	height_n = ((height_range/10)+1)*10;
	int y_min=100000;
    ////////////////////
     for (int i = Bond_x_min; i <=Bond_x_max; i++){
     	for (int j = Bond_y_min; j <=Bond_y_max; j++){
		 
		 if((i)>=Bond_x_min && (i)<=Bond_x_max && j<=Bond_y_max && j>=Bond_y_min)
		 {
		 	x=(cos(Angle*DegToRad)*(i)+sin(Angle*DegToRad)*(j));
		 	y=(-sin(Angle*DegToRad)*(i)+cos(Angle*DegToRad)*(j));
		 //	printf("%f %f\n",x,y);
		 	if(x>=0 && x<width && y>=0 && y<height)
			 {
			//	r[i][j]=R[i][j];
        	//	g[i][j] = G[i][j];
         	//	b[i][j] =B[i][j];
		 //		printf("%d %d\n",j,Bond_x_min);
		 
		 		r[i+abs(Bond_x_min)-128][j]=Bi_Interp(x,y,R);
		 		g[i+abs(Bond_x_min)-128][j]=Bi_Interp(x,y,G);
       			b[i+abs(Bond_x_min)-128][j]=Bi_Interp(x,y,B);
       	/*	if(r[i+abs(Bond_x_min)-128][j]>0)
			 {
			 if(j<y_min)
         		{y_min=j;}
         	//	printf("%d \n",y_min);
			 }	*/
		 	}
		 	
		 }
		 
		}
			 
    }
  /*  for(int i =0;i<Bond_y_max;i++)
    {
    	for(int j=Bond_x_min;j<Bond_x_max;j++)
    	{
    		r[j-Bond_x_min][j]=r[i][j];
    		
    	}
    	
    }*/
    
	printf("%d %d \n",width,height);	
	// 儲存處理結果至新的圖檔中
	save_bmp("lenna_new1.bmp", r, g, b); // for true color images
	//save_bmp("lena_new.bmp", r, g, b); // for gray images
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
	
	//printf("%f %f\n",a,b);
	tr_value=(a*b*f_pt+(1-a)*b*s_pt+a*(1-b)*t_pt+(1-a)*(1-b)*fth_pt);
	//printf("%f %f %d %d\n ",a,b,s_pt,t_pt);
	
	return tr_value;
}


