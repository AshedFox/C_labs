#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
	char line[80];
	int width;
	char buf;
	printf("TASK 3\nEnter line: ");
	
	gets(line);

	printf("Line length: %d\n", strlen(line));

	width = strlen(line);

	if ((width) % 4 == 0) {
		for (int i = 0; i < width / 2; i++) {
			buf = line[i];
			line[i] = line[width / 2 + i];
			line[width / 2 + i] = buf;
		}
	}
	printf("End line: %s\n", line);

	printf("TASK 2\nEnter word: ");
	gets(line);

	width = strlen(line);

	int IsPolyndrom = 1;

	for (int i = 0; i < width/2; i++) {
		if (line[i] != line[width - i - 1]) {
			IsPolyndrom = 0;
			break;
		}
	}
	if (IsPolyndrom == 1) {
		printf("Word %s is polyndrom.\n", line);
	}
	else {
		char NewLine[80];
		int NewWidth=0;
		for (int i = 0; i < width; i++) {
			if (line[i] >= 'A' && line[i]<='Z') {			
				NewLine[NewWidth] = line[i];
				NewWidth++;
			}
			NewLine[NewWidth] = '\0';
		}
		if (NewWidth != 0)
			printf("Line without low: %s\n", NewLine);
		else
			printf("Line without low is empty.\n");
	}

	char text[200]={ "woolves showed sharp steel" };
	//gets(text);

	printf("TASK 1\n");
	int i = strlen(text) - 1, j, e = strlen(text);
	while (i >= 0) {
		while (text[i] != ' ') {
			if (i == -1)
				break;
			i--;
		}

		j = i;
		for (int g = i + 1; g < e; g++) {
			printf("%c", text[g]);
		}
		printf(" ");
		e = j;
		i--;
	}
	printf("\n");
	return 0;
}
