fn get_value(valid: bool) -> Option<i32> {
    if valid { Some(10) } else { None }
}

fn main() {
    match get_value(false) {
        Some(val) => println!("{}", val),
        None => println!("No value found"),
    }
}
