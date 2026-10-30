# 🚦 Smart Traffic Monitoring and Congestion Management System

A C++-based Smart Traffic Management System designed to monitor traffic conditions, manage road infrastructure, track traffic incidents, and support efficient congestion management through a console-based application.

The system provides role-based access control, traffic record management, incident tracking, activity logging, and search and filtering capabilities.

---

## 📌 Project Overview

The Smart Traffic Monitoring and Congestion Management System aims to simplify the management of traffic-related information through a centralized application.

It allows administrators to manage traffic infrastructure and monitor congestion levels, while registered users can access relevant traffic information and report incidents.

The application uses file handling for persistent data storage, allowing records to remain available between program executions.

## ✨ Key Features

### 1. Role-Based Access Control
- Separate administrator and normal user access.
- Default administrator account.
- User registration and login functionality.
- Restricted administrative operations with permission checks.

### 2. Traffic Management
- Manage road and intersection records.
- Maintain vehicle-related information.
- Manage traffic signals.
- Store and monitor traffic readings.

### 3. Incident Reporting and Tracking
- Users can report accidents and roadblocks.
- Newly reported incidents receive the `Reported` status.
- Administrators can update incident status.
- Incident statuses include:
  - Reported
  - In Progress
  - Resolved

### 4. Search and Filtering
- Search roads using partial road names.
- Case-insensitive search functionality.
- Filter traffic readings by congestion level:
  - HIGH
  - MODERATE
  - LOW
- Search incidents by road name.
- Filter incidents by their current status.

### 5. Activity Logging
- Automatically records important system activities.
- Tracks logins, searches, record views, and modifications.
- Stores activity history in a dedicated log file.

### 6. File-Based Data Persistence
- Uses text files to store application data.
- Maintains records between program executions.
- Supports separate storage for roads, intersections, vehicles, signals, users, incidents, and traffic readings.

---

## 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| C++ | Core programming language |
| C++17 | Language standard |
| File Handling | Persistent data storage |
| STL | Standard Template Library |
| Git & GitHub | Version control and project hosting |

---

## 📂 Project Structure

```text
smart-traffic-management-system/
│
├── main.cpp
│
├── roads.txt
├── intersections.txt
├── vehicles.txt
├── signals.txt
├── readings.txt
├── incidents.txt
├── users.txt
├── activity_log.txt
│
├── README.md
└── .gitignore
```

*The text files are used for storing application data and activity records.*

---

## ⚙️ Installation and Setup

### Prerequisites

- C++ compiler (GCC or MinGW).
- C++17 or later.
- Terminal, Command Prompt, or VS Code.

### 1. Clone the Repository

```bash
git clone https://github.com/vaidic-512/smart-traffic-management-system.git
```

### 2. Navigate to the Project Directory

```bash
cd smart-traffic-management-system
```

### 3. Compile the Program

**Linux / macOS:**

```bash
g++ -std=c++17 main.cpp -o smart_traffic
```

**Windows (MinGW):**

```powershell
g++ -std=c++17 main.cpp -o smart_traffic.exe
```

### 4. Run the Application

**Linux / macOS:**

```bash
./smart_traffic
```

**Windows:**

```powershell
.\smart_traffic.exe
```

Make sure the program runs from the project directory so that the data files are stored in the expected location.

---

## 🔑 Demo Login Credentials

| Account | Username | Password |
|---|---|---|
| Administrator | `admin` | `admin123` |

Normal users can create their own accounts through the registration option.

---

## 🧪 Suggested Demo Workflow

1. Log in using the administrator credentials.
2. Add a road and a traffic reading.
3. Search for roads using partial names.
4. Filter traffic readings by congestion level.
5. Register a normal user account.
6. Log in as the normal user and report a traffic incident.
7. Log back in as administrator and update the incident status.
8. Check the activity log to view recorded system operations.
9. Attempt an administrator-only operation as a normal user to verify access restrictions.

---

## 🔐 Security Considerations

This project is developed as an academic console-based demonstration.

- User passwords are currently stored in plain text in `users.txt`.
- The default administrator credentials are intended only for demonstration purposes.
- The application is not designed for production deployment.

For real-world applications, secure password hashing, stronger authentication mechanisms, and improved data storage controls would be necessary.

---

## 🎯 Project Objectives

- Develop a centralized traffic information management application.
- Monitor traffic conditions and congestion levels.
- Improve incident reporting and tracking.
- Implement role-based access restrictions.
- Maintain system activity records.
- Demonstrate C++ programming and file-handling concepts.

---

## 👨‍💻 Author

**Vaidic Agrawal**

Computer Science and Engineering – Artificial Intelligence and Data Science

MIT World Peace University, Pune

GitHub: [@vaidic-512](https://github.com/vaidic-512)

---

⭐ If you find this project interesting, consider giving the repository a star!

**Repository:** [Smart Traffic Monitoring and Congestion Management System](https://github.com/vaidic-512/smart-traffic-management-system)
