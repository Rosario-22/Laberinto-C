#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "laberinto.h"

int main() {
	char laberinto[M][M];
	int op = 0;
	
	menuLaberinto(&op);
	
	if(op == 1) {
		// Iniciar juego con 3 intentos
		iniciarSimulacion(laberinto, 3);
	}
	
	return 0;
}

// ========================
// Menú inicial
// ========================
void menuLaberinto(int* op){
	printf("\n=== Juego de Laberinto ===\n");
	printf("1. Empezar partida\n");
	printf("2. Salir\n");
	scanf("%d", op);
}
	
// ========================
// Crear laberinto fijo
// ========================
void crearLaberintoFijo(char laberinto[M][M]) {
	// Inicializar todo vacío
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			laberinto[i][j] = ' ';
			
			// Bordes
			for (int i = 0; i < M; i++) {
				laberinto[0][i] = '-';
				laberinto[M-1][i] = '-';
				laberinto[i][0] = '|';
				laberinto[i][M-1] = '|';
			}
			
			// Entrada y salida
			laberinto[3][0] = 'E';
			laberinto[29][28] = 'S';
			
			// Caminos fijos de ejemplo (completá según tu diseño)
			laberinto[1][12] = ' '; laberinto[1][26] = ' ';
			laberinto[2][12] = ' '; laberinto[2][26] = ' ';
			laberinto[3][1] = ' '; laberinto[3][2] = ' '; laberinto[3][3] = ' ';
			laberinto[4][9] = ' '; laberinto[4][10] = ' '; laberinto[4][11] = ' '; laberinto[4][12] = ' ';
			laberinto[4][14] = ' '; laberinto[4][15] = ' '; laberinto[4][16] = ' '; laberinto[4][26] = ' ';
			// ... agregá el resto de tus caminos fijos
}

// ========================
// Generar trampas aleatorias
// ========================
void colocarTrampas(char laberinto[M][M]) {
	srand(time(NULL));
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (laberinto[i][j] == ' ') { // Solo espacios libres
				double prob = (double)rand() / RAND_MAX;
				if (prob < 0.10)
					laberinto[i][j] = '*'; // Trampa
				else
					laberinto[i][j] = ' '; // Mantener vacío
			}
		}
	}
}

// ========================
// Mostrar laberinto en consola
// ========================
void mostrarLaberinto(char laberinto[M][M], int cantVidas, int cantTesoros, int cantMovimientos) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++)
			printf("%c ", laberinto[i][j]);
		printf("\n");
	}
	printf("Vidas: %d | Tesoros: %d | Movimientos: %d\n", cantVidas, cantTesoros, cantMovimientos);
}

// ========================
// Preguntar movimiento
// ========================
void pregJugada(int *jugada){
	printf("\n¿Hacia dónde te querés mover?\n");
	printf("1. Arriba  2. Abajo  3. Derecha  4. Izquierda\n");
	scanf("%d", jugada);
}
	
	// ========================
	// Actualizar paso del jugador
	// ========================
	void actPaso(char laberinto[M][M], int*jugada, int*posC, int*posF, int* cantVidas){
		char jugador='>';
		int posAuxF = *posF;
		int posAuxC = *posC;
		
		int nuevaF = *posF;
		int nuevaC = *posC;
		
		if (*jugada == 1) nuevaF--;       // Arriba
		else if (*jugada == 2) nuevaF++;  // Abajo
		else if (*jugada == 3) nuevaC++;  // Derecha
		else if (*jugada == 4) nuevaC--;  // Izquierda
		
		// Revisar si el espacio es válido
		char objetivo = laberinto[nuevaF][nuevaC];
		if (objetivo == ' ' || objetivo == '.' || objetivo == '*') {
			if (objetivo == '*') (*cantVidas)--; // Pierde vida en trampa
			laberinto[*posF][*posC] = ' '; // Limpiar posición anterior
			*posF = nuevaF; *posC = nuevaC;
			laberinto[*posF][*posC] = jugador;
		} else {
			(*cantVidas)--; // Golpe contra pared
		}
	}
		
		// ========================
		// Actualizar estado general
		// ========================
		void actEstado(int* cantVidas, int* cantTesoros, char laberinto[M][M], int*salidaAviso, int* posF, int* posC, int* nIntentos){
			// Si llega a la salida
			if (laberinto[*posF][*posC] == 'S') *salidaAviso = 1;
			
			// Si pierde todas las vidas, reiniciar trampas
			if (*cantVidas <= 0) {
				(*nIntentos)--;
				*cantVidas = 3;
				
				// Limpiar jugador y poner en entrada
				laberinto[*posF][*posC] = ' ';
				*posF = 3; *posC = 0;
				laberinto[*posF][*posC] = '>';
				
				// Regenerar trampas
				colocarTrampas(laberinto);
				
				printf("\n¡Perdiste todas tus vidas! Se reiniciaron las trampas.\n");
			}
		}
			
			// ========================
			// Iniciar simulación
			// ========================
			void iniciarSimulacion(char laberinto[M][M], int nIntentos){
				int cantVidas = 3, cantTesoros = 0, cantMovimientos = 0;
				int posF = 3, posC = 0;
				int salidaAviso = 0;
				int jugada;
				
				// Crear laberinto y colocar trampas
				crearLaberintoFijo(laberinto);
				colocarTrampas(laberinto);
				
				// Colocar jugador
				laberinto[posF][posC] = '>';
				
				mostrarLaberinto(laberinto, cantVidas, cantTesoros, cantMovimientos);
				
				while (nIntentos > 0 && salidaAviso == 0) {
					pregJugada(&jugada);
					cantMovimientos++;
					actPaso(laberinto, &jugada, &posC, &posF, &cantVidas);
					actEstado(&cantVidas, &cantTesoros, laberinto, &salidaAviso, &posF, &posC, &nIntentos);
					mostrarLaberinto(laberinto, cantVidas, cantTesoros, cantMovimientos);
				}
				
				if (salidaAviso == 1)
					printf("\n¡Felicidades! Llegaste a la salida.\n");
				else
					printf("\n¡Perdiste todos tus intentos! Fin del juego.\n");
			}

