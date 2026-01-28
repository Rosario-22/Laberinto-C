# Laberinto-C
Juego de laberinto por consola desarrollado en C. 
El objetivo es guiar al jugador desde la entrada (E) hasta la salida (S), evitando trampas (*) y recolectando tesoros (.). Cada intento cuenta con un número limitado de vidas, y las trampas cambian de posición cada vez que pierdes todas las vidas, haciendo cada partida diferente.

Cómo jugar
El jugador se mueve mediante opciones numéricas:  
  1. Arriba  
  2. Abajo  
  3. Derecha  
  4. Izquierda

- Paredes ( | o - ): chocarlas resta una vida.  
- Trampas (*): restan una vida al caer en ellas.  
- Tesoros (.): recolectarlos puede aumentar tus vidas.  
- Entrada (E): punto inicial del jugador.  
- Salida (S): punto final que debes alcanzar para ganar.  
Cada vez que pierdes todas tus vidas, las trampas se regeneran aleatoriamente, pero los caminos y la estructura del laberinto permanecen iguales.

Características principales
- Laberinto fijo con paredes y caminos definidos.  
- Trampas que se regeneran de manera aleatoria en cada intento fallido.  
- Contadores de vidas, tesoros y movimientos.  
- Entrada (E) y salida (S) fijas.  
- Juego 100% por consola, sin dependencias externas.

Cómo compilar y ejecutar
Compilar el código en C:
gcc laberinto.c -o laberinto
