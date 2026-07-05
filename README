# Analizador de Conversaciones de Discord (Búsqueda por Palabra Clave)

Programa de consola en **C++** que procesa un archivo JSON con mensajes exportados de Discord, los agrupa automáticamente en "conversaciones" y permite **buscar en cuáles conversaciones aparece una palabra**, además de imprimir las estructuras internas y medir tiempos de búsqueda.

## ¿De qué trata?

1. El programa carga un archivo **JSON** con mensajes de Discord (cada uno con `id`, `content`, `timestamp` y `author`) usando la librería **[nlohmann/json](https://github.com/nlohmann/json)** (`json.hpp`, incluida en el repositorio).
2. Recorre los mensajes en orden y los agrupa en **conversaciones**: si pasan más de `ESPERA` segundos (20 por defecto) entre un mensaje y el siguiente, se considera que empieza una conversación nueva.
3. Con esa información construye tres estructuras (a las que el código llama "árboles", aunque están implementadas con `std::map`/`std::set`):
   - **Árbol A** — `palabra → conjunto de IDs de conversación` donde aparece esa palabra (es el índice que hace posible la búsqueda).
   - **Árbol B** — `timestamp + ID → contenido del mensaje`.
   - **Árbol C** — `ID de conversación → (primer mensaje, último mensaje)`.
   - **Árbol C+** — `ID de conversación → lista de mensajes completos` (autor, hora, contenido).
4. Un **menú interactivo en consola** permite:
   - `0` Realizar una consulta: pide un archivo `.txt` con palabras (una o varias) y genera un archivo `<nombre>_out.txt` con las conversaciones donde aparece cada palabra.
   - `1 / 2 / 3` Imprimir el contenido de los árboles A, B o C.
   - `4` Medir el tiempo que toman las búsquedas al hacer 100, 1 000, 10 000 y 100 000 consultas (para analizar el rendimiento del algoritmo).
   - `5` Salir.

## Antes de compilar: ajusta la ruta del archivo JSON que se desea

```cpp
string path = ".";                 // carpeta actual del proyecto
string file_name = "Registros";    // sin extensión .json
```

> `comentarios.json` es un archivo grande (~245 MB) con datos reales de ejemplo; `Registro.json`/`Registros.json` son más livianos y sirven bien para pruebas rápidas.

## Requisitos

- Un compilador de **C++17** o superior (`g++`, `clang++`, o Visual Studio).
- No se necesitan librerías externas: `json.hpp` (nlohmann/json) ya está incluido en la carpeta.

## Cómo compilar y ejecutar

```bash
# Compilar
g++ -std=c++17 Main.cpp Celda.cpp -o analizador

# Ejecutar
 analizador
```

En Windows con Visual Studio, crea un proyecto de consola e incluye `Main.cpp`, `Celda.cpp` y `Celda.h`/`json.hpp` en la misma carpeta.

## Uso del programa

1. Al iniciar, el programa carga y procesa el JSON configurado (puede tardar unos segundos si el archivo es grande).
2. Aparecerá el menú:
   ```
   Menu
   ========
   0 - Realizar consulta
   1 - Imprimir arbol A
   2 - Imprimir arbol B
   3 - Imprimir arbol C
   4 - Tiempos
   5 - Salir
   ```
3. Para buscar palabras, elige `0` y escribe el nombre (sin `.txt`) de un archivo con las palabras a buscar, una por línea o separadas por espacios — puedes usar el `palabras.txt` de ejemplo incluido. El resultado se guarda en `palabras_out.txt` (revisa ese archivo para ver un ejemplo de la salida esperada).

## Estructura del proyecto

```
Analizador-Conversaciones/
├── Main.cpp             # Lógica principal: carga el JSON, arma los árboles y el menú
├── Celda.h / Celda.cpp  # Representa un mensaje individual dentro de una conversación
├── Lista.h / Lista.cpp  # Lista doblemente enlazada de apoyo (no usada por Main.cpp)
├── Pila.h                # Pila de apoyo (no usada por Main.cpp)
├── json.hpp               # Librería nlohmann/json para leer archivos JSON
├── Registro.json           # Datos de ejemplo (pequeño)
├── Registros.json           # Datos de ejemplo
├── comentarios.json           # Datos de ejemplo (grande, ~245 MB)
├── palabras.txt                 # Palabras de ejemplo para probar una consulta
├── palabras_out.txt              # Ejemplo de salida generada por una consulta
├── diagrama.png                    # Diagrama de diseño del proyecto
└── html/ , latex/                    # Documentación generada con Doxygen
```



