
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

class c {

    public static void main(String[] args) throws Exception {
        List<Integer> lines = Files.readAllLines(Paths.get("input")).stream().filter(e -> e.length() > 0).map(s -> Integer.parseInt(s)).collect(Collectors.toList());
        Collections.sort(lines);
        lines.add(0, 0);
        lines.add(lines.get(lines.size() - 1) + 3);
        System.out.println(lines);

        //task 1
        int[] ds = new int[4];
        for (int i = 1; i < lines.size(); i++) {
            int d = lines.get(i) - lines.get(i - 1);
            ds[d]++;
        }
        System.out.println("Task 1: " + (ds[1] * ds[3]));

        //task 2
        long arr = bcombs(lines);
//        List<Integer> drop = new ArrayList();
//        System.out.println("drop: " + drop);
        System.out.println("Task 2: " + arr);
    }

    static Map<Integer, Long> cache = new HashMap();

    static long bcombs(List<Integer> lines) {
        int start = 0;
        long comb = 1;
        for (int i = 2; i < lines.size() - 2; i++) {
//            System.out.println("bcombs i: "+i);
            int d = lines.get(i) - lines.get(i - 2);
            if (d > 3) {
                long c = combs(lines.subList(start, i), 1);
//                System.out.println("section " + start + " - " + i + "; " + lines.subList(start, i) + " => " + c);
                comb *= c;
                start = i -1;
            }
        }
        if (start < lines.size())
            comb *= combs(lines.subList(start, lines.size()), 1);
        return comb;
    }

    static long combs(List<Integer> lines, int i) {
        if (i > lines.size() - 2)
            return 1;

        int d = lines.get(i + 1) - lines.get(i - 1);
        if (d == 2) {
            long s = combs(lines, i + 1);
            int v = lines.remove(i);
            s += combs(lines, i);
            lines.add(i, v);
            return s;
        } else if (d == 3) {
            long s = combs(lines, i + 1);
            int v = lines.remove(i);
            s += combs(lines, i);
            lines.add(i, v);
            return s;
        } else {//cannot be removed
            long s = combs(lines, i + 1);
            return s;
        }
    }
}
