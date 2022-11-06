use std::{collections::VecDeque, str::FromStr};

struct StdioScanner {
    buff: std::collections::VecDeque<String>
}

impl StdioScanner {
    fn new() -> StdioScanner{
        StdioScanner{buff: VecDeque::new()}
    }

    fn read(&mut self){
        let mut s = String::new();
        std::io::stdin().read_line(&mut s).expect("Error: read_line");

        for t in s.replace('\n', "").split(" "){
            self.buff.push_back(String::from(t).clone());
        }
    }

    fn next_int<T: FromStr>(&mut self) -> T {
        if self.buff.len() == 0{
            self.read();
        }
        let s = self.buff.pop_front().unwrap();
        let v = s.parse::<T>();
        match v {
           Ok(num) => num,
            _ => panic!("Error: next_int")
        }
    }

    fn next_line(&mut self) -> String {
        if self.buff.len() == 0 {
            self.read();
        }
        let s = self.buff.pop_front().unwrap();
        s
    }
}
