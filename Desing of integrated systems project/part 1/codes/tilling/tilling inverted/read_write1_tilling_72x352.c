#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define N 288 /* frame dimension for QCIF format */
#define M 352 /* frame dimension for QCIF format */
#define filename "akiyo_cif_0_yuv444.yuv"
#define file_y "akiyo2y.yuv"
#define iTile 72


/* code for armulator*/
#pragma arm section zidata="ram"
int current_y[N][M];
int gauss[N+2][M+2];
int newgauss[N+2][M+2];
int nonmaximum[N+2][M+2];
int threshold[N+2][M+2];
int sobel[N][M];
int newsobelx[N][M];
int newsobely[N][M];
double es[N][M];
float  eo[N][M];
double z=0;
float k=0;
int q=0;
int r=0;
int t1=70;
int t2=60;

#pragma arm section

int i,j,ii;


void canny(){
   for(ii=1; ii<N+2; ii+=iTile)
    for(j=1;j<M+2;j++)
      for(i=ii; i<ii+iTile; i++)
			gauss[i][j]=0;
			sobel[i][j]=0;
		   nonmaximum[i][j]=0;
           threshold[N][M]=0;

	for(ii=1; ii<N+1; ii+=iTile)
    for(j=1;j<M+1;j++)
      for(i=ii; i<ii+iTile; i++)
			gauss[i][j]=current_y[i-1][j-1];

/*Edw dinetai to filtrarisma me ton 2d pinaka gaussFilter*/
	for(ii=1; ii<N+1; ii+=iTile)
    for(j=1;j<M+1;j++)
      for(i=ii; i<ii+iTile; i++)
			newgauss[i][j]=(gauss[i][j] *(4) + // pollaplasiazei to idio stoixeio me 4
                          gauss[i-1][j-1] *(1) +   // stoixeio panw aristera
                          gauss[i][j-1]   *(2) +   // stoixeio aristera
                          gauss[i+1][j-1] *(1) +   // stoixeio katw aristera
                          gauss[i-1][j]   *(2) +   // stoixeio apo panw
                          gauss[i+1][j]   *(2) +   // stoixeio apo katw
                          gauss[i-1][j+1] *(1) +   // stoixeio panw deksia
                          gauss[i][j+1]   *(2) +   // stoixeio deksia
                          gauss[i+1][j+1] *(1)  // stoixeio katw deksia
                          );

for(ii=1; ii<N+1; ii+=iTile)
    for(j=1;j<M+1;j++)
      for(i=ii; i<ii+iTile; i++){
			current_y[i-1][j-1]=newgauss[i][j]/16;
            sobel[i-1][j-1]=current_y[i-1][j-1];
        
      }
    
//sobel 
   		for(ii=1; ii<N+1; ii+=iTile)
    for(j=1;j<M+1;j++)
      for(i=ii; i<ii+iTile; i++)
			newsobelx[i][j]=(sobel[i-1][j-1] *(-1) +   // stoixeio panw aristera
                          sobel[i][j-1]   *(-2) +   // stoixeio aristera
                          sobel[i+1][j-1] *(-1) +   // stoixeio katw aristera
                          sobel[i-1][j+1] *(1) +   // stoixeio panw deksia
                          sobel[i][j+1]   *(2) +   // stoixeio deksia
                          sobel[i+1][j+1] *(1)  // stoixeio katw deksia
                          );
   for(j=1;j<M+1;j++)
     for(ii=1; ii<N+1; ii+=iTile)
      for(i=ii; i<ii+iTile; i++)                   
            newsobely[i][j]=(sobel[i-1][j-1] *(1) +   // stoixeio panw aristera
                          sobel[i+1][j-1] *(-1) +   // stoixeio katw aristera
                          sobel[i-1][j]   *(2) +   // stoixeio apo panw
                          sobel[i+1][j]   *(-2) +   // stoixeio apo katw
                          sobel[i-1][j+1] *(1) +   // stoixeio panw deksia
                          sobel[i+1][j+1] *(-1)  // stoixeio katw deksia
                          ); 
                                     
	for(ii=0; ii<N; ii+=iTile)
    for(j=0;j<M;j++)
      for(i=ii; i<ii+iTile; i++)
 {    
     
		    if (newsobely[i][j]==0){
		        newsobely[i][j]=1;
	        
		    }   
       
             z=(newsobelx[i][j]*newsobelx[i][j])+(newsobely[i][j]*newsobely[i][j]);
             k= (float)newsobelx[i][j]/(float)newsobely[i][j];
              
		     es[i][j]=sqrt(z);//plath eikostoixeiwn
		     eo[i][j]=atan(k);//klisi eikonostoixeiwn
}
   
	for(ii=1; ii<N+1; ii+=iTile)
    for(j=1;j<M+1;j++)
      for(i=ii; i<ii+iTile; i++){
			current_y[i-1][j-1]=es[i][j];
          
        
      }
      
      //non maximun
    
                                    
	 for(ii=0; ii<N; ii+=iTile)
    for(j=0;j<M;j++)
      for(i=ii; i<ii+iTile; i++){
			eo[i][j]=(eo[i][j]*180)/3.14;
            if (eo[i][j]<0){
		        eo[i][j]+=180;
	        
		    }  
           
      }  
     
     for(ii=0; ii<N-1; ii+=iTile)
    for(j=0;j<M-1;j++)
      for(i=ii; i<ii+iTile; i++){
		 q=0;
		 r=0;		   
		    if ((0<=eo[i][j] && eo[i][j] <22.5) || (157.5 <=eo[i][j] &&eo[i][j] <= 180)){
		        q =current_y[i][j+1];
                r =current_y[i][j-1];
		    }  
            else if (22.5<=eo[i][j] && eo[i][j]<67.5){
                q =eo[i+1][j-1];
                r =eo[i-1][j+1];
                } 
            else if (67.5<=eo[i][j]&& eo[i][j]<112.5){
                q = current_y[i+1][j];
                r = current_y[i-1][j];
                } 
            else if (112.5<=eo[i][j] && eo[i][j]<157.5){
                q =current_y[i-1][j-1];
                r= current_y[i+1][j+1];                
                } 
                 
             
            if(current_y[i][j]>=q || current_y[i][j]>=r){
                nonmaximum[i][j]=current_y[i][j];
         
                 } 
            else {
                nonmaximum[i][j]=0;
            
                   }  
                  
                       
      }
        
    for(ii=1; ii<N+1; ii+=iTile)
    for(j=1;j<M+1;j++)
      for(i=ii; i<ii+iTile; i++){
			current_y[i-1][j-1]=nonmaximum[i][j];
          
        
      }  
      
       
   //thresholding

    for(ii=0; ii<N; ii+=iTile)
    for(j=0;j<M;j++)
      for(i=ii; i<ii+iTile; i++){
            if (current_y[i][j]<=t1 && current_y[i][j]>=t2){
             threshold[i][j]=100;
             
        }
            else if (current_y[i][j]>t1){
               threshold[i][j]=255;
              
               }
            else if (current_y[i][j]<t2) {
                 threshold[i][j]=0;
           
                }             
       }    
      
	for(ii=0; ii<N-1; ii+=iTile)
    for(j=0;j<M-1;j++)
      for(i=ii; i<ii+iTile; i++){
            if (threshold[i][j]==100){
                if(threshold[i+1][j-1] == 255 || threshold[i+1][j] == 255 || threshold[i+1][j+1] == 255
                        || threshold[i][j-1] == 255 || threshold[i][j+1] ==255
                        || threshold[i-1][j-1] == 255 || threshold[i-1][ j] == 255 || threshold[i-1][j+1] == 255)
                        {
                            threshold[i][j]=255;
                            }
                else{
                    threshold[i][j]=0;
                                }
                 }
      }
    for(ii=1; ii<N+1; ii+=iTile)
    for(j=1;j<M+1;j++)
      for(i=ii; i<ii+iTile; i++){
		   
			current_y[i-1][j-1]=threshold[i][j];
          
        
      }
      
      
}



void read()
{
  FILE *frame_c;
  if((frame_c=fopen(filename,"rb"))==NULL)
  {
    printf("current frame doesn't exist\n");
    getchar();
    
    exit(-1);
  }

  for(i=0;i<N;i++)
  {
    for(j=0;j<M;j++)
    {
      current_y[i][j]=fgetc(frame_c);
    }
  }

  fclose(frame_c);
}

void write()
{
  FILE *frame_y;
  frame_y=fopen(file_y,"wb");

  for(i=0;i<N;i++)
  {
    for(j=0;j<M;j++)
    {
      fputc(current_y[i][j],frame_y);
    }
  }
  fclose(frame_y);
}
int main()
{
  read();
  canny();
  write();
}
