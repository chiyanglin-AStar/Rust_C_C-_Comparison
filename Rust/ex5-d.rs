fn main() {
    let v1 = vec![1, 2, 3];
    let v2 = v1; // v1 is moved to v2

    // println!("v1: {:?}", v1); // This would cause a compile-time error
    println!("v2: {:?}", v2);
}
