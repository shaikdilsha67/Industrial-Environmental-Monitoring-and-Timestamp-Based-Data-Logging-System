
# ⚡ Industrial Environmental Monitoring and Timestamp-Based Data Logging System

![Domain](https://img.shields.io/badge/Domain-Embedded%20Systems-14B8A6)
![Controller](https://img.shields.io/badge/Controller-LPC2148%20ARM7-6366F1)
![Language](https://img.shields.io/badge/Language-Embedded%20C-22C55E)
![Sensor](https://img.shields.io/badge/Sensor-LM35%20Temperature%20Sensor-F97316)
![IDE](https://img.shields.io/badge/IDE-Keil%20%C2%B5Vision-F59E0B)
![Interfaces](https://img.shields.io/badge/Interfaces-ADC%20%7C%20RTC%20%7C%20UART0%20%7C%20EINT0-0EA5E9)

---

## 1. Project Overview

The **Industrial Environmental Monitoring and Timestamp-Based Data Logging System** is a bare-metal embedded systems project developed using the **NXP LPC2148 ARM7** microcontroller.

The primary goal of this project is to continuously monitor ambient industrial temperature, display real-time temperature alongside live calendar date and time on a **20×4 LCD**, trigger an audible **buzzer alert** upon temperature threshold violations, and transmit timestamped environmental monitoring data to a host PC via **UART0** for data logging and analysis.

An **LM35** precision analog temperature sensor measures the surrounding temperature (`10 mV/°C`), and the LPC2148's built-in **10-bit ADC** converts the analog voltage into digital data. At startup, the operator configures a custom temperature setpoint using a **4×4 matrix keypad** (`*` backspace and `#` confirmation). During normal operation, pressing an **External Interrupt (`EINT0`)** switch pauses monitoring and opens an interactive keypad menu featuring **SET SETPOINT** and **SET RTC** options. The RTC submenu provides **SET TIME**, **SET DATE**, and **SET BOTH** (time and date) configurations, allowing the operator to modify the internal **Real-Time Clock (RTC)** using keypad input (`HH:MM:SS` and `DD/MM/YYYY`).

When the measured temperature exceeds the configured setpoint (e.g., `35.0 °C`), the firmware activates the industrial buzzer, displays `BUZZER ALERT!!` on the LCD, and immediately transmits a `[!!] TEMPERATURE ALERT` notification over **UART0**. The system also periodically transmits temperature readings with RTC timestamps to the host PC, enabling continuous environmental monitoring and timestamp-based data logging.

---

## 2. Project Objectives
- Monitor industrial environmental temperature continuously in real time.
- Measure ambient temperature using an **LM35** analog temperature sensor (`10 mV/°C`).
- Convert the analog sensor output into a digital value using the LPC2148's built-in 10-bit ADC.
- Allow custom temperature setpoint configuration at startup using a 4×4 Matrix Keypad.
- Display live temperature, date, time, and alert messages on a **20×4 Alphanumeric LCD**.
- Maintain accurate wall-clock time and calendar date using the on-chip Real-Time Clock **(RTC)**.
- Use an External Interrupt (`EINT0`) switch connected to **P0.16** to access the interactive operator menu for temperature **setpoint** and **RTC** configuration.
- Activate an industrial Buzzer connected to **P0.23** whenever the measured temperature exceeds the configured setpoint.
- Transmit periodic temperature telemetry with RTC timestamps and instant temperature alert notifications to a host PC via UART0 (`9600 bps, 8N1`).

  ---

## 3. Hardware Components

| Component | Purpose |
| :--- | :--- |
| **NXP LPC2148 (ARM7TDMI-S)** | Main 32-bit microcontroller (`60 MHz` CCLK, `15 MHz` PCLK) |
| **LM35 Sensor** | Precision analog temperature measurement (`10 mV/°C`) |
| **Inbuilt 10-Bit ADC (`ADC1`)** | Analog-to-digital voltage conversion on `P0.28` (`AIN2`) |
| **20×4 Alphanumeric LCD** | Live local display for telemetry, setup menus, and alerts |
| **On-Chip RTC** | Hardware real-time clock and calendar (`1 Hz` prescaled timebase) |
| **4×4 Matrix Keypad** | User input for temperature setpoint and RTC date/time editing |
| **Push Button (`EINT1`)** | Hardware external interrupt trigger on `P0.16` for RTC setup |
| **Industrial Buzzer** | Audible alarm driven via `P0.23` during threshold breaches |
| **UART0 & MAX232** | RS-232 level-shifted serial telemetry to PC (`9600 baud`) |

---

## 4. Software Requirements

- **IDE & Compiler:** Keil µVision (ARMCC)
- **Programming Language:** Bare-Metal Embedded C
- **Target Hardware:** Advanced Development Board for ARM7 (`LPC2148`)
- **Serial Monitor:** PC Serial Terminal (`9600 bps, 8N1`, no flow control)
- **Flash Utility:** Flash Magic (ISP programming via UART0)

  ---
## 5. System Architecture

### 5.1 System Block Diagram

### 5.2 Interactive Architecture Flowchart

---

## 6. Hardware Showcase


---

## 7. Peripheral Interfacing and Working

### 7.1 LPC2148 ARM7 Microcontroller

---

### 7.2 LM35 Temperature Sensor

---

### 7.3 ADC Interfacing (`ADC1` – `AIN1` / `P0.28`)

---

### 7.4 20×4 LCD Interfacing

---

### 7.5 4×4 Matrix Keypad Interfacing

---

### 7.6 RTC Interfacing

---

### 7.7 External Interrupt (`EINT0` on `P0.16`)

---

### 7.8 UART Communication (`UART0`)

---

### 7.9 Buzzer Interfacing

---

## 8. Pin Configuration Summary


---


## 9. Overall Project Working

### 9.1 Step-by-Step Execution Sequence

---

### 9.2 Firmware Execution Flowchart

---

### 10.1 20×4 LCD Display States

---

### 10.2 Captured UART0 Serial Terminal Output

---

## 11. Software Modules

---

## 12. Testing & Verification

---

## 13. Applications

---

## 14. Limitations & Future Enhancements

### Current System Limitations

---

### Future Enhancements

---

## 15. Conclusion


---

## 17. Author









