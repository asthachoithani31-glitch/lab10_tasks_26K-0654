#include <stdio.h>
#include <string.h>

int countRepeat(char s[], int i)
{
    if (s[i + 1] == s[i])
        return 1 + countRepeat(s, i + 1);
    return 1;
}

void compress(char s[], int i, char out[], int j)
{
    if (s[i] == '\0')
    {
        out[j] = '\0';
        return;
    }
    int c = countRepeat(s, i);
    out[j] = s[i];
    out[j + 1] = '0' + c;
    compress(s, i + c, out, j + 2);
}

void expand(char in[], int i, char out[], int j)
{
    if (in[i] == '\0')
    {
        out[j] = '\0';
        return;
    }
    int c = in[i + 1] - '0';
    int k;
    for (k = 0; k < c; k++)
        out[j + k] = in[i];
    expand(in, i + 2, out, j + c);
}

int main(void)
{
    char original[100] = "AAAAAABBBCCCCD";
    char compressed[200], expanded[100];

    compress(original, 0, compressed, 0);
    expand(compressed, 0, expanded, 0);

    printf("Original: %s\n", original);
    printf("Compressed: %s\n", compressed);
    printf("Expanded: %s\n", expanded);
    printf("Match: %s\n", strcmp(original, expanded) == 0 ? "Yes" : "No");
    return 0;
}
