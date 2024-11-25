# MagiCube
esp32-2432s024r MagiCube ENVI
# MagiCube ENVI

## Hardware
- ESP32-2432S024R with 2.4" TFT Touch Display (ILI9341_2_DRIVER)
- PCA9685
- BME280
- 5v Piezzo Atomizer Disc Module
- 5v LED light
- 5v fan

## Define SPI pins for display
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15  // Chip select control pin
#define TFT_DC    2  // Data Command control pin
#define TFT_RST  -1  // Set to -1 if not used
#define TFT_BL   27  // LED back-light control pin

- I2C:
  - SDA: Pin 21
  - SCL: Pin 22

## Display Configuration
- Screen Width: 320
- Screen Height: 240
- Orientation: Horizontal

## Current Status
- Display: Working ✅
- Touch: Working ✅
- Sensors: under development ✅
- Controls: under developmnet ✅

## Development History
- [x] Initial setup with working display
- [x] Implemented sensor readings
- [x] Created basic UI layout
- [x] Fixed touch functionality



------------------------------------
2. Proposed File Structure
------------------------------------


* A well-organized file structure enhances collaboration and simplifies navigation. Below is a suggested structure for your GitHub repository:


MagiCube/
│
├── ── **Documentation/**
│    ├── README.md
│    ├── INSTALLATION_GUIDE.md
│    ├── USER_MANUAL.md
│    ├── CONTRIBUTING.md
│    └── DESIGN_DOCUMENTATION.md
│
├── ── **Firmware/**
│    ├── src/
│    │    ├── main.cpp
│    │    ├── sensor.cpp
│    │    ├── display.cpp
│    │    ├── network.cpp
│    │    └── utils.cpp
│    ├── include/
│    │    ├── sensor.h
│    │    ├── display.h
│    │    ├── network.h
│    │    └── utils.h
│    ├── lib/
│    │    ├── lv_conf.h
│    │    ├── TFT_eSPI/
│    │    └── XPT2046_Touchscreen/
│    └── examples/
│
├── ── **UI-UX/**
│    ├── assets/
│    │    ├── icons/
│    │    ├── fonts/
│    │    └── images/
│    ├── mockups/
│    ├── prototypes/
│    └── design_tools/
│
├── ── **Software/**
│    ├── backend/
│    │    ├── api/
│    │    ├── database/
│    │    └── services/
│    ├── frontend/
│    │    ├── src/
│    │    ├── public/
│    │    └── styles/
│    └── mobile_app/
│
├── ── **Hardware/**
│    ├── schematics/
│    ├── PCB_design/
│    ├── BOM.xlsx
│    └── 3D_models/
│
├── ── **Tests/**
│    ├── unit_tests/
│    ├── integration_tests/
│    └── UI_tests/
│
├── ── **Scripts/**
│    ├── build/
│    ├── deploy/
│    └── maintenance/
│
├── ── **.github/**
│    ├── workflows/
│    │    └── ci.yml
│    └── ISSUE_TEMPLATE/
│
└── LICENSE



----------------------------------------
Folder Descriptions
---------------------------------------



Documentation/: Contains all relevant documentation, including guides, manuals, and contribution guidelines.
Firmware/: Houses all firmware-related code, organized into source files (src/), headers (include/), libraries (lib/), and examples.
UI-UX/: Stores design assets, mockups, prototypes, and tools used for designing the GUI.
Software/: Encompasses backend and frontend code for any web or mobile applications associated with Magicube Pro.
Hardware/: Includes schematics, PCB designs, bill of materials (BOM), and 3D models related to the hardware components.
Tests/: Contains all testing scripts and test cases for unit, integration, and UI testing.
Scripts/: Includes scripts for building, deploying, and maintaining the project.
.github/: Contains GitHub-specific files like workflows for CI/CD and issue templates.
LICENSE: Specifies the licensing information for the project.
3. Primary Workflow
Establishing a clear workflow ensures that all team members can collaborate effectively, maintain code quality, and streamline the development process. Below is a step-by-step workflow tailored for your team:


------------------------------------------------------------------------------------------------------------------
Step 1: Version Control with GitHub
-------------------------------------------------------------------------------------------------------------------


Clone the Repository

bash
Copy code
git clone https://github.com/xxxcaliber/MagiCube.git
cd MagiCube
Branching Strategy

Main Branch (main): Stable, production-ready code.
Development Branch (develop): Integration branch for features.
Feature Branches (feature/feature-name): Individual features or fixes.
Release Branches (release/version): Prepare for production releases.
Hotfix Branches (hotfix/issue): Critical fixes on main.
Example:

bash
Copy code
git checkout -b feature/ui-enhancements
Commit and Push Changes

Commit Message Guidelines:
Use clear and concise messages.
Reference related issues if applicable.
bash
Copy code
git add .
git commit -m "Add responsive layout for dashboard UI"
git push origin feature/ui-enhancements
Pull Requests (PRs)

Create PRs from Feature Branches to develop.
Code Reviews: At least one team member reviews the PR.
Merge PRs: Once approved, merge into develop.
Step 2: Task Management
Utilize GitHub Issues and Projects for task tracking.

Create Issues

Types: Feature, Bug, Improvement, Documentation.
Templates: Use predefined templates for consistency.
Labels: Categorize by priority, type, or component.
Organize with GitHub Projects

Columns: To Do, In Progress, In Review, Done.
Cards: Assign issues to team members and move them through columns as they progress.
Step 3: Continuous Integration/Continuous Deployment (CI/CD)
Automate testing and deployment using GitHub Actions.


--------------------------------------------------------------------------------------------------
Set Up CI Workflows
--------------------------------------------------------------------------------------------------



Example (.github/workflows/ci.yml):
yaml
Copy code
name: CI

on:
  push:
    branches: [ develop, feature/* ]
  pull_request:
    branches: [ develop ]

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
    - uses: actions/checkout@v2
    - name: Set up Arduino
      uses: miketaylor2/setup-arduino@v1
      with:
        arduino-version: '1.8.13'
    - name: Install Dependencies
      run: |
        # Install necessary libraries
        arduino-cli lib install "TFT_eSPI"
        arduino-cli lib install "XPT2046_Touchscreen"
    - name: Build
      run: |
        arduino-cli compile --fqbn esp32:esp32:esp32 MagiCube/Firmware



------------------------------------------------------------------------------------------------------------
Deploy Workflows
------------------------------------------------------------------------------------------------------------



Automate firmware uploads or web deployments post successful builds.
Step 4: Development Stages
Feature Development

UI/UX Enhancements:
Design: Create high-fidelity mockups using tools like Figma or Adobe XD.
Implementation: Translate designs into code, ensuring responsiveness and aesthetic appeal.
Backend Integration:
Sensor Data Handling: Ensure accurate reading and processing of sensor data.
Automation Logic: Implement algorithms for humidity control, lighting schedules, etc.
Testing

Unit Tests: Verify individual components (e.g., sensor readings, UI elements).
Integration Tests: Ensure different modules work together seamlessly.
UI Tests: Check for responsiveness, navigation flow, and visual consistency.
Review and Feedback

Peer Reviews: Regularly review code and designs with the team.
User Testing: Conduct usability tests with real users to gather feedback.
Iteration

Refinement: Improve features based on feedback and testing results.
Optimization: Enhance performance and energy efficiency.
Step 5: Finalization and Release
Prepare for Release

Merge to main: Once features are stable in develop, merge into main.
Tagging: Use semantic versioning (e.g., v1.0.0).
bash
Copy code
git checkout main
git merge develop
git tag -a v1.0.0 -m "Release version 1.0.0"
git push origin main --tags
Deployment

Firmware: Upload the final firmware to the devices.
Documentation: Ensure all manuals and guides are up-to-date.
Marketing and Launch

Coordinate with the business strategy team to align the product launch with promotional activities.
4. UI/UX Design Best Practices for Magicube Pro
Creating a top-notch, eye-catching, and user-friendly GUI is crucial for Magicube Pro's success. Here are some best practices and steps to achieve an exceptional UI/UX experience:

A. Design Principles
Simplicity

Minimalist Design: Avoid clutter. Use whitespace effectively to highlight essential elements.
Intuitive Navigation: Ensure users can easily find and access different sections of the interface.
Consistency

Uniform Elements: Use consistent colors, fonts, and button styles throughout the interface.
Standard Icons: Utilize recognizable icons to represent common actions.
Feedback

Interactive Elements: Provide visual or auditory feedback when users interact with buttons or perform actions.
Error Handling: Clearly communicate errors and guide users on how to resolve them.
Accessibility

Readable Fonts: Use legible fonts with appropriate sizes.
Contrast: Ensure sufficient contrast between text and background for readability.
B. UI/UX Workflow
Wireframing and Mockups

Tools: Use Figma, Adobe XD, or Sketch to create wireframes and mockups.
Iterate Designs: Refine based on team feedback and usability considerations.
Asset Creation

Icons and Images: Design or source high-quality, modern icons and images that align with the Magicube brand.
Fonts: Choose unique, modern fonts that are easy to read on the ESP32 display.
Implementation

Responsive Layout: Ensure the UI adapts well to different screen orientations and sizes within the ESP32 display limitations.
Performance Optimization: Optimize graphics and animations to maintain responsiveness on the embedded system.
Testing and Refinement

User Testing: Gather feedback from real users to identify pain points and areas for improvement.
Performance Testing: Ensure the UI runs smoothly without lag or crashes.
C. Suggested UI Components
Dashboard

Main Display: Show current status (humidity, temperature, growth stage).
Quick Actions: Buttons for initiating different modes (Colonizing, Pinning, Fruiting).
Notifications: Alerts and updates displayed prominently.
Settings Menu

Customization Options: Allow users to adjust timers, brightness, and other settings.
Network Setup: Simplify the process for connecting to the ESP network.
Data Visualization

Graphs and Charts: Display historical data in an easy-to-understand format.
Status Indicators: Use color-coded indicators for different statuses (e.g., green for optimal, red for alerts).
User Feedback

Interactive Elements: Touch-responsive buttons with visual feedback.
Help Section: Access to troubleshooting guides and support.



----------------------------------------------------
5. Example File Structure Implementation
----------------------------------------------------

Here's an example of how specific parts of your project can be organized within the proposed file structure:

Firmware/src/main.cpp
cpp
Copy code
#include <lv_conf.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "sensor.h"
#include "display.h"
#include "network.h"
#include "utils.h"

void setup() {
    // Initialize Serial
    Serial.begin(115200);
    
    // Initialize Sensors
    initSensors();
    
    // Initialize Display
    initDisplay();
    
    // Initialize Network
    initNetwork();
    
    // Initialize UI
    initUI();
}

void loop() {
    // Handle sensor data
    updateSensors();
    
    // Update UI
    updateDisplay();
    
    // Handle network tasks
    handleNetwork();
    
    // Add any additional logic
    handleAutomation();
}

-----------------------------------------------------
UI-UX/mockups/dashboard.fig
-------------------------------------------------------------



Store your dashboard mockups as .fig (Figma) or relevant format files within the mockups/ folder.
UI-UX/assets/icons/refresh.png

Store all UI icons in the icons/ subfolder, categorized by function (e.g., refresh, settings, notifications).
Software/frontend/src/App.js


---------
javascript
------------


import React from 'react';
import Dashboard from './components/Dashboard';
import Settings from './components/Settings';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';
import './styles/main.css';

function App() {
  return (
    <Router>
      <Switch>
        <Route path="/settings" component={Settings} />
        <Route path="/" component={Dashboard} />
      </Switch>
    </Router>
  );
}



-------------------------------------------------------------------------------------------------------------------------------------------------------
export default App;
--------------

------------------------------------
Documentation/README.md
-----------------------------------

# Magicube Pro

Magicube Pro is a modern, automated mushroom growing chamber designed for ease of use and aesthetic appeal. This repository contains all the necessary firmware, UI/UX designs, and documentation to develop and maintain Magicube Pro.

## Table of Contents

- [Installation Guide](./INSTALLATION_GUIDE.md)
- [User Manual](./USER_MANUAL.md)
- [Contribution Guidelines](./CONTRIBUTING.md)
- [Design Documentation](./DESIGN_DOCUMENTATION.md)

## Features

- Automated humidity, lighting, and ventilation control
- User-friendly touch interface with customizable settings
- Historical data tracking and visualization
- Energy-efficient design with responsive UI

------------------------
## Getting Started
--------------------------------------

### Prerequisites

- Arduino IDE
- ESP32 board
- Required libraries (listed in `Firmware/lib/`)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/xxxcaliber/MagiCube.git
Open the project in Arduino IDE.
Install necessary libraries from the lib/ folder.
Upload the firmware to the ESP32 board.
License
This project is licensed under the MIT License - see the LICENSE file for details.

markdown
Copy code

---
---------------------------------------------
## **6. Additional Recommendations**
---------------------------------------------------------------



### **A. Utilize GitHub Projects and Milestones**

- **Projects:** Create a GitHub Project board to visualize and manage tasks using Kanban-style columns (To Do, In Progress, Review, Done).
- **Milestones:** Group related issues and PRs under milestones to track progress towards specific goals or releases.

### **B. Implement Code Standards and Linting**

- **Consistent Coding Style:** Adopt a consistent coding style to improve readability and maintainability.
- **Linting Tools:** Use tools like `ESLint` for JavaScript or `clang-format` for C++ to enforce coding standards automatically.

### **C. Documentation and Onboarding**

- **Comprehensive Documentation:** Ensure all aspects of the project are well-documented to assist new team members.
- **Onboarding Guide:** Create a guide for new developers to get up to speed quickly, including setup instructions and coding guidelines.

### **D. Regular Team Meetings**

- **Stand-ups:** Conduct daily or weekly stand-up meetings to discuss progress, blockers, and upcoming tasks.
- **Sprint Planning:** Organize development into sprints (e.g., 2-week cycles) to focus on specific goals and deliverables.

### **E. Backup and Security**

- **Regular Backups:** Ensure the repository is regularly backed up to prevent data loss.
- **Access Control:** Manage team access levels to maintain security and integrity of the project.

---

## **7. Conclusion**

By following this high-level overview, establishing a structured file hierarchy, and adhering to a clear workflow, the team can efficiently develop Magicube Pro into a polished, market-ready product. Focus on creating a seamless UI/UX experience while ensuring robust backend functionality. Remember to iterate based on feedback and maintain open communication within the team to address challenges promptly.







