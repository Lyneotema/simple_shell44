#include "shell.h"

/**
 * strtow - Split a string into words using specified delimiters.
 * @str: Input string to split.
 * @delimiters: Delimiter string.
 *
 * Return: Array of strings on success, or NULL on failure.
 */
char **strtow(char *str, char *delimiters)
{
    int i, j, k, m, num_words = 0;
    char **words;

    if (str == NULL || str[0] == '\0')
        return (NULL);

    if (!delimiters)
        delimiters = " ";

    for (i = 0; str[i] != '\0'; i++)
       if (!is_delim(str[i], delimiters) && (is_delim(str[i + 1], delimiters) || str[i + 1] == '\0'));

    if (num_words == 0)
        return (NULL);

    words = malloc((num_words + 1) * sizeof(char *));
    if (!words)
        return (NULL);

    for (i = 0, j = 0; j < num_words; j++)
    {
        while (is_delimiter(str[i], delimiters))
            i++;

        k = 0;
        while (!is_delimiter(str[i + k], delimiters) && str[i + k])
            k++;

        words[j] = malloc((k + 1) * sizeof(char));
        if (!words[j])
        {
            for (k = 0; k < j; k++)
                free(words[k]);
            free(words);
            return (NULL);
        }

        for (m = 0; m < k; m++)
            words[j][m] = str[i++];
        words[j][m] = '\0';
    }

    words[j] = NULL;
    return (words);
}

