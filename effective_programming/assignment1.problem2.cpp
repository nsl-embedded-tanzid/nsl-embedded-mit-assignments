#include<iostream>
#include<vector>

class Matrix{
    public:
        friend Matrix operator * (Matrix const& matrix1, Matrix const& matrix2);
        friend int operator == (Matrix const& matrix1, Matrix const& matrix2);

        Matrix(int no_row_, int no_col_) : no_row(no_row_), no_col(no_col_), data(no_row_){
            for(int i = 0; i < no_row_; i++)
                data[i].resize(no_col);
        }

        int get_data_index(int row, int col) const{ //returning the specific matrix index value
            return data[row][col];
        }

        void set_data_index(int row, int col, int value){ //replacing the specific matrix index with another value
            data[row][col] = value;
        }
//        Matrix operator * (Matrix const& matrix1){
//            Matrix res_matrix(no_row, matrix1.no_col);
//            for(int i = 0; i < no_row; i++){
//                for(int j = 0; j < matrix1.no_col; j++){
//                    res_matrix.set_data_index(i, j, 0);
//                    for(int k = 0; k < matrix1.no_row; k++){
//                        int res = res_matrix.get_data_index(i, j);
//                        res += get_data_index(i, k) * matrix1.get_data_index(k, j);
//                        res_matrix.set_data_index(i, j, res);
//                    }
//                }
//            }
//            return res_matrix;
//        }
    private:
        int no_row;
        int no_col;
        std::vector<std::vector<int>> data;
};

Matrix operator * (Matrix const& matrix1, Matrix const& matrix2){

    Matrix res_matrix(matrix1.no_row, matrix2.no_col); // creating result matrix with row as matrix1 row and column as matrix2 column

    for(int i = 0; i < matrix1.no_row; i++){
        for(int j = 0; j < matrix2.no_col; j++){
            int res = 0;
            for(int k = 0; k < matrix2.no_row; k++){
                res += (matrix1.get_data_index(i, k) * matrix2.get_data_index(k, j));
            }
            res_matrix.set_data_index(i, j, res);
        }
    }
    return res_matrix;
}

int operator == (Matrix const& matrix1, Matrix const& matrix2){

    if( (matrix1.no_row != matrix2.no_row) || (matrix1.no_col != matrix2.no_col))
        return 0;
    for(int i = 0; i < matrix1.no_row; i++){
        for(int j = 0; j < matrix1.no_col; j++){
            if( matrix1.get_data_index(i, j) != matrix2.get_data_index(i, j))
                return 0;
        }
    }
    return 1;
}

int main()
{
    FILE* input = fopen("assignment1.problem2_data/matrix.3.in","r");   // reading the matrix input file
    FILE* output = fopen("assignment1.problem2_data/matrix.3.out","r"); // reading the actual result matrix file

    int row, col;

    fscanf(input, "%d", &row);  // reading row for first matrix
    fscanf(input, "%d", &col);  // reading column for first matrix
    
    Matrix matrix1(row, col);
    // reading the first matrix values
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            fscanf(input, "%d", &matrix1.index[i][j]);
        }
    }

    fscanf(input, "%d", &row);  // reading row for second matrix
    fscanf(input, "%d", &col);  // reading column for second matrix

    Matrix matrix2(row, col);
    // reading the second matrix values
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            fscanf(input, "%d", &matrix2.index[i][j]);
        }
    }

    Matrix result_matrix = matrix1 * matrix2; // result_matrix is predicted result matrix
    
    fscanf(output, "%d", &row); // reading the actual result matrix row
    fscanf(output, "%d", &col); // reading the actual result matrix column
    
    Matrix out_matrix(row, col);
    // reading the actual answer matrix values
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++)
            fscanf(output, "%d", &out_matrix.index[i][j]);
    }

    if(out_matrix == result_matrix))
        std::cout << "Answer Matched";
    else
        std::cout << "Answer Mismatched";
    
    delete matrix1;
    delete matrix2;
    delete result_matrix;
    delete out_matrix;
    
    fclose(input);
    fclose(output);
}
