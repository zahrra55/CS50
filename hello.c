#include<stdio.h>
#include<cs50.h>
int main(void)
{
    string name = get_string("What's your name? ");
    //printf("Hello, %s\n", name);
    int age = get_int("How old are you? ");
    string phone = get_string("What's your phone number? ");
    printf("Hello,%s\nYou are %i years old\nYour phone number is: %s \n ",name,age,phone);
}
