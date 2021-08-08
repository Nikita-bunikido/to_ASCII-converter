#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char chars[] = " .:-=+^*#%%@";
int file = 0;
FILE *f;

main(int argc, char *argv[]){

    if (argc != 4 && argc != 5){
        printf("usage: toascii [file] [width] [heigth] [path to save]");
        return 1;
    }

    int gray, j, in, w, h, i = 0;
    char fin;
    w = atoi(argv[2]);
    h = atoi(argv[3]);

    if(argc == 5){
        file = !file;
        f = fopen(argv[4], "w");
    }

    WNDCLASSA wcl;
        memset(&wcl, 0, sizeof(WNDCLASSA));
        wcl.lpszClassName = "win";
        wcl.lpfnWndProc = DefWindowProcA;
    RegisterClassA(&wcl);

    HBITMAP img = (HBITMAP)LoadImage(NULL, argv[1], IMAGE_BITMAP, w,h, LR_LOADFROMFILE);
    HWND hwnd = CreateWindow("win", " ", WS_OVERLAPPEDWINDOW, 0, 0, w, h + 40, NULL, NULL, NULL, NULL);
    HWND hwndbackground = CreateWindow("static",NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, w, h, hwnd, NULL, NULL, NULL);
    SendMessage(hwndbackground, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img);
    
    ShowWindow(hwnd, SW_SHOWNORMAL);
    HDC dc = GetDC(hwnd);

    MSG msg;
    while(i++ < 8){
        if(GetMessage(&msg, NULL, 0, 0)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    system("color 0F");
    COLORREF color;
    double coeff = 255 / strlen(chars);
    for(i = 0; i < h; i++){
        for(j = 0; j < w; j++){
            color = GetPixel(dc, j, i);
            gray = GetRValue(color);
            putchar(fin = chars[(in = (int)(gray / coeff)) > strlen(chars) - 1 ? strlen(chars) - 1 : in]);
            if(file) fprintf(f, "%c", chars[strlen(chars) - in - 1]);
        }
        putchar('\n');
        if(file) fprintf(f, "\n");
    }
    if(file) fclose(f);
    return 0;
}