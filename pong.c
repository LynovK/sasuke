#include<stdio.h>


////////////////////////////////////////////////////////////////////////////////////
////                               ФУНКЦИИ                                    //////
////////////////////////////////////////////////////////////////////////////////////

void drawPole(int iLeft, int iRight, int iXBoll, int iYBoll, int iLPoint, int iRPoint); // прописовка
int leftM(int lRacket, char cKey); // функционал левой рокетки
int rightM(int rRacket, char cKey); // функционал правой рокетки
int moveBallX(int iBollX, int iDirectionX); // движение мяча по оси X
int moveBallY(int iBollY, int iDirectionY); //движение мяча по оси Y
int iBallRRej(int iBallXPosition, int iBallYPosition, int iRRocketPosition); // отталкивание от правой ракетки
int iBallLRej(int iBallXPosition, int BallYPosition, int ILRocketPosition); //отталкивание от левой рокетки






////////////////////////////////////////////////////////////////////////////////////
////                               ПЕРЕМЕННЫЕ                                  /////
////////////////////////////////////////////////////////////////////////////////////
char c = 0; // символ, введенный с клавиатуры
int iLeftRPosition = 13; // начальная координата левой рокетки
int iRightRPosition = 13; // начальная координата правой рокетки
int iBallPositionX = 13; // начальная коодрината мяча по оси X
int iBallPositionY = 60; // начальная координата мяча по оси Y
int iBollSwitchX = 1; // "вектор" направления по оси X
int iBollSwitchY = -1; //вектор направления по оси Y
int iLeftRPoint = 0; // очки левого игрока
int iRightRPoint= 0; // очки правого игрока
int iDirectionY = 0; // флаг направления




int main()
{
    while(c != 'q' && iRightRPoint <=21 && iLeftRPoint <= 21)
    {
        //printf("\033[0d\033[2j");
        c = getchar();
        if(c == 'a' || c == 'z' || c == 'k' || c == 'm' || c == ' ')
        {
            iLeftRPosition = leftM(iLeftRPosition, c);  // возвращает месторасположении левой рокетки
            iRightRPosition = rightM(iRightRPosition, c);// возвращает месторасположение правой рокетки

            iBallPositionX = moveBallX(iBallPositionX,iBollSwitchX); // возвращает координаты мяча по оси X
            iBallPositionY = moveBallY(iBallPositionY,iBollSwitchY ); // возвращает координаты мяча по оси Y
            if(iBallRRej(iBallPositionX, iBallPositionY, iRightRPosition) == 0) // отбивает правую сторону
            {
                iBollSwitchY = 0;
            }
            if(iBallLRej(iBallPositionX, iBallPositionY, iLeftRPosition) == -1)  // отбивает левую сторону
            {
                iBollSwitchY =  -1;
            }
            printf("%s%d%s%d\n", "XBall: ", iBallPositionX, " YBall: ", iBallPositionY);
            if(iBallPositionX == 25)
            {
                iBollSwitchX = 0;
            }
            else if(iBallPositionX == 1)
            {
                iBollSwitchX = 1;
            }
            if (iBallPositionY == 81)
            {

                iLeftRPoint++;
                iBallPositionY = 40;
                iBollSwitchY = 0;



            }
            if ( iBallPositionY == 0)
            {

                iRightRPoint++;
                iBallPositionY = 40;
                iBollSwitchY = -1;


            }
            drawPole(iLeftRPosition, iRightRPosition, iBallPositionX, iBallPositionY, iLeftRPoint, iRightRPoint);
        }
    }
    if (iLeftRPoint == 21) {
        printf("First player won");
        return 0;
    }
    if (iRightRPoint == 21) {
        printf("Second player won");
        return 0;
    }
}
int iBallLRej(int iBallXPosition, int iBallYPosition, int ILRocketPosition)//отталкивания от левой ракетки
{
    if((iBallXPosition == ILRocketPosition && iBallYPosition ==  11)||
        (iBallXPosition == ILRocketPosition && iBallYPosition ==  11)||
        (iBallXPosition == ILRocketPosition && iBallYPosition ==  11))
    {
        iDirectionY = -1;
    }
    else iDirectionY = 0;
    return iDirectionY; // возвращает флаг направления
}

int iBallRRej(int iBallXPosition, int iBallYPosition, int iRRocketPosition)//отталкивания от правой ракетки
{
    if((iBallXPosition == iRRocketPosition && iBallYPosition ==  69) ||
        ((iBallXPosition ==  (iRRocketPosition + 1)) && iBallYPosition == 69) ||
        ((iBallXPosition ==  (iRRocketPosition - 1)) && iBallYPosition == 69))
    {
        iDirectionY = 0;
    }
    else iDirectionY = -1;
    return iDirectionY; // возвращает флаг направления
}
void drawPole(int iLeft, int iRight, int iXBoll, int iYBoll, int iLPoint, int iRPoint)// пророисовка поля, мяча, рокеток
{
    for(int iX = 0; iX <= 26; iX++)
    {
        for(int iY = 0; iY <= 81; iY++)
        {
            if(iX != 0 && iX != 26 )
            {
                if(iY == 0 || iY == 81)
                {
                    printf("#");
                }
                else if((iX == iLeft || iX == iLeft - 1 || iX == iLeft + 1) && iY == 11)
                {
                    printf("|");
                }
                else if((iX == iRight || iX == iRight - 1 || iX == iRight + 1) && iY== 70)
                {
                    printf("|");
                }
                else if(iY == 40)
                {
                    printf("|");
                }
                else if(iX == 5 && iY == 20)
                {
                    printf("%d", iLPoint);
                }
                else if(iX == 5 && iY == 60)
                {
                    printf("%d", iRPoint);
                }
                else if (iX == iXBoll && iY == iYBoll)
                {
                    printf("o");
                }
                else
                    printf(" ");
            }
            else
                printf("#");
        }
        printf("\n");
    }
}

int leftM(int lRacket, char cKey)// движение левой рокетки
{
    if(cKey == 'a' && lRacket > 2)
    {
        --lRacket;
    }
    else if(cKey == 'z' && lRacket < 24)
    {
        ++lRacket;
    }
    return lRacket;
}
int rightM(int rRacket, char cKey) // движение правой рокетки
{
    if(cKey == 'k' && rRacket > 2)
    {
        --rRacket;
    }
    else if(cKey == 'm' && rRacket < 24)
    {
        ++rRacket;
    }
    return rRacket;
}
int moveBallX(int iBollX, int iDirectionX)// движение мяча по оси X
{
    if(iDirectionX == 1)
    {
        ++iBollX;
    }
    else
        --iBollX;
    return iBollX; // возвраащет координату по оси X
}
int moveBallY(int iBollY, int iDirectionY)// движение мяча по оси  Y
{
    if(iDirectionY == -1)
    {
        ++iBollY;
    }
    else
        --iBollY;
    return iBollY; // возвращает коодринату по оси Y
}
