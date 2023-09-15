#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "voucher.h"

char* dejCode(char* prefix)
{
	char* code = calloc(11, sizeof(char));
	char* charset = "abcdefghijklmnopqrstuvwxyz";
	int len = strlen(prefix);
	for (int i = 0; i < len; i++)
	{
		code[i] = prefix[i];
	}
	code[len] = '-';
	code[len + 1] = charset[rand() % 26];
	code[len + 2] = charset[rand() % 26];
	code[len + 3] = charset[rand() % 26];

	code[len + 4] = '-';
	code[len + 5] = charset[rand() % 26];
	code[len + 6] = charset[rand() % 26];
	code[len + 7] = charset[rand() % 26];

	code[len + 8] = '\0';

	return code;
}

void ulozVoucher(tVoucher v)
{
	char prefix[3] = { v.code[0], v.code[1], '\0'};
	char pripona[5] = ".csv";
	char jmenoSouboru[10];
	strcpy(jmenoSouboru, prefix);
	strcat(jmenoSouboru, pripona);

	FILE* soubor = fopen(jmenoSouboru, "a");
	if (soubor != NULL)
	{
		fprintf(soubor, "%d;%s;%s;%s\n", v.id, v.lokalita, v.poznamka, v.code);
	}
	fclose(soubor);
	printf("Voucher with code %s written into file.\n", v.code);
}

void zpracujData(char* jmSoub)
{
	srand(time(NULL));
	FILE* soubor = fopen(jmSoub, "r");
	if (soubor != NULL)
	{
		int count = 0;
		tVoucher vouchery[10];
		char radek[300];
		while (!feof(soubor))
		{
			fgets(radek, 300, soubor);
			vouchery[count].id = atoi(strtok(radek, ";"));
			strcpy(vouchery[count].lokalita, strtok(NULL, ";"));
			strcpy(vouchery[count].poznamka, strtok(NULL, ";"));

			char* prefixes[3] = { "01", "02", "03" };
			int randomPrefixIndex = rand() % 3;
			char* prefix = prefixes[randomPrefixIndex];
			char* code = dejCode(prefix);
			strcpy(vouchery[count].code, code);
			free(code);

			count++;
		}

		for (int i = 0; i < count; i++) {
			printf("ID: %d Nazev: %s Poznamka: %s Prefix: %s\n", vouchery[i].id, vouchery[i].lokalita, vouchery[i].poznamka, vouchery[i].code);
		}

		for (int i = 0; i < count; i++)
		{
			ulozVoucher(vouchery[i]);
		}
	}
}