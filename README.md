# Secure Bootloader Simulator for Embedded Systems

This project implements a simplified **Secure Bootloader** flow, simulating a critical security component used in defense and high-reliability embedded systems. The core goal is to ensure software integrity before execution.

### The Problem it Solves
Embedded devices (e.g., military radios, UAV flight controllers) need firmware updates in the field. However, these updates are vulnerable to:
1.  **Corruption** during transmission (accidental bit flips).
2.  **Tampering** by malicious actors (unauthorized software injection).

This project simulates the system startup check that validates a new firmware image against a known, pre-stored security key.

### Key Architectural Concepts (Multi-File C)
To simulate real-world embedded software engineering practices, the project is structured into distinct modules:

1.  **Common Types (`common_types.h`):** Defines shared data structures, specifically the `FirmwareImage_t` struct, which includes the version, binary data, and digital signature.
2.  **Hardware Abstraction Layer - Mock (`hal_mock.c/.h`):** Abstractions for non-volatile Flash memory (simulated via static array) and system status indicators (simulated via printf).
3.  **Security Engine (`secure_engine.c/.h`):** Contains the core integrity verification logic. It implements a mock hash generation and verification function that compares the embedded signature in the image with the calculated hash.
4.  **Main System Loop (`main.c`):** Orchestrates the startup flow, executes the secure verification, and handles failsafe logic if verification fails.

### Security Implementation Detail
- **Mock Hashing:** For simplicity within a student project, a XOR-based summation combined with a system-specific mock public key is used to simulate a digital signature process. This demonstrates the *principle* of integrity checking without requiring a complete SHA-256 or RSA library integration.

### Prerequisites to Run (Simulation)
- A Standard C Compiler (e.g., GCC).
- `git clone https://github.com/yourusername/Secure-Embedded-Bootloader.git`
- `gcc *.c -o bootloader`
- `./bootloader`
