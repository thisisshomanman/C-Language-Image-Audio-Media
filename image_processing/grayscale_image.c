void GrayscaleImage(void){
    int iWidth, iHeight, iMaxValue;
    struct RGB * pRGBInputData;
    int *pRGBOutputData;
    int i;

    printf("\n*** Grayscale Image ***\n");

    pRGBInputData = ReadPpm(&iWidth, &iHeight, &iMaxValue);

    int a = 0.3*1024;//赤の重み
    int b = 0.6*1024;//緑の重み
    int c = 0.1*1024+1;//青の重み

    pRGBOutputData = (int *)malloc(iWidth*iHeight*sizeof(int));

    for (i=0; i<iWidth*iHeight; i++){
        pRGBOutputData[i] = (a*pRGBInputData[i].iRed + b*pRGBInputData[i].iGreen + c*pRGBInputData[i].iBlue)/1024;
    }
    FreePpm(pRGBInputData);
    WritePgm(pRGBOutputData, iWidth, iHeight, iMaxValue);
    FreePpm(pRGBOutputData);
}
//少数演算で実現したコード
void GrayscaleImageFloat(void){
    int iWidth, iHeight, iMaxValue;
    struct RGB * pRGBInputData;
    int *pGrayOutputData;
    int i;

    printf("\n*** Grayscale Image ***\n");

    pRGBInputData = ReadPpm(&iWidth, &iHeight, &iMaxValue);

    float a = 0.299; // 赤の重み
    float b = 0.587; // 緑の重み
    float c = 0.114; // 青の重み

    pGrayOutputData = (int *)malloc(iWidth * iHeight * sizeof(int));

    for (i = 0; i < iWidth * iHeight; i++){
        pGrayOutputData[i] = (a * pRGBInputData[i].iRed + b * pRGBInputData[i].iGreen + c * pRGBInputData[i].iBlue);
    }
    FreePpm(pRGBInputData);
    WritePgm(pGrayOutputData, iWidth, iHeight, iMaxValue);
    FreePpm(pGrayOutputData);
}
// 濃淡画像生成の際のYに対して，重みを使用せずに，RGBを均等にした時
void GrayscaleImageEqualWeight(void){
    int iWidth, iHeight, iMaxValue;
    struct RGB * pRGBInputData;
    int *pRGBOutputData;
    int i;

    printf("\n*** Grayscale Image with Equal Weight ***\n");

    pRGBInputData = ReadPpm(&iWidth, &iHeight, &iMaxValue);

    int a = 1024/3; // R, G, Bの重みを等しくする
    int b = 1024/3;
    int c = 1024/3;

    pRGBOutputData = (int *)malloc(iWidth*iHeight*sizeof(int));

    for (i=0; i<iWidth*iHeight; i++){
        pRGBOutputData[i] = (a*pRGBInputData[i].iRed + b*pRGBInputData[i].iGreen + c*pRGBInputData[i].iBlue)/1024;
    }
    FreePpm(pRGBInputData);
    WritePgm(pRGBOutputData, iWidth, iHeight, iMaxValue);
    FreePpm(pRGBOutputData);
}