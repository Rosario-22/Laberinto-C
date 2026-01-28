#ifndef laberinto_h
#define laberinto_h
#define M 30

// Prototipos
void menuLaberinto(int* op);
void crearLaberintoFijo(char laberinto[M][M]);
void colocarTrampas(char laberinto[M][M]);
void mostrarLaberinto(char laberinto[M][M], int cantVidas, int cantTesoros, int cantMovimientos);
void pregJugada(int *jugada);
void actPaso(char laberinto[M][M], int*jugada, int*posC, int*posF, int* cantVidas);
void actEstado(int* cantVidas, int* cantTesoros, char laberinto[M][M], int*salidaAviso, int* posF, int* posC, int* nIntentos);
void iniciarSimulacion(char laberinto[M][M], int nIntentos);
#endif
