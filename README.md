
# 📚 EduLink – Book Sharing System

## 📖 Project Overview

**EduLink** is a console-based Book Sharing System developed using the C programming language. It is designed to help students share books, borrow available books, maintain borrowing history, and exchange book reviews.

The system provides a simple platform for students to access academic books and share knowledge with one another.

## 🎯 Objectives

* Encourage book sharing among students.
* Make academic books more accessible.
* Keep track of borrowed books and return dates.
* Allow students to share book reviews.
* Provide useful study tips and educational brain teasers.

## ✨ Features

### 👤 Student Management

* Student Registration
* Student Login
* Password Hashing
* Student ID and Semester Information

### 📚 Book Management

* Add Books to the List
* View Available Books
* Store Book Details
* Track Book Availability
* Record Book Owner Information

### 📖 Borrowing System

* Borrow Available Books
* Record Borrowing and Return Dates
* View Personal Borrowing History
* Display Return-Date Reminders

### ⭐ Additional Features

* Add Book Reviews
* View Book Reviews
* Interactive Brain Teasers
* Study Tips and Motivation

## 🛠️ Technologies Used

* **Programming Language:** C
* **File Handling:** C File I/O (`fopen`, `fprintf`, `fscanf`, `fclose`)
* **Data Structures:** Structures (`struct`)
* **String Handling:** C String Library
* **Development Tools:** C Compiler (GCC or compatible compiler)

## 💾 Data Storage

The system stores information in text files:

| File Name                  | Purpose                                           |
| -------------------------- | ------------------------------------------------- |
| `Students_Information.txt` | Student registration and login information        |
| `Books_Information.txt`    | Book details and availability                     |
| `Borrow_Information.txt`   | Borrowing history and dates                       |
| `Books_Review.txt`         | Book reviews                                      |
| `temp.txt`                 | Temporary storage when updating book availability |

## ⚙️ How to Run

### 1. Clone the Repository

```bash
git clone https://github.com/YOUR-USERNAME/EduLink-Book-Sharing-System.git
```

### 2. Navigate to the Project Folder

```bash
cd EduLink-Book-Sharing-System
```

### 3. Compile the C Program

```bash
gcc main.c -o edulink
```

*Replace `main.c` with your actual C source filename if it is different.*

### 4. Run the Program

**Windows:**

```bash
edulink.exe
```

**Linux:**

```bash
./edulink
```
Edulink home_page
https://github.com/sourov937/EduLink-Book-Sharing--System/blob/f585e0484ad83a564751dab442634fe3d29c58e1/Edulink%20dashboard.png

## 🚀 Future Improvements

* Implement secure password hashing.
* Add automatic overdue notifications.
* Support book titles and author names containing spaces.
* Prevent duplicate student registrations.
* Add a book search feature.
* Implement book return functionality.
* Upgrade the console application to a graphical or web-based interface.
* Migrate text-file storage to a database.

## 👨‍💻 Author

**Sourov Chandra Das**

## 🎓 Project Type

Academic Project — Book Sharing System using C.

---


