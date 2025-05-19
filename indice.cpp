#include "indice.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

IndiceInvertido::IndiceInvertido(StopWords* sw) : stopwords(sw) {}

void IndiceInvertido::procesarLinea(const std::string& linea, int docID) {
    // La línea tiene formato: URL|| contenido, separar por "||"
    size_t pos = linea.find("||");
    if (pos == std::string::npos) return;

    std::string contenido = linea.substr(pos + 2); // ignorar URL
    std::istringstream iss(contenido);
    std::string palabra;

    while (iss >> palabra) {
        // Procesar palabra: convertir a minúsculas, eliminar signos si quieres
        for (auto& c : palabra) c = tolower(c);

        if (!stopwords->esStopWord(palabra)) {
            listaPalabras.insertarPalabra(palabra, docID);
        }
    }
}

void IndiceInvertido::procesarDocumentos(const std::string& archivo_docs) {
    std::ifstream file(archivo_docs);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo de documentos: " << archivo_docs << std::endl;
        return;
    }

    std::string linea;
    int docID = 1;

    while (std::getline(file, linea)) {
        procesarLinea(linea, docID);

        if (docID % 1000 == 0) {
            std::cout << "Procesados " << docID << " documentos..." << std::endl;
        }

        docID++;
    }
    file.close();

    std::cout << "Índice construido con " << (docID - 1) << " documentos." << std::endl;
}

void IndiceInvertido::buscar(const std::string& consulta) {
    std::istringstream iss(consulta);
    std::string palabra;
    std::vector<NodoDoc*> listasDocs;

    while (iss >> palabra) {
        for (auto& c : palabra) c = tolower(c);
        if (stopwords->esStopWord(palabra)) {
            continue; // ignorar stop words en consulta
        }

        NodoPalabra* nodo = listaPalabras.buscarPalabra(palabra);
        if (!nodo) {
            std::cout << "La palabra \"" << palabra << "\" no se encuentra en ningún documento." << std::endl;
            return;
        }
        listasDocs.push_back(nodo->listaDocs);
    }

    if (listasDocs.empty()) {
        std::cout << "No hay términos válidos para buscar." << std::endl;
        return;
    }

    // Intersección simple de listas enlazadas (IDs de docs)
    std::vector<int> resultado;

    // Convertir la primera lista a vector para comparación
    for (NodoDoc* nd = listasDocs[0]; nd != nullptr; nd = nd->siguiente) {
        resultado.push_back(nd->docID);
    }

    for (size_t i = 1; i < listasDocs.size(); ++i) {
        std::vector<int> temp;
        NodoDoc* nd = listasDocs[i];
        while (nd) {
            if (std::find(resultado.begin(), resultado.end(), nd->docID) != resultado.end()) {
                temp.push_back(nd->docID);
            }
            nd = nd->siguiente;
        }
        resultado = temp;
    }

    if (resultado.empty()) {
        std::cout << "No hay documentos que contengan todas las palabras." << std::endl;
    } else {
        std::cout << "Los documentos que contienen todas las palabras son: ";
        for (size_t i = 0; i < resultado.size(); ++i) {
            std::cout << "doc" << resultado[i];
            if (i < resultado.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
}
