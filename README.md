<div align="center">
  <a href="https://github.com/missourimrdt/autonomy_software">
    <img width="125" src="https://i.postimg.cc/XYtdp84Z/logo.png" alt="Mars Rover Design Team Logo">
  </a>
  <h1>RoveSoSimulator</h1>
  <p><b>Autonomous Testing Simulator in Unreal Engine 5</b></p>
  <!-- <div>
    <a href="https://github.com/MissouriMRDT/Autonomy_Software/actions/workflows/codeql.yml">
      <img src="https://img.shields.io/github/actions/workflow/status/missourimrdt/autonomy_software/codeql.yml?branch=development&label=CodeQL&style=flat-round" alt="codeql-ci" />
    </a>
    <a href="https://github.com/MissouriMRDT/Autonomy_Software/actions/workflows/tests.yml">
      <img src="https://img.shields.io/github/actions/workflow/status/missourimrdt/autonomy_software/tests.yml?branch=development&label=Unit%20Tests&style=flat-round" alt="tests-ci" />
    </a>
    <a href="https://github.com/MissouriMRDT/Autonomy_Software/actions/workflows/doxygen_generate.yml">
      <img src="https://img.shields.io/github/actions/workflow/status/missourimrdt/autonomy_software/doxygen_generate.yml?branch=development&label=Docs&style=flat-round" alt="docs-ci" />
    </a>
    <a href="https://github.com/MissouriMRDT/Autonomy_Software/actions/workflows/clang_check.yml">
      <img src="https://img.shields.io/github/actions/workflow/status/missourimrdt/autonomy_software/clang_check.yml?branch=development&label=Clang&style=flat-round" alt="clang-ci" />
    </a>
    <a href="https://github.com/MissouriMRDT/Autonomy_Software/actions/workflows/valgrind.yml">
      <img src="https://img.shields.io/github/actions/workflow/status/missourimrdt/autonomy_software/valgrind.yml?branch=development&label=Valgrind&style=flat-round" alt="valgrind-ci" />
    </a>
  </div>

  <div>
    <a href="https://codecov.io/gh/MissouriMRDT/Autonomy_Software" > 
        <img src="https://codecov.io/gh/MissouriMRDT/Autonomy_Software/branch/topic%2Fcode-coverage/graph/badge.svg?token=AZVPRPE5A8" alt="codecov-ci" /> 
    </a>
    <a href="https://app.codacy.com/gh/missourimrdt/autonomy_software/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade">
      <img src="https://img.shields.io/codacy/grade/cd387bc34658475d98bff84db3ad5287?logo=codacy&style=flat-round" alt="codacy-ci" />
    </a>
    <a href="https://www.codefactor.io/repository/github/missourimrdt/autonomy_software">
      <img src="https://img.shields.io/codefactor/grade/github/missourimrdt/autonomy_software?logo=codefactor&style=flat-round" alt="codefactor-ci" />
    </a>
  </div>

  <div>
    <a href="https://github.com/MissouriMRDT/Autonomy_Software/pkgs/container/autonomy-jammy">
      <img src="https://img.shields.io/badge/Ubuntu_Jammy-latest-orange" alt="jammy-pkg" />
    </a>
    <a href="https://github.com/MissouriMRDT/Autonomy_Software/pkgs/container/autonomy-jetpack">
      <img src="https://img.shields.io/badge/NVIDIA_JetPack_6-latest-orange" alt="jetpack-pkg" />
    </a>
  </div> -->
  <div>
    <a href="https://opensource.org/license/mit">
      <img src="https://img.shields.io/badge/license-MIT-blue.svg?style=flat-round" alt="license" />
    </a>
    <a href="https://en.cppreference.com/w/cpp/20">
      <img src="https://img.shields.io/badge/language-C%2B%2B20-blue.svg?style=flat-round" alt="language" />
    </a>
  </div>
</div>


## 🚀 Introduction

Welcome to **RoveSoSimulator**, an advanced simulation environment designed to aid the Mars Rover Design Team in testing and refining autonomous navigation capabilities. Built on **Unreal Engine 5**, this cutting-edge simulator provides a realistic virtual landscape for testing various sensors, algorithms, and autonomous behaviors. It's an essential tool for validating software in an efficient, scalable, and repeatable way.

## 🌌 Overview

The **RoveSoSimulator** empowers developers and engineers on the Mars Rover Design Team to push the boundaries of our Rover's autonomous capabilities by providing:

- 🏞️ **Highly Detailed Virtual Landscapes**: Simulate complex Martian terrains, including rugged surfaces, rocky obstacles, and diverse environmental conditions.
- 🛠️ **Full Control of Simulation Parameters**: Customize terrain, weather, lighting, and other parameters to recreate various real-world scenarios.
- 🎥 **Stereoscopic Camera & Point Cloud Support**: Generate stereoscopic feeds, point clouds, and depth maps for object detection and path planning.
- 🤖 **Autonomous Testing & Validation**: Seamlessly integrate with the autonomy software to evaluate navigation algorithms, decision-making, and sensor fusion techniques.
- 📊 **Comprehensive Data Logging & Analysis**: Collect real-time data on rover behavior for further analysis and performance evaluation.

## 🛠️ Features

### 🌍 **Realistic Martian Environment**
Experience high-fidelity Martian terrain designed to mimic the conditions your rover will encounter on the actual red planet. From craters to sand dunes, this simulator provides a dynamic testing environment to ensure your autonomy software is prepared for anything.

### 🎥 **Stereoscopic Camera**
RoveSoSimulator includes a set of cameras, which outputs both a stereoscopic feed and depth map. This feature enables in-depth testing of the rover's visual navigation capabilities.

### 📡 **Sensor Integration**
Incorporate a variety of sensors into the simulator to test the rover's response to its environment. Simulated LIDAR, IMU, GPS, and other critical sensors are supported.

### 🛤️ **Pathfinding & Navigation Testing**
Test pathfinding algorithms with obstacles and varied terrains. Measure performance, optimize efficiency, and stress-test the rover’s ability to navigate autonomously in difficult scenarios.

### 📈 **Data Logging**
Log critical metrics, such as sensor readings, navigation decisions, and performance benchmarks, for post-simulation analysis.

### 🔄 **Customization & Expandability**
The simulation is fully customizable. Add new environments, tweak sensor configurations, or even modify the physics engine to reflect new experimental conditions.

## 🎮 How to Get Started

### 1️⃣ **Clone the Repository**

```bash
git clone --recurse-submodules https://github.com/MissouriMRDT/RoveSoSimulator.git
cd RoveSoSimulator
```

The `Content` directory in this project is a submodule that links to our self-hosted GitLab instance for unlimited Git LFS storage. Please be aware that the server has a 1000GB monthly bandwidth limit. Large pushes should be carefully considered as exceeding this limit WILL incur additional costs.

You can access the GitLab repository for the `Content` directory here: [Content Repository](https://gitlab.craysoftware.com/mrdt_blobs/Content). **The `Content` directory is very large, so expect a 2-3 hour initial clone time.**


### 2️⃣ **Install Prerequisites**
Make sure you have the following installed:

- [Unreal Engine 5](https://www.unrealengine.com/)
- [Autonomy Software](https://github.com/MissouriMRDT/Autonomy_Software/)

### 3️⃣ **Run the Simulation**
To start the simulator, follow these steps:

- Open the project in **Unreal Engine 5**.
- Configure the simulation parameters in the settings panel.
- Press the **Play** button to initiate the simulation.

### 4️⃣ **Logging & Data Analysis**
Results and logs can be found in the `/logs` directory. To analyze data, refer to the provided scripts in the `/analysis` folder.

## 📖 Documentation

Comprehensive documentation on **RoveSoSimulator** will be found [here](https://missourimrdt.github.io/RoveSoSimulator/) soon. This includes:

- Full installation guide
- Setup and configuration instructions
- Sensor and environment customization guides
- Data logging and post-analysis tutorials

## 🛠️ Contributing

We welcome contributions to improve **RoveSoSimulator**! Please follow the steps below to get started:

1. **Checkout and pull the latest development branch:**

    ```bash
    git checkout development
    git pull origin development
    ```

2. **Create a new branch for your feature or fix:**

    ```bash
    git checkout -b feature/AmazingFeature
    ```

3. **Commit your changes:**

    ```bash
    git commit -m 'Add some AmazingFeature'
    ```

4. **Push to your branch:**

    ```bash
    git push origin feature/AmazingFeature
    ```

5. **Open a Pull Request targeting the development branch.**

## 📜 License

RoveSoSimulator is licensed under the MIT License. See `LICENSE` for more information.

## 💬 Contact

For more information, questions, or feedback, feel free to reach out to the **Mars Rover Design Team** at [email](mailto:marsrover@mst.edu).
