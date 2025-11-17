class PrimoSequencial {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Uso: java PrimoSequencial <numero primo maximo: int>");
            System.exit(1);
        }

        int n = Integer.parseInt(args[0]);
        if (n < 1) {
            System.out.println("Entrada deve ser maior que zero.");
            System.exit(1);
        }

        System.out.println("Primos encontrados:");
        for (int i = 0; i < n; i++) {
            if (ehPrimo(i)) {
                System.out.println(i);
            }
        }

        System.out.println("Terminou");
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
