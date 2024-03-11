#!/bin/bash

# Creazione cartella di output
mkdir -p output output/endpoints output/formatters output/log

# Compila con Makefile
make

# Esegui
./server