#!/bin/bash

# Compilar
g++ -std=c++17 main.cpp indice.cpp lista_enlazada.cpp stopwords.cpp -o buscador

if [ $? -eq 0 ]; then
    echo "Compilación exitosa."
else
    echo "Error en compilación."
    exit 1
fi

# Ejecutar (recibe dos parámetros: archivo docs y archivo stopwords)
if [ $# -ne 2 ]; then
    echo "Uso: $0 <archivo_docs> <archivo_stopwords>"
    exit 1
fi

./buscador "$1" "$2"
