#include <stdio.h>

int finalBalance(int trans[], int n, int balance)
{
    if (n == 0)
        return balance;
    return finalBalance(trans + 1, n - 1, balance + trans[0]);
}

int totalDeposits(int trans[], int n)
{
    if (n == 0)
        return 0;
    int first = (trans[0] > 0) ? trans[0] : 0;
    return first + totalDeposits(trans + 1, n - 1);
}

int copyLarge(int trans[], int i, int n, int large[], int k)
{
    if (i == n)
        return k;
    if (trans[i] <= -10000)
    {
        large[k] = trans[i];
        k++;
    }
    return copyLarge(trans, i + 1, n, large, k);
}

int main(void)
{
    int start = 20000;
    int trans[7] = {20000, -5000, -12000, 8000, -25000, -2500, 15000};
    int large[7];
    int count, i;

    printf("Final balance: %d\n", finalBalance(trans, 7, start));
    printf("Total deposits: %d\n", totalDeposits(trans, 7));

    count = copyLarge(trans, 0, 7, large, 0);
    printf("Large withdrawals (%d): ", count);
    for (i = 0; i < count; i++)
        printf("%d ", large[i]);
    printf("\n");

    return 0;
}
