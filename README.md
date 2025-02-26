# Column Store DBMS

## Project Structure
```
project-root/
│-- src/
│   ├── main.cpp          # Entry point of the application
│   ├── createDB.cpp      # Implementation of database creation
│   ├── createDB.h        # Header file for createDB.cpp
│-- xml/
│   ├── sample_instance.xml # Example XML file
│-- include/              # Any required header files
│-- lib/                  # External libraries (if needed)
│-- Makefile (optional)   # Build automation
```

## Dependencies
To compile and run this project, ensure you have the following installed:
- **C++17 or later** (Recommended: GCC or Clang)
- **TinyXML-2** (for parsing XML files)
- **CMake** (Optional, for build automation)

### Installing Dependencies (macOS/Linux)
```sh
# Install TinyXML-2
brew install tinyxml2  # For macOS
sudo apt-get install libtinyxml2-dev  # For Ubuntu/Debian
```

## Compilation & Building

### DataBase Creation

#### Using g++
```sh
g++ -std=c++17 -o CreateDB src/main.cpp src/createDB.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -ltinyxml2
```

#### Using CMake (Optional)
If you prefer using CMake, create a `CMakeLists.txt` file and run:
```sh
mkdir build && cd build
cmake ..
make
```

### Running the Program
After building the executable, run the program with an XML file path as an argument:
```sh
./CreateDB xml/sample_instance.xml
```

### Expected Output
- If successful:
  ```
  Database created successfully.
  ```
- If an error occurs:
  ```
  Failed to create the database.
  ```

## Notes
- Ensure the XML file exists at the specified path before running the program.
- Modify `createDB.cpp` to implement custom database creation logic as needed.

## Troubleshooting
### **Error: TinyXML-2 Not Found**
Make sure the library is installed and correctly linked:
```sh
echo "Checking TinyXML-2..."
ls /usr/include/tinyxml2.h || ls /opt/homebrew/include/tinyxml2.h
```
If missing, install it via `brew install tinyxml2` or `sudo apt-get install libtinyxml2-dev`.

### **Permission Issues**
If you see `Permission denied`, run:
```sh
chmod +x CreateDB
```

## Future Improvements
- Add logging functionality for debugging.
- Implement a proper database storage mechanism.
- Improve XML parsing efficiency.

---
### **Author**: Pradyun Devarakonda

