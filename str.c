#include "shell.h"

char *_strcat(char *first, char *second)
{
  int len1, len2, i = 0, j = 0;
  char *result;

  len1 = _strlen(first);
  len2 = _strlen(second);
  result = malloc((len1 + len2 + 2) * sizeof(char));
  if (!result)
    return (NULL);
  *result = '\0';
  while (first[j])
    result[i++] = first[j++];
  result[i++] = '/';
  j = 0;
  while (second[j])
    result[i++] = second[j++];
  result[i] = '\0';
  return (result);
}

int _strlen(char *str)
{
  int len;

  for (len = 0; str[len]; len++)
    ;
  return (len);
}

int _strcmp(char *s1, char *s2)
{
  int cmp = 0, i;

  if (s1 == NULL || s2 == NULL)
    return (1);
  for (i = 0; s1[i]; i++)
  {
    if (s1[i] != s2[i])
    {
      cmp = s1[i] - s2[i];
      break;
    }
    else
      continue;
  }
  return (cmp);
}

char *_strchr(char *str, char c)
{
  char *ptr;

  if (str == NULL)
    return (NULL);
  for (ptr = str; *ptr; ptr++)
    if (*ptr == c)
      return (ptr);
  return (NULL);
}

char *_strdup(char *str)
{
  char *dupl;

  if (str == NULL)
    return (NULL);
  dupl = malloc(_strlen(str) + 1);
  if (dupl == NULL)
    return (NULL);
  _strcpy(dupl, str);
  return (dupl);
}
