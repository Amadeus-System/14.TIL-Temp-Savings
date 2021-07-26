// 12.4 연습문제: 덧셈, 뺄셈하기
// 다음 소스코드를 완성하여 100이 출력되게 만드시오.
#include <stdio.h>

int main()
{
    int num1;
    int num2 = 5;

    num1 = 10 - num2;  // 5

    num1 += 95;

    printf("%d\n", num1);

    return 0;
}
// printf로 출력할 때 num1의 값이 100이 되어있어야 한다.
// 먼저 num2에는 5가 들어있으므로 num1 = 10 - num2;를 처리하면 num1은 5가 된다.
// += 연산자는 변수의 값을 증가시키므로 100이 되려면 95만큼 증가시키면 된다.
