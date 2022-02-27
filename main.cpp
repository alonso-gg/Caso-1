#include <iostream>
#include <math.h>
#include <map>

using namespace std;

/** ITCR Campus Central Cartago - Ingeniería en computación
 * 	Análisis de algoritmos - Caso 1
 * 	Estudiante: Alonso Garita Granados
 * 	I Semestre de 2022
 * /

/* 1. Compare the Triplets */
int* compareTriplets1(int a[], int b[], int points[]){

	points[0] = ((a[0]>b[0])?1:0) + ((a[1]>b[1])?1:0) + ((a[2]>b[2])?1:0);

	points[1] = ((b[0]>a[0])?1:0) + ((b[1]>a[1])?1:0) + ((b[2]>a[2])?1:0);

	//A pesar de que se obtiene el puntaje directo, se realizan 6 comparaciones y 6 sumas.

	return points; //Retorna el arreglo de los puntos ganados
}

int* compareTriplets2(int a[], int b[], int points[]){

	if(a[0]!=b[0]){ //Evitar la situación de 0/0
		points[0] += ((a[0]-b[0])/abs(a[0]-b[0]))+1; //Si puntúa suma 2, y sino suma 0
		points[1] += ((b[0]-a[0])/abs(b[0]-a[0]))+1;
	}
	if(a[1]!=b[1]){
		points[0] += ((a[1]-b[1])/abs(a[1]-b[1]))+1;
		points[1] += ((b[1]-a[1])/abs(b[1]-a[1]))+1;
	}
	if(a[2]!=b[2]){
		points[0] += ((a[2]-b[2])/abs(a[2]-b[2]))+1;
		points[1] += ((b[2]-a[2])/abs(b[2]-a[2]))+1;
	}

	points[0] >>= 1; points[1] >>= 1; //Dado que se suman múltiplos de 2, al dividir entre 2 se obtiene
	//el puntaje real. Se hace un dezplazamiento de un bit a la derecha para la división entre 2.
	
	//En este segundo algoritmo se realizan solo 3 comparaciones, esto se logra determinando cuál es el
	//mayor usando el valor absoluto, aunque siempre se debe comprobar que a[n]!=b[n] para evitar el
	//caso de 0/0.

	return points;
}

/* 2. Time Conversion */
string timeConversion1(string s) {
	string format24h = s.substr(2, 6); //:mm:ss
	int hrs = stoi(s.substr(0,2)); //hh

	if(hrs==12) //Se hacen siempre 2 comparaciones
		if(s[8]=='A')
			hrs = 0; //Medianoche 00:mm:ss
	else if(s[8]=='P')
		hrs += 12; //Horas de la tarde (13-23)

	format24h = (hrs<10) ? "0"+to_string(hrs)+format24h : to_string(hrs)+format24h;

	//En los casos para las 12PM y las horas de la mañana no entra en ningún if, así que
	//por el pipelining tendría que deshacer y devolverse varias veces.

	return format24h;
}

string timeConversion2(string s) {
	string format24h = s.substr(2, 6); //:mm:ss
	int hrs = stoi(s.substr(0,2)); //hh
	int factor = ((hrs%12)/hrs); //Para PM: =0 si h=12 | =1 en otro caso
	
	if(s[8]=='A') //Se hace una sola comparación
		factor--; //Para AM: =-1 si h=12 | =0 en otro caso

	hrs += (12 * factor); //hrs-12 para 12AM | hrs+12 para 1PM-11PM | hrs+-0 en otro caso

	format24h = (hrs<10) ? "0"+to_string(hrs)+format24h : to_string(hrs)+format24h;
	
	//Convertir la hora con operaciones aritméticas nos ahorra una comparación.
	//Si la única comparación es falsa, sólo se debe deshacer una instrucción.

	return format24h;
}

/* 3. Subarray Division */
int birthday1(int chocolate[], int length, int day, int month) {
	//chocolat: arreglo | day: número a sumar
	//month: cant. de campos t.q. chocolat[i]+chocolat[i+1]+...+chocolat[i+month] = day
	//Sea L = "length", es decir el tamaño del arreglo "chocolate", y sea M el valor de "month"
	int max = length-month+1; //max = L-M+1
	int subtotal = 0;
	int opts = 0;

	for(int i=0; i<max; i++){ //Hace L-M+2 comparaciones
		for(int j=0; j<month; j++) //Hace M+1 comparaciones POR CICLO, y se ejecutan en total L-M+1 veces
			subtotal += chocolate[i+j];
		
		if(subtotal==day) //Este if hace L-M+1 comparaciones, una por ciclo
			opts++;

		subtotal = 0;
	}

 	//En total, el algoritmo siempre hace 3L-2M+LM-(M^2)+4 comparaciones
	
	return opts;
}

int birthday2(int chocolate[], int length, int day, int month) {
	//chocolat: arreglo | day: número a sumar
	//month: cant. de campos t.q. chocolat[i]+chocolat[i+1]+...+chocolat[i+month] = day
	//Sea L = "length", es decir el tamaño del arreglo "chocolate"
	int count = 1;
	int subtotal = 0;
	int opts = 0;

	for(int i=0; i<length; i++){ //Hace L+1 comparaciones
		subtotal+=chocolate[i];
		if(count==month){ //Se hacen 2L comparaciones (2 por ciclo L veces) en el peor de los casos
			if(subtotal==day)
				opts++;
			subtotal-=chocolate[i+1-month];
		}else
			count++;
	}
	
	//En total, el algoritmo hace 3L+1 comparaciones en el peor de los casos, por lo que el tiempo de
	//ejecición sólo depende del tamaño del arreglo.

	//Si usamos el ejemplo de Hackerrank donde L=5 y M=2 tenemos que:
	//	birthday1 realizaría 21 comparaciones
	//	birthday2 realizaría 16 comparaciones
	//Además, no usar un doble for ayuda al pipelining del procesador.

	return opts;
}

/* 4. The Minion Game */
string minionGame(string minionWord){
	int stuart = 0; //Cuenta consonantes
	int kevin = 0; //Cuenta vocales
	int length = minionWord.length();
	
	for(int i=0; i<length; i++){ //Recorre cada caracter de la palabra
		if(439704915%minionWord[i]==0) //Verifica si es una vocal
			kevin+= length-i;
		else
			stuart += length-i;
	}
	
	if(stuart>kevin)
		return "Stuart: " + to_string(stuart);
	else if(stuart==kevin)
		return "Empate";
	else
		return "Kevin: " + to_string(kevin);
}
	
/* 5. Cipher */
string cipher(int k, string s) {
	//n: tamaño de b | k: desplazamiento | s: código cifrado | b: código descifrado
	int n = s.length()-k+1;
    char bBits[n];
    bBits[0] = s[0]-48; //guardamos el valor 0 o 1, en lugar del caracter

	for (int i = 1; i < k; i++) //hallar los primeros k bits de b
        bBits[i] = s[i-1] ^ s[i];

    for (int i = k; i < n; i++){ //hallar el resto de bits
        bBits[i] = '0';
        for (int j = i-k+1; j < i; j++) //evalúa los k-1 bits anteriores
            bBits[i] = bBits[i] ^ bBits[j]; //si en los k-1 anteriores había par cantidad de 1, da 0, sino da 1
        bBits[i] = bBits[i] ^ s[i]; //determina bBits[i] con base en los k-1 anteriores y s[i]
		//-Estos XORs funcionan igual que este pseudocódigo que hice para analizar el problema:
		//si en s[i] hay un 1:
		//	si hay una cantidad par de 1 en los k-1 anteriores de bBits: entonces en bBits[i] va un 1
		//	sino: entonces en bBits[i] va un 0
		//sino:
		//	si hay una cantidad par de 1 en los k-1 anteriores de bBits: entonces en bBits[i] va un 0
		//	sino: entonces en bBits[i] va un 1
    }

    string bStr = "";
    for (int i = 0; i < n; i++)
        bStr += bBits[i]+48;

    return bStr;
}

/* 6. Pairs*/
int pairs(int k, int *array, int n) {
    int options = 0; //Cantidad de parejas (m, n) t.q. |m-n|=k 
	map<int, int> matches; //Hash con los números [i]+-k para hallar coincidencias

	for(int i=0; i<n; i++){
		if(matches.find(array[i]) != matches.end()) //Si el número está en el hash...
			options++; //Es porque hay otro en el arreglo con el que tiene diferencia de k
		matches.insert(pair<int, int>(array[i]+k, array[i]+k));
		matches.insert(pair<int, int>(array[i]-k, array[i]-k));
		//Se insertan los números [i]+-k para hallar más parejas si las hay
	}

    return options;
}

/*--- main ---*/
int main(int argc, char** argv) {
	cout << "1. Compare the Triplets" << "\n";
	int a[] = {17, 85, 16};
	int b[] = {99, 16, 46};
	int p[] = {0, 0};
	compareTriplets2(a, b, p);
	cout << "a={17, 85, 16} | b={99, 16, 46}\n" << "Alice: " << p[0] << " | Bob: " << p[1] << "\n";

	a[0] = 56; a[1] = 39; a[2] = 87;
	b[0] = 87; b[1] = 39; b[2] = 56;
	p[0]=p[1]=0;
	compareTriplets2(a, b, p);
	cout << "a={56, 39, 87} | b={87, 39, 56}\n" << "Alice: " << p[0] << " | Bob: " << p[1] << "\n\n";
	//---------------
	cout << "2. Time conversion" << "\n";
	cout << "12:15:07AM = " << timeConversion2("12:15:07AM") << "\n";
	cout << "03:15:07PM = " << timeConversion2("03:15:07PM") << "\n\n";
	//---------------
	cout << "3. Subarray Division" << "\n";
	int chocolateBar[] = {2,2,1,3,2}; //barra de chocolate
	int length = sizeof(chocolateBar)/sizeof(chocolateBar[0]); //tamaño de la barra
	int cant = birthday2(chocolateBar, length, 4, 2);
	cout << "{2,2,1,3,2} d=4 | m=2 : " << cant << "\n"; //salida: 2

	int chocolateBar2[] = {2,4,1,5,2,0,6,1};
	length = sizeof(chocolateBar2)/sizeof(chocolateBar2[0]);
	cant = birthday2(chocolateBar2, length, 7, 3);
	cout << "{2,4,1,5,2,0,6,1} d=7 | m=3 : " << cant << "\n\n"; //salida: 3
	//---------------
	cout << "4. The Minion Game" << "\n";
	cout << "HEREDIA - " << minionGame("HIELO") << "\n"; //salida: Kevin: 8
	cout << "BANANA - " << minionGame("BANANA") << "\n\n"; //salida: Stuart: 12
	//---------------
	cout << "5. Cipher" << "\n";
	cout << "Cifrado: 1110100110 | Descifrado: " << cipher(4, "1110100110") << "\n"; //salida: 1001010
	cout << "Cifrado: 1000110 | Descifrado: " << cipher(3, "1000110") << "\n\n"; //salida: 11010
	//---------------
	cout << "6. Pairs" << "\n";
	int ar1[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
	int n1 = sizeof(ar1)/sizeof(ar1[0]);
	cout << "Parejas con diferencia de 6: " << pairs(6, ar1, n1) << "\n"; //salida: 9

	int ar2[] = {3,14,19,5,0,8,11};
	int n2 = sizeof(ar2)/sizeof(ar2[0]);
	cout << "Parejas con diferencia de 5: " << pairs(5, ar2, n2) << "\n"; //salida: 3

	return 0;
}
