#include <stdio.h>
#include <cs50.h>

//main method
int main(void)
{
    //gets user name
    string name = get_string("What's your name?: ");

    //print in the terminal the aswer
    printf("hello, %s\n", name);
}