#include "includes/cub3d.h"

void    get_map(t_cb *cb, char **argv)
{
    int i = 0;
    while (argv[1][i])
        printf("%c\n", argv[1][i++]);
    //go through string until . ,check if ends with cub,
    //check if file exists and opens with read rights, assign it to fd and 
    // read completely and check if only 0 and 1 digits while counting lines for alloc 2d array
    //parse each line to parser, count ints, alloc for int array and set them
    

}

void    cub3d(char **argv)
{
    t_cb cb;

	ft_bzero(&cb, sizeof(t_cb));
    get_map(&cb, argv);
}

int main(int argc, char **argv)
{
    if (argc == 2)
        cub3d(argv);
    return 0;
}