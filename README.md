## Instructions to Run Tetris (C++)

1. Clone the repository:
    ```bash
    git clone https://github.com/Artdag05/Tetris.git
    ```

2. Navigate to the project directory:
    ```bash
    cd Tetris
    ```

3. Create a folder for the build files:
    ```bash
    mkdir build
    cd build
    ```

4. Generate build files using CMake:
    ```bash
    cmake .. -G "Unix Makefiles"
    ```

5. Build the project:
    ```bash
    make
    ```

   After the build completes, an executable file `tetris.exe` will be created in the `build` folder.

6. Run the application:
   - You can run the application by double-clicking `tetris.exe` from the `build` folder.

### Controls:

- **Rotate tetromino**: Press `Space`
- **Move right**: Press `→`
- **Move left**: Press `←`
