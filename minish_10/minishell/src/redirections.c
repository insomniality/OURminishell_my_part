#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	m_than(char *s, char *filnm, int i)
{
	// char a;
	// int fd;

	// if (s[i] == '>' && strlen(s) - 1 > i && s[i + 1] == '>')
	// 	fd = open(filnm, O_CREAT | O_RDWR);
	// else if (s[i] == '>' && strlen(s) - 1 > i && s[i + 1] != '>')
	// 	fd = open(filnm, O_CREAT | O_TRUNC | O_RDWR);
	// if (s[i] == '>' && strlen(s) - 1 > i && s[i + 1] == '>')
	// 	while (read(fd, &a, 1) != 0)
	// 		;
	// write(fd, c, strlen(c));
	// close(fd);
}

// int main() //int argc, char **argv, char **envp
// {
// 	char a;
// 	int fd;
// 	char c[] = "mmaakm";

// 	int i = 0;
// 	char s[] = ">>";

// 	if (s[i] == '>' && strlen(s) - 1 > i && s[i + 1] == '>')
// 		fd = open("qarerku.txt", O_CREAT | O_RDWR);
// 	else if (s[i] == '>' && strlen(s) - 1 > i && s[i + 1] != '>')
// 		fd = open("qarerku.txt", O_CREAT | O_TRUNC | O_RDWR);
// 	if (s[i] == '>' && strlen(s) - 1 > i && s[i + 1] == '>')
// 		while (read(fd, &a, 1) != 0)
// 			;
// 	write(fd, c, strlen(c));
// 	close(fd);
// }
