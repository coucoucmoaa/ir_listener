# Utilise Ubuntu 24.04
FROM ubuntu:24.04

# Installe les outils nécessaires
RUN apt-get update && apt-get install -y \
    mingw-w64 \
    cmake \
    make \
    g++ \
    wget \
    unzip \
    zip \
    && rm -rf /var/lib/apt/lists/*

# Télécharge et installe Raylib compilé pour MinGW (Windows)
# Télécharge et installe Raylib compilé pour MinGW (Windows)
RUN wget https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_win64_mingw-w64.zip && \
    unzip raylib-5.5_win64_mingw-w64.zip -d /opt/raylib && \
    rm raylib-5.5_win64_mingw-w64.zip

ENV RAYLIB_BASE=/opt/raylib/raylib-5.5_win64_mingw-w64
ENV RAYLIB_INCLUDE_PATH=${RAYLIB_BASE}/include
ENV RAYLIB_LIB_PATH=${RAYLIB_BASE}/lib

# Crée le répertoire de travail
WORKDIR /app

# Copie les fichiers du projet
COPY . /app

# Compile ton projet en statique pour Windows avec raylib et setupapi
RUN x86_64-w64-mingw32-g++ -static \
    -o hub_ir.exe \
    src/main.cpp src/Profil.cpp src/Core.cpp src/WindowsSerialBackend.cpp src/Config.cpp \
    src/UI/Ui.cpp src/UI/components/AButton.cpp src/UI/components/NewConfigButton.cpp \
    src/UI/components/LoadConfigButton.cpp src/UI/components/ExitButton.cpp \
    src/UI/components/ActionButton.cpp src/UI/components/ShowConfigButton.cpp \
    src/UI/components/StartButton.cpp src/UI/ButtonFactory.cpp src/UI/components/DefaultButton.cpp \
    src/UI/components/TextBox.cpp \
    -Iinclude -I${RAYLIB_INCLUDE_PATH} \
    -L${RAYLIB_LIB_PATH} -lraylib -lwinmm -lgdi32 -lsetupapi

# Le binaire compilé sera dans /app/hub_ir.exe
