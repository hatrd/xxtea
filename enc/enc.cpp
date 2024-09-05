#include <iostream>
#include <fstream>
#include <filesystem>
#include "xxtea.h"

void encryptFile(const std::string& filePath, const std::string& key, const std::string& outputPath) {
    std::ifstream inputFile(filePath, std::ios::binary);
    if (!inputFile) {
        std::cout << "Failed to open file: " << filePath << std::endl;
        return;
    }

    std::ofstream outputFile(outputPath, std::ios::binary);
    if (!outputFile) {
        std::cout << "Failed to create output file: " << outputPath << std::endl;
        return;
    }

    std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    size_t outlen = 0;
    char * encryptedContent = (char *)xxtea_encrypt((const void *)content.c_str(), content.size(), (const void *) key.c_str(), &outlen);
    // outlen 会 8 字节对齐，一般大于 content.size()。
    outputFile.write(encryptedContent, outlen);

    std::cout << "Encrypted file saved to: " << outputPath << std::endl;
}

void encryptFilesInDirectory(const std::string& directoryPath, const std::string& key) {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".lua") {
            std::filesystem::path relativePath = std::filesystem::relative(entry.path(), directoryPath);
            std::filesystem::path outputPath = std::filesystem::path("encrypt") / relativePath;
            std::filesystem::create_directories(outputPath.parent_path());
            encryptFile(entry.path().string(), key, outputPath.string());
        }
    }
}

int main(int argc, char* argv[]) {
    std::string path;
    std::string key;

    if (argc > 2) {
        path = argv[1];
        key = argv[2];
    } else {
        std::cout << "Enter file or directory path: ";
        std::cin >> path;
        std::cout << "Enter encryption key: ";
        std::cin >> key;
    }

    if (std::filesystem::is_directory(path)) {
        encryptFilesInDirectory(path, key);
    } else if (std::filesystem::is_regular_file(path)) {
        std::string outputPath = path + ".enc";
        encryptFile(path, key, outputPath);
    } else {
        std::cout << "Invalid path: " << path << std::endl;
    }

    return 0;
}