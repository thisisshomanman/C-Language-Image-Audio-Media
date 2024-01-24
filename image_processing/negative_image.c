void NegativeImage(void) {

    int iWidth, iHeight, iMaxValue;   // 画像の幅，高さ，解像度
    struct RGB * pRGBInputData;       // 入力データを格納
    struct RGB * pRGBOutputData;      // 画像処理したデータを格納
    int i;                            // ループカウンタ

    // ネガ画像
    printf("\n**** Negative Image *****\n");

    // PPM形式の入力データの読み込み
    pRGBInputData = ReadPpm(&iWidth, &iHeight, &iMaxValue);
    
    // 出力データ（１次元）のメモリ領域の確保
    // pRGBOutputData[iWidth*iHeight]
    pRGBOutputData = (struct RGB *)malloc(iWidth*iHeight*sizeof(struct RGB));

    // 入力データ(pRGBInputData)のRGBの値を反転して，
    // 出力データ(pRGBOutputData)に保存
    for(i = 0; i < iWidth*iHeight; i++){
	pRGBOutputData[i].iRed   = iMaxValue - pRGBInputData[i].iRed;
	pRGBOutputData[i].iGreen = iMaxValue - pRGBInputData[i].iGreen;
	pRGBOutputData[i].iBlue  = iMaxValue - pRGBInputData[i].iBlue;
    }

    // 入力データを保存しているメモリ領域を解放
    FreePpm(pRGBInputData);

    // PPM形式のファイルに出力データを出力
    WritePpm(pRGBOutputData, iWidth, iHeight, iMaxValue);

    // 出力データを保存しているメモリ領域を解放
    FreePpm(pRGBOutputData);
}
