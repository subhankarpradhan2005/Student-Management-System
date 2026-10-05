#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {

    const char* filename = "system_test.txt";
    const char* message = "Student Management System - Linux System Programming\n";

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        cout << "File open failed." << endl;
        return 1;
    }

    write(fd, message, strlen(message));

    close(fd);

    cout << "Data written using Linux system calls." << endl;

    return 0;
}
