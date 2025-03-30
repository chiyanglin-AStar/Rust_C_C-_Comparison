macro_rules! add {
    ($a:expr, $b:expr) => {
        $a + $b
    };
}

fn main() {
    println!("{}", add!(3, 4));
}
