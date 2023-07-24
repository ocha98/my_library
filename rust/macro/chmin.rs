macro_rules! chmin {
    ( $a: expr, $b: expr) => {
        {
            if $a > $b {
                $a = $b;
                true
            } else {
                false
            }
        }
    }
}