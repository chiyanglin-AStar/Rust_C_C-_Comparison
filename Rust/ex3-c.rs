use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    let counter = Arc::new(Mutex::new(0));

    let handles: Vec<_> = (0..2).map(|_| {
        let counter = Arc::clone(&counter);
        thread::spawn(move || {
            let mut num = counter.lock().unwrap();
            for _ in 0..100000 {
                *num += 1;
            }
        })
    }).collect();

    for handle in handles {
        handle.join().unwrap();
    }

    println!("{}", *counter.lock().unwrap()); // Always correct
}
