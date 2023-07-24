macro_rules! chmax {
    ( $a: expr, $b: expr) => {
        {
            if $a < $b {
                $a = $b;
                true
            } else {
                false
            }
        }
    }
}