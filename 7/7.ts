//c++
//groovy

import * as fs from 'fs';


const text: string = fs.readFileSync('input','utf8');
let lineEntries: Map<string, Map<string, number>> = new Map();

text.split('\n')
  .filter(line => !line.includes('no other bags') && line.length > 3)
  .forEach(line => {
  let color = line.split(' bags contain', 2)[0];
  let contents: Map<string, number> = new Map();
  line.split(' contain ', 2)[1]
    .replace('.', '')
    .split(', ')
    .map(bag => bag.replace(' bags', '').replace(' bag', ''))
    .forEach(bag =>  contents.set(bag.substring(bag.indexOf(' ') + 1), parseInt(bag.substring(0, bag.indexOf(' ')))));
  //console.log(color + " => ", contents);
  lineEntries.set(color, contents);
});

//task 1
let sum = Array.from(lineEntries.values()).map((value: Map<string, number>) => {
  return (canShiny(value) ? 1 : 0) as number;
}).reduce((a,b) => a + b);

console.log('Task 1: ' + sum);

function canShiny(bag: Map<string, number>): boolean {
  if (!bag)
    return false;
    
  if (bag.has('shiny gold'))
    return true;
  
  return Array.from(bag.keys()).some((key: string) => {
    return canShiny(lineEntries.get(key));
  });
}

//task 2
let contents = [];

lineEntries.get('shiny gold').forEach((value, key) => {
  for (let j = 0; j < value; j++)
    contents.push(key);
});

for (let i = 0; i < contents.length; i++) {
  let entry = lineEntries.get(contents[i]);
  if (entry) {
    entry.forEach((value, key) => {
      for (let j = 0; j < value; j++)
        contents.push(key);
    });
  }
}

console.log('Task 2: ' + contents.length);

