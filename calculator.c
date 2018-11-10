/* 	Membuat Calculator dengan mengimplementasikan Context-Free-Language/PushDown-Automata
	13517077 Dandi Agus Maulana
	13517080 Mgs. Muhammad Riandi Ramadhan 
	13517104 Muhammad Fikri Hizbullah
*/
/*
	1. Menerima input berupa string dari pengguna
	2. Mengecek apakah input dari pengguna sesuai dengan simbol terminal dan rules yang ada
		- bila tidak bisa tampilkan "SYNTAX ERROR"
		- kalau bisa lanjut ke langkah selanjutnya
	3. Mengecek apakah ekspresi bisa dioperasikan
		- bila tidak bisa tampilkan "MATH ERROR"
		- kalau bisa lanjut ke langkah selanjutnya
	4. Lakukan operasi dan tampilkan hasil di layar
*/

#include <stdio.h>
#include "mesinkar.h"
#include "boolean.h"

char terminal[16] = {'0','1','2','3','4','5','6','7','8','9','+','-','/','*','^','.'}; //simbol terminal
boolean NextStep = true; //untuk menentukan apakah perlu dilakukan step selanjutnya

boolean IsTerminal(char C);
/* Mengecek apakah C termasuk simbol terminal */

int main() {
	char ekspresi[50]; //Asumsi maksimum input user berupa 50 simbol terminal

	/* Menerima input user */
	scanf("%s", ekspresi);

	/* Mengecek input dari pengguna sesuai dengan simbol terminal dan rules yang ada */
	START(ekspresi);
	while (!EOP) {
		if (!IsTerminal(CC)) {
			printf("SYNTAX ERROR");
			NextStep = false;
			break;
		}
		else {
			ADV(ekspresi);
		}
	}
	

	/* Mengecek apakah ekspresi bisa dioperasikan */
	if (NextStep) {
		printf("\nPeriksa ekspresi");
	}
	
	/* Lakukan operasi dan tampilkan hasil di layar */


	return 0;
}

boolean IsTerminal(char C) {
	int i = 0;
	boolean exist = false;

	while ((i <= 15) && (!exist)) {
		if (C == terminal[i]) {
			exist = true;
		}
		else {
			i++;
		}
	}
	return exist;
}

