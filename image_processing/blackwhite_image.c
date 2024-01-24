void BlackWhiteImage(void){
    int Thr = 170;
    int iWidth, iHeight, iMaxValue;
    int *pRGBInputData;
    int *pRGBOutputData;
    int i;

    printf("\n*** BlackWhite Image ***\n");
    pRGBInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);
    pRGBOutputData = (int *)malloc(iWidth*iHeight*sizeof(int));
    
    for(i=0; i<iWidth*iHeight;i++){
        if(pRGBInputData[i]>Thr){
            pRGBOutputData[i] = 255;
        }else{
            pRGBOutputData[i] = 0;
        }
    }

    FreePgm(pRGBInputData);
    WritePgm(pRGBOutputData, iWidth, iHeight, iMaxValue);
    FreePgm(pRGBOutputData);
}
