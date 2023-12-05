use std::fs::File;
use std::io::{self, BufRead, BufReader};

use std::cmp::max;


fn main() {
    let file_result = File::open(file_path);
    let reader = match file_result {
        Err(err) => {
            eprintln!("Unable to open file {}", err);
            return Err(err);
        }
        Ok(file) => BufReader::new(file),
    };
    
}

fn solve(reader: BufReader<File>) {

    reader.lines()
}