#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <source_file> <destination_file>" << std::endl;
        return 1;
    }

    const char *source_file = argv[1];
    const char *dest_file = argv[2];

    int source_fd = open(source_file, O_RDONLY);

    if (source_fd == -1) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    int dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (dest_fd == -1) {
        std::cerr << "Error" << std::endl;
        close(source_fd);
        return 1;
    }

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        size_t bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            std::cerr << "Error: Write operation failed." << std::endl;
            close(source_fd);
            close(dest_fd);
            return 1;
        }
    }

    close(source_fd);
    close(dest_fd);

    std::cout << "File copied." << std::endl;

    return 0;
}
