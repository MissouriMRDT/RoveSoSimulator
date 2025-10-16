<div align="center">
  <h1>RoveSoSimulator</h1>
  <p><b>Autonomous Rover Testing Simulator in Unreal Engine 5</b></p>
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
#### Universal Dependencies:

- [Unreal Engine 5](https://www.unrealengine.com/)
- [Git](https://git-scm.com/downloads)
- [CMake](https://cmake.org/download/) (You may need to restart your computer after downloading CMake for it to properly work.)

#### If Using Autonomy:

- [Autonomy Software](https://github.com/MissouriMRDT/Autonomy_Software/)

#### Windows Dependencies:

- [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/)

#### Linux Dependencies:

Assistance for Linux Setup: [Setup on Linux](/linux-setup)

- [Dotnet SDK](https://learn.microsoft.com/en-us/dotnet/core/install/linux)
- clang and libc++

  In order to build the project with RoveComm_CPP, you will need to install the clang compiler and libc++ standard. If you are on a Debian-based system the following bash commands should install them:
  ```bash
  sudo apt update
  sudo apt install libc++-dev libc++abi-dev clang 
  ```
  

### 2️⃣ **Clone the Repository**

- Next you will want to install `Diversion` here: [Diversion](https://www.diversion.dev/). Create an account with whatever email you want to use, and install Diversion following the instructions for your OS. After you have created an account, message the Simulation Lead on Discord that you would like to help contribute as well as your email, and we will get you added to the repository.

- Once you are added to the repo, you will want to clone it onto your machine. It is over 40GB, so it may take some time to be fully downloaded on your machine.

- After it is cloned, you will want to install the `Diversion Unreal Engine Plugin` found here: [Unreal Plugin](https://docs.diversion.dev/unreal/unreal-engine-plugin). If you are on Windows, follow the instructions on the plugin's website to download and add the plugin to UE. If you are on Linux please proceed to this page: [Setup on Linux](/linux-setup#getting-the-diversion-plugin)

- After everything is downloaded, you should be able to open `RoveSoSimulator` on your install of Unreal Engine. 


### 3️⃣ **Troubleshooting Cloning** 

- Before moving on to running the simulation, however, you need to ensure that there are no errors when opening the sim. If you do encounter an error, you can see the source of it in your local folders at `RoveSoSimulator/Saved/Logs/RoveSoSimulator.log`. If you have any errors related to `RoveComm`, it can be often fixed by going to `RoveSoSimulator/Source/ThirdParty/`, deleting the `RoveComm_CPP` folder, and recloning it in the `/ThirdParty` folder using `git clone --recurse-submodules https://github.com/MissouriMRDT/RoveComm_CPP.git`. If you encounter further issues, let the Simulation Lead know, and we can take a look into the problem.

### 4️⃣ **Setting up Sim Mode on Autonomy_Software**

- Now that you are able to open and run the simulator, you'll need to be able run the Autonomy codebase inside of it. After you have initially followed all the steps to clone Autonomy_Software (see above in Pre Reqs) you will have to configure a few things. First, navigate to `src/AutonomyConstants.cpp`. Find the line that initializes `const std::string SIM_IP_ADDRESS` and set the IP to your own IP. You can find your IP by entering `ipconfig` into your terminal if you are on Windows and `ifconfig` on Linux. We utilize IPv4. If you are on Windows, the IP you should plug in will typically start with 192.168.x.x and will be listed with a default gateway, and on Linux, the IP the adapter will be named something like eth0 or wlan0.
-  You will also want to go into `CMakeLists.txt` and on the line that has `option(BUILD_SIM_MODE "Enable Simulation Mode" OFF)` change OFF to ON.
  
- Next, if you are running Windows, you will need to modify your .wslconfig file. In your File Explorer (or whatever you use to browse your files), go to C:/Users/<Your_User> and create a new file called `.wslconfig`, if you have not yet modified it before. Open it up and write `networkingMode=mirrored`. Save and close the file, then restart your machine so that the changes are made.
  
- Lastly, go back into Autonomy_Software in VSCode and follow these steps:
1. Delete the `build` directory.
2. Open up a new terminal.
3. Run `mkdir build && cd build`
4. Run `cmake .. && make -j$(nproc)` (nproc is the number of processing units)
- You should now have the build folder made to run the simulator! To run autonomy in the sim, follow the steps in the next section.


### 5️⃣ **Run the Simulation**
To start the simulator, follow these steps:

- Open the project in **Unreal Engine 5**.
- Configure the simulation parameters in the settings panel.
- Press the **Play** button to initiate the simulation.
  
You should now be able to play it normally! To run autonomy, follow the steps  below:

- Open up the project in Unreal and click the 'play' button.
- Ensure that it successfully initialized RoveCommUDP. After that, go back into VSCode and run `./Autonomy_Software_Sim`.
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
