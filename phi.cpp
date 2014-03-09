//Author: Abdullah Alzanidi.
//OpenMP version
#include<stdio.h>
#include<omp.h>



#define numt 8000  //number of threads

omp_lock_t mylock;

int main()
{
unsigned int x;
unsigned int count[numt] = { 0 };
//printf("Please enter Input: ");
x = x | 0xffffffff;
//scanf("%u",&x);
int nthreads;
nthreads = omp_get_max_threads();
printf("Number of threads = %d\n", nthreads);

printf("\nFinding Phi of:  %u\n",x);
unsigned int remainder = x%(numt -1);
        unsigned int size = x / (numt-1);
        unsigned int result_array[numt] = { 0 };
        //dividing the data 

        for (int i = 1; i < numt; i++)
        {
                count[i] = size + count[i - 1];
        }
        if (remainder)
        {
                count[numt - 1] += remainder;
        }
        count[0] = 1;
        unsigned int r2;
        unsigned int y;
        unsigned int x2;
        unsigned int f_result=0;
        //openACC directive 
        #pragma omp parallel for private(r2,y,x2) reduction(+:f_result)
        for(int i=0; i<numt;i++)
        {
                for(unsigned int j=count[i-1];j<count[i];j++)
                {
                        y=x;
                        x2=j;
                        r2 = x2%y;
                        while (r2 != 0)
                        {

                                x2 = y;
                                y = r2;
                                r2 = x2%y;
                        }
                        if (y == 1)
                                f_result++;
                }


        }



printf("result= %u \n",f_result);


return 0;
}


