# Laboratorio 2 - Redes - Detección y Corrección de Errores - Pt 1
## Descripción

Este laboratorio se enfoca en la implementación de técnicas de detección y corrección de errores en la transmisión de mensajes binarios. Se han abordado dos principales técnicas:

- **Corrección de Errores:**
  - **Códigos de Hamming** 🛠️: Implementados para códigos (n, m) que cumplen con la condición \((m + r + 1) \leq 2^r\).

- **Detección de Errores:**
  - **Fletcher Checksum** ✅: Se utiliza para tramas de longitud \(k\) con bloques de 8, 16 o 32 bits. Se aplicará padding si es necesario para ajustar la trama al tamaño del bloque (agregar 0s a la trama).

## Emisor

El emisor se encarga de:

1. Solicitar un mensaje en binario (por ejemplo, `110101`) 💬.
2. Ejecutar el algoritmo de detección o corrección de errores seleccionado y generar la información necesaria para comprobar la integridad del mensaje 🔄.
3. Devolver el mensaje en binario concatenado con la información generada 📤.

### Implementación
El emisor está implementado en Python 🐍.

## Receptor

El receptor realiza las siguientes tareas:

1. Solicitar un mensaje en binario concatenado con la información generada por el emisor 📥.
2. Ejecutar el algoritmo seleccionado para comprobar la integridad del mensaje 🔍.
3. Devolver la información correspondiente:
   - **No se detectaron errores** ✅: Mostrar el mensaje original (sin la información generada por el emisor).
   - **Se detectaron errores** ❌: Indicar que el mensaje se descarta debido a errores detectados.
   - **Se detectaron y corrigieron errores** ⚠️: Indicar que se corrigieron errores, mostrar la posición de los bits corregidos y el mensaje corregido.

### Implementación
El receptor está implementado en C++ 💻.

## Uso

Para ejecutar el emisor y el receptor, siga los pasos a continuación:

1. **Emisor:**
   - Ejecute el script en Python y proporcione el mensaje en binario cuando se le solicite 🖥️.
   - Obtenga el mensaje en binario concatenado con la información generada 📩.

2. **Receptor:**
   - Ejecute el programa en C++ y proporcione el mensaje en binario concatenado con la información generada por el emisor 🖥️.
   - Obtenga el resultado según la comprobación de errores 📊.

## Requisitos

- Se utilizó Python 3.11.8 para el emisor 🐍.
- Compilador C++ (g++ o similar) para el receptor 💻.

## Contacto

Para cualquier consulta o problema con el código, por favor, comuníquese con:

- Diego Alexander Hernández Silvestre | 21270 🛻
- Linda Inés Jiménez Vides | 21169 🏎️