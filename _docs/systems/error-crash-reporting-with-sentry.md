# **Sentry & Crash Reporting System**

## **1. Purpose**
The goal of the crash reporting system is to provide the engineering team with high-fidelity, actionable data when the simulator crashes in "the wild" (on operator laptops or during autonomy testing). Unlike standard logs, Sentry provides **symbolicated callstacks**, identifying the exact file and line number of the C++ failure, along with hardware analytics (GPU, RAM, OS version).

---

## **2. Core Components**
*   **Sentry SDK (Unreal Plugin):** Hooks into the engine's error handlers to capture minidumps and logs.
*   **Crashpad Handler:** A background process launched by Sentry that "watches" the sim and sends data if the sim process terminates unexpectedly.
*   **Sentry Dashboard:** The web-based interface where crashes are aggregated, deduplicated, and assigned to developers.
*   **Discord Integration:** An automated alert system that pings the team's `#sim-crashes` channel when a new issue is detected.

---

## **3. Engine Configuration (`DefaultEngine.ini`)**
The behavior of the SDK is controlled via the `[Sentry]` section in your project configuration.

```ini
[Sentry]
Dsn="https://YOUR_PUBLIC_KEY@o0.ingest.sentry.io/PROJECT_ID"
InitializeSdkAutomatically=False
EnableAutoLogAttachment=True
EnableAutoStackTrace=True
```

### **The "75% Splash Screen Hang" (Critical Linux Note)**
On Linux (Arch/Ubuntu), initializing Sentry automatically during engine startup frequently causes the editor to hang at **75%**. This is caused by the engine waiting for Sentry to complete its network handshake with the server before continuing.
*   **The Fix:** Always set `InitializeSdkAutomatically=False`.
*   **Manual Init:** You must manually initialize Sentry in your **GameInstance** or **Main Menu** blueprint using the `Initialize Sentry` node.

---

## **4. Initialization Workflow (Blueprint)**
Because auto-init is disabled for stability, we use the **`BP_GameInstance`** to kick off the reporting system as soon as the simulation starts.

1.  **Event Init:** Standard GameInstance entry point.
2.  **Initialize Sentry:** This node starts the background threads and the `crashpad_handler`.
3.  **Set User/Context:** (Optional) We can use `Set Sentry User` to tag reports with the specific Rover ID or Operator name for easier filtering.

---

## **5. Symbolication: Turning Hex into Code**
When a packaged sim crashes, the log usually shows hex addresses (e.g., `0x00007ff...`). To see readable code:
1.  **Package with Debug Files:** Ensure **Include Debug Files** is checked in Unreal's Packaging settings.
2.  **Upload to Sentry:** Use the `sentry-cli` tool to upload the resulting `.pdb` (Windows) or `.debug` (Linux) files.
3.  **The Result:** Sentry will automatically map the crash to your source code: 
    *   *Before:* `RoveSoSimulator.exe!UnknownFunction [0x1234]`
    *   *After:* `ImuComponent.cpp: Line 142 in UpdateImuData()`

---

## **6. Testing the Pipeline (Hard Crash)**
To verify the system is working, we have implemented a "Nuke" function in the **`AppLauncherLibrary`**.

### **Triggering a Manual Segfault (C++)**
```cpp
void UAppLauncherLibrary::TriggerManualCrash()
{
    // Purposefully dereference a null pointer to force an OS Access Violation
    volatile int* p = nullptr;
    *p = 0xDEADBEEF; 
}
```

### **Verification Steps**
1.  Run the Simulator.
2.  Open the **Basestation UI** and click **"DEBUG: FORCE CRASH"**.
3.  Verify the sim terminates instantly.
4.  Check the **Discord Channel** for a notification.
5.  Open **Sentry.io** to view the full callstack and device state.

---

## **7. Linux Environment Troubleshooting**
*   **Permissions:** If the sim crashes but no report is sent, the `crashpad_handler` binary in your `Plugins/Sentry/Binaries/Linux` folder may lack execution rights. Run `chmod +x` on that file.
*   **IPv6:** If the engine hangs even with manual init, your system might be timing out on an IPv6 connection to Sentry. Temporarily disable IPv6 or force an IPv4 preference in your OS settings.
*   **SSL Certificates:** If the log shows `SSL Certificate Error`, ensure you have the `ca-certificates` package installed (`sudo pacman -S ca-certificates` on Arch).

---

## **8. Maintenance**
*   **Deduplication:** Sentry automatically groups identical crashes. If you see an issue with "1.2k events," do not investigate 1.2k logs—just fix the one line of code identified in the group.
*   **Cleaning the Database:** Sentry stores a local cache in the project folder under `.sentry-native`. If you experience weird startup behavior, deleting this folder is a safe way to reset the local state.