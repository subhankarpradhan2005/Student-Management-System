# Student-Management-System# Student Management System

## 1. Project Overview

The Student Management System is a C/C++ based capstone project designed to manage student records efficiently.

The project demonstrates software architecture, C++ programming, file-based data storage, Linux system programming, and Linux device driver concepts.

## 2. Programming Language

- C
- C++

No Python or Java is used in the Student Management System application.

## 3. Operating System

The project is designed and executed on Linux OS.

The final compilation and demonstration are performed in a Linux environment.

## 4. Project Scope and Architecture

The project follows a software architecture consisting of:

- User Interface
- API/Server Layer
- Backend/Data Management Layer
- File-Based Storage
- Linux System-Level Components
- Linux Device Driver Component

The components communicate to provide student record management functionality.

## 5. Features

- Add Student
- View All Students
- Search Student
- Update Student
- Delete Student
- File-based student data storage
- Web-based interface
- Linux device driver component
- System-level testing
## 6. Project Structure

```text
Student Management system_project/

│
├── api/
│   ├── main.cpp
│   ├── crow/
│   ├── pages/
│   └── styles/
│
├── backend/
│   ├── Student.cpp
│   ├── Student.h
│   ├── StudentManager.cpp
│   └── StudentManager.h
│
├── data/
│   └── students.dat
│
├── linux/
│   ├── Makefile
│   ├── device_driver.c
│   ├── driver_test.cpp
│   ├── system_test.cpp
│   └── system_test.txt
│
├── .gitignore
└── README.md
```

## 7. Linux Device Driver

The project includes a Linux Device Driver component implemented in C.

The driver demonstrates basic Linux kernel module concepts and communication through a device file.

### Driver Files

* `device_driver.c`
* `driver_test.cpp`
* `system_test.cpp`
* `Makefile`

## 8. Source Code

The complete source code is included in this repository.

### Backend

The backend is implemented using C++ and contains student management classes.

### API

The API/server is implemented in C++ using the Crow framework.

### Linux Component

The Linux component contains the device driver and system-level testing code.
## 9. Compilation and Execution

### API Compilation

Navigate to the `api` directory:

```bash
cd api
```

Compile the project using:

```bash
g++ main.cpp ../backend/Student.cpp ../backend/StudentManager.cpp -I crow/include -I../backend -o student_server -pthread
```

Run the server:

```bash
sudo ./student_server
```

### Linux Device Driver Compilation

Navigate to the Linux directory:

```bash
cd linux
```

Build the driver and test programs:

```bash
make
```

## 10. Testing and Demonstration

The project has been tested for the following operations:

* Add Student
* View All Students
* Search Student
* Update Student
* Delete Student
* Linux Device Driver testing
* System-level testing

The project can be demonstrated through the C++ API and Linux components.

## 11. Project Objective

The objective of this project is to develop a Student Management System using C++ with proper software architecture concepts.

The project also demonstrates Linux system programming and Linux Device Driver concepts.

The system provides basic student management operations along with low-level Linux component integration.

## 12. Author

**Milan Swain**

B.Tech Computer Science and Engineering

Student Management System – Capstone Project
