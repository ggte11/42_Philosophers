#include "philosophers.h"

int	parsing(int nb_params, char **params)
{
    int i;
    int j;

    j = 1;
    if (nb_params < 5 && nb_params > 6)
        return(write(2, "Incorrect number of arguments", 30));
    while (j < nb_params)
    {
        i = 0;
        while (params[j][i] != '\0')
        {
            if (!ft_isdigit(params[j][i]))
                return(write(2, "Invalid character", 18));
            i++;
        }
        j++;
    }
    return (0);
}