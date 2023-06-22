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

//Matrixs
float global_matrix[4][4] = {{1,0,0,0},
                             {0,1,0,0},
                             {0,0,1,0},
                             {0,0,0,1}};
float end_matrix[4] = {0, 0, 0, 0};

//множенн матриць
int Matrixs(int X, int Y, int Z)
{
    int basic_matrix[4] = {X, Y, Z, 0};
    //int basic_matrix[4] = {put_matrix[0],put_matrix[1],put_matrix[2],put_matrix[3]};
    //матриці та їх множення

    for(int a = 0; a < 4; a++){
            end_matrix[a] = round(basic_matrix[0] * global_matrix[a][0] +
                                  basic_matrix[1] * global_matrix[a][1] +
                                  basic_matrix[2] * global_matrix[a][2] +
                                  basic_matrix[3] * global_matrix[a][3]);
    }

    return 0;
}

// перемноження координати на коефіцієнт, для збереження пропорцій на різних екранах
// коефіціент для x
//coef - coefficient
int CoefX(float x)       
{
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
        //тест градієнту
        printf("(%d : %d)\n", x, y);
        //printf("%d t| %d GradArea\n ", z, Zcolor);
    }
    printf("\n");
}

// виводить масив символів на екран
// int print_massive()
int get_screen()
{

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

    //тест: виводить координати точки (перевірка на "забруднення")
    printf("%d %d : %c\n", x,y, mas[x][y]);

    x = CoefX(x);
    y = CoefY(y);
    
    mas[x][y] = ch;
    //printf("%d %d | %c\n", x,y, mas[x][y]);
    return 0;
}

int print_circle(int radius)
{
    for (int y = 0; y < half_lengthY * 2; y++){
        for (int x = 0; x <= half_lengthX * 2; x++){

            int XX = CoefX(x);
            int YY = CoefY(y);
            if ((XX * XX) + (YY * YY) <= radius * radius)
                mas[CoefX(x)][CoefY(y)] = '@';
        }
    }

}
//<<<<<<><><><><><><><><><><><.mdnbfjsdnkjfshjdbfhsbdhfbsdhjbfhjs
//dbfhjdsbfnsbhdfbhsdbf

//тестові дві точки
int OnePoint[4] = {0, 0, 0, 0};
int TwoPoint[4] = {10, 20, 0, 0};

int print_line()
{
    //distance
    int x_dis = TwoPoint[0] - OnePoint[0];
    int y_dis = TwoPoint[1] - OnePoint[1];
    printf("x_dis: %d y_dis: %d\n", x_dis, y_dis);

    Matrixs(x_dis, y_dis, 0);

    //int lenght_line = round(sqrt((x_dis * x_dis) + (y_dis * y_dis)));
    int lenght_line = round(sqrt((end_matrix[0] * end_matrix[0]) + (end_matrix[1] * end_matrix[1])));
    //<><><>
    //printf("{%3.2f x : %3.2f y : %d lenght}\n",end_matrix[0], end_matrix[1], lenght_line);

    printf("mx - %3.2f \n",end_matrix[0]);
    printf("my - %3.2f \n",end_matrix[1]);
    printf("mz - %3.2f \n",end_matrix[2]);
    printf("m0 - %3.2f \n",end_matrix[3]);

    int MatX = end_matrix[0];
    int MatY = end_matrix[1];

    //float angle = MatX / lenght_line;

    for (int l = 0; l < lenght_line; l++){
        // int x = CoefX((l + OnePoint[0]) * x_dis / lenght_line);
        // int y = CoefY((l + OnePoint[1]) * y_dis / lenght_line);
        int x = CoefX(l * MatX / lenght_line);
        int y = CoefY(l * end_matrix[1]);
        //printf("((%d : %d))\n", x, y);
        Matrixs(x,y,0);
        x = roundf(end_matrix[0]);
        y = roundf(end_matrix[1]);
        mas[x][y] = '@';
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int main(int argc, char **argv)
{
    const int ObjectX = 0;
    const int ObjectY = 0;

    clear_screen();
    //vector();
    print_line();
    print_point(0,0,'%');
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

    return 0;
}