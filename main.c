#include <fcntl.h>
#include <stdio.h>

int get_next_line(int fd, char **line);

int main()
{
    int fd;
    char *a[5000];
    int i;
    int lin;
    int res;

    i = 0;
    fd = open("1.txt", O_RDONLY);
    while (i < 4)
    {
        res = get_next_line(fd, &a[i++]) > 0;
        printf("%i\n", res);
        lin++;
        i++;
    }
    printf("%i\n", lin);
}