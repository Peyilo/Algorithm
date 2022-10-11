package Algorithm;
import java.util.*;

public class RPN {

    final double eps = 1e-10;  // 精度范围

    ArrayList<String> infixString = new ArrayList<>(); // 中缀表达式
    ArrayList<String> suffixString = new ArrayList<>(); // 后缀表达式

    Stack<String> opStack = new Stack<>();         //运算符栈
    Map<String,Integer> opMap = new HashMap<>();   //运算符优先级

    public RPN() {
        //存入优先级关系
        opMap.put("(", 0);
        opMap.put("+", 1);
        opMap.put("-", 1);
        opMap.put("*", 2);
        opMap.put("/", 2);
    }


    public String getResult(String input) {
        //分割字符串
        infixString.clear();
        StringTokenizer stringTokenizer = new StringTokenizer(input, "+-*/()",true);
        while(stringTokenizer.hasMoreTokens()) {
            String temp = stringTokenizer.nextToken().strip();
            if (!temp.equals(""))
                infixString.add(temp);
        }
        System.out.println("中缀表达式：" + infixString);
        infixToSuffix();
        return computeSuffix();
    }


    //中缀转后缀
    private void infixToSuffix() {
        suffixString.clear();
        for(String str : infixString) {
            // 如果是运算符
            if(isOperator(str)) {
                handleOp(str);
            }
            // 如果是数字
            else {
                handleNum(str);
            }
        }

        //将opStack内剩余操作符出栈到后缀表达式
        while(!opStack.isEmpty()) {
            suffixString.add(opStack.pop());
        }

        System.out.println("后缀表达式: " + suffixString);

    }

    private String computeSuffix() {

        Stack<String> suffix = new Stack<>();

        for (String str : suffixString) {

            // 如果是操作符,弹出两个元素，并计算结果，将结果入栈
            if(isOperator(str)) {
                double dest = Double.parseDouble(suffix.pop());
                double sour = Double.parseDouble(suffix.pop());
                double result = switch (str) {
                    case "+" -> sour + dest;
                    case "-" -> sour - dest;
                    case "*" -> sour * dest;
                    case "/" -> sour / dest;
                    default -> 0;
                };
                suffix.push(String.valueOf(result));
            }
            // 如果是数字，入栈
            else {
                suffix.push(str);
            }

        }

        System.out.println("结果：" + suffix.peek());

        double value = Double.parseDouble(suffix.peek());
        System.out.println("转换int后：" + value);
        if((value % 1 - eps) < 0) {
            return String.valueOf((int) value);
        }
        return suffix.peek();

    }


    private void handleOp(String op) {

        //如果栈为空或者栈顶仍为左括号，直接入栈
        if(opStack.isEmpty() || opStack.peek().equals("(")) {
            opStack.push(op);
            return;
        }

        //如果栈不空,并且运算符为"("
        if(op.equals("(")) {
            opStack.push(op);
        }

        //如果栈不空，并且运算符为")"
        else if(op.equals(")")) {
            String string = "";
            //将()之间的所有操作符出栈到后缀表达式，并将"("舍弃
            while(!"(".equals(string = opStack.pop())) {
                suffixString.add(string);
            }
        }

        //如果栈不空，并且运算符比栈顶优先级高,直接入栈
        else if(opMap.get(op) > opMap.get(opStack.peek())) {
            opStack.push(op);
        }

        //如果栈不空，并且运算符比栈顶优先级高
        else {
            suffixString.add(opStack.pop());
            handleOp(op); //递归调用
        }

    }

    private void handleNum(String num) {
        suffixString.add(num);
    }


    private boolean isOperator(String str) {
        return str.matches("[\\+\\-\\*\\/\\(\\)]");
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String line = input.nextLine();
        RPN rpn = new RPN();
        rpn.getResult(line);
    }
}

