 /*===============================================================
             Filtering in the Frequency-Domain
              (Lowpass and Highpass Filtering)
              for instructional purposes only
                    by Prof. Lan
                    Apr. 15, 2010

In Dev-C++, first create a project file.  Then add Filter_Freq_students.cpp,
FFT1.c, FFT2.c, and bmp.cpp to this project.  Remember to put all these files
in the same directory.
===============================================================*/
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "bmp.h"

using namespace std;

void fft1(float data[],int nn,int isign);
void fft2(float data[],int nn,int isign);
void spectrum_shift(int mm);

int R[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h" 
float data[MaxBMPSizeX*MaxBMPSizeY*2]; // a long 1D array to keep the image and its spectrum
float sp_re[MaxBMPSizeX][MaxBMPSizeY]; // real part of the spectrum
float sp_im[MaxBMPSizeX][MaxBMPSizeY]; // imaginary part of the spectrum
float tmp[MaxBMPSizeX][MaxBMPSizeY];

// You can try various combinations of D and filt_order values.
const float D =500; // the D parameter of a Butterworth filter
const int filt_order = 2; // order of the Butterworth filter

int main(int argc, char *argv[])
{
	int width, height;
	int i, j;

	open_bmp("cameraman.bmp", R, R, R, width, height); // for gray images
	//open_bmp("lena.bmp", R, R, R, width, height); // for gray images
    printf("==========================================\n");
	
    /*----------------------------------------------------------------------------
	      �d�ҡG�]�бN�D�{����b���B�^ 
    ----------------------------------------------------------------------------*/
    // convert to the long 1D array
    int ptr = 0; // pointer for the data array
    for (i = 0; i < height; i++){
       for (j = 0; j < width; j++){
          data[ptr] = R[i][j];     // real part of the input data
          data[ptr+1] = 0;         // imaginary part of the input data
          ptr += 2;
       }
    }
    
    fft2(data,width,1); // perform the forward fft2
        
    // fetch the 2D spectrum from the long 1-D spectrum array
    ptr = 0;
    for (i=0; i<height; i++) {
       for (j=0; j<width; j++) {
          sp_re[i][j] = data[ptr];    // real part of the 2D spectrum
          sp_im[i][j] = data[ptr+1];  // imaginary part of the 2D spectrum
          ptr += 2;
           
       }
    }
       
   // shift the 2-D spectrum
   int mm = width/2; // mm is one half of the original image width
   spectrum_shift(mm);
      
   // perform Ideal Filtering in this sample program
   // Note that you should write your own code to perform Butterworth Lowpass Filtering and Highpass
   // Filtering, or Gaussian LPF/HPF.
   // Define the H(u,v) function and perform F(u,v)H(u,v).
   
   double sq_dist,sq_distx,sq_disty,H=0,H_hp=0;
   int k=0,sp1_re[i][j];
   for (i=0; i<height; i++) {
      for (j=0; j<width; j++) {
      		sq_distx = (double)((i-mm));
      		sq_disty = (double)((j-mm));
          sq_dist =hypot(sq_distx,sq_disty)/sqrt(D);//�p��D(u,v) 
          
          H=(1/(1+pow(sq_dist,filt_order)));	//�p��H_lowpass 
          H_hp=1-(1/(1+pow(sq_dist,filt_order)));	//�p��H_Highpass 
          sp_re[i][j]=(sp_re[i][j]*H);//�p��G(u,v)�곡 
          sp_im[i][j]=(sp_im[i][j]*H);//�p��G(u,v)�곡 
      
          
          
      }
   }
  
   // shift the 2-D spectrum back
   spectrum_shift(mm);
   
    // convert to the long 1D array
    ptr = 0; // pointer for the data array
    for (i = 0; i < height; i++){
       for (j = 0; j < width; j++){
          data[ptr] = sp_re[i][j];
          data[ptr+1] = sp_im[i][j];
          ptr += 2;
       }
    }

    fft2(data,width,-1); // perform the inverse fft2

    // convert back to the 2D image
    ptr = 0; // pointer for the data array
    for (i = 0; i < height; i++){
       for (j = 0; j < width; j++){
          sp_re[i][j] = data[ptr];
          ptr += 2;
       }
    }

    // overflow and underflow handling (by linear scaling)    
    float min = 1E99;
    float max = -1E99;
    for (i = 0; i < height; i++) {
       for (j = 0; j < width; j++) {
          if (sp_re[i][j] > max) max = sp_re[i][j]; 
          if (sp_re[i][j] < min) min = sp_re[i][j]; 
       }
    }
    float sf;
    sf = 255/(max-min);
    printf("%f \t %f \t %f \n",max,min,sf);
    for (i = 0; i < height; i++) {
       for (j = 0; j < width; j++) {
          R[i][j] = (int)((sp_re[i][j]-min)*sf); 
       }
    }
   
    //printf("%d \n", R[12][16]); // check the data value 

	// �x�s�B�z���G�ܷs�����ɤ�
	//save_bmp("lena_new1.bmp", r, g, b); // for true color images
	save_bmp("cameraman_new.bmp", R, R, R); // for gray images
	printf("Job Finished!\n");

	// ���� bmp �v������
	close_bmp();

   system("PAUSE"); /* so that the command window holds a while */
	return 0;
}

void spectrum_shift(int mm){
   for (int i=0; i<mm; i++) {
      for (int j=0; j<mm; j++) {
         //------------------------ the real part
         tmp[i][j] = sp_re[i][j]; // upper-left <-> lower-right
         sp_re[i][j] = sp_re[mm+i][mm+j];
         sp_re[mm+i][mm+j] = tmp[i][j];
         tmp[i][j] = sp_re[i][mm+j]; // upper-right <-> lower-left
         sp_re[i][mm+j] = sp_re[mm+i][j];
         sp_re[mm+i][j] = tmp[i][j];
         //--------------------------- the imag. part
         tmp[i][j] = sp_im[i][j]; // upper-left <-> lower-right
         sp_im[i][j] = sp_im[mm+i][mm+j];
         sp_im[mm+i][mm+j] = tmp[i][j];
         tmp[i][j] = sp_im[i][mm+j]; // upper-right <-> lower-left
         sp_im[i][mm+j] = sp_im[mm+i][j];
         sp_im[mm+i][j] = tmp[i][j];
      }
   }
}
