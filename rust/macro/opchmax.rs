macro_rules! opchmax {
    ($a: expr, $b: expr) => {
        if a.is_some_and(|v| v >= $b) {
            false
        } else {
            $a = Some($b);
            true
        }
    };
}
