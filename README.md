# 🧠 Philosophers - 42 Abu Dhabi

Welcome to the **Philosophers** project! This project simulates the classic synchronization problem involving philosophers who alternately think and eat. It serves as a deep dive into multithreading and process management in C, focusing on concurrent execution and resource sharing.

## 📜 Table of Contents

- [Introduction](#introduction)
- [Project Objectives](#project-objectives)
- [Concept](#concept)
- [Compilation](#compilation)
- [How to Run](#how-to-run)
- [Arguments](#arguments)
- [Bonus Part](#bonus-part)
- [Notes](#notes)
- [Contributors](#contributors)

## 🌟 Introduction

The **Philosophers** project is part of the 42 curriculum, challenging students to implement a solution for the well-known *Dining Philosophers Problem*. In this problem, multiple philosophers sit at a table and attempt to eat, but they need shared resources (forks) to do so. The project explores concepts such as thread synchronization, mutexes, semaphores, and deadlock prevention.

## 🎯 Project Objectives

- Understand and implement multithreading or multiprocessing in C.
- Manage shared resources using synchronization techniques (mutexes or semaphores).
- Avoid deadlocks, race conditions, and starvation.
- Develop a solution that works with multiple philosophers in a concurrent environment.

## 🤔 Concept

Five philosophers sit at a circular table. Each philosopher has a fork on either side. They alternate between thinking and eating, but can only eat if they have both forks (left and right). The challenge is to synchronize their actions so that no philosopher starves or causes a deadlock.

- **Philosophers' states**: 
  - Thinking 🧠
  - Eating 🍽️
  - Waiting for forks 🍴
- **Resources**: Shared forks that must be carefully allocated to avoid conflicts.

## ⚙️ Compilation

To compile the project, simply run the following command:

```bash

## How to run
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
