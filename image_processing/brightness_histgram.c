void BrightnessHistgram(void){
    int iWidth, iHeight, iMaxValue;
    int *pRGBInputData;
    int i;
    int hst[256]={};
    FILE*fp;

    printf("\n*** BrighnessHistgram ***\n");
    pRGBInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);

    if((fp = fopen("hist.dat", "w")) == NULL){
        printf("file open error!!\n");
    }

    for(i = 0; i<iWidth*iHeight; i++){
        hst[pRGBInputData[i]]++;
    }

    for(i=0; i<256; i++){
        fprintf(fp, "%d %d\n", i, hst[i]);
    }
}