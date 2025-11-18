public class QuantosPrimosSeq {

    public static void main(String[] args) {
        if (args.length != 1)
            throw new IllegalArgumentException("Uso: java FuturePoolSequencial <numero primo maximo: int>");

        int n = Integer.parseInt(args[0]);
        if (n < 1) {
            System.out.println("N deve ser maior que 1");
            System.exit(1);
        }

        long sum = 0;

        for (int i = 1; i <= n; i++) {
            if (ehPrimo(i)) {
                sum++;
            }
        }

        System.out.println("Quantidade de números primos encontrados: " + sum);
    }

    private static boolean ehPrimo(int n) {
        if (n <= 1) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;

        long limite = (long) Math.sqrt(n);
        for (long i = 3; i <= limite; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }
}
