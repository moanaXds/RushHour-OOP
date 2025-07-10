# 🎮 Rush Hour - 2D City Simulation Game

**Rush Hour** is a simple yet engaging 2D top-down simulation game developed in **C++** using **SFML**, **OpenGL (GLUT)**, and other multimedia libraries. The player takes on the role of a taxi driver navigating through a city to complete tasks like delivering packages or picking up passengers—all while managing fuel, time, and avoiding collisions.

---

## 🧾 Overview

- **Title:** Rush Hour
- **Developer:** Muanna Hamid
- **Language:** C++
- **Libraries Used:**
  - **SFML** for audio (music and sound effects)
  - **OpenGL/FreeGLUT** for rendering graphics
  - **Standard C++ Libraries** for logic and file handling
- **Gameplay:** Drive your taxi through a city grid, avoid obstacles, refuel at gas stations, and complete missions before time runs out or fuel depletes.

---

## ✅ Screenshots 

![game-board](https://github.com/user-attachments/assets/2ed511d2-e39a-4121-bea7-67a70caa3461)
![Menu](https://github.com/user-attachments/assets/c575ca54-1496-41d9-87b4-10d64060c092)
![leaderboard](https://github.com/user-attachments/assets/7984d079-e50a-4531-8294-8cd74e106cd4)

---

## 🕹️ Gameplay Features

- 🚖 Player-controlled taxi with arrow key movement.
- 🚗 AI-driven cars moving along fixed paths.
- 💰 Earn money by completing tasks:
  - Pick up and drop off passengers.
  - Deliver packages to specified locations.
- ⛽ Fuel management system with refueling stations.
- ⏱ Time-limited gameplay (3 minutes).
- 📊 Score tracking and leaderboard system.
- 🧱 Collision detection with buildings, trees, and other vehicles.
- 🎵 Background music and collision sound effects.

---

## 📁 Project Structure

```
Rush-Hour/
├── README.md
├── Makefile
├── Rules To Play.md
├── install-libraries.sh
├── CImg.h
├── game.cpp
├── recovery.cpp
├── util.cpp
├── util.h
├── game.o
├── util.o
```


## 📜 How to Play

For detailed instructions on controls, objectives, and scoring system, refer to [Rules To Play.md](Rules%20To%20Play.md).

---

## 🎨 Graphics & Sound

- **Graphics:** Rendered using OpenGL via GLUT.
- **Sound:** Background music and collision sounds powered by SFML.

---

## 🧪 Testing

If something goes wrong or the game crashes, you can use `recovery.cpp` to debug or restore saved states.

---

## 🤝 Contributing

Contributions are welcome! Feel free to fork the repository and submit pull requests for bug fixes, new features, or improvements.

---

## 📄 License

This project is reserved under copyright. For usage rights or modifications, please contact the developer.

---

## 👥 Developer Contact

- **Muanna Hamid**
- Email: i242593@isb.nu.edu.pk

