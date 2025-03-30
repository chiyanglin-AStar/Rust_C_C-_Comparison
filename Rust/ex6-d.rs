//static x:i32 = 10;

fn create_int<'a>() -> &'a i32 {
    let x = 10;
    &x // Compile-time error: `x` does not live long enough
}

fn main() {
    let ptr = create_int();
    println!("{}", ptr);
}
