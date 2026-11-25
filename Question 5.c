#include <stdio.h>

#define REC 23

int main(void)
{
    FILE *fp;
    char cat[50];
    float amt, total = 0;
    int n;

    fp = fopen("expenses.txt", "rb");
    if (fp == NULL)
    {
        fp = fopen("expenses.txt", "wb");
        fprintf(fp, "%-12s %9.2f\n", "Food", 1200.00);
        fprintf(fp, "%-12s %9.2f\n", "Transport", 500.00);
        fprintf(fp, "%-12s %9.2f\n", "Books", 850.00);
        fprintf(fp, "%-12s %9.2f\n", "Mobile", 300.00);
    }
    fclose(fp);

    printf("Category: ");
    scanf("%11s", cat);
    printf("Amount: ");
    scanf("%f", &amt);

    fp = fopen("expenses.txt", "ab");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }
    fprintf(fp, "%-12s %9.2f\n", cat, amt);
    fclose(fp);

    fp = fopen("expenses.txt", "rb+");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }

    fseek(fp, -2 * REC, SEEK_END);
    printf("Latest two: ");
    fscanf(fp, "%s %f", cat, &amt);
    printf("%s %.2f, ", cat, amt);
    fscanf(fp, "%s %f", cat, &amt);
    printf("%s %.2f\n", cat, amt);

    printf("Entry to fix: ");
    scanf("%d", &n);
    printf("Correct amount: ");
    scanf("%f", &amt);

    fseek(fp, (long)(n - 1) * REC, SEEK_SET);  
    fscanf(fp, "%s", cat);
    fseek(fp, (long)(n - 1) * REC, SEEK_SET);  
    fprintf(fp, "%-12s %9.2f\n", cat, amt);
    fflush(fp);

    rewind(fp);
    while (fscanf(fp, "%s %f", cat, &amt) == 2)
    {
        printf("%-12s %9.2f\n", cat, amt);
        total += amt;
    }
    printf("Total: %.2f\n", total);

    fclose(fp);
    return 0;
}
