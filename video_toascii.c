#include <stdio.h>
#include <windows.h>

char chars[] = " .':,\"!/r(l1Z4H9W8$@";

main(){
    system("color 0F");
    COLORREF color;
    double coeff = 255 / strlen(chars);

    int in;

    POINT start;
    POINT end;

    while (!(0x8000 & GetKeyState(32))){
        GetCursorPos(&start);
    }
    printf("Passed start\n");
    Sleep(100);
    while (!(0x8000 & GetKeyState(32))){
        GetCursorPos(&end);
    }
    printf("Passed end\n\n");
    printf("start - [%d,%d]\nend - [%d,%d]\nPress [space] to continue.\n\n", start.x, start.y, end.x, end.y);

    const int w = end.x - start.x;
    const int h = end.y - start.y;

    printf("w - %d\nh - %d\n\n", w / 7, h / 6);
    Sleep(100);
    while (!(0x8000 & GetKeyState(32)))
        ;
    system("cls");

    RGBQUAD *pixels = calloc(w * h, sizeof(RGBQUAD));
    if (pixels == NULL)
        printf("memory no");

    HDC const hDc = GetDC(0);
    HDC const hDcmem = CreateCompatibleDC(0);
    HBITMAP const hBmp = CreateCompatibleBitmap(hDc, w, h);
    auto const oldBmp = SelectObject(hDcmem, hBmp);

    BITMAPINFO bmi;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biHeight = h;
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);

    char *screen = malloc(w * h * sizeof(char));
    int scr = 0;

    while(!(0x800 & GetKeyState('E'))){
        BitBlt(hDcmem, 0, 0, w, h, hDc, start.x, start.y, SRCCOPY);
        GetDIBits(hDcmem, hBmp, 0, h, &pixels[0], &bmi, DIB_RGB_COLORS);
        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                int pix_in = j + (h - i) * w;
                int grayscale = (pixels[pix_in].rgbRed * 0.299) + (pixels[pix_in].rgbGreen * 0.587) + (pixels[pix_in].rgbBlue * 0.114);
                if (!(j % 6) && !(i % 7))
                    screen[scr++] = (chars[(in = (int)(grayscale / coeff)) > strlen(chars) - 1 ? strlen(chars) - 1 : in]);
            }
            if (!(i % 7))
                screen[scr++] = '\n';
        }
        while (screen[scr] != '\n')
            scr--;
        screen[scr] = '\0';
        printf("%s", screen);
        scr = 0;
        Sleep(50);
    }
    
    SelectObject(hDcmem, oldBmp);
    DeleteObject(hBmp);
    DeleteDC(hDcmem);
    ReleaseDC(0, hDc);
    printf("Done!");
    free(pixels);
    free(screen);
    return 0;
}