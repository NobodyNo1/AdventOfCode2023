use std::fs::File;
use std::io::{self, BufRead, BufReader};

use std::cmp::max;

struct GameInfo{
    game_id     : i32,
    max_colors  : Vec<i32>,
}

// Change &String to &str in the function parameter
pub fn run(file_path: &str, part: i32) -> io::Result<()> {
    let file_result = File::open(file_path);
    let reader = match file_result {
        Err(err) => {
            eprintln!("Unable to open file {}", err);
            return Err(err);
        }
        Ok(file) => BufReader::new(file),
    };

    // Call solve function with the created reader
    solve(reader, part)
}

// Fix the function signature to take a mutable reference to BufReader
fn solve(mut reader: BufReader<File>, part: i32) -> io::Result<()> {
    // Initialize variables to hold colors
    let max_colors = vec![12,13,14];
    let mut result = 0;
    // Use a for loop to iterate over lines directly
    for line in reader.lines() {
        // Use unwrap to simplify error handling
        let line = line.unwrap();
        let info = parse_text(&line);
        if part == 1 {
            let mut should_put = true;
            for i in 0..3 {
                if info.max_colors[i] > max_colors[i] {
                    should_put = false;
                    break;
                }
            }
            if should_put {
                result = result + info.game_id;
            }
        } else {
            // assuming at least one color present (if not it will add 1 each time)
            let mut multiplied_colors = 1;
            for i in 0..3 {
                if info.max_colors[i] != 0 {
                    multiplied_colors = multiplied_colors * info.max_colors[i];
                }
            }
            result = result + multiplied_colors;
        }
        // if info.
    }

    // Do something with the calculated colors
    println!("Part {}", part);
    println!("  result: {:?}", result);

    Ok(())
}

fn parse_text(text: &str) -> GameInfo {
    let mut colors = vec![0, 0, 0, 0];
    let mut game_values = text.split(": ");
    //game id
    let game_id = game_values.next().and_then(|value| value.split(' ').nth(1)).unwrap_or("").parse::<i32>().unwrap();
    game_values.next().map(|values| {
        values.split("; ").for_each(|round| {
            round.split(", ").for_each( | value_container | {
                let mut values = value_container.split(' ');
                if let Some(color_value_str) = values.next() {
                    if let Some(color_name) = values.filter(|&s| s != "").next() {
                        if let Ok(color_value) = color_value_str.parse::<i32>() {
                            let color_index = char_to_color(color_name);
                            colors[color_index] = max(colors[color_index], color_value);
                        }
                    }
                }
            });
        });
    });
    // println!("{}", colors[0]);
    // println!("{}", colors[1]);
    // println!("{}", colors[2]);
    GameInfo {
        game_id     : game_id, 
        max_colors  : colors
    }
}

fn char_to_color(ch: &str) -> usize {
    match ch {
        "red" => 0,
        "green" => 1,
        "blue" => 2,
        _ => 3, // Handle the default case
    }
}
