MiniKV file reading the RAM
### What does this project do?

The application enables storing, searching, deleting, and checking the count of entered data directly in the computer's RAM via a command line (REPL loop).

The user enters commands in real-time in the terminal:

* `SET <key> <value>` — stores data under a specific key.
* `GET <key>` — finds and returns the value associated with that key.
* `DEL <key>` — deletes the key and its value from memory.
* `SIZE` — returns the total number of stored items.
* `EXIT` — exits the program.

---

### Why is it made this way and what is its purpose?

1. **Professional Architecture (Separation of Concerns):** The code is divided into headers (`include/`), database logic (`src/store.cpp`), and the user interface (`src/main.cpp`). This structure mimics real-world working C++ projects, making it ideal for a GitHub portfolio.
2. **Memory Efficiency (`std::unordered_map`):** By using a hash table, search, insertion, and deletion operations are guaranteed with an extremely fast average complexity of $\mathcal{O}(1)$.
3. **Thread Safety (`std::shared_mutex`):** In real-world servers, multiple users access the database simultaneously. Using a shared mutex allows multiple threads to read data concurrently (`GET`), while writes and deletions (`SET`/`DEL`) are strictly exclusive. This prevents data races and system crashes.

---

### Detailed Code Breakdown by File

#### 1. `CMakeLists.txt` (Compilation Configuration)

This file tells the CMake tool how to build the project:

* Sets the standard to **C++17**.
* Includes the header directory (`include`).
* Links the `minikv` executable with source files (`src/main.cpp` and `src/store.cpp`) and includes the `pthread` system library for multi-threading support.

#### 2. `include/store.h` (Class Interface)

This header defines the `KeyValueStore` class:

* Hides the internal `std::unordered_map<std::string, std::string>` structure within the `private` section (encapsulation).
* Declares public methods (`set`, `get`, `remove`, `size`) that external code can use, protecting data from direct unauthorized modification.

#### 3. `src/store.cpp` (Database Logic)

Here, the methods declared in the header are implemented:

* **`set`**: Uses `std::unique_lock` for exclusive mutex locking during the insertion of a new key-value pair.
* **`get`**: Uses `std::shared_lock` to allow shared locking, permitting multiple concurrent reads without blocking.
* **`remove`**: Uses exclusive locking to safely delete an element from the map via `store_.erase(key)`.
* **`size`**: Returns the current size of the map using shared locking.

#### 4. `src/main.cpp` (Command Line Interface - REPL)

The main program that provides user interaction:

* Initializes an object of the `KeyValueStore` class.
* Runs an infinite `while` loop that reads input lines from the console (`std::getline`).
* Uses `std::stringstream` to parse the entered line into a command and arguments (key and value), passes them to the database, and prints the operation results to the terminal.

---
