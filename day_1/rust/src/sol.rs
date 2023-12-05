// open file
// read line by line
// parse line for part 1
// parse line for part 2
// calc sum 
// return
use std::fs::File;
use std::i32::MAX;
use std::io::{self, BufRead, BufReader};
use std::process::id;

//todo: Finish
pub fn run(parent_dir: &String) -> io::Result<()> {
    let file_result = File::open(
        format!("{}/input/input.txt", parent_dir)
    );

    let reader = match file_result {
        Err(err) => {
            eprintln!("Unable to open file {}", err);
            return Err(err)
        }
        Ok(file) => {
            BufReader::new(file)
        }
    };
    solve_part1(reader)
}

fn solve_part1(reader: BufReader<File>) -> io::Result<()> {

    let mut sum: u32 = 0;

    for line in reader.lines() {
        let line = line?;

        let first_digit = line.chars()
            .find_map(|c| c.to_digit(10)).unwrap();
        let last_digit  = line.chars().rev()
            .find_map(|c| c.to_digit(10)).unwrap();

        sum += first_digit*10 + last_digit;
    }
    println!("Sum {:?}", sum);

    Ok(())
}

fn solve_part2(reader: BufReader<File>) -> io::Result<()> {
    let digit_words = vec![
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    ];
    // TODO: solve part 2
    Ok(())
}

