package main

import (
	"bufio"
	"os"
	"strconv"
	"strings"
)

// Scanner
type Scanner struct {
	r *bufio.Reader
}

func NewScanner() Scanner {
	return Scanner{bufio.NewReader(os.Stdin)}
}

func (r Scanner) nextString() string {
	s, _ := r.r.ReadString('\n')
	return strings.TrimRight(s, "\r\n")
}

func (r Scanner) nextInt() int {
	s := r.nextString()
	v, _ := strconv.Atoi(s)
	return v
}

func (r Scanner) nextInt64() int64 {
	s := r.nextString()
	v, _ := strconv.ParseInt(s, 10, 0)
	return v
}

func (r Scanner) nextInts(n int) []int {
	retu := make([]int, 0, n)
	for _, v := range strings.Split(r.nextString(), " ") {
		if v == "" {
			continue
		}
		x, _ := strconv.Atoi(v)
		retu = append(retu, x)
	}
	return retu
}

func (r Scanner) nextInt64s(n int) []int64 {
	retu := make([]int64, 0, n)
	for _, v := range strings.Split(r.nextString(), " ") {
		if v == "" {
			continue
		}
		x, _ := strconv.ParseInt(v, 10, 0)
		retu = append(retu, x)
	}
	return retu
}
