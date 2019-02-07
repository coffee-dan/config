#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *document;

// Link to getline explanation and code referrenced for line reading 
// pubs.opengroup.org/onlinepubs/9699919799/functions/getline.html

// The "restrict" keyword is used in pointer declarations as a type qualifier. It
//  informs the compier that the given pointer is the only way to access the object
//  being pointed to by it and doesn't need to add any additional checks.
// \TODO Find out how ++ effects a char* variable
// Link to remove_spaces source, from comment by Lundin
// https://stackoverflow.com/questions/1726302/removing-spaces-from-a-string-in-c#
void remove_spaces (char* str_trimmed, const char* str_untrimmed);
void last_n_characters (char* n_characters, const char* source, int n);

int main()
{
  // Open the file in read only mode
  document = fopen("homepage.html", "r");
  char* line = NULL;
  size_t len = 0;
  // \TODO Find out what ssize_t is
  ssize_t read;
  
  char* comment_identifier = (char*)malloc(4+1);
  int comment_flag = 0;
  int comment_start = 0;
  int comment_end = 0;
  
  // Make sure file is not empty
  if (document == NULL)
	exit(1);
  // \TODO Find out what %zu means
  while ((read = getline(&line, &len, document)) != -1)
  {
    //printf("Retrieved line of length %zu :\n", read);
    char* modified_line = (char*)malloc(strlen(line+1));
    remove_spaces(modified_line, line);

    if (comment_flag == 0)
    {
      memcpy(modified_line, comment_identifier, 4);
      comment_identifier[5] = '\0';
      if (strcmp(comment_identifier, "<!--") == 0)
      {
        comment_flag = 1;
	  }
	}
	if (comment_flag == 0) printf("%s\n", modified_line);
	if (comment_flag == 1)
	{
	  last_n_characters(comment_identifier, modified_line, 3);
	  
      if (strcmp(comment_identifier, "-->") == 0)
      {
        comment_flag = 0;
	  }
	}
	
	
	free (modified_line);
  }
  if (ferror(document))
  {
	perror("Error in document: ");
  }
  free(line);
  fclose(document);
  return 0;
}

// Segmentation fault - the program tries to access an invalid memory address
void remove_spaces (char* str_trimmed, const char* str_untrimmed)
{
  while (*str_untrimmed != '\0')
  {
    if (!isspace(*str_untrimmed))
    {
      *str_trimmed = *str_untrimmed;
      str_trimmed++;
    }
    str_untrimmed++;
  }
  *str_trimmed = '\0';
}

int last_n_characters (char* n_characters, const char* source, int n)
{
  int length = strlen(source);
  if (length < n + 1) return -1;
  int i = length - n - 1;
  int j = 0;
  while (i < length)
  {
    n_characters[j] = source[i];
	j++;
  }
  n_characters[n+1] = '\0';
  return 0;
}
