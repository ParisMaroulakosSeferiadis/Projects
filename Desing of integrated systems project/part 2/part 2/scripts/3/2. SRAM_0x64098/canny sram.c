#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define N 288 /* frame dimension for QCIF format */
#define M 352 /* frame dimension for QCIF format */
#define filename "akiyo_cif_0_yuv444.yuv"
#define file_y "akiyo2y.yuv"


/* code for armulator*/
#pragma arm section zidata="sram"

int buffer1[M+2];
int buffer2[M+2];
int buffer3[M+2];
int current_y[N][M];

#pragma arm section

int i,j,k;

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
float l=0;
int q=0;
int r=0;
int t1=70;
int t2=60;


void canny(){
	for(i=0;i<N+2;i++)
		for(j=0;j<M+2;j++)
			gauss[i][j]=0;
			sobel[i][j]=0;
		 nonmaximum[i][j]=0;
         threshold[N][M]=0;

	for(i=1;i<N+1;i++)
		for(j=1;j<M+1;j++)
			gauss[i][j]=current_y[i-1][j-1];

/*Edw dinetai to filtrarisma me ton 2d pinaka gaussFilter*/

	for(i=1;i<N+1;i++){
		if(i==1){
			for(k=0;k<M+2;k++){
				buffer1[k]=gauss[0][k];
				buffer2[k]=gauss[1][k];
				buffer3[k]=gauss[2][k];
			}
		}else{
			for(k=0;k<M+2;k++){
             buffer1[k]=buffer2[k];
			 buffer2[k]=buffer3[k];
	         buffer3[k]=gauss[i+1][k];
			}
		}
	
	
	
		for(j=1;j<M+1;j++)
			newgauss[i][j]=(buffer2[j] *(4) + // pollaplasiazei to idio stoixeio me 4
                          buffer1[j-1] *(1) +   // stoixeio panw aristera
                          buffer2[j-1]   *(2) +   // stoixeio aristera
                          buffer3[j-1] *(1) +   // stoixeio katw aristera
                          buffer1[j]   *(2) +   // stoixeio apo panw
                          buffer3[j]   *(2) +   // stoixeio apo katw
                          buffer1[j+1] *(1) +   // stoixeio panw deksia
                          buffer2[j+1]   *(2) +   // stoixeio deksia
                          buffer3[j+1] *(1)  // stoixeio katw deksia
                          );
	}
	for(i=1;i<N+1;i++)
		for(j=1;j<M+1;j++){
			current_y[i-1][j-1]=newgauss[i][j]/16;
            sobel[i-1][j-1]=current_y[i-1][j-1];
        }
	  
	 for(i=1;i<N+1;i++){
        if(i==1){
            for(k=0;k<M+2;k++){
				buffer1[k]=sobel[0][k];
				buffer2[k]=sobel[1][k];
				buffer3[k]=sobel[2][k];
			}
		}else{
			for(k=0;k<M+2;k++){
			 buffer1[k]=buffer2[k];
			 buffer2[k]=buffer3[k];
	         buffer3[k]=sobel[i+1][k];
			}
		}
				
    
//sobel 
		for(j=1;j<M+1;j++)
			newsobelx[i][j]=(buffer1[j-1] *(-1) +   // stoixeio panw aristera
                          buffer2[j-1]   *(-2) +   // stoixeio aristera
                          buffer3[j-1] *(-1) +   // stoixeio katw aristera
                          buffer1[j+1] *(1) +   // stoixeio panw deksia
                          buffer2[j+1]   *(2) +   // stoixeio deksia
                          buffer3[j+1] *(1)  // stoixeio katw deksia
    );
    
    if(i==1){                      
     for(j=1;j<M+1;j++)
         for(i=1;i<N+1;i++)                           
            newsobely[i][j]=(sobel[i-1][j-1] *(1) +   // stoixeio panw aristera
                          sobel[i+1][j-1] *(-1) +   // stoixeio katw aristera
                          sobel[i-1][j]   *(2) +   // stoixeio apo panw
                          sobel[i+1][j]   *(-2) +   // stoixeio apo katw
                          sobel[i-1][j+1] *(1) +   // stoixeio panw deksia
                          sobel[i+1][j+1] *(-1)  // stoixeio katw deksia
                          );
     }  
	 }	 
	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
 {    
     
		    if (newsobely[i][j]==0){
		        newsobely[i][j]=1;
	        
		    }   
       
             z=(newsobelx[i][j]*newsobelx[i][j])+(newsobely[i][j]*newsobely[i][j]);
             l= (float)newsobelx[i][j]/(float)newsobely[i][j];
              
		     es[i][j]=sqrt(z);//plath eikostoixeiwn
		     eo[i][j]=atan(l);//klisi eikonostoixeiwn
}
    for(i=1;i<N+1;i++)
		for(j=1;j<M+1;j++){
			current_y[i-1][j-1]=es[i][j];
          
        
      }
      
      //non maximun
    
    for(i=0;i<N;i++)
		for(j=0;j<M;j++){
			eo[i][j]=(eo[i][j]*180)/3.14;
            if (eo[i][j]<0){
		        eo[i][j]+=180;
	        
		    }  
           
      }  
     
    for(i=1;i<N-1;i++)
		for(j=1;j<M-1;j++){
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
        
    for(i=1;i<N+1;i++)
		for(j=1;j<M+1;j++){
			current_y[i-1][j-1]=nonmaximum[i][j];
          
        
      }  
      
       
   //thresholding
    
    for(i=0;i<N;i++)
		for(j=0;j<M;j++){
		  
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
       
	    for(i=1;i<N+1;i++){
          if(i==1){
            for(k=0;k<M+2;k++){
				buffer1[k]=threshold[0][k];
				buffer2[k]=threshold[1][k];
				buffer3[k]=threshold[2][k];
			}
		}else{
			for(k=0;k<M+2;k++){
			 buffer1[k]=buffer2[k];
			 buffer2[k]=buffer3[k];
	         buffer3[k]=threshold[i+1][k];
			}
		}
     
		for(j=1;j<M-1;j++){
            if (buffer2[j]==100){
            
                if(buffer3[j-1] == 255 || buffer3[j] == 255 || buffer3[j+1] == 255
                        || buffer2[j-1] == 255 || buffer2[j+1] ==255
                        || buffer1[j-1] == 255 || buffer1[ j] == 255 ||buffer1[j+1] == 255)
                        {
                            threshold[i][j]=255;
                            }
                else{
                    threshold[i][j]=0;
                                }
                 }
         }
	    }
      
    for(i=1;i<N+1;i++)
		for(j=1;j<M+1;j++){
		   
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
