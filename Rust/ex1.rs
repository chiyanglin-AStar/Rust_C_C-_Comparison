fn main() {
    let ptr = Box::new(10); // Allocate memory on the heap
    println!("{}", ptr); // Automatically freed when `ptr` goes out of scope
}