use std::fs::File;
use std::io::prelude::*;

fn count_valid_passwords(passwords: &String) -> (u16, u16)
{
    let lines = passwords.lines();
    let mut valid_passwords_p1: u16 = 0;
    let mut valid_passwords_p2: u16 = 0;

    for line in lines
    {
        let mut to: u16 = 0;
        let mut from: u16 = 0;
        let mut found_to = false;
        let mut found_from = false;
        let mut found_letter = false;
        let mut letter: char = ' ';
        let mut to_s = String::new();
        let mut from_s = String::new();
        let mut password = String::new();

        for c in line.chars()
        {
            if !found_from
            {
                if c.is_numeric()
                {
                    from_s.push(c);
                }
                else
                {
                    from = from_s.parse::<u16>().unwrap();
                    found_from = true;
                }
            }
            else if !found_to
            {
                if c.is_numeric()
                {
                    to_s.push(c);
                }
                else
                {
                    to = to_s.parse::<u16>().unwrap();
                    found_to = true;
                }
            }
            else if found_from && found_to && c.is_alphabetic()
            {
                if found_letter
                {
                    password.push(c);
                }
                else
                {
                    letter = c;
                    found_letter = true;
                }
            }
        }

        let mut occurrences: u16 = 0;
        let second_pos: bool = password.chars().nth((to - 1).into()).unwrap() == letter;
        let first_pos: bool = password.chars().nth((from - 1).into()).unwrap() == letter;
        
        for c in password.chars()
        {
            if c == letter
            {
                occurrences += 1;
            }
        }

        if from <= occurrences && occurrences <= to
        {
            valid_passwords_p1 += 1;
        }

        if  (first_pos && !second_pos) || (!first_pos && second_pos)
        {
            valid_passwords_p2 += 1;
        }
    }
    return (valid_passwords_p1, valid_passwords_p2);
}

fn main() -> std::io::Result<()>
{
    let mut file = File::open("input.txt")?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    let result: (u16, u16) = count_valid_passwords(&contents);
    println!("valid passwords:\npt.1: {}\npt.2: {}", result.0, result.1);
    Ok(())
}
