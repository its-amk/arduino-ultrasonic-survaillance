# 🛡️ Autonomous Low-Cost Military Surveillance & Defense Perimeter System

A low-cost, integrated hardware-software surveillance system engineered for continuous perimeter security, automated intrusion detection, and crisis communication. Built using an **Arduino Uno microcontroller**, **ultrasonic distance sensing**, **thermal/PIR human detection**, and a **sweeping servo motor**, the system provides wide-area spatial coverage (0° to 180°) up to **200 cm**and operates in total darkness.

Real-time telemetry is streamed over serial communication every **500 ms** to a central web platform, featuring customized, role-based dashboards for **Civilians**, **Army Authorities**, and **Rescue Teams**.

---

## 🛠️ Key Technical Specifications

* **Detection Range:** 2 cm to 200 cm continuous perimeter monitoring.
* **Angular Sweep:** 0° to 180° motorized sweep arc.
* **Night Vision Capabilities:** Thermal/PIR intrusion sensing operational in zero-light/total darkness.
* **Telemetry Refresh Rate:** 500 ms serial stream data cycles.
* **Hardware Alert Latency:** < 50 ms (Local visual alert + OLED status push).
* **Power & Component Model:** Off-the-shelf, low-cost micro-electronics designed for modular maintenance.

---

## 🔌 Hardware Architecture & Component List

| Component | Technical Role | Connection Details |
| :--- | :--- | :--- |
| **Arduino Uno (ATmega328P)** | Central Processing Unit for sensor sampling & motor control | USB Serial to Host / DC Power |
| **HC-SR04 Ultrasonic Sensor** | Time-of-flight spatial distance calculator (2 cm - 200 cm) | Trig: Pin 9 \| Echo: Pin 10 |
| **PIR / Thermal Human Sensor** | Infrared passive motion & human presence verification | Digital Pin 2 (Interrupt) |
| **SG90 Micro Servo Motor** | 180° continuous sweep actuator mechanism | PWM Pin 11 |
| **0.96" I2C OLED Display** | Local node diagnostic interface & status message display | SDA: Pin A4 \| SCL: Pin A5 |
| **Visual Alert System (Red LED)** | Instant hardware visual alert indicator | Digital Pin 13 (via 220Ω resistor) |

---

## 🌐 Role-Based Web Interface Architecture

The system processes telemetry from the edge device and dynamically dispatches actionable data across three secure user views:

### 1. 🟢 Civilian Safety Portal
* **Live Safety Guidance:** Identifies active safe zones and immediate shelter locations during perimeter breaches.
* **Evacuation Routing:** Displays dynamically updated safe routes bypassing active alert areas.
* **Emergency Dispatch:** Direct line connection to regional emergency services.
* **Checklists:** Standard operating procedure (SOP) evacuation and safety checklists.

### 2. 🪖 Army Command & Control Dashboard
* **Live Tactical Radar:** Visualizes exact intruder angles (θ) and ranges (r) streamed from the field node.
* **Base Coordinates & Logistics:** Real-time tracking of forward base camps, personnel numbers, and supply reserves.
* **Aggregated Threat Logs:** System-wide historical threat frequency analysis and threat vector tracking.

### 3. 🚑 Emergency & Rescue Team Interface
* **Missing Persons Database:** Real-time logging, status updating, and search coordination for missing individuals.
* **Liaison Communication:** Direct military-to-rescue routing channels for coordinated tactical operations.
* **Priority Response Map:** Geographic hotspotting of confirmed breaches requiring immediate search-and-rescue assistance.

---

## 🚀 Setup & Deployment Guide

### Hardware Assembly
1. Mount the HC-SR04 Ultrasonic Sensor and PIR/Thermal sensor onto the horn of the SG90 Servo Motor.
2. Connect sensor trigger/echo pins and servo PWM lines to the respective digital pins on the Arduino board as outlined in the component table.
3. Wire the OLED panel to the hardware I2C bus (A4/A5) and connect the red LED to Pin 13.

---

---

## 📊 Project Decision Matrix

The following matrix evaluates the proposed IoT surveillance system against traditional and high-end alternative approaches across key technical and operational parameters:

| Selection Criteria | Weight (%) | Option 1: Manual Patrolling & Searchlights | Option 2: High-End Proprietary Military Systems | Option 3: Proposed IoT System (Arduino + Dual Sensors) |
| :--- | :---: | :---: | :---: | :---: |
| **Component & Deployment Cost** | **25%** | **4** (Low equipment cost, high labor cost) | **1** (Very expensive proprietary hardware) | **5** (Very low-cost, off-the-shelf parts) |
| **Night & Darkness Operation** | **20%** | **1** (Fails in total darkness/fog) | **5** (Full military-grade thermal/IR) | **4** (Effective via thermal PIR + ultrasonic) |
| **Soldier Safety / Stealth** | **20%** | **1** (Exposes position & risks soldier lives) | **4** (Remote monitoring enabled) | **4** (Autonomous early warning without location exposure) |
| **False Alarm Reduction** | **15%** | **2** (High human error & fatigue) | **4** (Advanced AI filter) | **4** (Dual-confirmation: Thermal + Ultrasonic) |
| **Multi-Role Information Sharing** | **10%** | **1** (Manual verbal/radio comms) | **3** (Restricted military command view only) | **5** (Web dashboard for Civilian, Army, & Rescue views) |
| **Portability & Ease of Setup** | **10%** | **2** (Requires personnel deployment) | **2** (Bulky & heavy field setup) | **4** (Compact micro-controller footprint) |
| **Weighted Total Score** | **100%** | **2.25 / 5.00** | **3.15 / 5.00** | **4.35 / 5.00 (Selected Solution)** |

*Scoring Scale: 1 = Very Poor, 2 = Poor, 3 = Moderate, 4 = Good, 5 = Excellent*

### 💡 Evaluation Summary

* **Option 1 (Manual Patrolling):** Exposes personnel to high danger and performs poorly in total darkness or adverse weather due to human fatigue[cite: 1].
* **Option 2 (High-End Military Systems):** Offers high accuracy but scores poorly on affordability, power requirements, and field deployment flexibility[cite: 1].
* **Option 3 (Proposed IoT System - Selected):** Scores highest overall (**4.35 / 5.00**). Combining passive thermal sensing with ultrasonic distance metrics on a sweeping servo motor delivers autonomous night coverage, low latency, and real-time multi-role threat dissemination[cite: 1].

---

## 🔄 System Operational Workflow

```text
       [ Servo Rotates 0° -> 180° ]
                    │
       [ Ultrasonic & Thermal Sensing ]
                    │
          Is Target in Range?
         (2 cm <= Distance <= 200 cm)
               /         \
            YES           NO
            /               \
 [Trigger Local Alert]   [Status: CLEAR]
 ├─ LED -> ON            ├─ LED -> OFF
 └─ OLED -> ALERT        └─ OLED -> SEARCHING
            │               │
     [Transmit Telemetry Stream via Serial]
         (Baud Rate: 9600 / 500ms Cycle)
                    │
       [Role-Based Web Dashboard Engine]
        ├── Civilian View
        ├── Army Authority View
        └── Rescue Team View
