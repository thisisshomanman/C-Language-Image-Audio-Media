void EdgeDetection(void){
    int iWidth, iHeight, iMaxValue;
    int *piInputData;
    int *piOutputData;
    int x, y, i, j;
    char sobel_x[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    char sobel_y[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    double sum_x, sum_y;
    double sum, max = 0;
    double para;

    printf("\n*** EdgeDetection ***\n");

    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);
    piOutputData = (int*)malloc(iWidth*iHeight*sizeof(int));

    for(i=0; i<iWidth; i++){
        piOutputData[i] = 0;
    }

    for(y=1;y<iHeight-1; y++){
        for(x=1; x<iWidth-1; x++){
            sum_x = 0;
            sum_y = 0;
            for(i=0; i<3; i++){
                for(j=0; j<3; j++){
                    sum_x += sobel_x[i*3+j]*piInputData[(i+y-1)*iWidth+(j+x-1)];
                    sum_y += sobel_y[i*3+j]*piInputData[(i+y-1)*iWidth+(j+x-1)];
                }
            }
            sum = sqrt(pow(sum_y, 2) + pow(sum_x, 2));

            if(sum<0){
                sum = fabs(sum);
            }else if(sum>255){
                sum = 255;
            }
            if (sum>max){
                max = sum;
            }
            piOutputData[y*iWidth+x] = sum;
        }
    }
    para = 255/max;

    for(i=0; i<iWidth*iHeight; i++){
        piOutputData[i] = piOutputData[i]*para;
    }

    FreePgm(piInputData);
    WritePgm(piOutputData, iWidth, iHeight, iMaxValue);
    FreePgm(piOutputData);
}
void ZeroEdgeDetection(void){
    int iWidth, iHeight, iMaxValue;
    int *piInputData;
    int *piPaddedData; // 追加: パディングされたデータ用のポインタ
    int *piOutputData;
    int x, y, i, j;
    char sobel_x[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    char sobel_y[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    double sum_x, sum_y;
    double sum, max = 0;
    double para;

    printf("\n*** EdgeDetection ***\n");

    piInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);
    piOutputData = (int*)malloc(iWidth*iHeight*sizeof(int));
    piPaddedData = (int*)malloc((iWidth+2)*(iHeight+2)*sizeof(int)); // パディングされたデータのためのメモリ確保

    // ゼロパディングを行う
    for(y = 0; y < iHeight + 2; y++){
        for(x = 0; x < iWidth + 2; x++){
            if(x == 0 || y == 0 || x == iWidth + 1 || y == iHeight + 1)
                piPaddedData[y*(iWidth+2) + x] = 0;
            else
                piPaddedData[y*(iWidth+2) + x] = piInputData[(y-1)*iWidth + (x-1)];
        }
    }

    for(y = 1; y < iHeight + 1; y++){
        for(x = 1; x < iWidth + 1; x++){
            sum_x = 0;
            sum_y = 0;
            for(i = 0; i < 3; i++){
                for(j = 0; j < 3; j++){
                    sum_x += sobel_x[i*3+j]*piPaddedData[(i+y-1)*(iWidth+2)+(j+x-1)];
                    sum_y += sobel_y[i*3+j]*piPaddedData[(i+y-1)*(iWidth+2)+(j+x-1)];
                }
            }
            sum = sqrt(pow(sum_y, 2) + pow(sum_x, 2));

            if(sum < 0)
                sum = fabs(sum);
            else if(sum > 255)
                sum = 255;

            if (sum > max)
                max = sum;

            piOutputData[(y-1)*iWidth + (x-1)] = sum; // 出力データをオリジナルのサイズに合わせる
        }
    }
    para = 255/max;

    for(i = 0; i < iWidth*iHeight; i++){
        piOutputData[i] = piOutputData[i]*para;
    }

    FreePgm(piInputData);
    FreePgm(piPaddedData); // パディングされたデータを解放
    WritePgm(piOutputData, iWidth, iHeight, iMaxValue);
    FreePgm(piOutputData);
}