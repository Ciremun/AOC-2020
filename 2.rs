use std::fs::File;
use std::io::prelude::*;

// How many passwords are valid?

// 1-3 a: abcde
// 1-3 b: cdefg
// 2-9 c: ccccccccc

// pt.1 valid_passwords: 2
// pt.2 valid_passwords: 1

fn count_matches(passwords: String) -> u16
{
    let lines = passwords.lines();
    let mut valid_passwords: u16 = 0;

    for line in lines
    {
        let mut from: u16 = 0;
        let mut to: u16 = 0;

        let mut from_s: String = "".to_string();
        let mut to_s: String = "".to_string();
        let mut letter: String = "".to_string();
        let mut password: String = "".to_string();

        let mut found_from = false;
        let mut found_to = false;
        let mut found_letter = false;
        let found_password = false;

        for c in line.chars()
        {
            if !found_from && !c.is_numeric()
            {
                from = from_s.parse::<u16>().unwrap();
                found_from = true;
                continue;
            }
            else if !found_from && c.is_numeric()
            {
                from_s.push(c);
            }
            else if !found_to && !c.is_numeric()
            {
                to = to_s.parse::<u16>().unwrap();
                found_to = true;
                continue;
            }
            else if !found_to && c.is_numeric()
            {
                to_s.push(c);
            }
            else if found_from && found_to && !found_letter && c.is_alphabetic()
            {
                letter = c.to_string();
                found_letter = true;
            }
            else if found_from && found_to && found_letter && !found_password && c.is_alphabetic()
            {
                password.push(c);
            }
        }
        
        // pt.1
        // let mut occurrences = 0;

        // for c in password.chars()
        // {
        //     if c.to_string() == letter
        //     {
        //         occurrences += 1;
        //     }
        // }

        // if from <= occurrences && occurrences <= to
        // {
        //     valid_passwords += 1;
        // }

        // pt.2
        let mut first_pos: bool = false;
        let mut second_pos: bool = false;

        if password.chars().nth((from - 1).into()).unwrap() == letter.chars().nth(0).unwrap()
        {
            first_pos = true;
        }

        if password.chars().nth((to - 1).into()).unwrap() == letter.chars().nth(0).unwrap()
        {
            second_pos = true;
        }

        if  (first_pos && !second_pos) || (second_pos && !first_pos)
        {
            valid_passwords += 1;
        }
    }
    return valid_passwords;
}

fn main() -> std::io::Result<()>
{
    let mut file = File::open("input.txt")?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    let valid_passwords: u16 = count_matches(contents);
    println!("valid_passwords: {}", valid_passwords);
    Ok(())
}
