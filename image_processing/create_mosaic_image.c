void CreateMosaicImage(void){
    int iWidth, iHeight, iMaxValue;
    int *pInputData, *pOutputData;
    int i, j, k, l;
    int n; // モザイクのブロックサイズ

    printf("Enter the block size for the mosaic: ");
    scanf("%d", &n);

    // PGMファイルから濃淡画像を読み込む
    pInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);

    pOutputData = (int *)malloc(iWidth * iHeight * sizeof(int));

    for (i = 0; i < iHeight; i += n) {
        for (j = 0; j < iWidth; j += n) {
            int sum = 0;
            int count = 0;

            // ブロック内のピクセル値の平均を計算
            for (k = i; k < i + n && k < iHeight; k++) {
                for (l = j; l < j + n && l < iWidth; l++) {
                    sum += pInputData[k * iWidth + l];
                    count++;
                }
            }

            int avg = sum / count;

            // ブロックを平均値で塗りつぶす
            for (k = i; k < i + n && k < iHeight; k++) {
                for (l = j; l < j + n && l < iWidth; l++) {
                    pOutputData[k * iWidth + l] = avg;
                }
            }
        }
    }

    // モザイク画像をPGMファイルとして保存
    WritePgm(pOutputData, iWidth, iHeight, iMaxValue);

    free(pInputData);
    free(pOutputData);
}