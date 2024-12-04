#!/bin/bash

# SFML version to download
SFML_VERSION="2.5.1"  # Change this if you want a different version
SFML_URL_WINDOWS="https://www.sfml-dev.org/files/SFML-$SFML_VERSION-windows-vc15-64-bit.zip"
SFML_URL_MAC="https://www.sfml-dev.org/files/SFML-$SFML_VERSION-osx-clang.zip"
SFML_URL_LINUX="https://www.sfml-dev.org/files/SFML-$SFML_VERSION-linux-gcc-64-bit.tar.gz"

# Function to check and install dependencies for Linux
install_linux_dependencies() {
    echo "Checking for required dependencies on Linux..."
    if ! dpkg -l | grep -q build-essential; then
        echo "Installing build-essential and other dependencies..."
        sudo apt-get update
        sudo apt-get install -y build-essential libsfml-dev
    else
        echo "Dependencies already installed."
    fi
}

# Function to check and install dependencies for macOS
install_mac_dependencies() {
    echo "Checking for Homebrew on macOS..."
    if ! command -v brew &> /dev/null; then
        echo "Homebrew not found. Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi

    echo "Installing SFML via Homebrew..."
    brew install sfml
}

# Function to check and install dependencies for Windows
install_windows_dependencies() {
    echo "Windows installation requires manual setup of Visual Studio and CMake."
    echo "Please visit https://www.sfml-dev.org/download.php for more details on setting up SFML with Visual Studio."
}

# Function to download and extract SFML
download_and_extract_sfml() {
    echo "Downloading SFML $SFML_VERSION..."

    case "$1" in
        "linux")
            wget $SFML_URL_LINUX -O SFML-$SFML_VERSION-linux.tar.gz
            tar -xvzf SFML-$SFML_VERSION-linux.tar.gz
            ;;
        "mac")
            curl -LO $SFML_URL_MAC
            unzip SFML-$SFML_VERSION-osx-clang.zip
            ;;
        "windows")
            curl -LO $SFML_URL_WINDOWS
            unzip SFML-$SFML_VERSION-windows-vc15-64-bit.zip
            ;;
        *)
            echo "Unsupported platform."
            exit 1
            ;;
    esac
}

# Function to create a simple SFML project structure
create_sfml_project() {
    echo "Creating a basic SFML project structure..."
    mkdir -p SFML_Project/src
    cd SFML_Project/src

    # Sample main.cpp for the SFML project
    cat > main.cpp << EOF
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}
EOF

    # Create a basic Makefile for Linux/macOS (can be adapted for Windows later)
    cat > Makefile << EOF
CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = src/main.cpp
OBJ = \$(SRC:.cpp=.o)
EXEC = sfml_project

all: \$(EXEC)

\$(EXEC): \$(OBJ)
	\$(CXX) \$(OBJ) -o \$(EXEC) \$(LDFLAGS)

%.o: %.cpp
	\$(CXX) \$(CXXFLAGS) -c \$< -o \$@

clean:
	rm -f \$(OBJ) \$(EXEC)

run: \$(EXEC)
	./\$(EXEC)
EOF

    echo "Project structure created in SFML_Project/src."
}

# Function to configure include paths based on platform
configure_paths() {
    echo "Configuring paths for the platform..."

    case "$1" in
        "linux")
            INCLUDE_PATH="/usr/include"
            LIB_PATH="/usr/lib/x86_64-linux-gnu"
            ;;
        "mac")
            INCLUDE_PATH="/usr/local/include"
            LIB_PATH="/usr/local/lib"
            ;;
        "windows")
            # Set the paths for SFML in Windows
            INCLUDE_PATH="C:\\SFML\\include"
            LIB_PATH="C:\\SFML\\lib"
            ;;
        *)
            echo "Unsupported platform for path configuration."
            exit 1
            ;;
    esac

    echo "Include path: $INCLUDE_PATH"
    echo "Library path: $LIB_PATH"

    # Set includePath and libPath for IDE
    configure_ides "$INCLUDE_PATH" "$LIB_PATH"
}

# Function to configure IDE settings (e.g., VSCode, Visual Studio)
configure_ides() {
    INCLUDE_PATH=$1
    LIB_PATH=$2

    echo "Configuring IDE settings..."

    # For VSCode (example for setting includePath)
    if [ -f "settings.json" ]; then
        echo "Found settings.json, updating includePath..."
        jq '.["includePath"] += ["'"$INCLUDE_PATH"'"]' settings.json > temp.json && mv temp.json settings.json
        jq '.["libPath"] += ["'"$LIB_PATH"'"]' settings.json > temp.json && mv temp.json settings.json
    else
        echo "No settings.json found, create one with appropriate paths."
    fi
}

# Main function to handle platform-specific setup
main() {
    # Detect OS
    OS_TYPE=$(uname -s)

    case "$OS_TYPE" in
        Linux*)
            echo "Detected Linux OS."
            install_linux_dependencies
            download_and_extract_sfml "linux"
            ;;
        Darwin*)
            echo "Detected macOS."
            install_mac_dependencies
            download_and_extract_sfml "mac"
            ;;
        MINGW* | CYGWIN* | Windows*)
            echo "Detected Windows OS."
            install_windows_dependencies
            download_and_extract_sfml "windows"
            ;;
        *)
            echo "Unsupported OS: $OS_TYPE"
            exit 1
            ;;
    esac

    # Configure the paths for the platform
    configure_paths "$OS_TYPE"

    # Create the SFML project
    create_sfml_project
    echo "SFML setup is complete! You can now build and run your SFML project."
}

# Run the main function
main
