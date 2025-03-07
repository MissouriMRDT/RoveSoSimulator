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

### 1️⃣ **Install Prerequisites**
Make sure you have the following installed:

- [Unreal Engine 5](https://www.unrealengine.com/)
- [Autonomy Software](https://github.com/MissouriMRDT/Autonomy_Software/)
- [Git](https://git-scm.com/downloads)
- [CMake](https://cmake.org/download/) (You may need to restart your computer after downloading CMake for it to properly work.)
- [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/)

#### Windows Dependencies:

#### Linux Dependencies:
    In order to build the project with RoveComm_CPP, you will need to install the clang compiler and libc++ standard.
    ```
    sudo apt update
    sudo apt install libc++-dev libc++abi-dev clang 
    ```

### 2️⃣ **Clone the Repository**

- Next you will want to install `Diversion` here: [Diversion](https://www.diversion.dev/). Create an account with whatever email you want to use, and install Diversion following the instructions for your OS. After you have created an account, message the Simulation Lead on Discord that you would like to help contribute as well as your email, and we will get you added to the repository.

- Once you are added to the repo, you will want to clone it onto your machine. It is over 40GB, so it may take some time to be fully downloaded on your machine. After it is cloned, you will want to install the `Diversion Unreal Engine Plugin` found here: [Unreal Plugin](https://docs.diversion.dev/unreal/unreal-engine-plugin). Follow the instructions and add the plugin to UE.

- After everything is downloaded, you should be able to open `RoveSoSimulator` on your install of Unreal Engine. 


### 3️⃣ **Troubleshooting Cloning** 

- Before moving on to running the simulation, however, you need to ensure that there are no errors when opening the sim. If you do encounter an error, you can see the source of it in your local folders at `RoveSoSimulator/Saved/Logs/RoveSoSimulator.log`. If you have any errors related to `RoveComm`, it can be often fixed by going to `RoveSoSimulator/Source/ThirdParty/`, deleting the `RoveComm_CPP` folder, and recloning it in the `/ThirdParty` folder using `git clone --recurse-submodules https://github.com/MissouriMRDT/RoveComm_CPP.git`. If you encounter further issues, let the Simulation Lead know, and we can take a look into the problem.


### 4️⃣ **Setting up Sim Mode on Autonomy_Software**

- Now that you are able to open and run the simulator, you'll need to be able run the Autonomy codebase inside of it. After you have initially followed all the steps to clone Autonomy_Software (see above in Pre Reqs) you will have to configure a few things. First, navigate to `src/AutonomyConstants.h`. Find the line that initializes `const std::string SIM_IP_ADDRESS` and set the IP to your own IP. You will also want to go into `CMakeLists.txt` and on the line that has `option(BUILD_SIM_MODE "Enable Simulation Mode" OFF)` change OFF to ON.
  
- Next, if you are running Windows, you will need to modify your .wslconfig file. In your File Explorer (or whatever you use to browse your files), go to C:/Users/<Your_User> and create a new file called `.wslconfig`, if you have not yet modified it before. Open it up and write `networkingMode=mirrored`. Save and close the file.
  
- Lastly, go back into Autonomy_Software in VSCode and follow these steps:
1. Delete the `build` directory.
2. Open up a new terminal.
3. Run `mkdir build && cd build`
4. Run `cmake .. && make -j1`
- You should now have the build folder made to run the simulator! To run autonomy in the sim, follow the steps in the next section.


### 5️⃣ **Run the Simulation**
To start the simulator, follow these steps:

- Open the project in **Unreal Engine 5**.
- Configure the simulation parameters in the settings panel.
- Press the **Play** button to initiate the simulation.
  
You should now be able to play it normally! To run autonomy, follow the steps  below:

- Open up the project in Unreal and click the 'play' button.
- Ensure that it successfully initialized RoveCommUDP. After that, go back into VSCode and run `./Autonomy_Software`.
- Go back into Unreal, and in the game, press 'B' on your keyboard to open up the Basestation menu. This will allow us to send waypoints and start autonomy. After sending a waypoint and clicking on 'Start Autonomy', the back panel of the rover should turn red and it should start autonomously navigating.

If you encounter any issues, let the Simulation Lead know!

### 6️⃣ **Logging & Data Analysis**
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
