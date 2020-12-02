SELECT count(*) FROM (
  SELECT q.*, (LENGTH(q.pw) - LENGTH(REPLACE(q.pw, q.c, ''))) as cnt from (
    SELECT 
        line,
        SUBSTRING_INDEX(SUBSTRING_INDEX(line, ' ', 1), '-', 1) AS cmin,
        SUBSTRING_INDEX(SUBSTRING_INDEX(line, ' ', 1), '-', -1) AS cmax,
        REPLACE(SUBSTRING_INDEX(SUBSTRING_INDEX(line, ' ', 2), ' ', -1), ':', '') AS c,
        SUBSTRING_INDEX(SUBSTRING_INDEX(line, ' ', 3), ' ', -1) AS pw
      FROM input
  ) q
) p WHERE cmin <= cnt AND cnt <= cmax


SELECT count(*) FROM (
  SELECT q.*, ((SUBSTR(q.pw, cmin, 1) = c) XOR (SUBSTR(q.pw, cmax, 1) = c)) as mtch from (
    SELECT 
        line,
        SUBSTRING_INDEX(SUBSTRING_INDEX(line, ' ', 1), '-', 1) AS cmin,
        SUBSTRING_INDEX(SUBSTRING_INDEX(line, ' ', 1), '-', -1) AS cmax,
        REPLACE(SUBSTRING_INDEX(SUBSTRING_INDEX(line, ' ', 2), ' ', -1), ':', '') AS c,
        SUBSTRING_INDEX(SUBSTRING_INDEX(line, ' ', 3), ' ', -1) AS pw
      FROM input
  ) q
) p WHERE mtch = 1
