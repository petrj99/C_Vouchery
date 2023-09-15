#pragma once

typedef struct voucher {
	int id;
	char lokalita[20];
	char poznamka[256];
	char code[10];
} tVoucher;

char* dejCode(char* prefix);
void ulozVoucher(tVoucher v);
void zpracujData(char* jmSoub);