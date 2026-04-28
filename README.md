# 🚗 QNX RTOS-Based Secured Communication Gateway for Autonomous Vehicles

## 📌 Overview
This project implements a secure communication gateway using QNX Neutrino RTOS to enable reliable and real-time data exchange between autonomous vehicle nodes. The system ensures secure, low-latency communication using a client-server architecture over a wired Ethernet network.

The gateway protects vehicle communication by incorporating authentication, encryption, and packet filtering mechanisms, preventing cyber threats such as spoofing and unauthorized access.

---

## 🚀 Key Features
- Real-time communication using QNX RTOS  
- Secure data transmission with authentication and encryption  
- Client-server architecture for multi-node communication  
- Low latency and high reliability using Ethernet  
- Collision detection and risk-level analysis  
- Scalable architecture for multiple vehicle nodes  

---

## 🏗️ System Architecture
- **Vehicle Nodes:** Raspberry Pi (sensor data collection)  
- **Server Systems:** Laptops running QNX RTOS  
- **Communication:** TCP/IP over Ethernet  
- **Network Device:** Ethernet Switch  

Each node is assigned a unique IP address for seamless communication within the LAN.

---

## ⚙️ Working Principle
1. Sensors collect real-time data (distance, obstacle detection)  
2. Raspberry Pi processes and sends data to server  
3. Server (QNX RTOS) performs:
   - Data validation  
   - Encryption & authentication  
   - Packet filtering  
4. Data is shared between nodes via Ethernet network  
5. System performs collision detection and generates alerts  

---

## 🔐 Security Features
- Secure boot mechanism  
- Data encryption and decryption  
- Device authentication  
- Packet filtering  
- Protection against:
  - Man-in-the-middle attacks  
  - Message spoofing  
  - Unauthorized access  
  - Denial of Service (DoS)  

---

## 🛠️ Tech Stack
- C Programming  
- QNX Neutrino RTOS  
- TCP/IP Networking  
- Raspberry Pi  
- Ethernet Communication  

---

## 📂 Project Structure
QNX-Secured-Gateway/
│── src/
│ ├── server.c
│ ├── client.c
│
│── docs/
│ ├── project_report.pdf
│
│── images/
│ ├── architecture.png
│
│── README.md

---

## 🔄 Communication Mechanism
- Ethernet-based communication ensures:
  - High reliability  
  - Low latency  
  - Minimal packet loss  
- Uses client-server model for structured data exchange  
- Supports bidirectional communication between vehicle nodes  

---

## 🧠 Core Concepts Used
- Microkernel architecture (QNX RTOS)  
- Inter-process communication (IPC)  
- Priority-based scheduling  
- Real-time data processing  
- Secure message passing  

---

## 🧪 Testing & Validation
- Step-by-step component testing  
- Real-time data transmission validation  
- Multi-node communication testing  
- Performance metrics:
  - Latency  
  - Data accuracy  
  - Communication reliability  

---

## 📊 Results
- Achieved stable real-time communication  
- Low latency in data transmission  
- Accurate collision detection  
- Secure and reliable multi-node communication  

---

## 🔮 Future Enhancements
- Integration with AI-based intrusion detection  
- Wireless communication support (V2X)  
- Cloud-based monitoring system  
- Deployment in real vehicle environments  

---

## ⚠️ Note
This repository focuses on system architecture, implementation approach, and project demonstration. Full setup requires QNX RTOS environment and hardware integration.

---

## 👩‍💻 Author
Hari Chandana Pulipati