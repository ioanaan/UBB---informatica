#pragma once
#include <stdexcept>
#include <string>
using std::string;

class AppException : public std::runtime_error {
public:
    explicit AppException(const string& msg) : std::runtime_error(msg) {}
};

class ValidationException : public AppException {
public:
    explicit ValidationException(const string& msg) : AppException(msg) {}
};

class CarteNotFoundException : public AppException {
public:
    explicit CarteNotFoundException(const string& titlu)
        : AppException("Cartea cu titlul \"" + titlu + "\" nu a fost gasita!") {
    }
};

class DuplicateTitluException : public AppException {
public:
    explicit DuplicateTitluException(const string& titlu)
        : AppException("Exista deja o carte cu titlul \"" + titlu + "\"!") {
    }
};

class CosException : public AppException {
public:
    explicit CosException(const string& msg) : AppException(msg) {}
};

class RepoLabException : public AppException {
public:
    explicit RepoLabException()
        : AppException("RepoLab: exceptie aleatoare aruncata!") {
    }
};