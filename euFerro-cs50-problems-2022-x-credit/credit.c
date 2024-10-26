#include <cs50.h>
#include <stdio.h>

long int cardNumber;
bool check(long int num);
int passNumber;
int sumDigits = 0;
int sumLeftNums = 0;

int main(void)
{
//GET USER INPUT
    do
    {
        cardNumber = get_long("Number: ");
    }
    while (cardNumber < 0);

//CHECK WITCH CARD FLAG THE NUMBER IS FROM
    if (check(cardNumber))
    {
        if (cardNumber >= 340000000000000 && cardNumber < 350000000000000)
        {
            printf("AMEX\n");
        }
        else if (cardNumber >= 370000000000000 && cardNumber < 380000000000000)
        {
            printf("AMEX\n");
        }
        else if (cardNumber >= 4000000000000 && cardNumber < 5000000000000)
        {
            printf("VISA\n");
        }
        else if (cardNumber >= 4000000000000000 && cardNumber < 5000000000000000)
        {
            printf("VISA\n");
        }
        else if (cardNumber >= 5100000000000000 && cardNumber < 5600000000000000)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

//CHECK IF NUMBER IS VALID
bool check(long int num)
{
    //FIRST PART (SUM MULTIPLIED BY 2)
    long int result;
    long int divider;

    //16 DIGIT DIVIDER
    if (cardNumber >= 1000000000000000 && cardNumber < 10000000000000000)
    {
        divider = 1000000000000000;
    }
    //15 DIGIT DIVIDER
    else if (cardNumber >= 100000000000000 && cardNumber < 1000000000000000)
    {
        divider = 10000000000000;
    }
    //13 DIGIT DIVIDER
    else if (cardNumber >= 1000000000000 && cardNumber < 10000000000000)
    {
        divider = 100000000000;
    }

    //GET 8 NUMS
    for (int i = 0; i < 8; i++)
    {
        //CHECK 16 DIGIT NUMBERS
        if (cardNumber > 999999999999999 && cardNumber < 10000000000000000)
        {
            if (divider == 1000000000000000)
            {
                result = (num / divider) * 2;
            }
            else
            {
                result = (((num / divider) - (10 * (num / (divider * 10)))) * 2);
            }
            if (result > 9)
            {
                int byTen = result / 10;
                sumDigits += (byTen + (result - (10 * byTen)));
            }
            else
            {
                sumDigits += result;
            }
            //CONTROLING THE DIVIDER TO GET THE NUMBERS
            if (divider > 10)
            {
                divider = divider / 100;
            }
        }
    }

    //GET 7 NUMS
    for (int i = 0; i < 7; i++)
    {
        //CHECK 15 DIGIT NUMBERS
        if (cardNumber >= 100000000000000 && cardNumber < 1000000000000000)
        {
            result = (((num / divider) - (10 * (num / (divider * 10)))) * 2);

            if (result > 9)
            {
                int byTen = result / 10;
                sumDigits += (byTen + (result - (10 * byTen)));
            }
            else
            {
                sumDigits += result;
            }
            //CONTROLING THE DIVIDER TO GET THE NUMBERS
            if (divider > 10)
            {
                divider = divider / 100;
            }
        }
    }

    //GET 6 NUMS
    for (int i = 0; i < 6; i++)
    {
        //CHECK 13 DIGIT NUMBERS
        if (cardNumber >= 1000000000000 && cardNumber < 10000000000000)
        {
            result = (((num / divider) - (10 * (num / (divider * 10)))) * 2);
            sumDigits += result;

            //CONTROLING THE DIVIDER TO GET THE NUMBERS
            if (divider > 10)
            {
                divider = divider / 100;
            }
        }
    }

    //GET NUMS NOT MULTIPLIED
    int result2;
    long int divider2;

    //16 DIGIT DIVIDER2
    if (cardNumber >= 1000000000000000 && cardNumber < 10000000000000000)
    {
        divider2 = 100000000000000;
    }
    //15 DIGIT DIVIDER2
    else if (cardNumber >= 100000000000000 && cardNumber < 1000000000000000)
    {
        divider2 = 100000000000000;
    }
    //13 DIGIT DIVIDER2
    else if (cardNumber >= 1000000000000 && cardNumber < 1000000000000000)
    {
        divider2 = 1000000000000;
    }

    for (int i = 0; i < 8; i++)
    {
        //16 DIGIT SUM OF LEFT NUMS
        if (cardNumber > 999999999999999 && cardNumber < 10000000000000000)
        {
            result2 = (num / divider2 - (10 * (num / (divider2 * 10))));
            sumLeftNums += result2;

            //CHECK THE DIVIDER TO GET THE LAST NUMBER (notMULTby2)
            if (divider2 > 1)
            {
                divider2 = divider2 / 100;
            }
        }
    }

    for (int i = 0; i < 8; i++)
    {
        //15 DIGIT SUM OF LEFT NUMS
        if (cardNumber > 99999999999999 && cardNumber < 1000000000000000)
        {
            if (divider == 100000000000000)
            {
                result2 = result2 / divider2;
            }
            else
            {
                result2 = ((num / divider2) - (10 * (num / (divider2 * 10))));
                sumLeftNums += result2;
            }

            //CHECK THE DIVIDER TO GET THE LAST NUMBER (notMULTby2)
            if (divider2 > 1)
            {
                divider2 = divider2 / 100;
            }
        }
    }

    for (int i = 0; i < 7; i++)
    {
        //13 DIGIT SUM OF LEFT NUMS
        if (cardNumber >= 1000000000000 && cardNumber < 10000000000000)
        {
            if (divider2 == 1000000000000)
            {
                result2 = num / divider2;
            }
            else
            {
                result2 = ((num / divider2) - (10 * (num / (divider2 * 10))));
            }
            sumLeftNums += result2;

            //CHECK THE DIVIDER TO GET THE LAST NUMBER (notMULTby2)
            if (divider2 > 1)
            {
                divider2 = divider2 / 100;
            }
        }
    }

    //SUMMING BOTH AND CHECKING THE RESULT
    passNumber = sumDigits + sumLeftNums;
    if (passNumber % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}






