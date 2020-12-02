use std::fs;

fn main() {
  let input: String = fs::read_to_string("input").expect("Unable to read file");
  'outer: for n1 in input.lines() {
    for n2 in input.lines() {
      let i1 = n1.parse::<i32>().unwrap();
      let i2 = n2.parse::<i32>().unwrap();
      if i1 + i2 == 2020 {
        println!("Task 1: {} * {} = {}", n1, n2, i1 * i2);
        break 'outer;
      }
    }
  }
  
  'outer2: for n1 in input.lines() {
    for n2 in input.lines() {
      for n3 in input.lines() {
        let i1 = n1.parse::<i32>().unwrap();
        let i2 = n2.parse::<i32>().unwrap();
        let i3 = n3.parse::<i32>().unwrap();
        if i1 + i2 + i3 == 2020 {
          println!("Task 2: {} * {} * {} = {}", n1, n2, n3, i1 * i2 * i3);
          break 'outer2;
        }
      }
    }
  }
}
