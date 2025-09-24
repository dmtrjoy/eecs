# Introduction

**<span style="color:limegreen">Eecs</span>** is a simple data-driven game engine, written in modern C++.

## Objectives

The **eecs** engine has the following design goals:

- simple
- performant
- complete

## ECS

Entity-component-system, often shortened to ECS, is a software pattern for organizing program logic around the data it transforms. As the name suggests, ECS is composed of three fundamental concepts:

- **Entities:** Unique "things" in the system, often represented by an identifier.
- **Components:** Bundles of data attached to entities.
- **Systems:** Logic that processes entities with certain components.

For example, one entity might have `position` and `velocity` components, while another might have `position` and `health` components. 

ECS encourages modularity and clear separation between the program logic and the data it transforms. This makes it easier to grow, reuse, debug, and reason about your system over time. By storing related data together, ECS offers massive performance gains, particularly at scale, and greater opportunities for parallelism.




So... what is an ECS? An ECS, short for entity-component-system, is data-oriented architecture focused on maximizing performance, modularity, and separation of concerns.

The story of ECS is best told through example and from the beginning. Imagine you are tasked with building in your own engine. How would you go about it? Naturally, the first idea many of us have is to model the world as objects, each with its own set of data or behaviors. This approach is intuitive. Games are full of objects: players, enemies, platforms, etc. Let's start there.

Now, say you have a `Monster` class to represent an enemy in your game.

``` cpp
struct Monster {
    int health;
    int damage;
    bool alive;
};
```



```{doxygentypedef} eecs::entity
```
