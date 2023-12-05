mod sol;

use std::env;
use std::io::{self};

fn main() -> io::Result<()> {
    /*
        Logic for accessing path from command
        necessary for reading input file
    */
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        eprintln!("Please provide a directory argument.");
        std::process::exit(1);
    }
    let parent_dir: &String = &args[1];
    sol::run(parent_dir)
}
