#!/bin/bash

# Creazione cartella di output
mkdir -p output output/endpoints output/formatters

# Compila con Makefile
make

# Esegui
./server