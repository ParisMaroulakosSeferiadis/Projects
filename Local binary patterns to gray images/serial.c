#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define N 256 
#define M 256 
#define filename "gr_limnio_256x256.raw"
#define file_y "gr_limnio_256x256_serial.raw"

int inimg[N][M];
int outimg[N][M];
int Maska[N+2][M+2];
int LBP[N+2][M+2];
int i,j,k,sum;

void test()
{
    
    
       for(i=0;i<N+2;i++)
		for(j=0;j<M+2;j++){
		    Maska[i][j]=0;
		    LBP[i][j]=0;
        }
        
        for(i=1;i<N+1;i++)
		for(j=1;j<M+1;j++){
			Maska[i][j]=inimg[i-1][j-1];
      }    
      for(i=1;i<N+1;i++)
		for(j=1;j<M+1;j++){
            k=Maska[i][j]; //katofli T
            sum=0;              
             if (Maska[i][j-1]>k){      //stoixeio aristera
		      
		       sum= sum+ 128;
		    }  
		      
           if (Maska[i+1][j-1]>k){       //stoixeio katw aristera
		       
		       sum= sum+ 64;
		    }  
		      
           if (Maska[i+1][j]>k){       //stoixeio katw 
		      
		       sum= sum+32;
		    }  
		    
            if (Maska[i+1][j+1]>k){       //stoixeio katw deksia
		     
		       sum=sum+16;
		    }  
		  
           if (Maska[i][j+1]>k){       //stoixeio  deksia
		     
		       sum=sum+8;
		    }  
	  
           if (Maska[i-1][j+1]>k){       //stoixeio  panw deksia
		    
		       sum=sum+4;
		    }  
		      
           if (Maska[i-1][j]>k){       //stoixeio  panw 
		     
		       sum=sum+2;
		    }  
           if (Maska[i-1][j-1]>k){       //stoixeio  panw aristera
		       
		       sum=sum+1;
		    }  
           printf("%d\n",k);
           LBP[i][j]=sum;                   
      }
         
            

             
      for(i=0;i<N;i++)
		for(j=0;j<M;j++){
		    outimg[i][j] = LBP[i+1][j+1];
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
      inimg[i][j]=fgetc(frame_c);
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
      fputc(outimg[i][j],frame_y);
    }
  }
  fclose(frame_y);
}
int main()
{
clock_t start, end;

  read();
  start = clock();
  test();
  end = clock();
  write();
 

printf("Sequential time: %.5fms\n",((double) (end - start)) / CLOCKS_PER_SEC);
getchar();
}

