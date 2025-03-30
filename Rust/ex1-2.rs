fn main() {
    let x = 5;
    let y = &x;
    println!("{}",x);
    println!("{}",y);
    println!("{}",*y);
    assert_eq!(5, x);
    assert_eq!(5, *y);
}
