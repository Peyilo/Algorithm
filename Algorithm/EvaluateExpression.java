package Algorithm;

import java.util.Stack;

public class EvaluateExpression {

    //计算一个字符串表达式
    public static double evaluateExpression(String expression){

        //用来存放操作数和操作符
        Stack<Double> operandStack = new Stack<>();
        Stack<Character> operatorStack = new Stack<>();

        //插入空格
        expression = insertBlanks(expression);

        String[] tokens = expression.split(" ");

        for (String token: tokens){
            if (token.length() == 0)
                continue;
            else if (token.charAt(0) == '+' || token.charAt(0) == '-'){
                while(!operatorStack.isEmpty() && (
                        operatorStack.peek() == '+' ||
                                operandStack.peek() == '-' ||
                                operandStack.peek() == '×' || operandStack.peek() == '÷'
                )){
                    processAnOperator(operandStack,operatorStack);
                }

                operatorStack.push(token.charAt(0));
            }
            else if (token.charAt(0) == '×' || token.charAt(0) == '÷'){
                while(!operatorStack.isEmpty() &&
                        (operatorStack.peek() == '×' ||
                                operatorStack.peek() == '÷')){
                    processAnOperator(operandStack,operatorStack);
                }
                operatorStack.push(token.charAt(0));
            }
            else if (token.trim().charAt(0) == '('){
                operatorStack.push('(');
            }
            else if (token.trim().charAt(0) == ')'){
                while (operatorStack.peek() != ')'){
                    processAnOperator(operandStack,operatorStack);
                }
                operatorStack.pop();
            }
            else{
                operandStack.push(new Double(token));
            }
        }
        while(!operatorStack.isEmpty()){
            processAnOperator(operandStack,operatorStack);
        }

        return operandStack.pop();
    }

    //从操作数栈和操作符栈中取出相应的数据进行一次运算
    public static void processAnOperator(Stack<Double> operandStack, Stack<Character> operatorStack){

        char op = operatorStack.pop();
        double op1 = operandStack.pop();
        double op2 = operandStack.pop();

        if (op == '+')
            operandStack.push(op1 + op2);
        else if (op == '-')
            operandStack.push(op2 - op1);
        else if (op == '×')
            operandStack.push(op2 * op1);
        else if (op == '÷')
            operandStack.push(op2 / op1);

    }

    //给字符串插入空格，以便拆分字符串
    public static String insertBlanks(String s){

        String result ="";

        for (int i = 0; i< s.length(); i++){
            if (s.charAt(i) == '(' || s.charAt(i) == ')'
                    || s.charAt(i) == '+' || s.charAt(i) == '-'
                    || s.charAt(i) == '×' || s.charAt(i) == '÷')
                result += " " + s.charAt(i) +" ";
            else
                result += s.charAt(i);
        }

        return result;
    }
}
