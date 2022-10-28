package com.anvei.algorithm;

import java.util.*;

public class RPN {

    // 中缀表达式转逆波兰式过程中，用于存储操作符的栈
    private final Stack<String> opStack = new Stack<>();

    // 存储表达式分割后获取的中缀表达式tokens
    private final List<String> infixExpression = new ArrayList<>();

    // 存储逆波兰式tokens
    private final List<String> suffixExpression = new ArrayList<>();

    // 存储操作符及其优先级
    private final Map<String ,Integer> operand = new HashMap<>();

    // 将要计算的字符串表达式
    private String expression;

    public RPN() {
        operand.put("+", 1);        // 初始化操作符 Map
        operand.put("-", 1);        // 设置优先级，数值越大优先级越高
        operand.put("*", 2);
        operand.put("/", 2);
        operand.put("^", 2);
    }

    public RPN(String expression) {
        this();
        this.expression = expression;
    }

    public void setExpression(String expression) {
        this.expression = expression;
        opStack.clear();
        infixExpression.clear();
        suffixExpression.clear();
    }

    public String getResult() {
        splitInfix();
        infixToSuffix();
        return calcSuffixExpression();
    }

    /**
     * 将完整的表达式进行切割，获取中缀表达式tokens
     */
    private void splitInfix() {
        infixExpression.clear();
        StringTokenizer tokenizer = new StringTokenizer(expression, "+-*/^()", true);
        while (tokenizer.hasMoreTokens()) {
            String temp = tokenizer.nextToken().strip();
            if (!temp.equals("")) {
                infixExpression.add(temp);
            }
        }
    }

    /**
     * 中缀表达式转后缀表达式
     */
    private void infixToSuffix() {
        suffixExpression.clear();
        for (String token : infixExpression) {
            if (isOperator(token)) {
                handleOperator(token);
            } else if (isBracket(token)) {
                handleBracket(token);
            } else {
                handleNumber(token);
            }
        }
        // 依次弹出opStack剩余操作符，将其加入suffixExpression中
        while (!opStack.empty()) {
            suffixExpression.add(opStack.pop());
        }
    }

    private boolean isOperator(String token) {
        return operand.containsKey(token);
    }

    private boolean isBracket(String token) {
        return token.equals("(") || token.equals(")");
    }

    private void handleOperator(String op) {
        if (opStack.empty() || opStack.peek().equals("(")) {
            opStack.push(op);
        } else if (operand.get(op) > operand.get(opStack.peek())) {
            opStack.push(op);
        } else {
            suffixExpression.add(opStack.pop());
            handleOperator(op);
        }
    }

    private void handleBracket(String bracket) {
        if (bracket.equals("(")) {
            opStack.push("(");
        } else {
            while (!opStack.peek().equals("(")) {
                suffixExpression.add(opStack.pop());
            }
            opStack.pop();      // 丢弃括号
        }
    }

    private void handleNumber(String number) {
        suffixExpression.add(number);
    }

    /**
     * 计算逆波兰式
     * @return 计算结果的字符串形式
     */
    private String calcSuffixExpression() {
        Stack<String> stack = new Stack<>();
        for (String token : suffixExpression) {
            if (isOperator(token)) {
                double operand1 = Double.parseDouble(stack.pop());
                double operand2 = Double.parseDouble(stack.pop());
                double resultValue = switch (token) {
                    case "+" -> operand2 + operand1;
                    case "-" -> operand2 - operand1;
                    case "*" -> operand2 * operand1;
                    case "/" -> operand2 / operand1;
                    case "^" -> Math.pow(operand2, operand1);
                    default -> 0;
                };
                stack.push(Double.toString(resultValue));
            } else {
                stack.push(token);
            }
        }
        return stack.pop();
    }

}
