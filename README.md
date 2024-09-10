# Snake Game

This is a console-based Snake game written in C. It brings back the classic gameplay experience with a few added features. The game runs directly in the terminal and is designed to be lightweight and simple, yet engaging.

## Features

- **Classic Snake Gameplay**: Control the snake to eat food and grow longer while avoiding walls and the snake's own body.
- **Simple Controls**: Use the arrow keys to navigate the snake in four directions.
- **Dynamic Difficulty**: The game speed increases as you progress, making it more challenging.
- **Score Tracking**: Keep track of your score and see how long you can survive!
- **Terminal-Based Graphics**: Uses simple ASCII characters for a retro, minimalistic feel.
- **Game Over Screen**: Displays a cool "Game Over" screen when the player loses.

## Controls

- **Arrow Keys**: Use `UP`, `DOWN`, `LEFT`, and `RIGHT` arrow keys to move the snake.
- **Pause**: Press `P` to pause the game.
- **Exit**: Press `ESC` to exit the game at any time.

## How to Run

To run the Snake game, you need a terminal that supports ANSI escape codes. Follow these steps:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/snake-game.git
   cd snake-game
   ```

2. **Compile the source code**:
   Use `gcc` or any compatible C compiler to build the game:
   ```bash
   gcc snake_game.c -o snake_game
   ```

3. **Run the game**:
   ```bash
   ./snake_game
   ```

## Game Mechanics

- **Snake Movement**: The snake is controlled using the arrow keys. It moves in the last direction pressed by the player.
- **Food Generation**: Food (represented by `X`) appears randomly on the screen. Eating food increases the snake's length by one unit.
- **Collision Detection**: The game ends if the snake collides with the wall or itself.
- **Scoring**: The score increases by 10 points for each piece of food eaten. The speed of the snake also increases with the score.

- **Graphics Handling**:
  - `gotoxy(int x, int y)`: Moves the cursor to position `(x, y)` in the terminal.
  - `clrscr()`: Clears the screen.
  - `refreshInfoBar(int score, int speed)`: Displays the current score and speed on the screen.

## Dependencies

- This game requires a terminal environment that supports ANSI escape codes. It has been tested primarily on Linux systems.
- You may need to adapt some code to run on Windows (e.g., replacing `unistd.h` with `windows.h` and using `getch()` from `<conio.h>`).

## Preview

![Screenshot from 2024-09-10 14-44-02](https://github.com/user-attachments/assets/44db03df-4cb7-4657-9d27-b0066c886996)

![Screenshot from 2024-09-10 14-47-37](https://github.com/user-attachments/assets/68b1a46a-8744-42ce-82d4-80e11dd74777)

![Screenshot from 2024-09-10 14-48-11](https://github.com/user-attachments/assets/4af81257-ab26-4ced-a8c7-292692559603)

