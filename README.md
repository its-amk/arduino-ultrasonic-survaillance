## 🛡️ Project Overview
This low-cost military surveillance system integrates hardware and software to provide an effective perimeter security solution. By combining a **thermal/PIR sensor** for human detection and an **HC-SR04 ultrasonic sensor** for distance measurement—both mounted on a rotating servo motor—the system achieves wide-area sweep coverage (0°–180°) even in total darkness.

### Key Capabilities:
* **Perimeter Intrusion Detection:** Detects human targets reliably within a **2 cm to 400 cm** perimeter.
* **Local Hardware Alerts:** Instantly displays threat warnings on a 0.96" I2C OLED display and illuminates a high-brightness Red LED indicator.
* **Real-Time Telemetry:** Transmits sensor coordinates (`Angle, Distance, Target Status`) every **500 ms** over serial communication to a central control dashboard.
* **Role-Based Software Dashboard:** Disseminates live radar data tailored to three distinct user roles:
  * 🟢 **Civilians:** Shelter maps, safe evacuation routes, emergency services, and safety checklists.
  * 🪖 **Army Authorities:** Live perimeter radar, camp coordinates, supply tracking, and aggregated threat alerts.
  * 🚑 **Rescue Teams:** Missing persons registry and direct military communications routing.

Built with affordable, off-the-shelf components, this prototype demonstrates how low-cost microcontrollers can deliver multi-role surveillance and crisis response capabilities previously restricted to high-cost proprietary defense platforms.
