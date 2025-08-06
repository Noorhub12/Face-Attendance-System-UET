# Automated Attendance System Using Facial Recognition

An AI-powered attendance system that leverages facial recognition to automate and streamline the attendance process. Built using Python (client-side) and C (server-side), the system implements socket programming, file handling, and computer vision to securely transmit and store attendance records.

---

## Technologies & Tools

| Component        | Technology Used             |
|------------------|-----------------------------|
| Face Detection   | OpenCV (Haar Cascade)       |
| Face Recognition | OpenCV                      |
| Client           | Python                      |
| Server           | C (Socket Programming - Winsock2) |
| Communication    | TCP/IP                      |
| GUI              | Tkinter (Python)            |
| Data Storage     | CSV Files                   |

---

## Key Features

- ✅ **Face-based student registration**
- ✅ **Real-time face recognition for attendance**
- ✅ **CSV-based attendance generation**
- ✅ **Client-server communication (Python ↔ C)**
- ✅ **Secure file transmission over network**
- ✅ **Structured file saving on server (by date/class)**

---

## System Architecture

### 🔹 Client Side (Python)
- Capture student images for registration
- Use Haar Cascade for face detection
- Recognize faces & mark attendance in CSV
- Send CSV attendance file to server via sockets

### 🔹 Server Side (C)
- Accept client connections using Winsock2 API
- Receive attendance file and store in structured format

---


