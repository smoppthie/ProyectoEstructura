#include <iostream>
#include <string>
#include "indice.h"
#include "stopwords.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Uso: " << argv[0] << " <archivo_docs> <archivo_stopwords>" << std::endl;
        return 1;
    }

    std::string archivo_docs = argv[1];
    std::string archivo_stopwords = argv[2];

    StopWords sw;
    sw.cargarDesdeArchivo(archivo_stopwords);

    IndiceInvertido indice(&sw);
    indice.procesarDocumentos(archivo_docs);

    std::string consulta;
    while (true) {
        std::cout << "\nIngrese término(s) a buscar (o 'salir' para terminar): ";
        std::getline(std::cin, consulta);
        if (consulta == "salir") break;
        indice.buscar(consulta);
    }

    return 0;
}
