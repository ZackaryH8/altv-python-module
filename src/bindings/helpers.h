#pragma once

#include <main.h>

unsigned int Hash(const std::string& strToHash) {
    return Core->Hash(strToHash);
}

void RegisterUtilFunctions(py::module_ m)
{
    m.def("hash", &Hash, "Hashes string");
}