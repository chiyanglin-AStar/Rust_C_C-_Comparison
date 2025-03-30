fn main() {
    let x = 5;
    // x = 10; // This would cause a compile-time error
    let mut y = 5; // Explicitly mutable
    y = 10;
    println!("{}", y);
}
