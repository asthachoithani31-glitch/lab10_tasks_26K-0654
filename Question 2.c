#include <stdio.h>

#define REC 24

int main(void)
{
    FILE *fp;
    int roll, no, att, leave;
    char name[20];

    fp = fopen("attendance.txt", "wb");
    if (fp == NULL) { printf("Cannot create file\n"); return 1; }
    fprintf(fp, "%-3d %-15s %3d\n", 1, "Ayesha", 18);
    fprintf(fp, "%-3d %-15s %3d\n", 2, "Bilal",  14);
    fprintf(fp, "%-3d %-15s %3d\n", 3, "Hamza",  20);
    fprintf(fp, "%-3d %-15s %3d\n", 4, "Sana",   12);
    fprintf(fp, "%-3d %-15s %3d\n", 5, "Zainab", 16);
    fclose(fp);

    fp = fopen("attendance.txt", "rb+");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }

    printf("Roll number: ");
    scanf("%d", &roll);
    fseek(fp, (long)(roll - 1) * REC, SEEK_SET);
    fscanf(fp, "%d %s %d", &no, name, &att);
    printf("%s: %d / 20 (%.1f%%)", name, att, att * 100.0 / 20);
    if (att * 100.0 / 20 < 75)
        printf(" Short attendance");
    printf("\n");
    printf("Roll number for leave: ");
    scanf("%d", &roll);
    printf("Lectures: ");
    scanf("%d", &leave);
    fseek(fp, (long)(roll - 1) * REC, SEEK_SET);
    fscanf(fp, "%d %s %d", &no, name, &att);
    att += leave;
    if (att > 20)
        att = 20;
    fseek(fp, (long)(roll - 1) * REC, SEEK_SET);
    fprintf(fp, "%-3d %-15s %3d\n", no, name, att);
    printf("%s: now %d / 20 (%.1f%%)\n", name, att, att * 100.0 / 20);
    fseek(fp, -REC, SEEK_END);
    fscanf(fp, "%d %s %d", &no, name, &att);
    printf("Last record: %d %s %d\n", no, name, att);

    fclose(fp);
    return 0;
}
