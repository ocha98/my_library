struct MinHeap<T: Ord> {
    heap: std::collections::BinaryHeap<std::cmp::Reverse<T>>,
}

#[allow(dead_code)]
impl<T: Ord> MinHeap<T> {
    fn new() -> Self {
        MinHeap {
            heap: std::collections::BinaryHeap::new(),
        }
    }

    fn push(&mut self, value: T) {
        self.heap.push(std::cmp::Reverse(value));
    }

    fn pop(&mut self) -> Option<T> {
        self.heap.pop().map(|x| x.0)
    }

    fn peek(&self) -> Option<&T> {
        self.heap.peek().map(|x| &x.0)
    }

    fn is_empty(&self) -> bool {
        self.heap.is_empty()
    }

    fn len(&self) -> usize {
        self.heap.len()
    }
}
