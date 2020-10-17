#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



int main()
{
	srand(time(NULL));
	
	char text[5000];
	printf("Enter line: ");
	gets(text);
	printf("\n");
	text[strlen(text)] = '\0';

	char words[50][100] = { "" };
	char base[100][100] = { "MY_","BEAUTIFUL_","MADNESS_","AND_","MY_","LOVELY_","VOID_","IS_","UNLIMITED_","AND_","PERFECT_", "MIX_", "FLOWERS_", "LIKE_"};
	char resultText[5000] = { "" };

	int i = 0, j = 0, k;
	while (text[j-1] != '\0') {
		k = 0;
		char buffer[100] = "";
		while (text[j] != '_' && text[j] != '\0') {
			buffer[k] += text[j];
			j++;
			k++;
		}
		buffer[k] = '\0';
		j++;
		for (int p = 0; p <= k; p++) {
			words[i][p] = buffer[p];
		}
		words[i][strlen(words[i])] = '_';
		i++;
	}

	int AmountOfWords = i, AmountOfBaseWords=0;
	j = 0;
	printf("Base: ");
	while (strlen(base[j]) != '\0') {
		AmountOfBaseWords++;
		printf(base[j]);
		j++;
	}
	printf("\n\n");
	int l = 0;
	for (i = 0; i < AmountOfWords; i++) {
		k = rand() % AmountOfBaseWords;
		for (int p = 0; base[k][p-1]!='_'; p++) {
			resultText[l] = base[k][p];
			l++;
		}
		k = rand() % AmountOfBaseWords;
		for (int p = 0; base[k][p - 1] != '_'; p++) {
			resultText[l] = base[k][p];
			l++;
		}
		for (int p = 0; p < strlen(words[i]); p++) {
			resultText[l] = words[i][p];
			l++;
		}

	}
	resultText[l-1] = '\0';
	printf("Result text: %s\n\n", resultText);
	//HELLO_WORLD_OK_NO_HMMMMM_MR_JHON_TRY_TO_FINISH_WORK_SOON
	return 0;
}
