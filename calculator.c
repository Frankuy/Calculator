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
float parseMultiDigit();
/* Memparsing string yang merupakan angka yang memiliki lebih dari 1 digit */ 
float parseExpression();
/* Memparsing string yang merupakan ekspresi keseluruhan */ 
float parseFactor();
/* Memparsing string yang merupakan perkalian dua factor */
float parseTambahKurang();
/* Memparsing string yang merupakan hasil pertambahan atau pengurangan dua bilangan */
float parseKaliBagi();
/* Memparsing string yang merupakan hasil perkalian atau pembagian dua bilangan */

/**** MAIN PROGRAM ****/
int main() {
	/**** KAMUS UTAMA ****/

	/**** ALGORITMA ****/
	/* Menerima input user */
	scanf("%s", ekspresi);
	START(ekspresi);

	/* Pengecekan masukan apakah diterima */



	/* Perhitungan ekspresi masukan */
	float hasil = parseExpression();
	printf("%.2f\n", hasil);

	return 0;
}

boolean IsTerminal(char C) {
	/* KAMUS lOKAL */
	int i = 0;
	boolean exist = false;
	
	/* ALGORITMA */
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
	/* KAMUS LOKAL */
	int bilangan;
	
	/* ALGORITMA */
	if (IsNumber(CC)) {
		bilangan = CC - '0';
		ADV(ekspresi);
		return bilangan;
	}
}

float parseMultiDigit() {
	/* KAMUS lOKAL */
	float factor, pembagi;
	
	/* ALGORITMA */
	factor = parseDigit();
	while (IsNumber(CC)) {
		factor = factor*10 + parseDigit();
	}
	if (CC == '.') {
		ADV(ekspresi);
		pembagi = 10;
		while (IsNumber(CC)) {
			factor += parseDigit()/pembagi;
			pembagi*=10;
		}
	}
	return factor;
}

float parseExpression() {
	/* KAMUS LOKAL */
	float factor;
	
	/* ALGORITMA */
	factor = parseTambahKurang();
	return factor;
}

float parseFactor() {
	/* KAMUS LOKAL */
	float factor;
	
	/* ALGORITMA */
	if (CC == '(') {
		ADV(ekspresi);
		factor = parseExpression();
		ADV(ekspresi);
	}
	else if (IsNumber(CC)) {
		factor = parseMultiDigit();
	}
	return factor;
}

float parseTambahKurang() {
	/* KAMUS LOKAL */
	float bil1, bil2;
	char operator;
	
	/* ALGORITMA */
	bil1 = parseKaliBagi();
	while ((CC == '+') || (CC == '-')) {
		operator = CC;
		ADV(ekspresi);
		bil2 = parseKaliBagi();
		if (operator == '+') {
			bil1 += bil2;
		}
		else if (operator == '-') {
			bil1 -= bil2;
		}	
	}
	return bil1;
}

float parseKaliBagi() {
	/* KAMUS LOKAL */
	float bil1, bil2;
	char operator;
	
	/* ALGORITMA */
	bil1 = parseFactor();
	while ((CC == '*') || (CC == '/')) {
		operator = CC;
		ADV(ekspresi);
		bil2 = parseFactor();
		if (operator == '*') {
			bil1 *= bil2;
		}
		else if (operator == '/') {
			bil1 /= bil2;
		}
	}
	return bil1;
}
