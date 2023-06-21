#include <stdio.h>
#include <math.h>

//роздільна здатність
int half_lengthX = 40;
int half_lengthY = 12;
int lengthT = 40;
char mas[81][25];

const float PiDiv180 = 3.14 / 180.0;
const char Gradient[] = "&$Xx=+~-:..."; 
//-~+#@   .:-~+=xX$& "&$Xx=+~-:."
//const char Gradient[] = "abcdefghi1234567890";


// перемноження координати на коефіцієнт, для збереження пропорцій на різних екранах
// коефіціент для x
//coef - coefficient
int CoefX(float x)       
{
    extern int half_lengthX;

    x = round(x);
    if (x < 40) //позбавлення багу "кривої лінії" на осі абсцис
        x++; //по факту не потрібна штука (роздільна здатність парна - центру немає)
    x += half_lengthX;
    //printf("(%2.2f)", x); //for debug
    return x;
}

// коефіціент для y
int CoefY(float y)       
{   
    extern int half_lengthY;

    y = round(y);
    if (y < 12) //позбавлення багу "кривої лінії" на осі ординат
        y++;
    y = y * 0.5 + half_lengthY; //0.5 <-- 1/2 <~~ 8/15 співідношення сторін символа  
    //printf("(%2.2f)", y); //for debug 
    return y;
}

//передає правдивість вектора на певній координаті
int vector()         //(int length, int degrees)
{
    extern char mas[81][25];
    extern int half_lengthX;
    extern int half_lengthY;

    int graduseXY = 30;  
    int graduseYZ = 10;
    int length_vec = 30;  

    //трохи оптимізації, щоб не обчислювати одне і це ж 
        float ResCosXY = cos(graduseXY * PiDiv180);     //ResCos --> Result Cosinus
        float ResSinXY = sin(graduseXY * PiDiv180);
        float ResCosYT = cos(graduseYZ * PiDiv180);
    
    int half_Gradient = round(sizeof(Gradient) / 2);
    int ColorArea = round(lengthT / sizeof(Gradient));
    
    //printf("%d, %s \n", ColorArea, "color "); //тестова штука
    //int GGG = sizeof(Gradient);
    //printf("%d, sizeof \n", GGG);

    for (int a = 0; a < length_vec; a++){

        int x = CoefX(a * ResCosXY);
        int y = CoefY(a * ResSinXY);
        int z = a * ResCosYT + 2; //створюю глибину екрану || +1 --> посунув вектор в глибину на 1
        //видає колір пікселю із градієнту
        int Zcolor = trunc(z / ColorArea);

        if (Zcolor >= sizeof(Gradient) - 1)
            mas[x][y] = '!';
        else mas[x][y] = Gradient[Zcolor];
        if (Zcolor <= 0)
            mas[x][y] = '#';

        //mas[x][y] = '#';
        printf("(%d : %d) -> ", x, y);
        printf("%d t| %d GradArea\n ", z, Zcolor);
    }
    printf("\n");
}

// виводить масив символів на екран
// int print_massive()
int get_screen()
{
    extern int half_lengthX;
    extern int half_lengthY;
    extern char mas[81][25];
    for (int y = half_lengthY * 2; y >= 1; y--){
        printf("|");
        for (int x = 1; x <= half_lengthX * 2; x++){
            printf("%c", mas[x][y]);
            //тест дії перетворення координат
            //printf("(%d:%d)" , x, y);
        }
        printf("|\n");
    }
    return 0;
}
// очищує масив символів для виведення масиву на екран
// int update_massive()
int clear_screen()
{   
    extern int half_lengthX;
    extern int half_lengthY;
    extern char mas[81][25];
    
    for (int y = half_lengthY * 2; y >= 1; y--){
        for (int x = 1; x <= half_lengthX * 2; x++){
            mas[x][y] = ' ';

            //тест дії перетворення координат
            //printf("(%d:%d)" , x, y);
            // printf("%d ", mas[x - half_lengthX][y - half_lengthY]);
            //printf("%d ", y);
        }
        //printf("|\n");
    }
    return 0;
}

//малює точку
int print_point(int x, int y, char ch)
{
    extern char mas[81][25];
    extern int half_lengthX;
    extern int half_lengthY;
    //тест: виводить координати точки (перевірка на "забруднення")
    printf("%d %d : %c\n", x,y, mas[x][y]);

    x = CoefX(x);
    y = CoefY(y);
    //x = x + 5;
    //y = y + 5;
    
    mas[x][y] = ch;
    //printf("%d %d | %c\n", x,y, mas[x][y]);
    return 0;
}

int print_circle(int radius)
{
    extern char mas[81][25];
    extern int half_lengthX;
    extern int half_lengthY;

    for (int y = 0; y < half_lengthY * 2; y++){
        for (int x = 0; x <= half_lengthX * 2; x++){

            int XX = CoefX(x);
            int YY = CoefY(y);
            if ((XX * XX) + (YY * YY) <= radius * radius)
                mas[CoefX(x)][CoefY(y)] = '@';
        }
    }

}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int main(int argc, char **argv)
{
    const int ObjectX = 0;
    const int ObjectY = 0;

    //extern const int lengthX;
    //extern const int lengthY;
    //extern char mas[][];

    clear_screen();

    vector();
    
    //print_point(0,0,'@');
    //print_circle(8);

    get_screen();
                // int T = vector(x,y);
                //     if (T = 1)
                //         printf("%d ", 1);
                //         else printf("%d ", 0);

                // if (vector(x,y, rep) != 0){
                //     mas[x][y] = '@';
                // }
                // else mas[x][y] = ' ';


            //малювання кругу в центрі екрану
                // if (x * x + y * y < 40){
                //     //printf("%d:%d|", x, y);
                //     mas[x][y] = '@';
                // }
                 //else mas[x][y] = ' ';

    return 0;
}