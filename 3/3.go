package main

import (
  "fmt"
  "io/ioutil"
  "log"
  "strings"
)

type Pair struct {
    a, b int
}

func main() {
  content, err := ioutil.ReadFile("input")
  if err != nil {
    log.Fatal(err)
  }

  text := string(content)
  lines := strings.Split(text,"\n")
  
  right := 3
  down := 1
  
  count := 0
  for x, y := 0, 0; y < len(lines); x, y = x + right, y + down {
    if lines[y] == "" {
      break
    }
    pos := x % (len(lines[y]))
    if lines[y][pos:pos+1] == "#" {
      count++;
    }
  }
  
  fmt.Println("Trees hit:", count)
  
  //task 2
  
  queue := [5][2]int{
    {1, 1}, 
    {3, 1}, 
    {5, 1}, 
    {7, 1}, 
    {1, 2}}
  
  var res [5]int
  
  for i := 0; i < 5; i++ {
    right := queue[i][0]
    down := queue[i][1]
    
    count := 0
    for x, y := 0, 0; y < len(lines); x, y = x + right, y + down {
      if lines[y] == "" {
        break
      }
      pos := x % (len(lines[y]))
      if lines[y][pos:pos+1] == "#" {
        count++;
      }
    }
    fmt.Println("r", right, "d", down, "Trees hit:", count)
    res[i] = count
  }
  
  mul := 1
  for i := 0; i < 5; i++{
    mul *= res[i]
  }
  fmt.Println("Mult:", mul)
}
