#include "parser.h"

char   *ft_straj(char *str, char c)
{
  char  *res;
  int   i;

  i = 0;
  if (!(res = (char *)malloc(sizeof(char) * ft_strlen(str) + 2)))
    return (NULL);
  if (str)
    while(str[i]){
      res[i] = str[i];
      i++;
    }
  res[i] = c;
  res[i + 1] = '\0';
  return res;
}

int   get_next_word(char **str, char **res)
{
  if (!*str)
    return (0);
  while(ft_isspace(**str))
    (*str)++;
  if (**str == '\0')
    return (0);
  while(!ft_isspace(**str) && **str != '\0'){
    *res = ft_straj(*res, **str);
    (*str)++;
  }
  return (1);
}
