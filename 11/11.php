<?php
$lines = explode("\n", file_get_contents('input'));
if(strlen($lines[count($lines) - 1]) < 10) {
  unset($lines[count($lines) - 1]);
}

$grid = array_map(function ($line) { return str_split($line); }, $lines);

//task 1
$newgrid = copyGrid($grid);
$lastgrid = null;
for($step = 0; !grideq($newgrid, $lastgrid); $step++) {
  print "\rstep $step";
  $lastgrid = copyGrid($newgrid); //makes copy
  $newgrid = step($lastgrid);
}
print "\n";

$c = 0;
for ($y = 0; $y < count($newgrid); $y++) {
  for ($x = 0; $x < count($newgrid[$y]); $x++) {
    if($newgrid[$y][$x] == '#') {
      $c++;
    }
  }
}

print 'Task 1: steps='.$step.'; occupied='.$c."\n";

//task 2:
$newgrid = copyGrid($grid);
$lastgrid = null;
for($step = 0; !grideq($newgrid, $lastgrid); $step++) {
  print "\rstep $step";
  //printGrid($newgrid);
  //echo "----------\n";
  $lastgrid = copyGrid($newgrid); //makes copy
  $newgrid = step2($lastgrid);
}
print "\n";
//printGrid($newgrid);
//echo "----------\n";

$c = 0;
for ($y = 0; $y < count($newgrid); $y++) {
  for ($x = 0; $x < count($newgrid[$y]); $x++) {
    if($newgrid[$y][$x] == '#') {
      $c++;
    }
  }
}

print 'Task 2: steps='.$step.'; occupied='.$c."\n";


//util
function step($grid) {
  $ass = 0;
  $unass = 0;
  $newgrid = $grid;
  for ($y = 0; $y < count($grid); $y++) {
    //print $y;
    for ($x = 0; $x < count($grid[$y]); $x++) {
      if ($grid[$y][$x] == 'L') {
        $n = neighbors($y, $x);
        //var_dump($n);
        for($i = 0; $i < count($n); $i++) {
          if($grid[$n[$i][0]][$n[$i][1]] == '#') { //neighbor occupied
            continue 2;
          }
        }
        $newgrid[$y][$x] = '#';
        $ass++;
        //sleep(10);
      } else if($grid[$y][$x] == '#') {
        $n = neighbors($y, $x);
        $c = 0;
        for($i = 0; $i < count($n); $i++) {
          if($grid[$n[$i][0]][$n[$i][1]] == '#') { //neighbor occupied
            $c++;
          }
        }
        
        if($c >= 4) {
          $newgrid[$y][$x] = 'L';
          $unass++;
        }
        //sleep(10);
      }
    }
  }
  
  //print "ass $ass, unass $unass\n";
  return $newgrid;
}

function step2($grid) {
  $ass = 0;
  $unass = 0;
  $newgrid = $grid;
  for ($y = 0; $y < count($grid); $y++) {
    //print $y;
    for ($x = 0; $x < count($grid[$y]); $x++) {
      if ($grid[$y][$x] == 'L') {
        $n = lines_of_sight($y, $x);
        //var_dump($n);
        for($reti = 0; $reti < count($n); $reti++) {
          for($i = 0; $i < count($n[$reti]); $i++) {
            if($grid[$n[$reti][$i][0]][$n[$reti][$i][1]] == '#') { //neighbor occupied
              continue 3;
            } else if($grid[$n[$reti][$i][0]][$n[$reti][$i][1]] == 'L') { //neighbor occupied
              break;
            }
          }
        }
        $newgrid[$y][$x] = '#';
        $ass++;
        //sleep(10);
      } else if($grid[$y][$x] == '#') {
        $n = lines_of_sight($y, $x);
        $c = 0;
        for($reti = 0; $reti < count($n); $reti++) {
          for($i = 0; $i < count($n[$reti]); $i++) {
            if($grid[$n[$reti][$i][0]][$n[$reti][$i][1]] == '#') { //neighbor occupied
              $c++;
              break;
            } else if($grid[$n[$reti][$i][0]][$n[$reti][$i][1]] == 'L') { //neighbor occupied
              break;
            }
          }
        }
        
        if($c >= 5) {
          $newgrid[$y][$x] = 'L';
          $unass++;
        }
        //sleep(10);
      }
    }
  }
  
  //print "ass $ass, unass $unass\n";
  return $newgrid;
}

function grideq($g1, $g2) {
  if(($g1 == null) || ($g2 == null))
    return false;
  for ($y = 0; $y < count($g1); $y++) {
    for ($x = 0; $x < count($g1[$y]); $x++) {
      if($g1[$y][$x] != $g2[$y][$x]) {
        return false;
      }
    }
  }
  return true;
}

function neighbors($y, $x) {
  global $grid;
  $ret = array(
    array($y - 1, $x - 1),
    array($y - 1, $x),
    array($y - 1, $x + 1),
    array($y, $x - 1),
    array($y, $x + 1),
    array($y + 1, $x - 1),
    array($y + 1, $x),
    array($y + 1, $x + 1),
  );
  for($i = 7; $i >= 0; $i--) {
    if ($ret[$i][0] < 0
      || $ret[$i][0] >= count($grid)
      || $ret[$i][1] < 0
      || $ret[$i][1] >= count($grid[0])) {
      //var_dump($ret);
      array_splice($ret, $i, 1);
      //var_dump($ret);
      //echo '--------';
    }
  }
  return $ret;
}
function lines_of_sight($y, $x) {
  global $grid;
  $ret = array();
  for($i = 1; $i < max(count($grid), count($grid[0])); $i++) {
    $ret[0][] = array($y - $i, $x - $i);
    $ret[1][] = array($y - $i, $x);
    $ret[2][] = array($y - $i, $x + $i);
    $ret[3][] = array($y, $x - $i);
    $ret[4][] = array($y, $x + $i);
    $ret[5][] = array($y + $i, $x - $i);
    $ret[6][] = array($y + $i, $x);
    $ret[7][] = array($y + $i, $x + $i);
  }
  
  for($reti = 0; $reti < 8; $reti++) {
    for($i = count($ret[$reti]) - 1; $i >= 0; $i--) {
      if ($ret[$reti][$i][0] < 0
        || $ret[$reti][$i][0] >= count($grid)
        || $ret[$reti][$i][1] < 0
        || $ret[$reti][$i][1] >= count($grid[0])) {
        //var_dump($ret);
        array_splice($ret[$reti], $i, 1);
        //var_dump($ret);
        //echo '--------';
      }
    }
  }
  return $ret;
}

function copyGrid($grid) {
  $ret = array();
  for($i = 0; $i < count($grid); $i++) {
    $ret[$i] = array_map(function ($e) { return $e; }, $grid[$i]);
  }
  return $ret;
}

function printGrid($grid) {
  for($y = 0; $y < count($grid); $y++) {
    for($x = 0; $x < count($grid[$y]); $x++) {
      print $grid[$y][$x];
    }
    print "\n";
  }
}

?>
