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
