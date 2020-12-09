
groups = File.read("input").split(/\n\n/)
sum = 0
groups.each do |g|
  lines = g.split(/\n/)
  #puts lines
  #puts "\n\n"
  
  #puts lines[0].split('')
  
  q = ''
  lines.each do |line|
    line.split('').each do |c|
      #puts "line: " + line
      if not q.include? c
        q += c
      end
    end
  end
  sum += q.length
end


puts "Task 1: #{sum}"

groups = File.read("input").split(/\n\n/)
sum = 0
groups.each do |g|
  lines = g.split(/\n/)
  #puts lines
  #puts "\n\n"
  
  #puts lines[0].split('')
  
  lines[0].split('').each do |c|
    inall = true
    lines.each do |line|
      #puts "line: " + line
      if not line.include? c
        inall = false
        break
      end
    end
    if inall
      sum += 1
      #puts "#{c} in all true #{sum}\n"
    else
      #puts "#{c} in all false #{sum}\n"
    end
  end
  #puts "\n\n\n\n"
end


puts "Task 2: #{sum}"
