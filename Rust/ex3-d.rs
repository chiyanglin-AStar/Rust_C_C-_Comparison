use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    let data = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..2 {
        let data = Arc::clone(&data);
        let handle = thread::spawn(move || {
            for _ in 0..100000 {
                let mut data = data.lock().unwrap();
                *data += 1;
            }
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Shared data: {}", *data.lock().unwrap());
}
