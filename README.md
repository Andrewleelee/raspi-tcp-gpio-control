# TCP-based Remote GPIO Control via Linux Kernel Module

This project implements a remote GPIO control system using Linux kernel modules and TCP/IP communication.
By combining kernel-level GPIO control with network-based command transmission, the system enables real-time and extensible remote hardware control on embedded Linux platforms.

---

## Project Overview

This project adopts a dual Raspberry Pi architecture:

- **Raspberry Pi 3**  
  Responsible for Linux kernel module development and direct GPIO control.

- **Raspberry Pi 4**  
  Runs a TCP server that monitors button input and transmits control commands over the network.

The system demonstrates kernel-space and user-space integration, kernel-level networking, and embedded hardware control.

---

## System Architecture

The system consists of three main components:

### 1. Linux Kernel Module (project.c)

- Implemented as a Linux kernel module
- Creates a character device interface for user-space access
- Controls three GPIO-connected LEDs directly in kernel space
- Exposes a simple and extensible interface for external control commands

### 2. TCP Server (tx.c)

- Runs on Raspberry Pi 4
- Monitors the state of a physical button connected to GPIO 27
- Detects button events and sends control commands sequentially:
  - `"100"` → `"010"` → `"001"`
- Transmits commands to the remote device via TCP/IP

### 3. TCP Client & User-space Controller (user.c)

- Runs on Raspberry Pi 3
- Receives TCP commands from the remote server
- Writes received commands to the kernel module through the character device
- Triggers real-time LED state updates at the kernel level

---

## Control Flow

1. A button press is detected by the TCP server on Raspberry Pi 4  
2. A control command (`"100"`, `"010"`, or `"001"`) is sent over TCP/IP  
3. The TCP client on Raspberry Pi 3 receives the command  
4. The command is written to the kernel module via the character device  
5. The kernel module updates the GPIO output and switches the LED state in real time  

---

## Key Features

- Linux kernel module–based GPIO control
- Kernel-space and user-space communication via character devices
- TCP/IP–based remote command transmission
- Real-time hardware response with low latency
- Modular and extensible design for future IoT applications

---

## Environment & Technologies

- **Hardware**: Raspberry Pi 3, Raspberry Pi 4  
- **OS**: Embedded Linux  
- **Language**: C  
- **Kernel Components**: Linux Kernel Module, Character Device  
- **Networking**: TCP/IP  
- **Hardware Interface**: GPIO  

---

## Learning Outcomes

Through this project, I gained hands-on experience in:

- Linux kernel module development and device driver design
- Kernel-space and user-space interaction
- Kernel-level TCP/IP communication
- Embedded system integration and real hardware testing
- Designing extensible remote hardware control systems

---

## Applications & Extensions

This system architecture can be extended to:

- Remote hardware control systems
- Smart home automation
- IoT device management
- Distributed embedded control platforms
