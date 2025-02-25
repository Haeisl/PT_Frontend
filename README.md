Epilepsy Planning Tool - Frontend
=================================

**Important:** Before following the instructions step by step, please read through the entire README.

---

## Overview:
This Unreal Engine 5 frontend handles visualization of a patient's head mesh, placement of a region of interest (ROI) in and electrodes on that mesh. It also handles the interpolation of electrode positions between successful simulations and visualizes results in the ROI using colormaps and histograms.

---

## Prerequisites:
To use or further develop this project, please ensure you have the following dependencies installed.
- **Unreal Engine:** For further development of the tool.
    - Detailed installation instructions can be found [here](https://dev.epicgames.com/documentation/en-us/unreal-engine/installing-unreal-engine). The version used for development up until now was **5.3.2**.
- **Visual Studio:** For further development of the tool.
    - Detailed installation instructions and useful tools can be found [here](https://dev.epicgames.com/documentation/en-us/unreal-engine/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine) and [here](https://learn.microsoft.com/en-us/visualstudio/gamedev/unreal/get-started/vs-tools-unreal-install) respectively.
- **Python:** Required for executing scripts at runtime.
    - **Matplotlib:** Required for creating histograms in the interpolation screen.

---

## Setup:
There are two possible use cases for which you may want to open and interact with this frontend.

1. Normal usage of the program in its current form
2. Development

The following walks you through the steps on how to open the project for both use cases.

### Normal Usage:
1. Find the `EpilepsyTherapyPlanningTool.zip` file and unpack it.
2. Navigate into the `Windows` subdirectory.
3. Execute `PlanningTool_ET.exe`.


### Development:
1. With **Unreal Engine 5** installed, right-click on `PlanningTool_ET.uproject` and click on "Generate Visual Studio project files".
2. This will create a file called `PlanningTool_ET.sln`.
    > **Important:** Visual Studio solution files are specific to the current user / developer. You should always generate your own solution file, even if there is already one present in the GitHub repository.
3. Open `PlanningTool_ET.sln` using **Visual Studio**.
4. Launch the Unreal Engine 5 editor through Visual Studio by clicking on either green triangle as shown below.
![Visual Studio launch UE Editor](./pictures/VS_launch_UE_editor.png)

---

## Walkthrough:
Upon launching the program (both packaged project and in-editor-play) you will be presented with three buttons, associated with three distinct use-cases of the program.

### Server Management Screen:
Enter the IP and Port of a (local) server to connect to and confirm by clicking on "Save".
Click on "Refresh" to view whether the server could be reached.
From here on out we assume a working connection to the backend.

### Configuration Screen:
1. Enter a Patient ID to load the head mesh of the corresponding patient from the backend.
2. Define and place a grid of electrodes (represented as points as of now) on the head mesh.
3. Name the grid of electrodes using the "Config ID:" field and click on "Send" to transmit this data to the backend.
4. Define and position a ROI in the mesh.
5. Name the ROI using the "ROI ID:" field and click on "Send to transmit this data to the backend.
6. Click on "Run Simulation" to run the simulations defined by the electrode positions and ROI.

### Interpolation Screen:
1. Enter Patient, Config and ROI IDs of a completed simulation ensemble and click "Load".
2. On the plane above the electrode positions, click or drag where you would like to interpolate between the simulated electrodes.
3. Define percentiles and click on "Update Color" to apply the corresponding colormap to the field magnitude data inside the ROI.
4. Enter a number of bins and click on "Histogram" to view a logarithmic histogram of the currently displayed data.

---

### Miscellaneous:

Further development of this frontend is only advised for people with experience in UE5 development, especially with Blueprints.

If you try to resolve the faulty colormap values, try the JSON converter classes and associated Blueprints.

If you want to add calculations regarding surface normals, look into the Procedural Mesh components in the mesh actor classes.

<!--

Old Readme
# **SETUP:**
1. Unpack the PlanningTool_Build.zip file
2. Start the application with an double click on the PlanningTool_ET.exe

# **Configuration:**
1. Enter Patient ID and click load
2. Move the Grid to the desired position
3. Modify Grid by using the slider and text box in Grid Configuration
4. Enter Configuration ID and click on the "Send" button to save the grid configuration
5. Move the ROI to desired position
6. Modify ROI by using the text boxes in ROI Configuration
7. Enter ROI ID and click on the "Send" button to save the ROI configuration
8. Proceed in Backend to the next step (Simulation/Processing etc.)

# **Interpolation:**
1. Enter Patient ID. Config ID and ROI ID and clicl load
2. Move electrode to desired position (with mouse or per local coordinates in the text boxes in the interpolation configuration)
3. Enter the interpolation ID and click on the "Send" button to save the electrode configuration -->
