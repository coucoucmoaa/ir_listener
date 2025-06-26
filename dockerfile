# Utilise une image Linux avec MinGW
FROM ubuntu:24.04

# Installe les outils nécessaires
RUN apt-get update && apt-get install -y \
    mingw-w64 \
    cmake \
    make \
    g++ \
    zip \
    && rm -rf /var/lib/apt/lists/*

# Crée un répertoire de travail
WORKDIR /app

# Copie les fichiers de ton projet dans le conteneur
COPY . /app

# Compile avec MinGW pour Windows
RUN x86_64-w64-mingw32-g++ -static \
    -o hub_ir.exe \
    src/main.cpp \
    src/Profil.cpp \
    src/Core.cpp \
    src/WindowsSerialBackend.cpp \
    src/Config.cpp \
    -Iinclude \
    -lsetupapi

# Le binaire `.exe` sera dans `/app/hub_ir.exe`
