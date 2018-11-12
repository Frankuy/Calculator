/* 	Membuat Calculator dengan mengimplementasikan Context-Free-Language/PushDown-Automata
	13517077 Dandi Agus Maulana
	13517080 Mgs. Muhammad Riandi Ramadhan 
	13517104 Muhammad Fikri Hizbullah
*/
/*
	ALGORITMA
	1. Menerima input berupa string dari pengguna
	Revisi : menggunakan algoritma Recursive-Descent Parsing untuk menghitung dan menemukan error
	2. Mengecek apakah input dari pengguna sesuai dengan simbol terminal dan rules yang ada
		- bila tidak bisa tampilkan "SYNTAX ERROR"
		- kalau bisa lanjut ke langkah selanjutnya
	3. Mengecek apakah ekspresi bisa dioperasikan
		- bila tidak bisa tampilkan "MATH ERROR"
		- kalau bisa lanjut ke langkah selanjutnya
	4. Lakukan operasi dan tampilkan hasil di layar
*/
/* CFG yang digunakan
S -> T | S+T | S-T --penjumlahan dan pengurangan
T -> F | T*F | T/F --perkalian dan pembagian
F -> G | G^F -- perpangkatan
G -> (S) | -A | A | A.A | -A.A --FACTOR
A -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | AA --DIGIT atau ANGKA
*/

#include <stdio.h>
#include "mesinkar.h"
#include "boolean.h"
#include "stackt.h"

/**** KAMUS GLOBAL ****/
char terminal[18] = {'0','1','2','3','4','5','6','7','8','9','+','-','/','*','^','.','(',')'}; //simbol terminal
char ekspresi[50]; //Asumsi maksimum input user berupa 50 simbol terminal
boolean NextStep = true; //untuk menentukan apakah perlu dilakukan step selanjutnya

/**** FUNGSI ****/
boolean IsTerminal(char C);
/* Mengecek apakah C termasuk simbol terminal */
boolean IsNumber(char C);
/* Mengecek apakah C adalah Bilangan */
boolean IsOperator(char C);
/* Mengecek apakah C adalah Operator */
int parseDigit();
/* Memparsing string yang merupakan sebuah factor */ 
float parseFactor();
/* Memparsing string yang merupakan perkalian dua factor */

/**** MAIN PROGRAM ****/
int main() {
	/**** KAMUS MAIN ****/
	

	/**** ALGORITMA ****/
	/* Menerima input user */
	scanf("%s", ekspresi);

	/*1. Mengecek input dari pengguna sesuai dengan simbol terminal dan rules yang ada */
	START(ekspresi);
	printf("%.2f", parseFactor());





	/*while (!EOP) {
		if (!IsTerminal(CC)) {
			printf("SYNTAX ERROR");
			NextStep = false;
			break;
		}
		else {
			
		}
	}*/

	

	/* Mengecek apakah ekspresi bisa dioperasikan */
	if (NextStep) {
		printf("\nPeriksa ekspresi");
	}
	
	/* Lakukan operasi dan tampilkan hasil di layar */
	if (NextStep) {
		printf("\nLakukan Operasi");
	}

	return 0;
}

boolean IsTerminal(char C) {
	int i = 0;
	boolean exist = false;

	while ((i <= 17) && (!exist)) {
		if (C == terminal[i]) {
			exist = true;
		}
		else {
			i++;
		}
	}
	return exist;
}

boolean IsNumber(char C) {
	return (C == '0') || (C == '1') || (C == '2') || (C == '3') || (C == '4') || (C == '5') || (C == '6') || (C == '7') || (C == '8') || (C == '9');
}

boolean IsOperator(char C) {
	return (C == '(') || (C == ')') || (C == '*') || (C == '/') || (C == '-') || (C == '+') || (C == '^') || (C == '.');
}

int parseDigit() {
	if (IsNumber(CC)) {
		int bilangan = CC - '0';
		ADV(ekspresi);
		return bilangan;
	}
}

float parseFactor() {
	boolean sign;
	if (CC == '-') {
		sign = true;
		ADV(ekspresi);
	}
	else {
		sign = false;
		ADV(ekspresi);
	}
	float factor = (float) parseDigit();
	while (IsNumber(CC)) {
		factor = factor*10 + parseDigit();
	}
	if (CC == '.') {
		ADV(ekspresi);
		float pembagi = 10;
		while (IsNumber(CC)) {
			factor += (parseDigit()/pembagi);
			pembagi*=10;
		}
	}
	if (sign) {
		return -1*factor;
	}
	else {
		return factor;
	}
}


