#include <stdio.h>

#define REC 17

int main(void)
{
    FILE *fp;
    char city[20], hottest[20];
    float temp, max;
    int n, i;

    fp = fopen("temperature.txt", "wb");
    if (fp == NULL) { printf("Cannot create file\n"); return 1; }
    for (i = 1; i <= 5; i++)
    {
        printf("City %d name: ", i);
        scanf("%9s", city);
        printf("City %d temperature: ", i);
        scanf("%f", &temp);
        fprintf(fp, "%-10s %5.1f\n", city, temp);
    }
    fclose(fp);

    fp = fopen("temperature.txt", "rb+");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }

    /* Task 2: read one city */
    printf("City number: ");
    scanf("%d", &n);
    fseek(fp, (long)(n - 1) * REC, SEEK_SET);
    fscanf(fp, "%s %f", city, &temp);
    printf("%s %.1f\n", city, temp);

    /* Task 3: correct a temperature */
    printf("City number to correct: ");
    scanf("%d", &n);
    printf("New temperature: ");
    scanf("%f", &temp);
    fseek(fp, (long)(n - 1) * REC, SEEK_SET);
    fscanf(fp, "%s", city);                   
    fseek(fp, (long)(n - 1) * REC, SEEK_SET);  
    fprintf(fp, "%-10s %5.1f\n", city, temp);
    printf("%s updated to %.1f\n", city, temp);
    fflush(fp);

    rewind(fp);
    fscanf(fp, "%s %f", hottest, &max);
    while (fscanf(fp, "%s %f", city, &temp) == 2)
    {
        if (temp > max)
        {
            max = temp;
            for (i = 0; city[i] != '\0'; i++)
                hottest[i] = city[i];
            hottest[i] = '\0';
        }
    }
    printf("Hottest city: %s (%.1f)\n", hottest, max);

    fclose(fp);
    return 0;
}
