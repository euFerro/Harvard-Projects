#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    int increaseHash = 1;
    int decreaseSpace = 1;
    int counter;

    //prompt user to type the height
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //Creates Pyramid

    //EACH ROW
    for (int i = 0; i < height; i++)
    {
        counter = 0;
        //SPACES BEFORE EACH ROW
        for (int s = 0; s < height - decreaseSpace; s++)
        {
            printf(" ");
        }
        //EACH COLUMN
        for (int j = 0; j < 2; j++)
        {
            //EACH SIDE
            for (int b = 0; b < increaseHash; b++)
            {
                printf("#");
            }
            //ONE SPACE IN MIDDLE
            for (int q = 0; q <= counter; q++)
            {
                printf("  ");
            }
            counter--;
        }
        increaseHash++;
        decreaseSpace++;
        printf("\n");
    }
}