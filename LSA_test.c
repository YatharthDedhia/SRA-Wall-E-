#include<stdio.h>
#include<string.h>
int main()
{
    FILE *finp = fopen("testingTXT.txt","r");
    FILE *fchout = fopen("Characters.txt","w");
    FILE *fintout = fopen("Integers.txt","w");
    char ch;
    if(finp==NULL)
    {
        printf("file not opened");
    }
    else
    {
        while((ch = fgetc(finp))!=EOF)
        {
            if(sizeof(ch == 1))
            {
                putw(ch,fchout);
            }

            else if(sizeof(ch==4))
            {
                putw(ch,fintout);
            }
        }
    }
    fclose(finp);
    fclose(fchout);
    fclose(fintout);
}
