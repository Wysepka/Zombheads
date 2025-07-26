# Zombheads - Zombie Survival Game

A complete zombie survival game demo project built entirely in Unreal Engine 5, inspired by the classic Boxhead 2 Players Flash game from the 2000s. This project demonstrates advanced game development techniques including custom C++ implementation, AI crowd management, and performance optimization.

## 🎮 Project Overview

Zombheads is a third-person zombie survival game featuring:

- **Custom C++ Implementation**: All core game logic implemented in C++ for maximum performance
- **Advanced AI Crowd Management**: Handles 300+ simultaneous zombie agents using Unreal's Detour Crowd Manager
- **Custom Pawn Movement System**: Lightweight movement implementation for optimal performance
- **Slate UI Framework**: Complete HUD and menu system built with Unreal's Slate framework
- **Weapon System**: Multiple firearms with realistic mechanics and sound effects
- **Wave-based Gameplay**: Progressive difficulty with increasing zombie waves

## 🏗️ Project Status

**This project is fully functional and complete.** The developer worked on this project for 13 months while maintaining a full-time job, learning advanced Unreal Engine 5 concepts and C++ game development.

## 📁 Project Structure

```
wysepka-zombheads/
├── README.md
├── Zombheads.uproject
├── Config/                    # Engine configuration files
│   ├── DefaultEditor.ini
│   ├── DefaultEngine.ini
│   ├── DefaultGame.ini
│   ├── DefaultInput.ini
│   └── HoloLens/
├── Content/                   # Game assets and content
│   ├── Add-Ons/              # Third-party assets
│   │   └── Zombie_Voxels/    # Voxel zombie assets
│   ├── AI/                   # AI behavior trees and queries
│   ├── Animations/           # Character animations
│   │   ├── Player/          # Player character animations
│   │   └── Zombie/          # Zombie animations
│   ├── BPs/                  # Blueprint assets
│   │   ├── AI/              # AI-related blueprints
│   │   ├── Managers/        # Game management systems
│   │   ├── Player/          # Player-related blueprints
│   │   ├── UI/              # User interface blueprints
│   │   └── Weapons/         # Weapon system blueprints
│   ├── Data/                 # Data assets and configurations
│   ├── GFX/                  # Graphics and visual assets
│   │   ├── Blockouts/       # Level blockouts
│   │   ├── Materials/       # Material definitions
│   │   ├── Source/          # Source files (Blender, etc.)
│   │   └── UI/              # UI graphics
│   ├── Input/                # Input system configurations
│   ├── Levels/               # Game levels and maps
│   └── SFX/                  # Sound effects and audio
├── Source/                   # C++ source code
│   └── Zombheads/           # Main game module
│       ├── Private/         # Implementation files
│       │   ├── Actors/      # Actor implementations
│       │   ├── AI/          # AI system implementations
│       │   ├── Animations/  # Animation system
│       │   ├── Callbacks/   # Event callback systems
│       │   ├── Characters/  # Character implementations
│       │   ├── Data/        # Data management systems
│       │   ├── Managers/    # Game management systems
│       │   ├── Player/      # Player system implementations
│       │   └── UI/          # User interface implementations
│       └── Public/          # Header files
│           ├── Actors/      # Actor headers
│           ├── AI/          # AI system headers
│           ├── Animations/  # Animation system headers
│           ├── Callbacks/   # Event callback headers
│           ├── Characters/  # Character headers
│           ├── Data/        # Data management headers
│           ├── Managers/    # Game management headers
│           ├── Player/      # Player system headers
│           └── UI/          # User interface headers
└── ZombheadsEditorModule/   # Editor-specific module
```

## 🧠 Core Systems Architecture

### Game Management
- **Game Mode System**: Central game state management
- **Statistics Tracking**: Real-time game statistics and scoring
- **Wave Management**: Progressive difficulty system
- **Asset Loading**: Dynamic asset management system

### Player Systems
- **Custom Pawn Movement**: Lightweight movement implementation
- **Inventory System**: Weapon and item management
- **Vitality System**: Health and stamina management
- **Camera System**: Third-person camera with smooth following

### AI and Enemy Systems
- **Crowd Management**: Detour-based crowd simulation for 300+ agents
- **Enemy Spawning**: Dynamic enemy spawn system
- **Pathfinding**: Advanced navigation with collision avoidance
- **Behavior Trees**: Complex AI decision making

### Weapon Systems
- **Firearm Mechanics**: Realistic weapon handling
- **Projectile System**: Bullet physics and collision
- **Sound Integration**: Weapon sound effects
- **Ammunition Management**: Ammo tracking and reloading

### User Interface
- **Slate Framework**: Native Unreal UI system
- **HUD System**: Real-time game information display
- **Menu System**: Main menu and game over screens
- **Custom Widgets**: Specialized UI components

## 🎯 Key Features

### Performance Optimization
- **Custom Pawn Movement**: Replaces heavy Character class for better performance
- **Crowd Manager Integration**: Efficient handling of large numbers of AI agents
- **Memory Management**: Optimized asset loading and memory usage
- **Rendering Optimization**: Efficient graphics pipeline utilization

### AI Crowd System
- **300+ Simultaneous Agents**: Advanced crowd simulation
- **Collision Avoidance**: Intelligent pathfinding with obstacle avoidance
- **Performance Scaling**: Maintains frame rate with large crowds
- **Behavioral Complexity**: Individual agent decision making

### Custom C++ Implementation
- **Core Game Logic**: All gameplay systems in C++
- **Performance Critical Systems**: Optimized for real-time performance
- **Modular Architecture**: Clean separation of concerns
- **Extensible Design**: Easy to add new features

### User Interface
- **Slate Framework**: Native Unreal UI system for maximum performance
- **Real-time HUD**: Live game statistics and information
- **Responsive Design**: Adapts to different screen sizes
- **Custom Widgets**: Specialized UI components for game needs

## 🛠️ Technical Stack

### Core Technologies
- **Unreal Engine 5.2**: Latest engine version with advanced features
- **C++17**: Modern C++ for performance-critical systems
- **Slate Framework**: Native Unreal UI system
- **Detour Crowd Manager**: Advanced AI crowd simulation

### Key Modules
- **AIModule**: Advanced AI behavior and pathfinding
- **NavigationSystem**: Navigation mesh and pathfinding
- **EnhancedInput**: Modern input system
- **UMG**: User interface framework (limited use)

### External Assets
- **Zombie Voxels**: Third-party zombie character assets
- **Sound Effects**: Free sound assets from freesound.org
- **Blender Assets**: Custom 3D models and animations

## 🚀 Building and Running

### Prerequisites
- Unreal Engine 5.2 or higher
- Visual Studio 2019/2022 with C++ development tools
- Windows 10/11 (64-bit)

### Setup Instructions

1. **Clone the repository**
   ```bash
   git clone <repository-url>
   cd wysepka-zombheads
   ```

2. **Open the project**
   - Double-click `Zombheads.uproject`
   - Or open through Unreal Engine launcher

3. **Build the project**
   - Right-click on `Zombheads.uproject`
   - Select "Generate Visual Studio project files"
   - Open the generated `.sln` file
   - Build the solution

4. **Run the game**
   - Press F5 in Visual Studio, or
   - Use the "Play" button in Unreal Editor

### Working Build
A pre-built version is available at:
**https://drive.google.com/drive/folders/1Tt5LFsXJftc9qYB-8PHjZTHv95R-BrMJ?usp=drive_link**

## 🎮 Gameplay

### Controls
- **WASD**: Movement
- **Mouse**: Look/Aim
- **Left Click**: Fire weapon
- **1/2**: Switch weapons
- **Left Shift**: Sprint
- **B**: Switch to spectator mode

### Game Mechanics
- **Wave-based Survival**: Survive increasingly difficult zombie waves
- **Weapon Management**: Switch between pistol and shotgun
- **Stamina System**: Manage sprint stamina for tactical movement
- **Health System**: Monitor and maintain player health
- **Scoring System**: Track kills and survival time

## 📊 Performance Features

### Optimization Techniques
- **Custom Movement System**: Replaces heavy Character class
- **Efficient AI**: Crowd manager for large numbers of agents
- **Memory Management**: Optimized asset loading
- **Rendering Pipeline**: Efficient graphics utilization

### Scalability
- **300+ AI Agents**: Maintains performance with large crowds
- **Dynamic LOD**: Level of detail optimization
- **Efficient Pathfinding**: Optimized navigation calculations
- **Memory Optimization**: Reduced memory footprint

## 🎥 Media and Demonstrations

### YouTube Demo
[![Zombheads Demo](https://img.youtube.com/vi/qUiEi5Xrt18/0.jpg)](https://www.youtube.com/watch?v=qUiEi5Xrt18)

### Key Screenshots

#### Slate Editor Standalone Panel
![Slate Editor Panel](https://github.com/user-attachments/assets/088ebb0e-56bd-4dbf-aafe-56dcdccdc7ae)

The project includes a custom Slate editor panel for managing complex data structures with scrolling capabilities.

#### Custom Lightweight Pawn Movement
![Custom Movement System](https://github.com/user-attachments/assets/ba675981-ed1f-48f3-a2d3-dff38e8133ed)

Custom pawn movement system implemented for better performance compared to the standard Character class.

#### Managing 300+ AI Agents
![Crowd Management](https://github.com/user-attachments/assets/e6d6b8ed-d39c-4204-a982-ef0342023656)

Advanced crowd management system handling 300+ simultaneous zombie agents while maintaining performance.

#### AI Pathfinding Visualization
![AI Pathfinding](https://github.com/user-attachments/assets/fc46ec81-54c6-408b-b2c6-c2f555d8bd70)

Real-time visualization of AI pathfinding and crowd behavior.

## 🔧 Key Components

### Core Systems (`Source/Zombheads/`)

- **`ZombheadsGameModeBase.h/cpp`**: Main game mode and state management
- **`ComponentUtility.h/cpp`**: Utility functions for component management
- **`LogClearer.h/cpp`**: Logging and debugging utilities

### Actor Systems (`Source/Zombheads/Private/Actors/`)

- **`Enemy/`**: Zombie AI and enemy management
- **`Spawner/`**: Enemy spawning and wave management
- **`Components/`**: Reusable actor components

### Player Systems (`Source/Zombheads/Private/Player/`)

- **`PlayerPawn.cpp`**: Main player character implementation
- **`CharacterMovement.cpp`**: Custom movement system
- **`Inventory/`**: Weapon and item management
- **`Camera/`**: Third-person camera system

### AI Systems (`Source/Zombheads/Private/AI/`)

- **`EnemyCrowdFollowingComponent.cpp`**: Crowd management implementation
- **`EnemyController.cpp`**: AI behavior and decision making
- **`EnemyZombie.cpp`**: Zombie-specific AI logic

### UI Systems (`Source/Zombheads/Private/UI/`)

- **`HUDGameplay.cpp`**: Main HUD implementation
- **`Slate/HUD/`**: Slate-based UI components
- **`Widgets/`**: Custom UI widgets

## 📈 Performance Considerations

### Optimization Features
- **Custom Pawn Movement**: Replaces heavy Character class
- **Crowd Manager Integration**: Efficient AI crowd simulation
- **Memory Management**: Optimized asset loading and usage
- **Rendering Optimization**: Efficient graphics pipeline

### Known Limitations
- **AI Pathfinding Jitter**: Occasional path switching in dense crowds
- **Memory Usage**: Large asset library requires significant RAM
- **Build Size**: Complete project with assets is substantial

## 🐛 Known Issues

The project has some minor issues:

1. **AI Pathfinding Jitter**: Zombies may occasionally switch paths rapidly in dense crowds
2. **Editor Module**: Separate editor module required due to engine limitations
3. **Performance Scaling**: Very large crowds may impact performance on lower-end systems

## 📚 Learning Outcomes

This project demonstrates advanced Unreal Engine 5 development:

- **C++ Game Development**: Extensive use of modern C++ in Unreal
- **AI Crowd Management**: Advanced crowd simulation techniques
- **Performance Optimization**: Custom systems for better performance
- **Slate UI Framework**: Native Unreal UI development
- **Game Architecture**: Modular and extensible design patterns

## 🤝 Contributing

This project serves as a learning resource for:

- Unreal Engine 5 C++ development
- AI crowd management and pathfinding
- Performance optimization techniques
- Game architecture and design patterns
- Slate UI framework implementation

## 📄 License

This project is provided as-is for educational purposes. The developer retains all rights to the codebase and assets.

## 🙏 Acknowledgments

- **Unreal Engine Community**: Forums and documentation
- **Freesound.org**: Free sound effects
- **Zombie Voxels**: Character assets
- **Unreal Engine Discord Fellowship**: Technical support and guidance

## 📞 Contact

For more information or questions about this project:
- **Email**: wysepkawyspa@gmail.com
- **GitHub**: [Project Repository]

---

*This README documents the project structure and implementation details for educational purposes. The project demonstrates advanced Unreal Engine 5 development techniques and serves as a comprehensive example of modern game development practices.* 
