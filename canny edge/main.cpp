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

using namespace std;

int R[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
//int G[1024][1024];
//int B[1024][1024];
int r[MaxBMPSizeX][MaxBMPSizeY];
int r1[MaxBMPSizeX][MaxBMPSizeY];
int r2[MaxBMPSizeX][MaxBMPSizeY];
int r_grad[MaxBMPSizeX][MaxBMPSizeY];
int test[MaxBMPSizeX][MaxBMPSizeY];
//int g[1024][1024];
//int b[1024][1024];

int main(int argc, char *argv[])
{
	int width, height;
	int i, j, k,temp,a,b,c=0,d,e;
    int m[8]={0},y[8]={0};

	// 開啟並讀取全彩(24bits)bmp 影像圖檔
	// RGB 三個 channel 的值存入 R, G, B 三個自訂的陣列中
	// 陣列大小不得大於 1024x1024
	//open_bmp("lenna.bmp", R, G, B, width, height); for true color images
	open_bmp("house.bmp", R, R, R, width, height); // for gray images


   for (int a = 0; a < 256; a++)
	{ 	
	
       for ( b = 0; b< 256; b++)
	   {	k=0;
	  
	   /////形成遮罩 
        for(i=0;i<3;i++)
         {
         	for(j=0;j<3;j++)
         	{
         	
         		m[k]=R[j+a][i+b];
          
          		k=k+1;
         		
         	}
         	         	
         }
      
		c=(int)(m[0]*0.1+m[1]*0.11+m[2]*0.1+m[3]*0.11+m[5]*0.11+m[6]*0.1+m[7]*0.11+m[8]*0.1+m[4]*0.13+0.5);
		r[a+1][b+1]=c;
	
       }
      
    }
    /////////進行Sobel運算 
 for (int a = 0; a < 256; a++)
	{ 	
	
       for (int b = 0; b< 256; b++)
	   {	k=0;
	  
	
	   /////形成遮罩 
        for(i=0;i<3;i++)
         {
         	for(j=0;j<3;j++)
         	{
         	
         		m[k]=r[j+a][i+b];
          
          		k=k+1;
         		
         	}
         	         	
         }
      
		d=(int)(m[0]*(-1)+m[2]+m[3]*(-2)+m[5]*(2)-m[6]+m[8]+0.5);
		r1[a+1][b+1]=d;
		e=(int)(m[0]*(-1)+m[1]*(-2)+m[2]*(-1)+m[6]+m[7]*2+m[8]+0.5);
		 r2[a+1][b+1]=e;
		
		r_grad[a][b]=(int)(abs(r1[a][b])+abs(r2[a][b]));
		 	
       }
    
    }


    	int total =0,total1=0;
     for (int a = 0; a < 256; a++)
	{ 	
	
       for ( b = 0; b< 256; b++)
	   {
	   	
	
	   	if(r1[a][b]!=0 && r2[a][b]!=0)
		 {
		 //	r3[a][b]=r1[a][b]+r2[a][b];
			double angle;
			angle=atan((double)(r2[a][b]/r1[a][b]))*(180/3.14159);
			if(angle<0) angle=angle+360;
			if((angle<22.5 && angle>337.5) || (angle>157.5 && angle<202.5) )angle=0;
			else if((angle>=22.5 && angle<=67.5) || (angle>202.5 && angle<=247.5) ) angle=45;
			else if((angle>67.5 && angle<=112.5) || (angle>247.5 && angle<=292.5)) angle=90;
			else if((angle>112.5 && angle<=157.5) || (angle>292.5 && angle<337.5)) angle=135;
			//printf("%f\n",angle);
		
			switch((int)angle)
			{
				
				case 0:
					{
						
							if(r_grad[a+1][b]>r_grad[a][b] || r_grad[a-1][b]>r_grad[a][b] )
							
							{
								r_grad[a][b]=0;
							}
					
							break;
							
					}
					
				
				case 90:
					{
				
								if(r_grad[a][b+1]>r_grad[a][b] || r_grad[a][b-1]>r_grad[a][b] )
							
							{
								r_grad[a][b]=0;
							}
					
							break;
						
					}
				
				
				case 45:
					{
						
							if(r_grad[a-1][b+1]>r_grad[a][b] || r_grad[a+1][b-1]>r_grad[a][b] )
							
							{
								r_grad[a][b]=0;
							}
						
						break;
						
					}
				
				case 135:
					{
						
						if(r_grad[a+1][b+1]>r_grad[a][b] || r_grad[a-1][b-1]>r_grad[a][b] )
							
							{
								r_grad[a][b]=0;
							}
					
						break;
					}
				
				default:
					{
						printf("not angle %d\n",(int)angle);
					}
				
				
				
			}
	
			if((r_grad[a][b]>=200 ))
			 {
				total++;
				r_grad[a][b]=255;
			}
			
			else if (r_grad[a][b]>100 && r_grad[a][b]<200 )
			{
				total1++;
				r_grad[a][b]=1000;
			}
			else if(r_grad[a][b]<100)
			{
				r_grad[a][b]=0;
			}
		
		 }
	  

       }
      
    }
 

	for(int k=0;k<(total+total1);k++)
	{
		for(int i=0;i<256;i++)
		{
			for(int j=0;j<256;j++)
			{
				
				if(r_grad[i][j]==1000)
				{
					if((r_grad[i-1][j-1]==255 || r_grad[i-1][j]==255 || r_grad[i-1][j+1]==255 || r_grad[i][j-1]==255 || r_grad[i][j+1]==255 || r_grad[i+1][j-1]==255 || r_grad[i+1][j]==255 || r_grad[i+1][j+1]==255 )) 
					{
						r_grad[i][j]=255;
						
					}
				 
				
				}
				
			}
		}
	}

for(int i=0;i<256;i++)
{
	for(int j=0;j<256;j++)
	{
			if((r_grad[i][j] !=0 && r_grad[i][j] !=255 && r_grad[i][j]!=1000) ||r_grad[i][j]==1000 )
					{
						r_grad[i][j]=0;
					//	printf("%d %d %d \n",i,j,r_grad[i][j]);
					}
	}
}
	// 儲存處理結果至新的圖檔中
	//save_bmp("lenna_new1.bmp", r, g, b); // for true color images
	save_bmp("house_new.bmp",	r_grad,	r_grad,		r_grad); // for gray images
	printf("Job Finished!\n");

	// 關閉 bmp 影像圖檔
	close_bmp();

	system("PAUSE"); /* so that the command window holds a while */
	return 0;
}
 
