macro_rules! square {
    ($x:expr) => {{
        $x * $x
    }};
}

fn main() {
    let x = 5;
    println!("{}", square!(x + 1)); // Outputs 36
}
