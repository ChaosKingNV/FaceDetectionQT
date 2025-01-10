# FaceDetectionQT: Face Detection and Attendance System

FaceDetectionQT is a simple yet powerful application for face detection and attendance management. Using a combination of a pre-trained model and Haar Cascade classifiers, this system detects faces, counts the number of people, and saves their photos. The application also features a user-friendly graphical interface built with Qt in C++.

## Overview

FaceDetectionQT is designed to:

- Detect faces in real-time using a trained model and Haar Cascade classifiers.
- Count the number of detected individuals.
- Save photos of detected individuals for attendance records.
- Provide an intuitive GUI for ease of use.

## Features

- **Real-Time Face Detection:** Utilizes a camera feed to detect faces.
- **Attendance Management:** Automatically records attendance by saving photos and counting individuals.
- **GUI Built with Qt:** Offers a clean and interactive interface for users.
- **Photo Saving:** Captures and stores images of detected individuals in a specified directory.

## Prerequisites

To compile and run the project, you will need:

- A C++ compiler (e.g., GCC, Clang, or MSVC)
- OpenCV library installed on your system
- Qt framework installed on your system

## Getting Started

1. Clone this repository:
   ```bash
   git clone https://github.com/ChaosKingNV/FaceDetectionQT.git
   cd FaceDetectionQT
   ```

2. Install OpenCV and Qt on your system if not already installed. Refer to the [OpenCV installation guide](https://docs.opencv.org/master/df/d65/tutorial_table_of_content_introduction.html) and [Qt installation guide](https://doc.qt.io/qt-5/gettingstarted.html).

3. Build the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. Deploy the application (Windows):
   ```bash
   .\windeployqt.exe "C:\path\to\FaceDetectionQT\build\FaceDetectionQT.exe"
   ```

5. Run the application:
   ```bash
   ./FaceDetectionQT
   ```

## Usage

1. Launch the application.
2. Select the input source (webcam or video file) via the GUI.
3. The system will detect faces, count individuals, and save their photos automatically.
4. View attendance records in the designated folder.

## Learning Resources

Here are some resources for learning about the tools and technologies used:

- [OpenCV Documentation](https://docs.opencv.org/)
- [Qt Documentation](https://doc.qt.io/qt-5/)
- [Haar Cascade Classifier](https://docs.opencv.org/master/d7/d8b/tutorial_py_face_detection.html)
---

Happy coding and exploring face detection with FaceDetectionQT!
