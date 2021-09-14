
#ifndef matrix_h
#define matrix_h

#include <stdio.h>
#include<stdlib.h>

#endif /* matrix_h */

                        /* The vector structure */
struct vector
{
    unsigned length;
    double * head;
};
typedef struct vector vector;

/* Prototypes */

/* Construction and destruction */
vector createVector(unsigned);
void freeVector(vector);

/* Printing and scaning */
void printVector(vector);
void scanVector(vector *);

/* Arithmetic operations */
vector sumVector(vector, vector);
vector scaleVector(double, vector);



                        /* The matrix structure */

struct matrix
{
    unsigned row;
    unsigned column;
    double ** head;
};
typedef struct matrix matrix;

/* Prototypes */

/* Construction and destruction */
matrix createMatrix(unsigned, unsigned);
void freeMatrix(matrix);

/* Printing and scaning */
void printMatrix(matrix);
void scanMatrix(matrix *);

/* Arithmetic operations */
matrix sumMatrix(matrix,matrix);
matrix productMatrix(matrix,matrix);
matrix scaleProductMatrix(double,matrix);


/* Echelon forms */
matrix transposeMatrix(matrix);
void rowExchangeMatrix(matrix *M,unsigned i,unsigned j);
void addRowMatrix(matrix *,vector,unsigned);
matrix rowEchelonForm(matrix);
matrix columnEchelonForm(matrix);
/* The function create*/
vector createVector(unsigned n)
{
    vector V;
    V.length=n;
    V.head=(double *)malloc(n*sizeof(double));
    return V;
}
/* The function scaleVector */
vector scaleVector(double a,vector V)
{
    vector W=createVector(V.length);
    for(int i=0;i<W.length;i++)
        W.head[i]=a*V.head[i];
    return W;
}
/* The function freeVector*/

void freeVector(vector V)
{
    if(V.head!=NULL)
        free(V.head);
    V.head=NULL;
}


                        /* Implementation of the matrix data structure */

/* The function createMatrix */
matrix createMatrix(unsigned r,unsigned c)
{
    matrix M={0,0,NULL};
    M.row=r;
    M.column=c;
    M.head=(double **)malloc(r*sizeof(double *));
    for(int i=0;i<M.row;i++)
        M.head[i]=(double *)malloc(c*sizeof(double));
    return M;
}

/* The function freeMatrix */
void freeMatrix(matrix M)
{
    if(M.head!=NULL)
    {
        for(int i=0;i<M.row;i++)
        {
            if(M.head[i]!=NULL)
                free(M.head[i]);
        }
        free(M.head);
    }
    return;
}

/* The function printMatrix */
void printMatrix(matrix M)
{
    if(M.head==NULL)
    {
        printf("|  |\n");
        return;
    }
    for(int i=0;i<M.row;i++)
    {
        printf("| ");
        for(int j=0;j<M.column-1;j++)
            printf("%lf ",M.head[i][j]);
        printf("%lf |\n\n",M.head[i][M.column-1]);
    }
    printf("\n");
    return;
}

/* The function scanMatrix */
void scanMatrix(matrix * M)
{
    if(M->head==NULL)
        return;
    for(int i=0;i<M->row;i++)
    {
        for(int j=0;j<M->column;j++)
            scanf("%lf",M->head[i]+j);
    }
    return;
}
/* The function transposeMatrix */
matrix transposeMatrix(matrix M)
{
    matrix R={0,0,NULL};
    if(M.head==NULL)
        return R;
    R=createMatrix(M.column,M.row);
    for(int i=0;i<R.row;i++)
    {
        for(int j=0;j<R.column;j++)
            R.head[i][j]=M.head[j][i];
    }
    return R;
}
/* The function rowExchangeMatrix */
void rowExchangeMatrix(matrix *M,unsigned i,unsigned j)
{
    if(i>=M->row || j>=M->row)
        return;
    if(M==NULL)
        return;
    double x;
    for(int k=0;k<M->column;k++)
    {
        x=M->head[i][k];
        M->head[i][k]=M->head[j][k];
        M->head[j][k]=x;
    }
    return;
}
/* The function addRowMatrix */
void addRowMatrix(matrix * M,vector V,unsigned i)
{
    if(M==NULL || V.head==NULL)
        return ;
    if(M->column!=V.length)
        exit(EXIT_FAILURE);
    if(i>=M->column)
        return ;
    for(int j=0;j<M->column;j++)
        M->head[i][j]+=V.head[j];
    return ;
}
/* The function vecteur_ieme */
vector vecteur_ieme(matrix M,unsigned j)
{
	vector V=createVector(M.row);
    for(int i=0;i<V.length;i++)
        V.head[i]=M.head[j][i];
    return V;
	
}
/* The fuction echlonneMatrix */
matrix echelonneMatrix(matrix *L)
{
	matrix *M=L;
	for(int i=0;i<M->row;i++)
		{
			for(int j=0;j<M->row-1 ;j++)
			{
				if(M->head[j+1][i] !=0)
				{
					addRowMatrix(M, scaleVector(-(M->head[j][i])/(M->head[j+1][i]),vecteur_ieme( *M , j+1 )),j );
					freeVector(scaleVector(-(M->head[j][i])/(M->head[j+1][i]),vecteur_ieme( *M , j+1 )));

				}
				else
				{
					rowExchangeMatrix(M,j,j+1);
				}
			}
		}
	*M=transposeMatrix( *M);
return *M;

}
int main()
{
	printf("la matrice carree est d'ordre n= ");
	unsigned i;
	scanf("%d",&i);
   	matrix P=createMatrix(i,i);
  	scanMatrix(&P);
   	printMatrix(P);
	P=echelonneMatrix(&P);
	printMatrix(P);
    	freeMatrix(P);
    	return 0;
}
