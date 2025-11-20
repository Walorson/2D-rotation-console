#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define H 30
#define W 40

char canvas[H][W];
char newCanvas[H][W];
short center_x, center_y;

void fillCanvas(char c)
{
    for(char i = 0; i < H; i++)
    {
        for(char j = 0; j < W; j++)
        {
            canvas[i][j] = c;
            newCanvas[i][j] = c;
        }
    }
}

void updateCanvas()
{
    for(char y = 0; y < H; y++)
    {
        for(char x = 0; x < W; x++)
        {
            canvas[y][x] = newCanvas[y][x];
        }
    }
}

void renderCanvas()
{
    for(char y = 0; y < H; y++)
    {
        for(char x = 0; x < W; x++)
        {
            printf("%c ", canvas[y][x]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void drawFrame(char c, short x, short y, short width, short height)
{
    for(short i = y; i < y + height; i++)
    {
        for(short j = x; j < x + width; j++)
        {
            if(i == y || i == y + height - 1)
                canvas[i][j] = c;
            else if(j == x || j == x + width - 1)
                canvas[i][j] = c;
        }
    }

    center_x = round((2*x + width) / 2);
    center_y = round((2*y + height) / 2);
}

void drawSquare(char c, short x, short y, short width, short height)
{
    for(short i = y; i < y + height; i++)
    {
        for(short j = x; j < x + width; j++)
        {
            canvas[i][j] = c;
        }
    }

    center_x = round((2*x + width) / 2);
    center_y = round((2*y + height) / 2);
}

void rotate(float deg, char c)
{
    deg = (deg * M_PI) / 180; //degree to rad
    for(char y = 0; y < H; y++)
    {
        for(char x = 0; x < W; x++)
        {
            if(canvas[y][x] == c)
            {
                short cx = x - center_x; //move to center to rotate
                short cy = y - center_y;

                short new_x = round(cx * cos(deg) - cy * sin(deg)); //rotate
                short new_y = round(cx * sin(deg) + cy * cos(deg));

                new_x += center_x; //back to the starting position
                new_y += center_y;

                newCanvas[new_y][new_x] = c;
            }
        }
    }

    updateCanvas();
}

int main()
{
    const char FPS = 40;

    for(short i = 0; i <= 360; i += 5)
    {
        fillCanvas(' ');
        drawFrame('*', 5, 5, 20, 20);
        Sleep(1000 / FPS);

        system("cls");

        if(i > 0)
            rotate(i, '*');

        renderCanvas();

        if(i == 0)
        {
            printf("Wait a second...\n");
            Sleep(2000);
        }
    }

    return 0;
}
