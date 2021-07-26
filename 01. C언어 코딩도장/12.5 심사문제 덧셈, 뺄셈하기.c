// 12.5 심사문제: 덧셈, 뺄셈하기
// 표준입력으로 실수 2개가 입력된다.
// 다음 소스코드를 완성하여 입력된 두 실수를 더한 값에서 4.5를 감소시킨 값이 출력되게 만드시오.
// 정답에는 밑줄 친 부분에 들어갈 코드만 작성해야 한다.
#include <stdio.h>

int main()
{
    float num1;
    float num2;
    float num3;

    printf("input two float number: ");
    scanf("%f %f", &num1, &num2);

    num3 = num1 + num2;
    num3 -= 4.5f;

    printf("%f\n", num3);

    return 0;
}
