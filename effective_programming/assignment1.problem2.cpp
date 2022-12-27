#include<iostream>
#include<stdlib.h>

class Matrix{    
    public:
        int row, col;
        int** index;

        Matrix(int row, int col){
            this->row = row;
            this->col = col;
            this->index = (int**)malloc(sizeof(int*) * row);
        }
        
        void create_matrix(){
            for(int i=0; i < this->row; i++)
                index[i] = (int*)malloc(sizeof(int) * this->col);
        }
};

Matrix matrix_multiplication(Matrix matrix1, Matrix matrix2){

    Matrix ans_matrix(matrix1.row, matrix2.col);
    ans_matrix.create_matrix();

    for(int i=0; i<matrix1.row; i++){
        for(int j=0; j<matrix2.col; j++){
            ans_matrix.index[i][j] = 0;
            for(int k=0; k<matrix2.row; k++)
                ans_matrix.index[i][j] += (matrix1.index[i][k] * matrix2.index[k][j]);
        }
    }
    return ans_matrix;
}

bool check_ans(Matrix matrix1, Matrix matrix2){

    if(matrix1.row != matrix2.row)  return false;
    if(matrix1.col != matrix2.col)  return false;

    for(int i=0; i<matrix1.row; i++){
        for(int j=0; j<matrix1.col; j++){
            if(matrix1.index[i][j] != matrix2.index[i][j])
                return false;
        }
    }
    return true;
}

int main()
{
    FILE* input = fopen("assignment1.problem2_data/matrix.3.in","r");
    FILE* output = fopen("assignment1.problem2_data/matrix.3.out","r");

    int row, col;

    fscanf(input, "%d", &row);
    fscanf(input, "%d", &col);
    
    Matrix matrix1(row, col);
    matrix1.create_matrix();
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            fscanf(input, "%d", &matrix1.index[i][j]);
        }
    }

    fscanf(input, "%d", &row);
    fscanf(input, "%d", &col);

    Matrix matrix2(row, col);
    matrix2.create_matrix();
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            fscanf(input, "%d", &matrix2.index[i][j]);
        }
    }

    Matrix result_matrix = matrix_multiplication(matrix1, matrix2);
    
    fscanf(output, "%d", &row);
    fscanf(output, "%d", &col);
    
    Matrix out_matrix(row, col);
    out_matrix.create_matrix();
    
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++)
            fscanf(output, "%d", &out_matrix.index[i][j]);
    }

    if(check_ans(out_matrix, result_matrix))
        std::cout << "Answer Matched";
    else
        std::cout << "Answer Mismatched";

    fclose(input);
    fclose(output);
}