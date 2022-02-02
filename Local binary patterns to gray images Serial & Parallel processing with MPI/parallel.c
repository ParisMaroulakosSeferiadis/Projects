#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#define mpi_root 0
#define height 384
#define width 256



int main (int argc, char * argv[]) {
	int rank, value, size;
	char name[80];

	double t1, t2, ts;

	MPI_Status status;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );

	char infname[50], outfname[50];
	//unsigned char inimg[height][width], outimg[height][width];
	short i, j, k, l, counter, b;
	unsigned char *inimg[height];
	for (i=0; i<height; i++)
        inimg[i] = (unsigned char *)malloc(width * sizeof(unsigned char));
	unsigned char *outimg[height];
	for (i=0; i<height; i++)
        outimg[i] = (unsigned char *)malloc(width * sizeof(unsigned char));
	FILE *infile, *outfile;
	if (rank==0){
	printf("input image filename: "); scanf("%s",infname);
	printf("output image filename: "); scanf("%s",outfname);
	infile=fopen(infname,"r");
	for (i=0; i<height; i++)
	fread(inimg[i], 1, width, infile);
	fclose(infile);
	}

	t1 = MPI_Wtime();

	//unsigned char lnew[height][width+2];
	unsigned char *lnew[height];
	for (i=0; i<height; i++)
        lnew[i] = (unsigned char *)malloc((width+2) * sizeof(unsigned char));
	for (i=0; i< height; i++){
		for (j=0; j<width+2; j++){
			lnew[i][j] = 0;
		}
	}
	for (i=0; i< height; i++){
		for (j=0; j<width; j++){
			lnew[i][j+1] = inimg[i][j];
		}
	}

	//unsigned char lnewC[height/size+2][width+2],LBP[height/size+2][width+2];
	unsigned char *lnewC[height/size+2];
	for (i=0; i<height/size+2; i++)
        lnewC[i] = (unsigned char *)malloc((width+2) * sizeof(unsigned char));
	unsigned char *LBP[height/size+2];
	for (i=0; i<height/size+2; i++)
        LBP[i] = (unsigned char *)malloc((width+2) * sizeof(unsigned char));
	MPI_Scatter(&lnew[0][0],(width*height+2*width)/size,MPI_UNSIGNED_CHAR,&lnewC[1][0],(width*height+2*width)/size,MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);
	if (rank==0){
		for (i=0; i<width+2; i++){
			lnewC[0][i]=0;
		}
	}
	if (rank==size-1){
		for (i=0; i<width+2; i++){
			lnewC[height/size+1][i]=0;
		}
	}
	if (rank!=size-1){
		MPI_Send(&lnewC[height/size][0],height/size+2,MPI_UNSIGNED_CHAR,rank+1,0,MPI_COMM_WORLD);
	}
	if (rank!=0){
		MPI_Recv(&lnewC[0][0],height/size+2,MPI_UNSIGNED_CHAR,rank-1,0,MPI_COMM_WORLD,&status);
	}
	if (rank!=0){
		MPI_Send(&lnewC[1][0],height/size+2,MPI_UNSIGNED_CHAR,rank-1,0,MPI_COMM_WORLD);
	}
	if (rank!=size-1){
		MPI_Recv(&lnewC[height/size+1][0],height/size+2,MPI_UNSIGNED_CHAR,rank+1,0,MPI_COMM_WORLD,&status);
	}

	for (i=0; i< height/size+2; i++){
		for (j=0; j<width+2; j++){
			LBP[i][j] = 0;
		}
	}
	unsigned char Maska[3][3];
	for (i=0; i< 3; i++){
		for (j=0; j<3; j++){
			Maska[i][j] = 0;
		}
	}

	unsigned char T;//,C2;
	unsigned char B[9];//isws 8 kai panw sto Maska nai einai oi distaseis Maska[2][2]

	for (i=1; i<height/size+1 ; i++){
		for (j=1; j<width+1; j++){
			T=lnewC[i][j];
			for (k=i-1; k<= i+1; k++){
				for (l=j-1; l<=j+1; l++){
					Maska[k-i+1][l-j+1]=lnewC[k][l];
				}
			}
			Maska[1][1]=0;

			/*C2=0;

			for (k=i-1; k<= i+1; k++){
				for (l=j-1; l<=j+1; l++){
				C2=C2+Maska[k-i+1][l-j+1];
				}
			}*/

			counter=0;
			//unsigned char sumsumMaskaB[9];
			for (l=0; l<3; l++){
				for (k=0; k<3; k++){
					if(Maska[k][l]>T){
						B[counter]=counter+1;
						//sumsumMaskaB[counter]=Maska[k][l];
					}
					else{
						B[counter]=0;
						//sumsumMaskaB[counter]=0;
					}
					counter=counter+1;
				}
			}

			unsigned char empty_B;
			empty_B = 0;
			//unsigned char C1;lbp_par.c
			//C1=0;
			for (k=0; k<9; k++){
				empty_B = empty_B + B[k];
			}
			//unsigned char number_1;
			if (empty_B>0){
				/*for (k=0; k<9; k++){
					C1=C1+sumsumMaskaB[k];
				}*/
				for (k=0; k< 3; k++){
					for (l=0; l<3; l++){
						if(Maska[k][l]>T){
							Maska[k][l] = 1;
						}else{
							Maska[k][l] = 0;
						}
					}
				}
				/*number_1 = 0;
				for (k=0; k< 3; k++){
					for (l=0; l<3; l++){
						number_1 = number_1 + Maska[k][l];
					}
				}*/
			}else{
			//	C1=0;
				for (k=0; k< 3; k++){
					for (l=0; l<3; l++){
						Maska[k][l] = 0;
					}
				}
			//	number_1=0;
			}
			LBP[i][j]=Maska[0][0]*128+Maska[0][1]*64+Maska[0][2]*32+Maska[1][2]*16+Maska[2][2]*8+Maska[2][1]*4+Maska[2][0]*2+Maska[1][0];
			/*C2=C2-C1;
			if (number_1>0){
				if (8-number_1>0){
					C[i][j]=(C1/number_1)-(C2/(8-number_1));
				}else{
					C[i][j]=C1/number_1;
				}
			}else{
				C[i][j]=-(C2/(8-number_1));
			}*/
		}
	}

	//unsigned char lnewD[height][width+2];
	unsigned char *lnewD[height];
	for (i=0; i<height; i++)
        lnewD[i] = (unsigned char *)malloc((width+2) * sizeof(unsigned char));
	MPI_Gather(&LBP[1][0],(width*height+2*width)/size,MPI_UNSIGNED_CHAR,&lnewD[0][0],(width*height+2*width)/size,MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

	if (rank==0){
	for (i=0; i< height; i++)
		for (j=0; j<width; j++)
			outimg[i][j] = lnewD[i][j+1];
	t2 = MPI_Wtime();
	if (rank==0) printf("execution time measured : %f sec\n", t2-t1);

	outfile=fopen(outfname,"w");
	for (i=0; i< height; i++)
		fwrite(outimg[i], 1, width, outfile);
	fclose (outfile);
	}
	MPI_Finalize( );
}
