# C++ Particle System

A real-time colorful particle system built in C++ using SFML. Thousands of particles explode from your mouse cursor with gravity, fading trails, and random colors.

## Features

- Particles spawn at the mouse cursor every frame
- Each particle flies outward in a random direction at a random speed
- Gravity pulls particles downward over time
- Particles fade out smoothly as their lifetime expires
- Semi-transparent trail effect using layered rendering
- Fully random RGB colors per particle

## How To Compile & Run

Make sure you have SFML installed and a C++ compiler (g++ recommended).

```bash
g++ -o particles main.cpp -lsfml-graphics -lsfml-window -lsfml-system
./particles
```

On Windows:
```bash
g++ -o particles main.cpp -lsfml-graphics -lsfml-window -lsfml-system
particles.exe
```

## Built With

- C++
- SFML
- STL

## Author

**masteroforder** — [github.com/masteroforder](https://github.com/masteroforder)
