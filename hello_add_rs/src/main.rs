use std::time::Instant;

fn add(n: usize, x: &Vec<f32>, y: &mut Vec<f32>) {
    for i in 0..n {
        y[i] = x[i] + y[i];
    }
}

fn main() {
    // Allocate arrays
    const N: usize = 1 << 20;

    let x: Vec<f32> = vec![1.0; N];
    let mut y: Vec<f32> = vec![2.0; N];

    // Perform compute
    let start = Instant::now();
    add(N, &x, &mut y);
    println!("{} ms", start.elapsed().as_millis());

    // Check result
    let mut err: f32 = 0.0;
    for yi in y.iter() {
        err = err.max(yi - 3.0)
    }

    println!("Max error: {err}");
}
