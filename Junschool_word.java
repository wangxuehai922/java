import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;
import java.util.Scanner;

public class Junschool_word {

    private static final int MAX_NUM = 10; // 控制最大数
    private static final int MAX_EXPRESSIONS = 10; // 控制题目数量
    private static final boolean ALLOW_DECIMALS = true; // 是否允许小数
    private static final boolean ALLOW_PARENS = true; // 是否允许括号
    private static final char[] OPERATORS = {'+', '-', '*', '/'}; // 运算符

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("请输入生成的题目数量：");
        int n = scanner.nextInt();
        System.out.print("是否包含加法（+）？（y/n）");
        boolean allowAddition = scanner.next().equalsIgnoreCase("y");
        System.out.print("是否包含减法（-）？（y/n）");
        boolean allowSubtraction = scanner.next().equalsIgnoreCase("y");
        System.out.print("是否包含乘法（*）？（y/n）");
        boolean allowMultiplication = scanner.next().equalsIgnoreCase("y");
        System.out.print("是否包含除法（/）？（y/n）");
        boolean allowDivision = scanner.next().equalsIgnoreCase("y");
        System.out.print("最大数是多少？");
        int maxNum = scanner.nextInt();

        String[] expressions = generateExpressions(n, allowAddition, allowSubtraction, allowMultiplication, allowDivision, maxNum, ALLOW_DECIMALS, ALLOW_PARENS);
        printExpressions(expressions);
        saveToFile(expressions);
    }

    private static String[] generateExpressions(int n, boolean allowAddition, boolean allowSubtraction, boolean allowMultiplication, boolean allowDivision, int maxNum, boolean allowDecimals, boolean allowParens) {
        String[] expressions = new String[n];
        Random random = new Random();

        for (int i = 0; i < n; i++) {
            int op1 = random.nextInt(maxNum) + 1;
            int op2 = random.nextInt(maxNum) + 1;
            char op = getRandomOperator(allowAddition, allowSubtraction, allowMultiplication, allowDivision);
            if (op == '/') {
                // 防止除以0
                while (op2 == 0 || op1 % op2 != 0) {
                    op2 = random.nextInt(maxNum) + 1;
                }
            }
            String expression = op1 + " " + op + " " + op2;
            if (allowParens && random.nextBoolean()) {
                // 加括号
                expression = "(" + expression + ")";
            }
            if (allowDecimals && random.nextBoolean()) {
                // 加小数
                double decimal = random.nextDouble() * maxNum;
                expression += " + " + String.format("%.2f", decimal);
            }

            expressions[i] = expression;
        }
        return expressions;
    }

    private static char getRandomOperator(boolean allowAddition, boolean allowSubtraction, boolean allowMultiplication, boolean allowDivision) {
        Random random = new Random();
        char op;
        do {
            op = OPERATORS[random.nextInt(4)];
        } while ((op == '+' && !allowAddition)
                || (op == '-' && !allowSubtraction)
                || (op == '*' && !allowMultiplication)
                || (op == '/' && !allowDivision));
        return op;
    }

    private static void printExpressions(String[] expressions) {
        for (int i = 0; i < expressions.length; i++) {
            System.out.println((i + 1) + ". " + expressions[i] + " = ");
        }
    }

    private static void saveToFile(String[] expressions) {
        try {
            PrintWriter writer = new PrintWriter(new File("exercises.txt"));
            for (int i = 0; i < expressions.length; i++) {
                writer.println((i + 1) + ". " + expressions[i] + " = ");
            }
            writer.close();
            System.out.println("题目已保存至 exercises.txt");
        } catch (IOException e) {
            System.out.println("保存文件失败。");
        }
    }
}