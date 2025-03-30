# Rust_C_C-_Comparison

### Smart Pointer 

- [Smart Pointers in C++ geekforgeek](https://www.geeksforgeeks.org/smart-pointers-cpp/)
- [Smart Pointer in C++](https://medium.com/@lulululu_ej/smart-pointer-in-c-58d55dbace1f)

# **🚀 Summary of Key Differences**
| Feature              | C/C++ | Rust |
|----------------------|-------|------|
| **Memory Safety**    | Manual (`new/delete`) | Automatic (`ownership`) |
| **Null Pointers**    | Possible (`nullptr`) | Not possible (`Option<T>`) |
| **Concurrency**      | Possible Data Races | Safe with `Mutex` & `Arc` |
| **Error Handling**   | Exceptions (`try/catch`) | `Result<T, E>` Enum |
| **Type Casting**     | Implicit | Explicit (`as`) |
| **Templates vs Macros** | Templates | Macros (`macro_rules!`) |
| **Mutability**       | Mutable by default | Immutable by default |

### 1. **Memory Safety**
   - **C/C++**: Manual memory management, which can lead to memory leaks, dangling pointers, and buffer overflows.
   - **Rust**: Ownership system ensures memory safety at compile time without a garbage collector.

#### Example: Memory Management

**C++ Example (Manual Memory Management):**
```cpp
#include <iostream>

int main() {
    int* ptr = new int(10); // Allocate memory
    std::cout << *ptr << std::endl;
    delete ptr; // Manually free memory
    // ptr is now a dangling pointer
    return 0;
}
```

**Rust Example (Ownership System):**
```rust
fn main() {
    let ptr = Box::new(10); // Allocate memory on the heap
    println!("{}", ptr); // Automatically freed when `ptr` goes out of scope
}
```
```rust
fn main() {
    let x = 5;
    let y = &x;
    println!("{}",x);
    println!("{}",y);
    println!("{}",*y);
    assert_eq!(5, x);
    assert_eq!(5, *y);
}
```
## **1️⃣ Memory Safety (No Null, No Dangling Pointers)**
### **C++ Example (Dangling Pointer Issue)**
```cpp
#include <iostream>
using namespace std;

int* getPointer() {
    int x = 10;
    return &x; // Returning a pointer to a local variable (undefined behavior)
}

int main() {
    int* p = getPointer();
    cout << *p << endl; // Undefined behavior: accessing a dangling pointer
}
```

### **Rust Example (Safe Memory Management)**
```rust
fn get_value() -> i32 {
    let x = 10;
    x // Ownership ensures safe return
}

fn main() {
    let value = get_value();
    println!("{}", value);
}
```
✅ **Rust prevents returning a reference to a local variable that goes out of scope.**  

---


### 2. **Null Pointers**
   - **C/C++**: Use of `NULL` or `nullptr`, which can lead to null pointer dereferencing.
   - **Rust**: No null pointers; instead, Rust uses `Option<T>` to handle the absence of a value.

#### Example: Handling Null Values

**C++ Example (Null Pointer):**
```cpp
#include <iostream>

void print(int* ptr) {
    if (ptr) {
        std::cout << *ptr << std::endl;
    } else {
        std::cout << "Pointer is null" << std::endl;
    }
}

int main() {
    int* ptr = nullptr;
    print(ptr); // Potential null pointer dereference
    return 0;
}
```

**Rust Example (Option<T>):**
```rust
fn print(ptr: Option<&i32>) {
    match ptr {
        Some(value) => println!("{}", value),
        None => println!("Pointer is null"),
    }
}

fn main() {
    let ptr: Option<&i32> = None;
    print(ptr); // Safe handling of null-like state
}
```

## **2️⃣ Ownership & Borrowing vs Manual Memory Management**
### **C++ Example (Manual Memory Management)**
```cpp
#include <iostream>

void allocateMemory() {
    int* ptr = new int(10);
    std::cout << *ptr << std::endl;
    delete ptr; // Must manually free memory
}

int main() {
    allocateMemory();
}
```

### **Rust Example (Ownership & Borrowing)**
```rust
fn allocate_memory() {
    let value = 10; // Rust handles memory automatically
    println!("{}", value);
}

fn main() {
    allocate_memory();
}
```
✅ **Rust’s ownership system prevents memory leaks and use-after-free errors.**

---

### 3. **Concurrency**
   - **C/C++**: Concurrency is managed using threads, mutexes, and condition variables, which can lead to data races.
   - **Rust**: Ownership and borrowing rules prevent data races at compile time.

#### Example: Concurrency

**C++ Example (Data Race):**
```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int shared_data = 0;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        mtx.lock();
        ++shared_data;
        mtx.unlock();
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Shared data: " << shared_data << std::endl;
    return 0;
}
```

**Rust Example (Safe Concurrency):**
```rust
use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    let data = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..2 {
        let data = Arc::clone(&data);
        let handle = thread::spawn(move || {
            for _ in 0..100000 {
                let mut data = data.lock().unwrap();
                *data += 1;
            }
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Shared data: {}", *data.lock().unwrap());
}
```

## **3️⃣ Data Races & Concurrency**
### **C++ Example (Possible Data Race)**
```cpp
#include <iostream>
#include <thread>

int counter = 0;

void increment() {
    for (int i = 0; i < 100000; i++) {
        counter++; // Data race: multiple threads modifying shared memory
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    
    t1.join();
    t2.join();

    std::cout << counter << std::endl; // Output is unpredictable
}
```

### **Rust Example (Safe Concurrency with Mutex)**
```rust
use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    let counter = Arc::new(Mutex::new(0));

    let handles: Vec<_> = (0..2).map(|_| {
        let counter = Arc::clone(&counter);
        thread::spawn(move || {
            let mut num = counter.lock().unwrap();
            for _ in 0..100000 {
                *num += 1;
            }
        })
    }).collect();

    for handle in handles {
        handle.join().unwrap();
    }

    println!("{}", *counter.lock().unwrap()); // Always correct
}
```
✅ **Rust prevents data races at compile time using `Arc<Mutex<T>>`.**

---

### 4. **Error Handling**
   - **C/C++**: Error handling is typically done using return codes or exceptions.
   - **Rust**: Uses `Result<T, E>` for recoverable errors and `panic!` for unrecoverable errors.

#### Example: Error Handling

**C++ Example (Return Codes):**
```cpp
#include <iostream>

bool divide(int a, int b, int& result) {
    if (b == 0) {
        return false; // Error
    }
    result = a / b;
    return true; // Success
}

int main() {
    int result;
    if (!divide(10, 0, result)) {
        std::cout << "Division by zero!" << std::endl;
    } else {
        std::cout << "Result: " << result << std::endl;
    }
    return 0;
}
```

**Rust Example (Result<T, E>):**
```rust
fn divide(a: i32, b: i32) -> Result<i32, &'static str> {
    if b == 0 {
        Err("Division by zero!")
    } else {
        Ok(a / b)
    }
}

fn main() {
    match divide(10, 0) {
        Ok(result) => println!("Result: {}", result),
        Err(e) => println!("Error: {}", e),
    }
}
```

## **4️⃣ Error Handling: Exceptions vs Result & Option**
### **C++ Example (Exceptions)**
```cpp
#include <iostream>
#include <stdexcept>

int divide(int a, int b) {
    if (b == 0) throw std::runtime_error("Division by zero!");
    return a / b;
}

int main() {
    try {
        std::cout << divide(10, 0) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
```

### **Rust Example (Result Enum)**
```rust
fn divide(a: i32, b: i32) -> Result<i32, String> {
    if b == 0 {
        Err("Division by zero!".to_string())
    } else {
        Ok(a / b)
    }
}

fn main() {
    match divide(10, 0) {
        Ok(result) => println!("{}", result),
        Err(e) => println!("Error: {}", e),
    }
}
```
✅ **Rust forces you to handle errors explicitly, reducing runtime crashes.**

---

### 5. **Move Semantics**
   - **C++**: Move semantics are introduced in C++11, but they can still lead to use-after-move errors.
   - **Rust**: Move semantics are the default, and the compiler ensures that moved values are not used again.

#### Example: Move Semantics

**C++ Example (Move Semantics):**
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = std::move(v1); // Move v1 to v2

    std::cout << "v1 size: " << v1.size() << std::endl; // v1 is now in a valid but unspecified state
    std::cout << "v2 size: " << v2.size() << std::endl;

    return 0;
}
```

**Rust Example (Move Semantics):**
```rust
fn main() {
    let v1 = vec![1, 2, 3];
    let v2 = v1; // v1 is moved to v2

    // println!("v1: {:?}", v1); // This would cause a compile-time error
    println!("v2: {:?}", v2);
}
```
## **5️⃣ Null Pointers vs Option Type**
### **C++ Example (Null Pointer Dereference)**
```cpp
#include <iostream>

int* getPointer(bool valid) {
    if (valid) return new int(10);
    return nullptr; // Unsafe: null pointer possibility
}

int main() {
    int* ptr = getPointer(false);
    std::cout << *ptr << std::endl; // Segmentation fault
}
```

### **Rust Example (Option Type)**
```rust
fn get_value(valid: bool) -> Option<i32> {
    if valid { Some(10) } else { None }
}

fn main() {
    match get_value(false) {
        Some(val) => println!("{}", val),
        None => println!("No value found"),
    }
}
```
✅ **Rust eliminates null pointers by using `Option<T>`.**

---

### 6. **Lifetimes**
   - **C/C++**: No built-in support for tracking the lifetimes of references, which can lead to dangling references.
   - **Rust**: Lifetimes are explicitly annotated, ensuring that references are always valid.

#### Example: Lifetimes

**C++ Example (Dangling Reference):**
```cpp
#include <iostream>

int* create_int() {
    int x = 10;
    return &x; // Dangling reference
}

int main() {
    int* ptr = create_int();
    std::cout << *ptr << std::endl; // Undefined behavior
    return 0;
}
```

**Rust Example (Lifetimes):**
```rust
fn create_int<'a>() -> &'a i32 {
    let x = 10;
    &x // Compile-time error: `x` does not live long enough
}

fn main() {
    let ptr = create_int();
    println!("{}", ptr);
}
```
## **6️⃣ No Implicit Type Casting**
### **C++ Example (Implicit Casting Can Cause Bugs)**
```cpp
#include <iostream>

void printNumber(double num) {
    std::cout << num << std::endl;
}

int main() {
    printNumber(10); // Implicitly converts int to double
}
```

### **Rust Example (No Implicit Casting)**
```rust
fn print_number(num: f64) {
    println!("{}", num);
}

fn main() {
    let x: i32 = 10;
    print_number(x as f64); // Must explicitly convert
}
```
✅ **Rust forces explicit type conversion, preventing unintended behavior.**

---


### 7. **Macros**
   - **C/C++**: Preprocessor macros are text-based and can lead to hard-to-debug code.
   - **Rust**: Macros are more powerful and hygienic, with better integration into the language.

#### Example: Macros

**C++ Example (Preprocessor Macro):**
```cpp
#include <iostream>

#define SQUARE(x) ((x) * (x))

int main() {
    int x = 5;
    std::cout << SQUARE(x + 1) << std::endl; // Outputs 11, not 36
    return 0;
}
```

**Rust Example (Macro):**
```rust
macro_rules! square {
    ($x:expr) => {{
        $x * $x
    }};
}

fn main() {
    let x = 5;
    println!("{}", square!(x + 1)); // Outputs 36
}
```
## **7️⃣ Macros vs Templates**
### **C++ Example (Templates)**
```cpp
#include <iostream>

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(3, 4) << std::endl;
}
```

### **Rust Example (Macros)**
```rust
macro_rules! add {
    ($a:expr, $b:expr) => {
        $a + $b
    };
}

fn main() {
    println!("{}", add!(3, 4));
}
```
✅ **Rust macros allow flexible code generation at compile time.**

---

### 8. **Immutable by Default**
   - **C/C++**: Variables are mutable by default.
   - **Rust**: Variables are immutable by default, and mutability must be explicitly declared.

#### Example: Immutability

**C++ Example (Mutable by Default):**
```cpp
#include <iostream>

int main() {
    int x = 5;
    x = 10; // Mutable by default
    std::cout << x << std::endl;
    return 0;
}
```

**Rust Example (Immutable by Default):**
```rust
fn main() {
    let x = 5;
    // x = 10; // This would cause a compile-time error
    let mut y = 5; // Explicitly mutable
    y = 10;
    println!("{}", y);
}
```
## **8️⃣ Immutable by Default**
### **C++ Example (Mutable by Default)**
```cpp
#include <iostream>

int main() {
    int x = 10;
    x = 20; // Allowed
    std::cout << x << std::endl;
}
```

### **Rust Example (Immutable by Default)**
```rust
fn main() {
    let x = 10;
    // x = 20; // Error: cannot mutate immutable variable
    println!("{}", x);
}
```
✅ **Rust variables are immutable by default, ensuring safer code.**

---

### 9. **Pattern Matching**
   - **C/C++**: Limited support for pattern matching (e.g., `switch` statements).
   - **Rust**: Powerful pattern matching with `match` expressions.

#### Example: Pattern Matching

**C++ Example (Switch Statement):**
```cpp
#include <iostream>

int main() {
    int x = 2;

    switch (x) {
        case 1:
            std::cout << "One" << std::endl;
            break;
        case 2:
            std::cout << "Two" << std::endl;
            break;
        default:
            std::cout << "Other" << std::endl;
    }

    return 0;
}
```

**Rust Example (Pattern Matching):**
```rust
fn main() {
    let x = 2;

    match x {
        1 => println!("One"),
        2 => println!("Two"),
        _ => println!("Other"),
    }
}
```

### 10. **Trait System vs. Inheritance**
   - **C++**: Uses inheritance and virtual functions for polymorphism.
   - **Rust**: Uses traits for polymorphism, which are more flexible and do not require inheritance.

#### Example: Polymorphism

**C++ Example (Inheritance):**
```cpp
#include <iostream>

class Animal {
public:
    virtual void speak() const = 0;
};

class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Woof!" << std::endl;
    }
};

int main() {
    Animal* animal = new Dog();
    animal->speak();
    delete animal;
    return 0;
}
```

**Rust Example (Traits):**
```rust
trait Animal {
    fn speak(&self);
}

struct Dog;

impl Animal for Dog {
    fn speak(&self) {
        println!("Woof!");
    }
}

fn main() {
    let dog = Dog;
    dog.speak();
}
```

### Conclusion
Rust provides several advantages over C/C++ in terms of memory safety, concurrency, and modern language features. However, it also comes with a steeper learning curve due to its strict compile-time checks and unique features like ownership and borrowing. Understanding these differences is crucial when transitioning from C/C++ to Rust.
