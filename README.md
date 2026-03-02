
# High-Performance Real-Time Log Processing & System Monitoring (C++)

## 📌 Overview

High-Performance Real-Time Log Processing & System Monitoring is a Linux-based system-level application built in C++ that simulates streaming log data while monitoring live CPU metrics using `/proc/stat`.

The system processes logs in real-time, tracks system health, and generates intelligent alerts based on configurable thresholds. It demonstrates strong understanding of multithreading, system programming, and modular OOP design.

---

## 🎯 Key Features

- Real-time log streaming (simulated production-style logs)
- Live CPU monitoring using Linux `/proc/stat`
- Multithreaded architecture (`std::thread`)
- Thread-safe shared resource handling
- ANSI colored interactive dashboard
- Log analytics (INFO/WARNING/ERROR/CRITICAL tracking)
- Error rate calculation
- Intelligent alert status reporting
- Clean modular architecture (header/source separation)

---

## 🏗 Architecture

            +--------------------+
            |    Dashboard       |
            |  (Main Thread)     |
            +--------------------+
                     ↑
 ----------------------------------------------
 |                                            |

+----------------+ +------------------+
| CPU Monitor | | Log Generator |
| (Thread 1) | | (Thread 2) |
| Reads /proc | | Streams logs |
+----------------+ +------------------+


---

## ⚙️ Technology Stack

- **Language:** C++
- **Concurrency:** `std::thread`
- **Synchronization:** `std::mutex`
- **Platform:** Linux
- **System Interface:** `/proc/stat`
- **Build Tool:** Makefile

---

## 🛠 Build Instructions

Clone the repository:

```bash
git clone https://github.com/adwaita-powar/real-time-log-monitor.git
cd real-time-log-monitor

Build the project:

make

Run the application:

./log_engine

Clean build files:

make clean
📊 Sample Output
====================================================
        HIGH-PERFORMANCE REAL-TIME SYSTEM MONITOR
====================================================

SYSTEM METRICS
----------------------------------------------------
CPU Usage  : 11.7%
CPU State  : IDLE

LOG ANALYTICS
----------------------------------------------------
Total Logs : 219
Logs/sec   : 5

INFO      : 129
WARNING   : 39
ERROR     : 39
CRITICAL  : 12

Error Rate : 17.8%

ALERT STATUS
----------------------------------------------------
● NORMAL - System Stable