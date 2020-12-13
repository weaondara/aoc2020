my $file = 'input';
open my $info, $file or die "Could not open $file: $!";

@lines = (); 
while (my $line = <$info>) {
  push(@lines, $line);
  #last if $. == 2;
}

close $info;

#task 1
my $ns = 0;
my $we = 0;
my $rot = 90;

foreach (@lines) {
  my $dir = substr $_, 0, 1;
  my $val = int(substr $_, 1);
  if ($dir eq "N") {
    $ns -= $val;
  } elsif ($dir eq "E") {
    $we += $val;
  } elsif ($dir eq "S") {
    $ns += $val;
  } elsif ($dir eq "W") {
    $we -= $val;
  } elsif ($dir eq "L") {
    $rot = ($rot - $val + 360) % 360;
  } elsif ($dir eq "R") {
    $rot = ($rot + $val) % 360;
  } elsif ($dir eq "F") {
    if ($rot == 0) {
      $ns -= $val;
    } elsif ($rot == 90) {
      $we += $val;
    } elsif ($rot == 180) {
      $ns += $val;
    } elsif ($rot == 270) {
      $we -= $val;
    }
  }
  #print $dir, $val, "=>", $ns, ", ", $we, "\n"
}
print "Task 1: ", abs($ns) + abs($we), "\n";

#task 2
$ns = 0;
$we = 0;
my $wpns = -1;
my $wpwe = 10;

foreach (@lines) {
  my $dir = substr $_, 0, 1;
  my $val = int(substr $_, 1);
  if ($dir eq "N") {
    $wpns -= $val;
  } elsif ($dir eq "E") {
    $wpwe += $val;
  } elsif ($dir eq "S") {
    $wpns += $val;
  } elsif ($dir eq "W") {
    $wpwe -= $val;
  } elsif ($dir eq "L") {
    if ($val == 0) {
      #nothing to do
    } elsif ($val == 90) {
      my $newns = -$wpwe;
      my $newwe = $wpns;
      $wpns = $newns;
      $wpwe = $newwe;
    } elsif ($val == 180) {
      my $newns = -$wpns;
      my $newwe = -$wpwe;
      $wpns = $newns;
      $wpwe = $newwe;
    } elsif ($val == 270) {
      my $newns = $wpwe;
      my $newwe = -$wpns;
      $wpns = $newns;
      $wpwe = $newwe;
    } 
    #$rot = ($rot - $val + 360) % 360;
  } elsif ($dir eq "R") {
    if ($val == 0) {
      #nothing to do
    } elsif ($val == 90) {
      my $newns = $wpwe;
      my $newwe = -$wpns;
      $wpns = $newns;
      $wpwe = $newwe;
    } elsif ($val == 180) {
      my $newns = -$wpns;
      my $newwe = -$wpwe;
      $wpns = $newns;
      $wpwe = $newwe;
    } elsif ($val == 270) {
      my $newns = -$wpwe;
      my $newwe = $wpns;
      $wpns = $newns;
      $wpwe = $newwe;
    } 
    #$rot = ($rot + $val) % 360;
  } elsif ($dir eq "F") {
    $ns += $wpns * $val;
    $we += $wpwe * $val;
  }
  #print $dir, $val, "=>", $ns, ", ", $we, " ; ", $wpns, ", ", $wpwe, "\n"
}
print "Task 2: ", abs($ns) + abs($we), "\n"
