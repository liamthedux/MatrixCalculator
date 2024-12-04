#include <stdio.h>
#include <time.h>

// DEFINE all the dimensions of the matrices change if needed
#define SIZE 2

int result[SIZE][SIZE];

int matrix_multiplier(int M1[][SIZE], int M2[][SIZE], int i, int j, int k, int n){

    static int counter = 0;

    if ( counter >= SIZE*2 ){
        return 1; // base condition
    }

    if (counter % 2 == 0 && counter > 0){ // handle the second result element
        counter++;

        result[n-1][k-1] = M1[i-1][i-2] * M2[i-2][j-4] + M1[i-1][i-1] * M2[i-1][j-4];

        return matrix_multiplier(M1, M2, 2, 2, k-1, n+1);
    }
    else{
        if ( counter > 2 ){ // handle last result element
            counter++;
            result[n-1][k-1] = M1[i-1][i-2] * M2[i-2][j-1] + M1[i-1][i-1] * M2[i-1][j-1];
            
            return matrix_multiplier(M1, M2, i, j+1, k+1, n);

        }else{ // handle first and second result matrix element
            counter++;
            result[n-1][k-1] = M1[i-2][i-2] * M2[i-2][j-2] + M1[i-2][i-1] * M2[i-1][j-2];

            return matrix_multiplier(M1, M2, i, j+1, k+1, n);
        }      
    }
}

int main() {

    int M1[SIZE][SIZE] = { {1, 2}, {3, 4} };
    int M2[SIZE][SIZE] = { {5, 6}, {7, 8} };

    clock_t tic = clock(); // time in cpu

    matrix_multiplier(M1, M2, 2, 2, 1, 1);

    clock_t toc = clock(); // time out cpu

    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);


    // output/result of the matrix multiplication
    printf("The result of the matrix:\n");

    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}