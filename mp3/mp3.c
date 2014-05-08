#include <stdio.h>
#include<stdlib.h>
#include<string.h>

//Global Variables
char c[8], comma;
int dimension, i=0, j=0, vertex1, vertex2;  //easy part
int cost=0, column=0, row=0, top=0, stack_column[300], stack_row[300];  //core of the problem
int sequence_array[100], length=0, max=0, flag=0, counter=0;   //sequencing

//----------SEQUENCE FUNCTION----------//
sequence() {
    for(i=0; i<100; i++) sequence_array[i]=0;
    sequence_array[0]=cost;
    for(i=0; i<top; i++) sequence_array[i+1]=stack_column[i];
    //printf("c: %d, s: %d ", sequence_array[0], vertex1);
    //for(i=1; i<=top; i++) printf("%d ", sequence_array[i]+1);
    max=cost;
    length=top;
}

//----------MAIN FUNCTION----------//
main () {
            printf("---------------------------------------------------\n");
            printf("||\\\\\\\\\\\\\\\\\\\\\\\\|  MACHINE PROBLEM 3  |////////////||\n");
            printf("||////////////|     GRAPH THEORY    |\\\\\\\\\\\\\\\\\\\\\\\\||\n");
            printf("||\\\\\\\\\\\\\\\\\\\\\\\\|                     |////////////||\n");
            printf("||////////////|                     |\\\\\\\\\\\\\\\\\\\\\\\\||\n");
            printf("||\\\\\\\\\\\\\\\\\\\\\\\\|   Gozum, Ryan Paul  |////////////||\n");
            printf("||////////////|      2011-50419     |\\\\\\\\\\\\\\\\\\\\\\\\||\n");
            printf("---------------------------------------------------\n");

   FILE *f;
   char filename[20];

   printf("Enter Filename: ");
   scanf("%s", filename);
   f = fopen(filename,"r");
   if(f==NULL) {
        printf("\nCould not find '%s'", filename);
        exit(1);
    }

   printf("\n");
   c: while(!feof(f)) {
      int k=0;
      *c='\0';

      //get the matrix dimension
      printf("****** DATA SET ******\n\n");
      do {
            c[k]=fgetc(f);
            k++;
       } while(c[k-1]!='\n');
       dimension=atoi(c);
       int matrix[dimension][dimension];
       int gray[dimension];

       //initialize gray array
       for(i=0; i<dimension; i++) gray[i]=0;

       //save matrix to array
       for(i=0; i<dimension; i++) {
            for(j=0; j<dimension; j++) {
                k=0;
                *c='\0';
                do {
                    c[k]=fgetc(f);
                    if(c[k]=='\n' || feof(f)) break;
                    k++;
                } while(c[k-1]!='\t');
                matrix[i][j]=atoi(c);
            }
       }

        if(!feof(f)) c[k]=fgetc(f);

       //printf matrix array
       printf("ADJACENCY MATRIX\n");
       for(i=1; i<=dimension; i++) printf("\t%d", i);
       printf("\n");
       for(i=0; i<dimension; i++) {
            printf("%d\t", i+1);
            for(j=0; j<dimension; j++) {
                printf("%d\t", matrix[i][j]);
            }
            printf("\n");
       }
       printf("\n");

       //INPUT (i, j)
       a: printf("Enter pair of vertices: ");
           scanf("%d %c %d", &vertex1, &comma, &vertex2);
       if(vertex1<0 || vertex1>dimension || vertex2<0 || vertex2>dimension) {
            printf("Invalid pair of vertices!\n\n");
            goto a;
       }
       printf("\n");

       while(vertex1!=0 && vertex2!=0) {
           //TRAVERSING GRAPH
            row=vertex1-1;
            gray[row]=1;
            b: while(column<dimension) {
                if(matrix[row][column]!=0) {
                    if(gray[column]==1 && column!=vertex2-1) {
                        column++;
                        goto b;
                    }
                    gray[column]=1;
                    stack_column[top]=column;
                    stack_row[top]=row;
                    top++;
                    cost+=matrix[row][column];
                    row=column;
                    column=0;
                    if(row==vertex2-1) {
                        counter++;
                        if(counter==1) max=cost;
                        if(max<cost || counter==1) sequence();
                        top--;
                        row=stack_row[top];
                        column=stack_column[top];
                        gray[column]=0;
                        cost-=matrix[row][column];
                        column++;
                        goto b;
                    }
                    goto b;
                }
                column++;
            }   //end of while
            if(column==dimension && row==vertex1-1) {
                if(sequence_array[0]=='\0') {
                    printf("The cost of the longest path from %d to %d is:  %d\nThe longest path from %d to %d is:  No Path Found! ", vertex1, vertex2, sequence_array[0], vertex1, vertex2);
                    flag=1;
                }
            } else {
                top--;
                row=stack_row[top];
                column=stack_column[top];
                gray[column]=0;
                cost-=matrix[row][column];
                column++;
                goto b;
            }
           //--------
           if(flag==0) {
               printf("The cost of the longest path from %d to %d is:  %d\nThe longest path from %d to %d is:  %d ", vertex1, vertex2, sequence_array[0], vertex1, vertex2, vertex1);
               for(j=1; j<=length; j++) {
                    printf("%d ", sequence_array[j]+1);
               }
           }
           printf("\n\n");

           //REINITIALIZE
           for(i=0; i<dimension; i++) gray[i]=0;
           for(j=0; j<100; j++) sequence_array[j]=0;
           for(i=0; i<300; i++) {
                stack_column[i]=0;
                stack_column[j]=0;
           }
           i=0, j=0, cost=0, column=0, row=0, top=0, length=0, max=0, flag=0, counter=0;

           goto a;
       }    //end of while (vertex1!=0 || vertex2!=0)

    }   //End of while(!feof(f))
}
