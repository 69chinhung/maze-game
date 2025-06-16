# 作業7
# 迷宫终端游戏

![游戏截图](./screenshots/gameplay.png) 
![UML类图](./diagrams/uml_class_diagram.png)

## 项目描述
一个基于C++的终端迷宫游戏，具有碰撞检测和胜利/失败条件：
- 玩家（蓝色方块）需避开障碍物（红色）
- 到达终点（绿色方块）获胜
- 使用 ANSI 颜色代码渲染

## 功能特性
- [x] WASD 键盘控制
- [x] 实时碰撞检测
- [x] 胜利/失败条件判断
- [x] 终端彩色渲染

## 如何运行
### 编译
```bash
g++ -std=c++11 src/*.cpp -o maze_game
