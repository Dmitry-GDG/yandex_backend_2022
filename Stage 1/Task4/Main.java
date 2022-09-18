
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(), m = sc.nextInt();
        char[][] a = new char[n][m];
        sc.nextLine();
        int x = 0, y = 0;
        for (int i = 0; i < a.length; i++) {
            a[i] = sc.nextLine().toCharArray();
            for (int j = 0; j < a[i].length; j++) {
                if (a[i][j] == 'S') {
                    y = j;
                    x = i;
                }
            }
        }
        step('L', x, y+1, a, n, m);
        step('R', x, y-1, a, n, m);
        step('U', x + 1, y, a, n, m);
        step('D', x - 1, y, a, n, m);
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < a[i].length; j++) {
                System.out.print(a[i][j]);
            }
            System.out.println();
        }
    }

    static void step(char l, int x, int y, char[][] map, int n, int m) {
        if (x < n &&  y < m && map[x][y] == '.') {
            map[x][y] = l;
            step('L', x, y+1, map, n, m);
            step('R', x, y-1, map, n, m);
            step('U', x + 1, y, map, n, m);
            step('D', x - 1, y, map, n, m);
        }
    }
}

//5 8
//########
//#......#
//#.#S#.##
//##...###
//########