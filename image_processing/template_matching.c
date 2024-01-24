void MakeTemplateImage(void){
    //変数宣言
    int iWidth, iHeight, iMaxValue;   // 入力画像の幅，高さ，解像度
    int tMaxvalue;     
    int * pGrayInputData;       // 入力データを格納
    int * pGrayTemplateData;       //テンプレートデータを格納
    int ** W = NULL;    //計算用ポインタ（２次元配列）
    int i, h, w;  //カウンタ


    //テンプレートとして取り出す点の元画像における座標
    // int X=100; 
    // int Y=150;
    int X=20;
    int Y=30;
    // //テンプレート画像のWidth, Height
    // int tWidth = 500;
    // int tHeight = 250;
    int tWidth = 125;
    int tHeight = 100;


    //メモリ領域の確保
    pGrayInputData = (int *)malloc(iWidth*iHeight*sizeof(int));
    pGrayTemplateData = (int *)malloc(tWidth*tHeight*sizeof(int));

    // PGM形式の入力データの読み込み
    pGrayInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue);

    //計算用ポインタ（２次元配列）の領域確保
    W = (int**)malloc(sizeof(int*) * iWidth);
    if(W == NULL){
        printf("Error:W-1\n");
    }
    for(i = 0; i < iWidth; i++){
        W[i] = (int*)malloc(sizeof(int) * iHeight);
        if(W[i] == NULL){
            printf("Error:W-2\n");
        }
    }
    //入力画像を2次元配列化
    i = 0;
    for(h=0; h<iHeight; h++){
        for(w=0; w<iWidth; w++){
            W[w][h] = pGrayInputData[i];
            i++;
        }
    }


    //テンプレート画像の１次元配列を作成
    i=0;
    for(h=0; h<tHeight; h++){
        for(w=0; w<tWidth; w++){
            pGrayTemplateData[i] = W[X+w][Y+h];
            i++;
        }
    }

    //tMaxvalueの取得
    tMaxvalue = pGrayTemplateData[0];
    for (int i = 1; i < tHeight*tWidth; i++) {
        if(tMaxvalue<pGrayTemplateData[i]){
            tMaxvalue = pGrayTemplateData[i];
        }
    }

    WritePgm(pGrayTemplateData, tWidth, tHeight, tMaxvalue);

    free(pGrayInputData);
    free(pGrayTemplateData);

}
//テンプレートマッチング
void TemplateMatching(void){
    int iWidth, iHeight, iMaxValue;   // 画像の幅，高さ，解像度
    int tWidth, tHeight, tMaxvalue;
    int * pGrayInputData;       // 入力データを格納
    int * pGrayTemplateData;    //テンプレート画像格納
    int * pPredictData;         //予測(出力)結果を格納
    int ** W = NULL;            //入力データ２次元配列化用のポインタ
    int ** T = NULL;            //テンプレートデータ用ポインタ
    float ** R = NULL;          //相関関数用のポインタ
    int t, w, h, i, j;          // ループカウンタ
    int x, y;                   //注目点の座標
    float WT, Wa, Wb;           //講義資料と同様
    int X_best = 0;             //相関最大の座標保存用
    int Y_best = 0;
    float Buff = 0.0;         
    int count=0;


    printf("\n*** Template Matching ***\n");

    //メモリ領域の確保
    pPredictData = (int *)malloc(tWidth*tHeight*sizeof(int));   //output data
    pGrayInputData = (int *)malloc(iWidth*iHeight*sizeof(int)); //input data
    pGrayTemplateData = (int *)malloc(tWidth*tHeight*sizeof(int));//template data

    // PGM形式の入力データの読み込み
    printf("Template Image: ");
    pGrayInputData = ReadPgm(&iWidth, &iHeight, &iMaxValue); 
    printf("Part Image: ");
    pGrayTemplateData = ReadPgm(&tWidth, &tHeight, &tMaxvalue);
    

    //計算用ポインタの宣言
    //入力画像
    W = (int**)malloc(sizeof(int*) * iWidth);
    if(W == NULL){
        printf("Error:W-1\n");
    }
    for(i = 0; i < iWidth; i++){
        W[i] = (int*)malloc(sizeof(int) * iHeight);
        if(W[i] == NULL){
            printf("Error:W-2\n");
        }
    }
    //テンプレート画像
    T = (int**)malloc(sizeof(int*) * tWidth);
    if(T == NULL){
        printf("Error:T-1\n");
    }
    for(i = 0; i < tWidth; i++){
        T[i] = (int*)malloc(sizeof(int) * tHeight);
        if(T[i] == NULL){
            printf("Error:T-2\n");
        }
    }
    //相関関数
    R = (float**)malloc(sizeof(float*) * (iWidth-tWidth+1));
    if(R == NULL){
        printf("Error:R-1\n");
    }
    for(i = 0; i < (iWidth-tWidth+1); i++){
        R[i] = (float*)malloc(sizeof(float) * (iHeight-tHeight+1));
        if(R[i] == NULL){
            printf("Error:R-2\n");
        }
    }

    int M=tWidth;
    int N=tHeight;
    int K=iWidth;
    int L=iHeight;

    //データの２次元化
    //Input Data
    i = 0;
    for(h=0; h<iHeight; h++){
        for(w=0; w<iWidth; w++){
            W[w][h] = pGrayInputData[i];
            i++;
        }
    }
    printf("Wshape: %ld\n", sizeof W);
    //template data
    i=0;
    for(h=0; h<tHeight; h++){
        for(w=0; w<tWidth; w++){
            T[w][h] = pGrayTemplateData[i];
            i++;
        }
    }

    //テンプレートの輝度値算出
    float Ta=0.;
    float Tb=0.;

    for(h=0; h<tHeight; h++){
        for(w=0; w<tWidth; w++){
            Ta += T[w][h];
            Tb += T[w][h] * T[w][h];
        }
    }

    //相関を求める
    for(y=0; y<L-N+1; y++){
        for(x=0; x<K-M+1; x++){
            WT=0.;
            Wa=0.;
            Wb=0.;
  
            for(j=0; j<N; j++){
                for(i=0; i<M; i++){
                    WT += W[x+i][y+j] * T[i][j];
                    Wa += W[x+i][y+j];
                    Wb += W[x+i][y+j] * W[x+i][y+j];
                }
            }
            float A=(WT -Wa*Ta/(M*N)); 
            float B=(Wb-Wa*Wa/(M*N))*(Tb-Ta*Ta/(M*N)); 
            R[x][y] = (A)/(sqrt(B));

            if(Buff<R[x][y]){   //最良結果を保存
                X_best = x;
                Y_best = y;
                Buff = R[x][y];
            }
            printf("(x,y)=(%d, %d), R: %f\n", x,y,R[x][y]);
        }
    }

    printf("Best_XY: %d, %d\n", X_best, Y_best);
    printf("Max_R: %f\n", Buff);

    //出力データの１次元配列を作成
    i=0;
    for(h=0; h<tHeight; h++){
        for(w=0; w<tWidth; w++){
            pPredictData[i] = W[X_best+w][Y_best+h]; 
            i++;
        }
    }

        // X方向およびY方向の相関値の計算と保存
    float *correlationX = (float *)malloc((K-M+1) * sizeof(float));
    float *correlationY = (float *)malloc((L-N+1) * sizeof(float));

    for(x = 0; x < K-M+1; x++){
        correlationX[x] = R[x][Y_best];
    }
    for(y = 0; y < L-N+1; y++){
        correlationY[y] = R[X_best][y];
    }

    // ファイルに保存
    FILE *file;

    file = fopen("datX.dat", "w");
    if (file != NULL){
        for(int i = 0; i < K-M+1; i++){
            fprintf(file, "%d %f\n", i+1, correlationX[i]);
        }
        fclose(file);
    }
    else {
        printf("Failed to open file dayX");
    }
    free(correlationX);



    file = fopen("datY.dat", "w");
    if (file != NULL){
        for(int i = 0; i < L-N+1; i++){
            fprintf(file, "%d %f\n", i+1, correlationY[i]);
        }
        fclose(file);
    }
    else {
        printf("Failed to open file datY");
    }
    free(correlationY);


    WritePgm(pPredictData, tWidth, tHeight, tMaxvalue);

    free(pPredictData);
    free(pGrayInputData);
    free(pGrayTemplateData);
    free(W);
    free(T);
    free(R);
}