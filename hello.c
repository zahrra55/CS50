#include<stdio.h>
#include<cs50.h>
int main(void)
{
    string name = get_string("What's your name? ");
    //printf("Hello, %s\n", name);
    string age = get_string("How old are you? ");
    long int phone = get_string("What's your phone number? ");
    printf("Hello,%s\nYou are %s years old\nYour phone number is: %s \n ",name,age,phone);
}
