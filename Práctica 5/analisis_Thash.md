# Análisis de tablas de dispersión

* *Oier Fernandez de Leceta Villalmanzo ofv00003@red.ujaen.es*
* *Roberto Luque Peña rlp00041@red.ujaen.es*

## Tamaño de tabla: 230771 (lo que he hecho es: 150000/0.65=230769,2. El siguiente primo es 230771)
| función                | máximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |
|------------------------|:--------------------:|:--------------------:|:---------------:|:----------------------:|
| Exploración cuadrática |          30          |         3123         |     0.58256     |        1.19873         |
| Dispersión doble 1     |          16          |          26          |     0.58256     |        0.464132        |
| Dispersión doble 2     |          19          |          33          |     0.58256     |        0.460465        |

## Tamaño de tabla: 220589 (lo que he hecho es: 150000/0.68=220588,2. El siguiente primo es 220589)
|  función               | máximo de colisiones | supera 10 colisiones | factor de carga  | promedio de colisiones |
|------------------------|:--------------------:|:--------------------:|:----------------:|:----------------------:|
| Exploración cuadrática |          51          |         5638         |     0.60945      |         1.6456         |
| Dispersión doble 1     |          18          |          51          |     0.60945      |        0.531792        |
| Dispersión doble 2     |          19          |          44          |     0.60945      |        0.528906        |

## Justificación de la configuración elegida
Hemos optado por la dispersión doble 1 con λ = 0.65 (tamaño 230771). La exploración cuadrática la descartamos por producir  
muchas más colisiones (más de 3000 inserciones superan las 10 colisiones). Entre las dos dispersiones dobles, el promedio es prácticamente igual, pero la dispersión doble 1 obtiene el menor máximo de        
colisiones (16) y el menor número de inserciones que superan 10 colisiones (26), lo que nos garantiza un mejor caso peor en las búsquedas. Respecto al factor de carga, λ = 0.68 
empeora todas las métricas, por lo que compensa usar λ = 0.65.


## Comparación de tiempos dados en milisegundos
Tiempo en realizar las búsquedas en la Tabla Hash: 0.239542 ms
Tiempo en realizar las búsquedas en la Lista: 3571.53ms

Explicación:
Esto se debe a la complejidad de cada búsqueda:              
    - Tabla hash: O(1). Con la clave djb2(assetnum) se calcula directamente la posición del árbol. Según nuestro análisis,  
      el promedio es de solo 0,46 colisiones por inserción, así que casi siempre se encuentra al primer o segundo intento.
    - Lista: O(n). Hay que recorrerla secuencialmente desde el principio hasta encontrar el árbol.                                                   
Por tanto, para búsquedas por identificador la tabla hash es claramente la estructura adecuad