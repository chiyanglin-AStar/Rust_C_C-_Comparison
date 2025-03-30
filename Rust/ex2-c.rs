fn get_value() -> i32 {
    let x = 10;
    x // Ownership ensures safe return
}

fn main() {
    let value = get_value();
    println!("{}", value);
}
