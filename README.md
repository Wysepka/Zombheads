# Zombheads
Demo Project, Windows inspired by Boxhead 2 Players Flash game made in '00
Made entirelly in Unreal Engine 5, uses Slate built in UI framework for all HUD elements,
and Crowd Manager Detour built-in engine pathfinding algorithm for AI for handling complex AI collisions,
i.e. more than 300 simultaneously Agents, while maintaining reasonable FPS.

## Working Build
### https://drive.google.com/drive/folders/1Tt5LFsXJftc9qYB-8PHjZTHv95R-BrMJ?usp=drive_link

# YouTube Link in Image below (click!)
[![Zombheads Demo](https://img.youtube.com/vi/qUiEi5Xrt18/0.jpg)](https://www.youtube.com/watch?v=qUiEi5Xrt18)

## Slate Editor Standalone Panel
![image](https://github.com/user-attachments/assets/088ebb0e-56bd-4dbf-aafe-56dcdccdc7ae)
For learning purposes project composes Slate C++ standalone panel window for selecting
assigning and removing "complex" struct with different data, this was such way because
other ways did not include scrolling.

## Custom-Lighweight Pawn Movement
![image](https://github.com/user-attachments/assets/ba675981-ed1f-48f3-a2d3-dff38e8133ed)
Due to the heavy impact on performance while using Character class from Unreal, I have made
my own Pawn and implemented logic

https://forums.unrealengine.com/t/apawn-custom-aicontroller-and-ucrowdfollowingcomponent-c-setup-for-detour-crowdmanager/1598053

## Managing more than 300 agents
![UnrealEditor-Win64-DebugGame_bF8ftpfD98](https://github.com/user-attachments/assets/e6d6b8ed-d39c-4204-a982-ef0342023656)
Due to the nature of not-so-good implementation by Unreal Engine Pawn Movement is sometimes Jittering
because AI is switching paths every frame
![UnrealEditor-Win64-DebugGame_ZeYF4VMeIS](https://github.com/user-attachments/assets/fc46ec81-54c6-408b-b2c6-c2f555d8bd70)

Also project implements seperate Module for Editor Stuff, due to the error inside of Engine
and help from one of the unreal-engine-discord-fellowship i could not fix it and
implement seperate module for UI stuff

For more informations contact me wysepkawyspa[D-O-T]gmail.com
