#ifndef MAT_H_INCLUDED
#define MAT_H_INCLUDED

class MAT
{
    private:
        size_t rows;
        size_t cols;
        size_t stride;
        float *arr = nullptr;

    public:

        void deallocate()
        {
            delete[] arr;
        }

        MAT(size_t rows,size_t cols,size_t stride,float *arr)
        {
            this->rows = rows;
            this->cols = cols;
            this->stride = stride;
            if(arr == nullptr)
                throw std::invalid_argument("Arr must not be null");
            this->arr = arr;
        }
        MAT(size_t rows,size_t cols,float *arr)
        {
            this->rows = rows;
            this->cols = cols;
            this->stride = cols;
            if(arr == nullptr)
                throw std::invalid_argument("Arr must not be null");
            this->arr = arr;
        }
        MAT(size_t rows,size_t cols)
        {
            this->rows = rows;
            this->cols = cols;
            this->stride = cols;
            printf("warning! : you have allocated memory 'MAT(rows,cols)'. **Don't forget to call MAT.deallocate() if not use the MAT\n");
            while(arr == nullptr)
                this->arr = new float[rows*cols];

        }

         float getElement(size_t r,size_t c)
         {
             return arr[r*this->stride + c];
         }
         void setElement(float value, size_t r,size_t c)
         {
             arr[r*this->stride + c] = value;
         }


         void print_mat()
         {
             printf("[\n");
             for(size_t nrow=0;nrow<rows;nrow++)
             {
                 printf("\t|");
                 for(size_t ncol=0;ncol<cols;ncol++)
                 {
                     printf("%f ",getElement(nrow,ncol));
                 }
                 printf("|\n");
             }
             printf("]\n");
         }

        MAT getRow(size_t row)
        {
            return MAT(1,this->cols,this->stride,&arr[row*this->stride]);  // deallocate may affect this MAT
        }
        MAT getCol(size_t col)
        {
            return MAT(this->rows,1,this->stride,&arr[col]); // deallocate may affect this MAT
        }

        // copy new MAT that do not share the same memory
        MAT clone()
        {
            MAT newM = MAT(this->rows,this->cols);
            for(size_t i=0;i<this->rows;i++)
            {
                for(size_t j=0;j<this->cols;j++)
                {
                    float value = getElement(i,j);
                    newM.setElement(value,i,j);
                }
            }
            return newM;
        }



        ///get&set
        size_t getRows(){
            return this->rows;
        }
        size_t getCols(){
            return this->cols;
        }
        size_t getStride(){
            return this->stride;
        }
        void getArr(float *pt){
            pt = this->arr; // deallocate may affect this
        }
        void setRows(size_t rows){
            this->rows = rows;
        }
        void setCols(size_t cols){
            this->cols = cols;
        }
        void setStride(size_t stride){
            this->stride = stride;
        }
        void setArr(float *pt){
            this->arr = pt;
        }
         ///get$set

};

float randfloat();

void mat_sum(MAT dest, MAT a, MAT b);
void mat_mul(MAT dest, MAT a, MAT b);

void mat_fill(MAT a,float value);
void mat_rand(MAT a,float minimum,float maximum);

void mat_copy(MAT dest, MAT src);


#endif // MAT_H_INCLUDED

#ifdef MAT_OPERATION

float randfloat()
{
    return (float)rand() / RAND_MAX;
}

void mat_rand(MAT a,float minimum,float maximum)
{
    for(int i=0;i<a.getRows();i++)
    {
        for(size_t j=0;j<a.getCols();j++)
        {
            float value = randfloat()*(maximum-minimum) + minimum;
            a.setElement(value,i,j);
        }
    }
}
void mat_fill(MAT a,float value)
{
    for(int i=0;i<a.getRows();i++)
    {
        for(size_t j=0;j<a.getCols();j++)
        {
            a.setElement(value,i,j);
        }
    }
}

void mat_sum(MAT dest, MAT a, MAT b)
{
    if(a.getRows() != b.getRows())
        throw std::invalid_argument("first MAT' rows not equal to second MAT");
    if(b.getCols() != a.getCols())
        throw std::invalid_argument("first MAT' cols not equal to second MAT");
    if(dest.getRows() != b.getRows())
        throw std::invalid_argument("dest MAT' rows invalid");
    if(dest.getCols() != a.getCols())
        throw std::invalid_argument("dest MAT' cols invalid");

    for(size_t i=0;i<dest.getRows();i++)
    {
        for(size_t j=0;j<dest.getCols();j++)
        {
            float sum = a.getElement(i,j)+b.getElement(i,j);
            dest.setElement(sum,i,j);
        }
    }

}

void mat_mul(MAT dest, MAT a, MAT b)
{
    if(a.getRows() != dest.getRows())
        throw std::invalid_argument("dest MAT' rows must be equal to first MAT");
    if(b.getCols() != dest.getCols())
        throw std::invalid_argument("dest MAT' cols must be equal to first MAT");
    if(a.getCols() != b.getRows())
        throw std::invalid_argument("first MAT' cols must be equal to second MAT' cols");

    for(size_t i=0;i<dest.getRows();i++)
    {
        for(size_t j=0;j<dest.getCols();j++)
        {
            float sum = 0;
            for(size_t k=0;k<a.getCols();k++)
            {
                sum += a.getElement(i,k)*b.getElement(k,j);
            }
            dest.setElement(sum,i,j);
        }
    }

}

void mat_copy(MAT dest, MAT src)
{
    if(dest.getRows() != src.getRows())
        throw std::invalid_argument("dest' rows not equal to src");
    if(dest.getCols() != src.getCols())
        throw std::invalid_argument("dest' cols not equal to src");

    for(size_t i=0;i<dest.getRows();i++)
    {
        for(size_t j=0;j<dest.getCols();j++)
        {
            float value = src.getElement(i,j);
            dest.setElement(value,i,j);
        }
    }
}


#endif // MAT_OPERATION
