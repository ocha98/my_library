#[cfg(test)]
mod random_test {
    use std::io::{Read, Write};
    use std::process::{Command, Stdio};
    use rand::Rng;
    use rand::{rngs::StdRng, SeedableRng};
    type Input = String;

    type Output = String;

    #[test]
    fn test() {
        const NUMBER_OF_TESTS: usize = 100;
        let mut rng = StdRng::seed_from_u64(12345);
        for case_i  in 0..NUMBER_OF_TESTS {
            let input = generator(&mut rng);
            let expected_output = expected(input.clone());
            let actual_output = actual(input.clone());

            assert_eq!(expected_output, actual_output, 
            "
Wrong Answer on Test {}.

[Input]
{}


[Expected Output]
{}

[Actual Output]
{}

            ", case_i, input, expected_output, actual_output
            );
        }
    }

    fn generator(rng: &mut StdRng) -> Input {
        use std::fmt::Write;
        let mut input = String::new();

        todo!();

        input
    }

    fn expected(input: Input) -> Output {
        use proconio::{*, source::auto::AutoSource};
        let source = AutoSource::from(input.as_str());
        use std::fmt::Write;
        let mut out = String::new();

        input! {
            from source,
        }

        todo!();

        out
    }

    // src/main.rs専用
    // 他のものにする場合は書き換える
    fn actual(input: Input) -> Output {
        let child = Command::new("cargo")
            .args(["run"])
            .stdin(Stdio::piped())
            .stdout(Stdio::piped())
            .spawn()
            .unwrap();

        child.stdin.unwrap().write_all(input.as_bytes()).unwrap();

        let mut output = String::new();
        child.stdout.unwrap().read_to_string(&mut output).unwrap();

        output
    }

    fn generate_random_uppercase(length: usize, rng: &mut StdRng) -> String {
        const CHARSET: &[u8] = b"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        let random_string: String = (0..length)
            .map(|_| {
                let idx = rng.gen_range(0..CHARSET.len());
                CHARSET[idx] as char
            })        .collect();
        random_string
    }

    fn generate_random_lowercase(length: usize, rng: &mut StdRng) -> String {
        const CHARSET: &[u8] = b"abcdefghijklmnopqrstuvwxyz";
        let random_string: String = (0..length)
            .map(|_| {
                let idx = rng.gen_range(0..CHARSET.len());
                CHARSET[idx] as char
            })
            .collect();
        random_string
    }
}

// [Example]
// fn main() {
//     input! {
//         a: usize,
//         b: usize,
//     }

//     println!("{}", a+b);
// }
//
// [Generator]
//
// fn generator(rng: &mut StdRng) -> Input {
//     use std::fmt::Write;
//     let mut input = String::new();

//     writeln!(&mut input, "{} {}", rng.gen_range(1..10), rng.gen_range(1..10)).unwrap();

//     input
// }
//
// [Expected]
//
// fn expected(input: Input) -> Output {
//     use proconio::{*, source::auto::AutoSource};
//     let source = AutoSource::from(input.as_str());
//     use std::fmt::Write;
//     let mut out = String::new();

//     input! {
//         from source,
//         a: usize,
//         b: usize,
//     }

//     writeln!(&mut out, "{}", a+b).unwrap();
//     out
// }

