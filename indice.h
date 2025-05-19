#ifndef INDICE_H
#define INDICE_H

#include "lista_enlazada.h"
#include "stopwords.h"
#include <string>

class IndiceInvertido {
private:
    ListaEnlazada listaPalabras;
    StopWords* stopwords;

    void procesarLinea(const std::string& linea, int docID);

public:
    IndiceInvertido(StopWords* sw);
    void procesarDocumentos(const std::string& archivo_docs);
    void buscar(const std::string& consulta);
};

#endif
