#![feature(getpid)]
#![allow(unused_variables)]

use std::process;

fn unsafe_example() {
    let mut num = 5;

    let r1 = &num as *const i32;
    let r2 = &mut num as *mut i32;

    unsafe {
        println!("r1 is: {}", *r1);
        println!("r2 is: {}", *r2);
    }
}

fn split_at_mut_example() {
    let mut v: Vec<i32> = vec![1, 2, 3, 4, 5, 6];

    let r = &mut v[..];

    let (a, b) = r.split_at_mut(3);

    assert_eq!(a, &mut [1, 2, 3]);
    assert_eq!(b, &mut [4, 5, 6]);
}

macro_rules! vec {
    ( $( $x:expr ),* ) => {
        {
            let mut temp_vec = Vec::new();
            $(
                temp_vec.push($x);
            )*
            temp_vec
        }
    };
}

macro_rules! foo {
    (x => $e:expr) => (println!("mode X: {}", $e));
    (y => $e:expr) => (println!("mode Y: {}", $e));
}

macro_rules! o_O {
    (
        $(
            $x:expr; [ $( $y:expr );* ]
        );*
    ) => {
        &[ $($( $x + $y ),*),* ]
    }
}

macro_rules! five_times {
    ($x:expr) => (5 * $x);
}

fn get_log_state() -> i32 { 3 }
macro_rules! log {
    ($msg:expr) => {{
        let state: i32 = get_log_state();
        if state > 0 {
            println!("log({}): {}", state, $msg);
        }
    }};
}

macro_rules! foo {
    ($v:ident) => (let $v = 3;);
}

fn main() {
//    println!("My pid is {}", process::id());
//    split_at_mut_example();
//    let x: Vec<u32> = vec![1, 2, 3];
//    assert_eq!(x, [1, 2, 3]);
//    foo!(y => 3);
//    let a: &[i32] = o_O!(10; [1; 2; 3];
//                         20; [4; 5; 6]);
//
//    assert_eq!(a, [11, 12, 13, 24, 25, 26]);
//    assert_eq!(25, five_times!(5));
//
//    let state: &str = "reticulating splines";
//    log!(state);

    foo!(x);
    println!("{}", x);
}
