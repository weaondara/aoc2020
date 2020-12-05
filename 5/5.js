var fs = require("fs");

fs.readFile("input", "utf8", function(err, data) {
  console.log('Task 1: ' + Math.max(...data.split('\n')
    .filter(function (line) { return line.length == 10; })
    .map(function (line) { return parseInt(line.replaceAll('F', '0').replaceAll('L', '0').replaceAll('B', '1').replaceAll('R', '1'), 2); })
    ));
});

fs.readFile("input", "utf8", function(err, data) {
  console.log('Task 2: ', data.split('\n')
    .filter(function (line) { return line.length == 10; })
    .map(function (line) { return parseInt(line.replaceAll('F', '0').replaceAll('L', '0').replaceAll('B', '1').replaceAll('R', '1'), 2); })
    .sort(function (a, b) { return a - b; })
    .filter(function (seat, index, seats) {
      console.log(seat);
        if(index == seats.length - 1)
          return false;
        return seats[index + 1] != seat + 1;
      })[0] + 1
    );
});
