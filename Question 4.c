#include <stdio.h>
#include <string.h>

#define REC 39
#define RATE 8000.00

int main(void)
{
    FILE *fp;
    int room, nights, i, found, choice;
    int rn, rnights;
    char status, name[30], gname[30];
    float rate;
    char guests[10][21];
    int rooms[10];

    /* Task 1: create file with all rooms free */
    fp = fopen("hotel.txt", "wb");
    if (fp == NULL) { printf("Cannot create file\n"); return 1; }
    for (i = 101; i <= 110; i++)
        fprintf(fp, "%3d %c %-20s %2d %8.2f\n", i, 'F', "-", 0, RATE);
    fclose(fp);

    fp = fopen("hotel.txt", "rb+");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }

    do
    {
        printf("\n1. Check-in  2. Search guest  3. Check-out  0. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1)           
        {
            printf("Check-in room: ");
            scanf("%d", &room);
            printf("Name: ");
            scanf("%20s", name);
            printf("Nights: ");
            scanf("%d", &nights);

            fseek(fp, (long)(room - 101) * REC, SEEK_SET);
            fscanf(fp, "%d %c %s %d %f", &rn, &status, gname, &rnights, &rate);
            if (status == 'F')
            {
                fseek(fp, (long)(room - 101) * REC, SEEK_SET);
                fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'B', name, nights, RATE);
                fflush(fp);
                printf("Room %d booked\n", room);
            }
            else
                printf("Room already booked\n");
        }
        else if (choice == 2)       
        {
            rewind(fp);
            for (i = 0; i < 10; i++)
            {
                fscanf(fp, "%d %c %s %d %f", &rooms[i], &status, guests[i], &rnights, &rate);
            }
            printf("Search name: ");
            scanf("%20s", name);
            found = 0;
            for (i = 0; i < 10; i++)
            {
                if (strcmp(guests[i], name) == 0)
                {
                    printf("%s is in room %d\n", name, rooms[i]);
                    found = 1;
                    break;
                }
            }
            if (!found)
                printf("Guest not found\n");
        }
        else if (choice == 3)       
        {
            printf("Check-out room: ");
            scanf("%d", &room);
            fseek(fp, (long)(room - 101) * REC, SEEK_SET);
            fscanf(fp, "%d %c %s %d %f", &rn, &status, gname, &rnights, &rate);
            if (status == 'B')
            {
                printf("Bill: %d x %.2f = %.2f\n", rnights, rate, rnights * rate);
                fseek(fp, (long)(room - 101) * REC, SEEK_SET);
                fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'F', "-", 0, RATE);
                fflush(fp);
            }
            else
                printf("Room is already free\n");
        }
    } while (choice != 0);

    fclose(fp);
    return 0;
}
